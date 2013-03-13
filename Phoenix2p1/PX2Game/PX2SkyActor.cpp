/*
*
* �ļ�����	��	PX2SkyActor.cpp
*
*/

#include "PX2SkyActor.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Actor, SkyActor);
PX2_IMPLEMENT_STREAM(SkyActor);
PX2_IMPLEMENT_FACTORY(SkyActor);

//----------------------------------------------------------------------------
SkyActor::SkyActor (SkySphere *sky)
	:
mSky(sky)
{
	if (sky)
	{
		SetMovable(sky);
	}
}
//----------------------------------------------------------------------------
SkyActor::~SkyActor ()
{
}
//----------------------------------------------------------------------------
void SkyActor::SetSky (SkySphere *sky)
{
	mSky = sky;
	SetMovable(mSky);
}
//----------------------------------------------------------------------------
void SkyActor::DoEnter ()
{
}
//----------------------------------------------------------------------------
void SkyActor::DoExecute (Event *event)
{
}
//----------------------------------------------------------------------------
void SkyActor::DoLeave ()
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// ����֧��
//----------------------------------------------------------------------------
Object* SkyActor::GetObjectByName (const std::string& name)
{
	Object* found = Actor::GetObjectByName(name);
	if (found)
	{
		return found;
	}

	return 0;
}
//----------------------------------------------------------------------------
void SkyActor::GetAllObjectsByName (const std::string& name,
	std::vector<Object*>& objects)
{
	Actor::GetAllObjectsByName(name, objects);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// �־û�֧��
//----------------------------------------------------------------------------
SkyActor::SkyActor (LoadConstructor value)
	:
Actor(value)
{
}
//----------------------------------------------------------------------------
void SkyActor::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Actor::Load(source);
	source.ReadPointer(mSky);

	PX2_END_DEBUG_STREAM_LOAD(SkyActor, source);
}
//----------------------------------------------------------------------------
void SkyActor::Link (InStream& source)
{
	Actor::Link(source);
	source.ResolveLink(mSky);
}
//----------------------------------------------------------------------------
void SkyActor::PostLink ()
{
	Actor::PostLink();
}
//----------------------------------------------------------------------------
bool SkyActor::Register (OutStream& target) const
{
	if (Actor::Register(target))
	{
		target.Register(mSky);

		return true;
	}	

	return false;
}
//----------------------------------------------------------------------------
void SkyActor::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Actor::Save(target);
	target.WritePointer(mSky);

	PX2_END_DEBUG_STREAM_SAVE(SkyActor, target);
}
//----------------------------------------------------------------------------
int SkyActor::GetStreamingSize () const
{
	int size = Actor::GetStreamingSize();
	size += PX2_POINTERSIZE(mSky);

	return size;
}
//----------------------------------------------------------------------------