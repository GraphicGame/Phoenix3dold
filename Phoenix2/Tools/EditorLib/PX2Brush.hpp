/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2EditBrush.hpp
*
* �汾		:	1.0 (2011/06/06)
*
* ����		��	more
*
*/

#ifndef PX2BRUSH_HPP
#define PX2BRUSH_HPP

#include "PX2EditorLibPrerequisites.hpp"

namespace PX2Editor
{

	class Brush
	{
	public:
		Brush ();
		virtual ~Brush ();

		virtual void SetPos (PX2::APoint pos);
		PX2::APoint GetPos () { return mPos; }

		virtual void SetSize (float size);
		float GetSize () { return mSize; }

		void SetStrength (float strength) { mStrength = strength; }
		float GetStrength () { return mStrength; }

	protected:
		PX2::APoint mPos;
		float mSize;
		float mStrength;
	};

}

#endif
