/*
* Phoenix2 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2TerrainEditPane.hpp
*
* �汾		:	1.0 (2011/04/27)
*
* ����		��	more
*
*/

#ifndef PX2TERRAINBRUSHPANE_HPP
#define PX2TERRAINBRUSHPANE_HPP

#include "PX2EditorPrerequisites.hpp"

namespace PX2Editor
{

	class TerrainBrushPanel : public wxPanel
	{
	public:
		TerrainBrushPanel (wxWindow *parent);

		void OnChoice (wxCommandEvent &event);
		void OnSliderUpdate (wxCommandEvent &event);
		void OnCheckbox (wxCommandEvent& event);

		void RefleshCtrls ();

	protected:
		TerrainBrushPanel ();

		// Brush
		wxChoice *mInterplate;
		wxSlider *mSize;
		wxSlider *mStrength;

		wxCheckBox *mUseHelpGrid;

		DECLARE_EVENT_TABLE();
	};

}

#endif