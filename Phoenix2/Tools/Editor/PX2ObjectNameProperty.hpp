/*
* Phoenix2 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2BaseProperty.hpp
*
* �汾		:	1.0 (2011/03/29)
*
* ����		��	more
*
*/

#ifndef PX2OBJECTNAMEPROPERTY_HPP
#define PX2OBJECTNAMEPROPERTY_HPP

#include "PX2EditorPrerequisites.hpp"
#include "PX2Property.hpp"

namespace PX2Editor
{

	class ObjectNameProperty : public Property
	{
	public:
		ObjectNameProperty (PropertyPage *parent, std::string name,
			PX2::Object *object);
		virtual ~ObjectNameProperty ();

		virtual void OnChange (wxPropertyGridEvent &event);

		// PX2 Event
		virtual void DoEnter ();
		virtual void DoUpdate ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

	protected:
		PX2::ObjectPtr mObject;
	};

}

#endif