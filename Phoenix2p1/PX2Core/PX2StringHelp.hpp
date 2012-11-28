/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2StringHelp.hpp
*
* �汾		:	1.0 (2011/01/29)
*
* ����		��	more
*
*/

#ifndef PX2STRINGHELP_HPP
#define PX2STRINGHELP_HPP

#include "PX2CorePre.hpp"

namespace PX2
{

	class StringHelp
	{
	public:
		static bool Initlize();

		// ���ļ�·����׼������"\\"����'/'��, ���ĩβû��'/',���'/'
		static std::string StandardisePath (const std::string &path);

		/// ���ļ�·������ļ��������ļ���
		/**
		* ����"E:\\Phoenix\\Data\\Tdtf\\Normal.tdtf"��ɵĽ��Ϊ
		* outPath = "E:/Phoenix/Data//Tdtf/"
		* outBaseFileName = "Normal.tdtf"
		*/
		static void SplitFilename (const std::string &fullName,
			std::string &outPath, std::string &outBaseFileName);

		/// ���ļ�������ļ����ƺ���չ��
		/**
		* ����"Normal.tdtf"��ɵĽ��Ϊ
		* outBaseName = "Normal"
		* outExtention = "tdtf"
		*/
		static void SplitBaseFilename (const std::string &baseFileName,
			std::string &outBaseName, std::string &outExtention);

		/// ���ļ�·������ļ��������ļ����ƺ���չ����
		static void SplitFullFilename (const std::string &fullName,
			std::string &outPath, std::string &outBaseName, 
			std::string &outExtention);

		static int UnicodeToAnsi (char *dest, int maxChar, const wchar_t *src,
			int srcChar=-1);
		static int AnsiToUnicode (wchar_t *dest, int maxChar, const char *src, 
			int srcChar=-1);

		static const char *UnicodeToAnsi (const wchar_t *src, int srcChar=-1);
		static wchar_t *AnsiToUnicode (const char *src, int srcChar=-1);

		static std::string IntToString (int i);

		// Hash
		static unsigned int Hash(const std::string &str, unsigned int type);
		static unsigned int Hash(const char *str, unsigned int type,
			int length=-1); //< ���length<0,��ʾ������ַ�������\0��β
	};

}

#endif