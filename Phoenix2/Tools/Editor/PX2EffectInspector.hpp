/*
* Phoenix2 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2EffectInspector.hpp
*
* �汾		:	1.0 (2012/01/19)
*
* ����		��	more
*
*/

#ifndef PX2EFFECTINSPECTOR_HPP
#define PX2EFFECTINSPECTOR_HPP

#include "PX2EditorPrerequisites.hpp"

namespace PX2Editor
{

	class EffectPanel;
	class EffectEventsPanel;

	class EffectInspector : public wxScrolledWindow, public PX2::EventHandler
	{
	public:
		EffectInspector (wxWindow *parent);
		~EffectInspector ();

		// PX2 Event
		virtual void DoEnter ();
		virtual void DoUpdate ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

		void OnSize(wxSizeEvent& e);

	protected:
		EffectInspector ();

		DECLARE_EVENT_TABLE()

		wxFoldPanelBar *mFoldPaneBar;
		EffectEventsPanel *mEffectEventsPanel;
		EffectPanel *mEffectPanel;
	};

}

#endif