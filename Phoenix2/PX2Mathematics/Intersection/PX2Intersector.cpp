/*
*
* �ļ�����	��	PX2Intersector.cpp
*
*/

#include "PX2Intersector.hpp"

namespace PX2
{
//----------------------------------------------------------------------------
template <typename Real, typename TVector>
Intersector<Real,TVector>::Intersector ()
{
    mContactTime = (Real)0;
    mIntersectionType = IT_EMPTY;
}
//----------------------------------------------------------------------------
template <typename Real, typename TVector>
Intersector<Real,TVector>::~Intersector ()
{
}
//----------------------------------------------------------------------------
template <typename Real, typename TVector>
Real Intersector<Real,TVector>::GetContactTime () const
{
    return mContactTime;
}
//----------------------------------------------------------------------------
template <typename Real, typename TVector>
int Intersector<Real,TVector>::GetIntersectionType () const
{
    return mIntersectionType;
}
//----------------------------------------------------------------------------
template <typename Real, typename TVector>
bool Intersector<Real,TVector>::Test ()
{
    // ������ʵ��
    assertion(false, "Function not yet implemented\n");
    return false;
}
//----------------------------------------------------------------------------
template <typename Real, typename TVector>
bool Intersector<Real,TVector>::Find ()
{
    // ������ʵ��
    assertion(false, "Function not yet implemented\n");
    return false;
}
//----------------------------------------------------------------------------
template <typename Real, typename TVector>
bool Intersector<Real,TVector>::Test (Real, const TVector&, const TVector&)
{
    // ������ʵ��
    assertion(false, "Function not yet implemented\n");
    return false;
}
//----------------------------------------------------------------------------
template <typename Real, typename TVector>
bool Intersector<Real,TVector>::Find (Real, const TVector&, const TVector&)
{
    // ������ʵ��
    assertion(false, "Function not yet implemented\n");
    return false;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// ʵ��
//----------------------------------------------------------------------------
template PX2_MATHEMATICS_ENTRY
class Intersector<float,Vector2f>;

template PX2_MATHEMATICS_ENTRY
class Intersector<float,Vector3f>;

template PX2_MATHEMATICS_ENTRY
class Intersector<double,Vector2d>;

template PX2_MATHEMATICS_ENTRY
class Intersector<double,Vector3d>;
//----------------------------------------------------------------------------
}
