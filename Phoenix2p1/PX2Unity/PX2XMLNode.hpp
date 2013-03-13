/*
*
* �ļ�����	��	PX2XMLNode.hpp
*
*/

#ifndef PX2XMLNODE_HPP
#define PX2XMLNODE_HPP

#include "PX2UnityPre.hpp"

class TiXmlElement;

namespace PX2
{

	class XMLNode
	{
	public:
		XMLNode (std::string name="");
		XMLNode (TiXmlElement *element);
		~XMLNode ();

		bool IsNull ();
		void Create ();
		void LinkEndChild (XMLNode node);

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
		std::string mName;
		TiXmlElement *mElement;
	};

}

#endif