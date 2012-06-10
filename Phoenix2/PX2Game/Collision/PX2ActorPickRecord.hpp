/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2ActorPickRecord.hpp
*
* �汾		:	1.0 (2011/06/05)
*
* ����		��	more
*
*/

#ifndef PX2ACTORPICKRECORD_HPP
#define PX2ACTORPICKRECORD_HPP

#include "PX2GamePrerequisites.hpp"
#include "PX2Actor.hpp"

namespace PX2
{

	class ActorPickRecord
	{
	public:
		ActorPickRecord ()
		{
			T = 0.0f;
		}

		~ActorPickRecord ()
		{
		}

		ActorPtr Intersected;

		// ����P + t*D�е�����Ԫ������T������t�ı�ʾ��
		float T;
	};

}

#endif