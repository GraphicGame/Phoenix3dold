/*
* Phoenix2 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2TerrainEditController.hpp
*
* �汾		:	1.0 (2011/03/29)
*
* ����		��	more
*
*/

#ifndef PX2TERRAINEDITCONTROLLER_HPP
#define PX2TERRAINEDITCONTROLLER_HPP

#include "PX2EditorPrerequisites.hpp"
#include "PX2PaneController.hpp"

namespace PX2Editor
{

	class TerrainEditController : public PaneController
	{
	public:
		TerrainEditController (ControllerInstance *callback);
		virtual ~TerrainEditController ();

		virtual void HandleLeftDown (RenderViewWindow *win, wxMouseEvent &e);
		virtual void HandleLeftUp (RenderViewWindow *win, wxMouseEvent &e);
		virtual void HandleMiddleDown(RenderViewWindow *win, wxMouseEvent &e);
		virtual void HandleMiddleUp(RenderViewWindow *win, wxMouseEvent &e);
		virtual void HandleMouseWheel(RenderViewWindow *win, wxMouseEvent &e);
		virtual void HandleRightDown(RenderViewWindow *win, wxMouseEvent &e);
		virtual void HandleRightUp(RenderViewWindow *win, wxMouseEvent &e);
		virtual void HandleMotion (RenderViewWindow *win, wxMouseEvent &e);

	protected:
		void UpdateBrushPos (RenderViewWindow *win, wxMouseEvent &e);

		bool mLeftDown;
		bool mRightDown;
		bool mMiddleDown;
	};

}

#endif