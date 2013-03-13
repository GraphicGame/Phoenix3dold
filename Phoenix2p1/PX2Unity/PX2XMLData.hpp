/*
*
* �ļ�����	��	PX2XMLData.hpp
*
*/

#ifndef PX2XMLDATA_HPP
#define PX2XMLDATA_HPP

#include "PX2UnityPre.hpp"
#include "PX2XMLNode.hpp"

class TiXmlDocument;

namespace PX2
{

	class XMLData
	{
	public:
		XMLData ();
		~XMLData ();

		bool LoadFile (const std::string &fileName);
		bool LoadBuffer (const char *buffer, int size);
		bool SaveFile (const std::string &fileName);
		void Create ();

		XMLNode GetRootNode ();

		// path="Config.RenderSystem.FXSetting",����м��κ�һ���ڵ㲻����,����
		// �սڵ�
		XMLNode GetNodeByPath (const char *path);

		void LinkEndChild (XMLNode node);

	private:
		XMLData (const XMLData &);
		XMLData &operator= (const XMLData &);

		TiXmlDocument *mDocument;
	};

}

#endif