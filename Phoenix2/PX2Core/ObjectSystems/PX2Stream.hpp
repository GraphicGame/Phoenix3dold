/*
* Phoenix 3D ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Stream.hpp
*
* �汾		:	1.0 (2011/01/30)
*
* ����		��	more
*
*/

#ifndef PX2STREAM_HPP
#define PX2STREAM_HPP

#include "PX2CorePrerequisites.hpp"
#include "PX2BufferIO.hpp"
#include "PX2InitTerm.hpp"
#include "PX2SmartPointer.hpp"

namespace PX2
{

	class PX2_CORE_ENTRY Stream
	{
	public:
		/// �ַ����Ĵ洢�����ֽ�����
		/**
		* �ַ����ĳ����ȱ���Ϊһ������ֵ���ȴ洢�������ŵ����ַ���д����ַ���
		* ���浽4�ֽڵı�����С��
		*/
		static int GetStreamingSize (const std::string& input);

	protected:
		// �������
		Stream ();
		virtual ~Stream ();
	};

}

//----------------------------------------------------------------------------
#define PX2_DECLARE_STREAM(classname) \
public: \
    static bool RegisterFactory (); \
    static void InitializeFactory (); \
    static Object* Factory (InStream&); \
    virtual void Load (InStream&); \
    virtual void Link (InStream&); \
    virtual void PostLink (); \
    virtual bool Register (OutStream&) const; \
    virtual void Save (OutStream&) const; \
    virtual int GetStreamingSize () const; \
protected: \
    friend class Memory; \
    classname (LoadConstructor value); \
private: \
    static bool msStreamRegistered
//----------------------------------------------------------------------------
#define PX2_IMPLEMENT_STREAM(classname) \
bool classname::msStreamRegistered = false; \
\
bool classname::RegisterFactory () \
{ \
    if (!msStreamRegistered) \
    { \
        InitTerm::AddInitializer(classname::InitializeFactory); \
        msStreamRegistered = true; \
    } \
    return msStreamRegistered; \
} \
\
void classname::InitializeFactory () \
{ \
    if (!msFactories) \
    { \
        msFactories = new0 Object::FactoryMap(); \
    } \
    msFactories->insert(std::make_pair(TYPE.GetName(), Factory)); \
}
//----------------------------------------------------------------------------
#define PX2_IMPLEMENT_DEFAULT_STREAM(baseclassname, classname) \
classname::classname (LoadConstructor value) \
    : \
    baseclassname(value) \
{ \
} \
\
void classname::Load (InStream& source) \
{ \
    PX2_BEGIN_DEBUG_STREAM_LOAD(source); \
    baseclassname::Load(source); \
    PX2_END_DEBUG_STREAM_LOAD(baseclassname, source); \
} \
\
void classname::Link (InStream& source) \
{ \
    baseclassname::Link(source); \
} \
void classname::PostLink () \
{ \
    baseclassname::PostLink(); \
} \
\
bool classname::Register (OutStream& target) const \
{ \
    return baseclassname::Register(target); \
} \
\
void classname::Save (OutStream& target) const \
{ \
    PX2_BEGIN_DEBUG_STREAM_SAVE(target); \
    baseclassname::Save(target); \
    PX2_END_DEBUG_STREAM_SAVE(baseclassname, target); \
} \
\
int classname::GetStreamingSize () const \
{ \
    return baseclassname::GetStreamingSize(); \
}
//----------------------------------------------------------------------------
#define PX2_IMPLEMENT_ABSTRACT_FACTORY(classname) \
Object* classname::Factory (InStream&) \
{ \
    assertion(false, "Abstract classes have no factory.\n"); \
    return 0; \
}
//----------------------------------------------------------------------------
#define PX2_IMPLEMENT_FACTORY(classname) \
Object* classname::Factory (InStream& source) \
{ \
    classname* object = new0 classname(LC_LOADER); \
    object->Load(source); \
    return object; \
}
//----------------------------------------------------------------------------
#define PX2_REGISTER_STREAM(classname) \
static bool gsStreamRegistered_##classname = classname::RegisterFactory()
//----------------------------------------------------------------------------
#ifdef PX2_USE_ASSERT
#define PX2_BEGIN_DEBUG_STREAM_LOAD(source) \
    int beginLoad_ = source.GetBytesRead()
#else
#define PX2_BEGIN_DEBUG_STREAM_LOAD(source)
#endif
//----------------------------------------------------------------------------
#ifdef PX2_USE_ASSERT
#define PX2_END_DEBUG_STREAM_LOAD(classname,source) \
    int endLoad_ = source.GetBytesRead(); \
    int usedLoad_ = endLoad_ - beginLoad_ + \
        Stream::GetStreamingSize(GetRttiType().GetName()); \
    int usedReported_ = classname::GetStreamingSize(); \
    assertion(usedLoad_ == usedReported_, \
        "Mismatched bytes during Load: loaded = %d, required = %d\n", \
        usedLoad_, usedReported_)
#else
#define PX2_END_DEBUG_STREAM_LOAD(classname,source)
#endif
//----------------------------------------------------------------------------
#ifdef PX2_USE_ASSERT
#define PX2_BEGIN_DEBUG_STREAM_SAVE(target) \
    int beginSave_ = target.GetBytesWritten()
#else
#define PX2_BEGIN_DEBUG_STREAM_SAVE(target)
#endif
//----------------------------------------------------------------------------
#ifdef PX2_USE_ASSERT
#define PX2_END_DEBUG_STREAM_SAVE(classname,target) \
    int endSave_ = target.GetBytesWritten(); \
    int usedSave_ = endSave_ - beginSave_; \
    int usedReported_ = classname::GetStreamingSize(); \
    assertion(usedSave_ == usedReported_, \
        "Mismatched bytes during Save: saved = %d, required = %d\n", \
        usedSave_, usedReported_)
#else
#define PX2_END_DEBUG_STREAM_SAVE(classname,target)
#endif
//----------------------------------------------------------------------------
// PX2_POINTERSIZE���ڳ־û�ϵͳ��ʹ�õģ����ָ���С�ĺꡣָ�뱻����һ��4byte
// ��unsigned intд�뵽Ӳ���С�
#define PX2_POINTERSIZE(value) 4
//----------------------------------------------------------------------------
// PX2_BOOLSIZE���ڳ־û�ϵͳ��ʹ�õģ����bool���ʹ�С�ĺꡣһ��boolֵ������4
// byte��Сд�뵽Ӳ�̡�
#define PX2_BOOLSIZE(value) 4
//----------------------------------------------------------------------------
// PX2_ENUMSIZE���ڳ־û�ϵͳ��ʹ�ã�һ��ö�����ͱ�����4byte��Сд�뵽Ӳ�̡�
#define PX2_ENUMSIZE(value) 4
//----------------------------------------------------------------------------
#define PX2_STRINGSIZE(value) Stream::GetStreamingSize(value)
//----------------------------------------------------------------------------

#endif