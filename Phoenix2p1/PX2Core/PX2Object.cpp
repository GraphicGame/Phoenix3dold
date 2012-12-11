/*
*
* �ļ�����	��	PX2Object.cpp
*
*/

#include "PX2Object.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
Object::Object ()
{
}
//----------------------------------------------------------------------------
Object::~Object ()
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// ����ʶ����Ϣ
//----------------------------------------------------------------------------
const Rtti Object::TYPE("PX2.Object", 0);
//----------------------------------------------------------------------------
const Rtti& Object::GetRttiType () const
{
	return TYPE;
}
//----------------------------------------------------------------------------
bool Object::IsExactly (const Rtti& type) const
{
	return GetRttiType().IsExactly(type);
}
//----------------------------------------------------------------------------
bool Object::IsDerived (const Rtti& type) const
{
	return GetRttiType().IsDerived(type);
}
//----------------------------------------------------------------------------
bool Object::IsExactlyTypeOf (const Object* object) const
{
	return object && GetRttiType().IsExactly(object->GetRttiType());
}
//----------------------------------------------------------------------------
bool Object::IsDerivedTypeOf (const Object* object) const
{
	return object && GetRttiType().IsDerived(object->GetRttiType());
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// ��Դ·��
//----------------------------------------------------------------------------
void Object::SetResourcePath (const std::string& name)
{
	mResourcePath = name; 
}
//----------------------------------------------------------------------------
const std::string& Object::GetResourcePath () const
{
	return mResourcePath;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// ����
//----------------------------------------------------------------------------
void Object::SetName (const std::string& name)
{
	mName = name;
}
//----------------------------------------------------------------------------
const std::string& Object::GetName () const
{
	return mName;
}
//----------------------------------------------------------------------------
Object* Object::GetObjectByName (const std::string& name)
{
	return (name == mName ? this : 0);
}
//----------------------------------------------------------------------------
void Object::GetAllObjectsByName (const std::string& name,
								  std::vector<Object*>& objects)
{
	if (name == mName)
	{
		objects.push_back(this);
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// �־û�
//----------------------------------------------------------------------------
Object::FactoryMap* Object::msFactories = 0;
bool Object::msStreamRegistered = false;
//----------------------------------------------------------------------------
Object* Object::Factory (InStream&)
{
	assertion(false, "Abstract classes have no factory.\n");
	return 0;
}
//----------------------------------------------------------------------------
bool Object::RegisterFactory ()
{
	if (!msStreamRegistered)
	{
		InitTerm::AddInitializer(Object::InitializeFactory);
		InitTerm::AddTerminator(Object::TerminateFactory);
		msStreamRegistered = true;
	}
	return msStreamRegistered;
}
//----------------------------------------------------------------------------
void Object::InitializeFactory ()
{
	if (!msFactories)
	{
		msFactories = new0 Object::FactoryMap();
	}
	msFactories->insert(std::make_pair(TYPE.GetName(), Factory));
}
//----------------------------------------------------------------------------
void Object::TerminateFactory ()
{
	delete0(msFactories);
	msFactories = 0;
}
//----------------------------------------------------------------------------
Object::FactoryFunction Object::Find (const std::string& name)
{
	assertion(msFactories != 0, "FactoryMap was not yet allocated.\n");
	FactoryMap::iterator iter = msFactories->find(name);
	if (iter != msFactories->end())
	{
		return iter->second;
	}
	return 0;
}
//----------------------------------------------------------------------------
Object::Object (LoadConstructor)
{
}
//----------------------------------------------------------------------------
void Object::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	// RTTI�����Ѿ�����ȡ��

	// ��ȡID���ṩ�����������Ϣ
	source.ReadUniqueID(this);

	// ��Դ·��
	source.ReadString(mResourcePath);

	// ��ȡ���������
	source.ReadString(mName);

	PX2_END_DEBUG_STREAM_LOAD(Object, source);
}
//----------------------------------------------------------------------------
void Object::Link (InStream&)
{
	// Objectû����ҪLink�ĳ�Ա
}
//----------------------------------------------------------------------------
void Object::PostLink ()
{
	// Objectû����ҪPostLink�ĳ�Ա
}
//----------------------------------------------------------------------------
bool Object::Register (OutStream& target) const
{
	return target.RegisterRoot(this);
}
//----------------------------------------------------------------------------
void Object::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	// д��RTTI����
	target.WriteString(GetRttiType().GetName());

	// д��ID
	target.WriteUniqueID(this);

	// ��Դ·��
	target.WriteString(mResourcePath);

	// д���������
	target.WriteString(mName);

	PX2_END_DEBUG_STREAM_SAVE(Object, target);
}
//----------------------------------------------------------------------------
int Object::GetStreamingSize () const
{
	// RTTI����.
	int size = PX2_STRINGSIZE(GetRttiType().GetName());

	// ����ID
	size += sizeof(unsigned int);

	// ��Դ·��
	size += PX2_STRINGSIZE(mResourcePath);

	// ���������
	size += PX2_STRINGSIZE(mName);

	return size;
}
//----------------------------------------------------------------------------
Object* Object::Copy (const std::string& uniqueNameAppend) const
{
	// Save the object to a memory buffer.
	OutStream saveStream;
	saveStream.Insert((Object*)this);
	int bufferSize = 0;
	char* buffer = 0;
	saveStream.Save(bufferSize, buffer, BufferIO::BM_DEFAULT_WRITE);

	// Load the object from the memory buffer.
	InStream loadStream;
	loadStream.Load(bufferSize, buffer, BufferIO::BM_DEFAULT_READ);
	delete1(buffer);

	if (uniqueNameAppend != "")
	{
		int numObjects = loadStream.GetNumObjects();
		for (int i=0; i<numObjects; i++)
		{
			PX2::Object *obj = loadStream.GetObjectAt(i);
			std::string name = obj->GetName();
			if (name.length() > 0)
			{
				name += uniqueNameAppend;
				obj->SetName(name);
			}
		}
	}

	return loadStream.GetObjectAt(0);
}
//----------------------------------------------------------------------------
