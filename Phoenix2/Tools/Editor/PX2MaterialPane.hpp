/*
* Phoenix2 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2MaterialPane.hpp
*
* �汾		:	1.0 (2011/03/29)
*
* ����		��	more
*
*/

#ifndef PX2MATERIALPANE_HPP
#define PX2MATERIALPANE_HPP

#include "PX2EditorPrerequisites.hpp"

namespace PX2Editor
{

	class MaterialPropertyGrid;

	class MaterialPanel : public wxPanel
	{
	public:
		MaterialPanel (wxWindow *parent);
		~MaterialPanel ();

		void OnMaterialChoose (wxCommandEvent &event);
		void OnButton (wxCommandEvent& event);

		void SetRenderable (PX2::Renderable *ren);

	protected:
		DECLARE_EVENT_TABLE();

		MaterialPanel ();

		wxChoice* mMaterialChoose;
		MaterialPropertyGrid *mMaterialGrid;
		wxButton* mApply;
		PX2::RenderablePtr mRenderable;
		PX2::MaterialPtr mNewMaterial;
		PX2::MaterialInstancePtr mNewMaterialInstance;
	};

}

#endif