/*
*
* �ļ�����	��	PX2LightWorldPositionConstant.cpp
*
*/

#include "PX2LightWorldPositionConstant.hpp"
#include "PX2Camera.hpp"
#include "PX2Renderable.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, ShaderFloat, LightWorldPositionConstant);
PX2_IMPLEMENT_STREAM(LightWorldPositionConstant);
PX2_IMPLEMENT_FACTORY(LightWorldPositionConstant);

//----------------------------------------------------------------------------
LightWorldPositionConstant::LightWorldPositionConstant (Light* light)
:
ShaderFloat(1),
mLight(light)
{
	EnableUpdater();
}
//----------------------------------------------------------------------------
LightWorldPositionConstant::~LightWorldPositionConstant ()
{
}
//----------------------------------------------------------------------------
void LightWorldPositionConstant::SetLight (Light *light)
{
	mLight = light;
}
//----------------------------------------------------------------------------
Light* LightWorldPositionConstant::GetLight ()
{
	return mLight;
}
//----------------------------------------------------------------------------
void LightWorldPositionConstant::Update (const Renderable*, const Camera*)
{
	const APoint& worldPosition = mLight->Position;

	const float* source = (const float*)worldPosition;
	float* target = mData;
	for (int i = 0; i < 4; ++i)
	{
		*target++ = *source++;
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// ����֧��
//----------------------------------------------------------------------------
Object* LightWorldPositionConstant::GetObjectByName (const std::string& name)
{
	return ShaderFloat::GetObjectByName(name);
}
//----------------------------------------------------------------------------
void LightWorldPositionConstant::GetAllObjectsByName (const std::string& name,
													  std::vector<Object*>& objects)
{
	ShaderFloat::GetAllObjectsByName(name, objects);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// �־û�
//----------------------------------------------------------------------------
LightWorldPositionConstant::LightWorldPositionConstant (LoadConstructor value)
:
ShaderFloat(value)
{
}
//----------------------------------------------------------------------------
void LightWorldPositionConstant::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	ShaderFloat::Load(source);

	source.ReadPointer(mLight);

	PX2_END_DEBUG_STREAM_LOAD(LightWorldPositionConstant, source);
}
//----------------------------------------------------------------------------
void LightWorldPositionConstant::Link (InStream& source)
{
	ShaderFloat::Link(source);

	source.ResolveLink(mLight);
}
//----------------------------------------------------------------------------
void LightWorldPositionConstant::PostLink ()
{
	ShaderFloat::PostLink();
}
//----------------------------------------------------------------------------
bool LightWorldPositionConstant::Register (OutStream& target) const
{
	if (ShaderFloat::Register(target))
	{
		target.Register(mLight);
		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void LightWorldPositionConstant::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	ShaderFloat::Save(target);

	target.WritePointer(mLight);

	PX2_END_DEBUG_STREAM_SAVE(LightWorldPositionConstant, target);
}
//----------------------------------------------------------------------------
int LightWorldPositionConstant::GetStreamingSize () const
{
	int size = ShaderFloat::GetStreamingSize();
	size += PX2_POINTERSIZE(mLight);
	return size;
}
//----------------------------------------------------------------------------
