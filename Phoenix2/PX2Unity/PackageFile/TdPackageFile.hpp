/*
* Turandot 3D ��Ϸ���� Version 1.0
*
* Copyright (C) 2009-2011 http://www.Turandot3d.org/
*
* �ļ�����	��	TdPackageFile.hpp
*
* �汾		:	1.0 (2011/07/10)
*
* ����		��	���
*
*/

#ifndef TDPACKAGEFILE_HPP
#define TDPACKAGEFILE_HPP

#include "TdUnityPrerequisites.hpp"

namespace Td
{
	struct PackageHeader
	{
		unsigned int id;
		int version;
		int numFiles;
		int keyOffset;
		int keyLength;
		int dataOffset;
		int dataLength;
	};

	struct PackageFileInfo
	{
		unsigned int key0;
		unsigned int key1;
		unsigned int offset;
		unsigned int originSize;
		unsigned int packSize; // δѹ���ļ�packSize == originSize
		unsigned int flags; // bit0: compress
	};

	class TD_UNITY_ENTRY FilePackage
	{
	public:
		FilePackage ();

		bool Open (const std::string &filename, bool readOnly);
		void Close ();

		int GetFilesNum ();

		const PackageFileInfo &GetPackageFileInfo (int i);

		DataStream *OpenFile (int fileNum);
		unsigned int ReadFile (void *buffer, unsigned int offset, unsigned int len);

		bool AppendOrReplaceFile (unsigned int key0, unsigned int key1,
			const void *data, unsigned int originSize, unsigned int packageSize);

		bool AppendOrReplaceFile (const char *fileName, bool doCompress);

	private:
		bool mReadOnly;
		FileIO mFileIO;
		PackageHeader mPackageHeader;
		std::vector<PackageFileInfo> mFileTable;

		static Mutex msMutex;
	};

}

#endif