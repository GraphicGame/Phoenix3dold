/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Math.hpp
*
* �汾		:	1.0 (2011/01/30)
*
* ����		��	more
*
*/

#ifndef PX2MATH_HPP
#define PX2MATH_HPP

#include "PX2MathematicsPrerequisites.hpp"
#include "PX2Assert.hpp"
#include <cfloat>
#include <cmath>
#include <cstdlib>

namespace PX2
{

	template <typename Real>
	class Math
	{
	public:
		static Real ACos (Real value);
		static Real ASin (Real value);
		static Real ATan (Real value);
		static Real ATan2 (Real y, Real x);
		static Real Ceil (Real value);
		static Real Cos (Real value);
		static Real Exp (Real value);
		static Real FAbs (Real value);
		static Real Floor (Real value);
		static Real FMod (Real x, Real y);
		static Real InvSqrt (Real value);
		static Real Log (Real value);
		static Real Log2 (Real value);
		static Real Log10 (Real value);
		static Real Pow (Real base, Real exponent);
		static Real Sin (Real value);
		static Real Sqr (Real value);
		static Real Sqrt (Real value);
		static Real Tan (Real value);

		//  ��������Ǹ�ֵ������-1���������0������0����������Ϊ��ֵ������+1��
		static Real Sign (Real value);

		/// ����һ��������[0,1]�������������������Ӳ�ҪС��0��
		static Real UnitRandom (unsigned int seed = 0);

		/// ����һ��������[-1,1]�������������������Ӳ�ҪС��0��
		static Real SymmetricRandom (unsigned int seed = 0);

		/// ����һ��������[fMin,fMax]�������������������Ӳ�ҪС��0��
		static Real IntervalRandom (Real min, Real max, unsigned int seed = 0);

		// �������ֵ��ȡ��[min,max].
		static Real Clamp (Real value, Real minValue, Real maxValue);

		// �������ȡ������[0,1].
		static Real Saturate (Real value);

		// ����
		PX2_MATHEMATICS_ENTRY static const Real EPSILON;
		PX2_MATHEMATICS_ENTRY static const Real ZERO_TOLERANCE;
		PX2_MATHEMATICS_ENTRY static const Real MAX_REAL;
		PX2_MATHEMATICS_ENTRY static const Real PI;
		PX2_MATHEMATICS_ENTRY static const Real TWO_PI;
		PX2_MATHEMATICS_ENTRY static const Real HALF_PI;
		PX2_MATHEMATICS_ENTRY static const Real INV_PI;
		PX2_MATHEMATICS_ENTRY static const Real INV_TWO_PI;
		PX2_MATHEMATICS_ENTRY static const Real DEG_TO_RAD;
		PX2_MATHEMATICS_ENTRY static const Real RAD_TO_DEG;
		PX2_MATHEMATICS_ENTRY static const Real LN_2;
		PX2_MATHEMATICS_ENTRY static const Real LN_10;
		PX2_MATHEMATICS_ENTRY static const Real INV_LN_2;
		PX2_MATHEMATICS_ENTRY static const Real INV_LN_10;
		PX2_MATHEMATICS_ENTRY static const Real SQRT_2;
		PX2_MATHEMATICS_ENTRY static const Real INV_SQRT_2;
		PX2_MATHEMATICS_ENTRY static const Real SQRT_3;
		PX2_MATHEMATICS_ENTRY static const Real INV_SQRT_3;
	};

#include "PX2Math.inl"

	typedef Math<float> Mathf;
	typedef Math<double> Mathd;

}

#endif