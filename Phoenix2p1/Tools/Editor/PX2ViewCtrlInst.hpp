/*
*
* �ļ�����	��	PX2ViewCtrlInst.hpp
*
*/

#ifndef PX2VIEWCTRLINST_HPP
#define PX2VIEWCTRLINST_HPP

#include "PX2EditorPre.hpp"

namespace PX2Editor
{

	/// ����ģʽ
	enum InteractionMode
	{
		IM_GENERAL,
		IM_TEREDIT,
		IM_MAX_MODE
	};

	/// ѡ��ģʽ
	enum SelectionMode
	{
		SM_REPLACE = 0,
		SM_ADD = 1,
		SM_SUBTRACT = 2
	};

	class RenderViewWindow;
	class ViewCtrl;
	class Selection;

	class ViewCtrlInst
	{
	public:
		ViewCtrlInst();
		virtual ~ViewCtrlInst();

		virtual void Activate() = 0;
		virtual void DeActivate() = 0;

		virtual void DoSelection (PX2::Renderer *renderer, const PX2::Vector2f &point,
			SelectionMode mode);
		virtual void DoSelection (PX2::Renderer *renderer, const PX2::Vector2f &topLeft, 
			const PX2::Vector2f &bottonRight, SelectionMode mode);

		PX2::APoint CalculateSelectPoint (PX2::Renderer *renderer, const PX2::Vector2f &point);
		PX2::APoint GetSelectPoint ();

		virtual void SetInteractionMode (InteractionMode im);
		virtual InteractionMode GetInteractionMode () const;

		virtual void HandleLeftDown (RenderViewWindow *win, wxMouseEvent &e);
		virtual void HandleLeftUp (RenderViewWindow *win,	wxMouseEvent &e);
		virtual void HandleMiddleDown (RenderViewWindow *win,	wxMouseEvent &e);
		virtual void HandleMiddleUp (RenderViewWindow *win, wxMouseEvent &e);
		virtual void HandleMouseWheel (RenderViewWindow *win, wxMouseEvent &e);
		virtual void HandleRightDown (RenderViewWindow *win, wxMouseEvent &e);
		virtual void HandleRightUp (RenderViewWindow *win, wxMouseEvent &e);
		virtual void HandleMotion (RenderViewWindow *win, wxMouseEvent &e);

	protected:
		virtual void SwitchPaneController (ViewCtrl *ctrl);

		virtual void EnterGeneralMode ();
		virtual void ExitGeneralMode ();
		virtual void EnterTerEditMode ();
		virtual void ExitTerEditMode ();

		PX2::Ray3f mRay;
		InteractionMode mInteractionMode;
		ViewCtrl *mViewCtrl;
		PX2::APoint mSelectPoint;
	};

#include "PX2ViewCtrlInst.inl"

}

#endif