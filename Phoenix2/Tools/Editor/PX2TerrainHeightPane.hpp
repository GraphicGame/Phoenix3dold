/*
* Phoenix2 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2TerrainHeightPane.hpp
*
* �汾		:	1.0 (2011/04/27)
*
* ����		��	more
*
*/

#ifndef PX2TERRAINHEIGHTPANE_HPP
#define PX2TERRAINHEIGHTPANE_HPP

#include "PX2EditorPrerequisites.hpp"

namespace PX2Editor
{
	 
	class TerrainHeightPanel : public wxPanel
	{
	public:
		TerrainHeightPanel (wxWindow *parent);

		void OnRadio (wxCommandEvent &event);
		void RefleshCtrls ();

	protected:
		TerrainHeightPanel ();

		wxRadioBox *mHeightModeRadio;

		DECLARE_EVENT_TABLE();
	};

}

#endif