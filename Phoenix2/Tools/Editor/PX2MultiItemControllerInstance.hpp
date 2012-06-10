/*
* Phoenix2 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2MultiItemControllerInstance.hpp
*
* �汾		:	1.0 (2011/03/29)
*
* ����		��	more
*
*/

#ifndef PX2MULTIITEMCONTROLLERINSTANCE_HPP
#define PX2MULTIITEMCONTROLLERINSTANCE_HPP

#include "PX2EditorPrerequisites.hpp"
#include "PX2ControllerInstance.hpp"

namespace PX2Editor
{

	class MultiItemControllerInstance : public ControllerInstance
	{
	public:
		MultiItemControllerInstance ();
		~MultiItemControllerInstance ();

		virtual void Activate();
		virtual void DeActivate();

		virtual void NotifySelection (const Selection &selection);
	};


}

#endif