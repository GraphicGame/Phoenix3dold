/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2XMLData.hpp
*
* �汾		:	1.0 (2011/02/09)
*
* ����		��	more
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

		XMLNode GetRootNode ();

		// path="Config.RenderSystem.FXSetting",����м��κ�һ���ڵ㲻����,����
		// �սڵ�
		XMLNode GetNodeByPath (const char *path);

	private:
		XMLData (const XMLData &);
		XMLData &operator= (const XMLData &);

		TiXmlDocument *mDocument;
	};

}

#endif