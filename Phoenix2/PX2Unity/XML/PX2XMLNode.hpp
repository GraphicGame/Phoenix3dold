/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2XMLNode.hpp
*
* �汾		:	1.0 (2011/02/09)
*
* ����		��	more
*
*/

#ifndef PX2XMLNODE_HPP
#define PX2XMLNODE_HPP

#include "PX2UnityPrerequisites.hpp"

class TiXmlElement;

namespace PX2
{

	class XMLNode
	{
	public:
		XMLNode ();
		XMLNode (TiXmlElement *element);
		~XMLNode ();

		bool IsNull ();

		const char *GetName ();
		char *GetFullName (char *buffer, size_t maxBuffer);
		const char *GetText ();

		// ����
		bool HasChild (const char *name);
		XMLNode GetChild (const char *name); //< ��õ�һ����name�ĺ���
		XMLNode IterateChild (); //< ��õ�һ������
		XMLNode IterateChild (XMLNode previous);		

		// ����
		bool HasAttribute (const char *name);
		int AttributeToInt (const char *name);
		float AttributeToFloat (const char *name);
		bool AttributeToBool (const char *name);
		const char *AttributeToString (const char *name);

		bool AttribToInt(const char *name, int &value);
		bool AttribToFloat(const char *name, float &value);

		void SetAttributeInt (const char *name, int value);
		void SetAttributeFloat (const char *name, float value);
		void SetAttributeBool (const char *name, bool value);
		void SetAttributeString (const char *name, const char *string);

	public:
		TiXmlElement *mElement;
	};

}

#endif