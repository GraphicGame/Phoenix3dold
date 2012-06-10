/*
* Phoenix2 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2EditorOption.hpp
*
* �汾		:	1.0 (2011/04/18)
*
* ����		��	more
*
*/

#ifndef PX2EDITOROPTIONS_HPP
#define PX2EDITOROPTIONS_HPP

#include "PX2EditorPrerequisites.hpp"
#include "PX2Singleton.hpp"

namespace PX2Editor
{

	class EditorOptions : public PX2::Singleton<EditorOptions>
	{
	public:
		EditorOptions ();
		~EditorOptions ();

		bool Save (std::string filename);
		bool Load (std::string filename);

		float mGridSize; //< ���������С
		float mOrthoAdjust; //< �������������
		float mOrthoFrustumMin;
		bool mViewFull; //< 
		int mViewFullIndex; //<
		bool mShowEffectEditorBar;
	};

}

#endif