/*
* Phoenix2 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2TextureInspector.hpp
*
* �汾		:	1.0 (2011/11/28)
*
* ����		��	more
*
*/

#ifndef PX2TEXTUREINSPECTOR_HPP
#define PX2TEXTUREINSPECTOR_HPP

#include "PX2ObjectPropertyGrid.hpp"

namespace PX2Editor
{

	class TexturePropertyGrid : public ObjectPropertyGrid
	{
	public:
		TexturePropertyGrid (wxWindow *parent);
		~TexturePropertyGrid ();

		DECLARE_DYNAMIC_CLASS(TexturePropertyGrid)

		virtual void OnSetObject(PX2::Object *object);

		virtual void OnPropertyGridChange (wxPropertyGridEvent &event);
		virtual void OnPropertyGridChanging (wxPropertyGridEvent &event);
		virtual void OnPropertyGridSelect (wxPropertyGridEvent &event);

		// PX2 Event
		virtual void DoEnter ();
		virtual void DoUpdate ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

	protected:
		DECLARE_EVENT_TABLE()

		TexturePropertyGrid ();
		void RefreshOnTexture ();
	};

}

#endif