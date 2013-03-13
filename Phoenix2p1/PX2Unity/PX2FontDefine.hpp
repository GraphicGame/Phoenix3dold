/*
*
* �ļ�����	��	PX2FontDefine.hpp
*
*/

#ifndef PX2FONTDEFINE_HPP
#define PX2FONTDEFINE_HPP

#include "PX2UnityPre.hpp"

namespace PX2
{

#define FES_NORMAL 0		//< ��ͨ
#define FES_ITALIC 1		//< б��
#define FES_UNDERLINE 2		//< �»���

#define FD_NORMAL 0
#define FD_SHADOW 1
#define FD_BORDER 2

#define FONT_MAXRECTNUM 2048 // һ����Ⱦ��������θ���
#define FONT_TEXSIZE 512	 // ������ͼ�ĳߴ�

	enum CharacterSet
	{
		CS_ENGLISH = 0,		//< Ӣ��
		CS_CHINESE_GB,		//< ���Ĺ������
		CS_CHINESE_GBK,		//< ���Ĺ������
		CS_CHINESE_BIG5,	//< ����BIG5����
	};

	struct FontDrawRect
	{
		Rectf Rect;
		Rectf RectUV;
		Float4 Color;
	};

	enum CharCtrlCode			//< ������
	{
		CCC_CHARACTER = 0,		//< ��ͨ�ַ�
		CCC_RETURN,				//< �س�
		CCC_NEWLINE,			//< ����
		CCC_ENDOFSTRING,		//< �ַ�������
		CCC_TRANSFER,			//< ת����Ʒ�
		CCC_UNKNOWN,			//< δ֪����������
	};

	enum CharCodingType
	{
		CCT_GBK,
		CCT_UTF8,
		CCT_MAX_TYPE
	};

}

#endif