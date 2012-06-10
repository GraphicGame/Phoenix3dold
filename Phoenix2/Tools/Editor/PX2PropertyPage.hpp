/*
* Phoenix2 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2PropertyPage.hpp
*
* �汾		:	1.0 (2011/06/28)
*
* ����		��	more
*
*/

#ifndef PX2PROPERTYPAGE_HPP
#define PX2PROPERTYPAGE_HPP

#include "PX2EditorPrerequisites.hpp"
#include "PX2Property.hpp"

namespace PX2Editor
{

	class PropertyGrid;

	class PropertyPage
	{
	public:
		PropertyPage (PropertyGrid *parent, std::string name = "");
		~PropertyPage ();

		std::string GetName () { return mName; }

		void AddProperty (std::string name, Property::PropertyType type,
			void *data);
		Property *GetProperty (std::string name);

		void OnPropertyGridChange (wxPropertyGridEvent &event);
		void OnPropertyGridChanging (wxPropertyGridEvent &event);
		void OnPropertyGridSelect (wxPropertyGridEvent &event);

	protected:
		std::string mName;

public_internal:
		PropertyGrid *mParent;
		std::vector<PropertyPtr> mProperties;
		wxPropertyGridPage *mPage;
	};

	typedef PX2::Pointer0<PropertyPage> PropertyPagePtr;

}

#endif