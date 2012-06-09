/*
* Phoenix 3D ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2DateTime.hpp
*
* �汾		:	1.0 (2011/01/30)
*
* ����		��	more
*
*/

#ifndef PX2DAYTIME_HPP
#define PX2DAYTIME_HPP

#include "PX2CorePrerequisites.hpp"

namespace PX2
{

	struct DayTime 
	{
		DayTime ();
		DayTime (unsigned int year, unsigned int month, unsigned int day, 
			unsigned int hour, unsigned int minute, unsigned int second,
			unsigned int minsecond);

		unsigned int Year;
		unsigned int Month;
		unsigned int Day;
		unsigned int Hour;
		unsigned int Minute;
		unsigned int Second;
		unsigned int Minsecond;	
	};

	DayTime GetDateTime (bool isUtc = false);

}

#endif