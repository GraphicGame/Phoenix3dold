/*
* Phoenix2 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2DlgNewTerrain.hpp
*
* �汾		:	1.0 (2011/04/27)
*
* ����		��	more
*
*/

#ifndef PX2DLGNEWMAP_HPP
#define PX2DLGNEWMAP_HPP

#include "PX2EditorPrerequisites.hpp"

namespace PX2Editor
{

	class DlgNewTerrain : public wxDialog
	{
	public:
		DlgNewTerrain (wxWindow *parent);

		void OnButton (wxCommandEvent& event);

		std::string mValue_TerrainName;
		int mValue_TerrainWidth;
		int mValue_PageWidth;
		float mValue_GridSpace;

	protected:
		wxButton *mTerrainOK;
		wxButton *mTerrainCancel;
		wxTextCtrl *mTerrainName;
		wxComboBox *mTerrainWidth;
		wxComboBox *mPageWidth;
		wxTextCtrl *mGridSpace;

		DECLARE_EVENT_TABLE();
	};

}

#endif