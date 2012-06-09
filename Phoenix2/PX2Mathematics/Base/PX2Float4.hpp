/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Float4.hpp
*
* �汾		:	1.0 (2011/01/30)
*
* ����		��	more
*
*/

#ifndef PX2FLOAT4_HPP
#define PX2FLOAT4_HPP

#include "PX2MathematicsPrerequisites.hpp"
#include "PX2Tuple.hpp"

namespace PX2
{

	class PX2_MATHEMATICS_ENTRY Float4 : public Tuple<4,float>
	{
	public:
		Float4 ();   //< δ��ʼ��
		~Float4 ();  // hides ~Tuple<4,float>
		Float4 (float f0, float f1, float f2, float f3);
		Float4 (const Float4& tuple);

		// ��ֵ
		Float4& operator= (const Float4& tuple);
	};

}

#endif
