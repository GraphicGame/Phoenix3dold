/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Float3.hpp
*
* �汾		:	1.0 (2011/01/30)
*
* ����		��	more
*
*/

#ifndef PX2FLOAT3_HPP
#define PX2FLOAT3_HPP

#include "PX2MathematicsPrerequisites.hpp"
#include "PX2Tuple.hpp"

namespace PX2
{

	class PX2_MATHEMATICS_ENTRY Float3 : public Tuple<3,float>
	{
	public:
		Float3 ();   //< δ��ʼ��
		~Float3 ();  // hides ~Tuple<3,float>
		Float3 (float f0, float f1, float f2);
		Float3 (const Float3& tuple);

		// ��ֵ
		Float3& operator= (const Float3& tuple);
	};

}

#endif