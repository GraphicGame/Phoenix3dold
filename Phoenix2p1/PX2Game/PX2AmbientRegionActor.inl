/*
*
* �ļ�����	��	PX2AmbientRegionActor.inl
*
*/

//----------------------------------------------------------------------------
inline void AmbientRegionActor::SetLight (Light *light)
{
	mLight = light;
}
//----------------------------------------------------------------------------
inline Light *AmbientRegionActor::GetLight ()
{
	return mLight;
}
//----------------------------------------------------------------------------