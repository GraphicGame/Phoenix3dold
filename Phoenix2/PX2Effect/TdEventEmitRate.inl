/*
*
* �ļ�����	��	TdEventEmitRate.inl
*
*/

//----------------------------------------------------------------------------
inline TRange<int> ParticleEvent_EmitRate::GetRateRange () const
{
	return mEmitRateRange;
}
//----------------------------------------------------------------------------
inline bool ParticleEvent_EmitRate::FadeAllowed ()
{
	return true;
}
//----------------------------------------------------------------------------