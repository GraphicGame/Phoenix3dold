/*
*
* �ļ�����	��	PX2BtDynamicWorld.inl
*
*/

//----------------------------------------------------------------------------
inline btDynamicsWorld *DynamicWorld::GetBulletDynamicWorld () const
{
	return (btDynamicsWorld*)mWorld;
}
//----------------------------------------------------------------------------