/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Application.hpp
*
* �汾		:	1.0 (2011/02/02)
*
* ����		��	more
*
*/

#ifndef PX2APPLICATION_HPP
#define PX2APPLICATION_HPP

#include "PX2Core.hpp"
#include "PX2Mathematics.hpp"
#include "PX2Graphics.hpp"
#include "PX2Renderers.hpp"
#include "PX2EventSystem.hpp"
#include "PX2Unity.hpp"
#include "PX2UserInterface.hpp"
#include "PX2Game.hpp"
#include "PX2Awesomium.hpp"

namespace PX2
{

	class Application
	{
	protected:
		Application ();
	public:
		virtual ~Application ();

		// ��ʼ/�ս�
		virtual bool Initlize ();
		virtual bool Ternamate ();

		// ����
		virtual void Run ();

	protected:
		GraphicsRoot *mRoot;
	};

}

#endif
