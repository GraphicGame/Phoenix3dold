/*
* Phoenix 3D ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2FileIO.hpp
*
* �汾		:	1.0 (2011/01/30)
*
* ����		��	more
*
*/

#ifndef PX2FILEIO_HPP
#define PX2FILEIO_HPP

#include "PX2CorePre.hpp"

namespace PX2
{

	/// �ļ���д��
	/**
	* ֧�ֶ������ļ���д��������ԡ�ֻ�����ķ�ʽ���ļ�������д�����ᵼ�´���
	* ͬ���ģ�������ԡ�ֻд����ʽ���ļ������ö���������ִ�������಻ͬʱ
	* ֧�֡���д�����ʡ�������װ��׼�ļ�������
	*/
	class FileIO
	{
	public:
		/// �ļ���ȡ��ʽ
		/**
		* FM_READ			�Ӵ��̶�ȡ��û���ֽڽ�����
		* FM_WRITE			д����̣�û���ֽڽ�����
		* FM_READ_AND_SWAP	�Ӵ��̶�ȡ���ҽ�����2-��4-��8-���룩
		* FM_WRITE_AND_SWAP	д����̲��ҽ�����2-��4-��8-���룩
		*/
		enum
		{
			FM_NONE,
			FM_READ,
			FM_WRITE,
			FM_READ_AND_SWAP,
			FM_WRITE_AND_SWAP,

#ifdef PX2_LITTLE_ENDIAN
			FM_DEFAULT_READ = FM_READ,
			FM_DEFAULT_WRITE = FM_WRITE
#else
			FM_DEFAULT_READ = FM_READ_AND_SWAP,
			FM_DEFAULT_WRITE = FM_WRITE_AND_SWAP
#endif
		};

		FileIO ();
		FileIO (const std::string& filename, int mode);
		~FileIO ();

		bool Open (const std::string& filename, int mode);
		bool Close ();

		// ��ʽת������������ļ��Ƿ�ɹ��򿪡�
		operator bool () const;

		inline int GetMode () const;

		enum SeekMode
		{
			SM_SET = 0,
			SM_CUR = 1,
			SM_END = 2
		};

		int Seek (long offset, SeekMode mode);

		// �����ɹ�����'true'
		bool Read (size_t itemSize, void* datum);
		bool Read (size_t itemSize, int numItems, void* data);
		bool Write (size_t itemSize, const void* datum);
		bool Write (size_t itemSize, int numItems, const void* data);

		// �������ļ����ص�buffer
		static bool Load (const std::string& filename, bool binaryFile,
			int& bufferSize, char*& buffer);

		// ��buffer���浽�ļ�
		static bool Save (const std::string& filename, bool binaryFile,
			int bufferSize, const char* buffer);

		// ��buffer���ӵ��ļ�
		static bool Append (const std::string& filename, bool binaryFile,
			int bufferSize, const char* buffer);

		/// ��ÿ�д·��
		/**
		* ��PC��Ϊ����ǰĿ¼�����ƶ��豸���ɸ��豸API���ء�
		*/
		static std::string GetWriteablePath ();

	private:
		FILE* mFile;
		int mMode;
	};

#include "PX2FileIO.inl"

}

#endif