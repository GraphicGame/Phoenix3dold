/*
* Phoenix 3D ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Endian.hpp
*
* �汾		:	1.0 (2011/01/30)
*
* ����		��	more
*
*/

#ifndef PX2ENDIAN_H
#define PX2ENDIAN_H

#include "PX2CorePrerequisites.hpp"

namespace PX2
{

	/// �ֽ�����
	/**
	* �ֽ�˳����ָռ�ڴ����һ���ֽ����͵��������ڴ��еĴ��˳��ͨ����С�ˡ�
	* ��������ֽ�˳��С���ֽ���ָ���ֽ����ݴ�����ڴ�͵�ַ�������ֽ����ݴ�
	* �����ڴ�ߵ�ַ��������ֽ����Ǹ��ֽ����ݴ���ڵ͵�ַ�������ֽ����ݴ����
	* �ߵ�ַ����
	* ���� int a = 0x05060708 ����
	* ��BIG-ENDIAN������´��Ϊ�� 
	*	�ֽں� 0  1  2  3 ����
	*	����   05 06 07 08 ��
	* ��LITTLE-ENDIAN������´��Ϊ�� 
	*	�ֽں� 0  1  2  3 
	*	����   08 07 06 05 
	*/
	class PX2_CORE_ENTRY Endian
	{
	public:
		/// �ֽ������Ƿ��Ǵ��ֽ���
		static bool IsBig ();

		/// �ֽ������Ƿ���С�ֽ���
		static bool IsLittle ();

		// �����ֽ�˳��
		static void Swap2 (void* datum);
		static void Swap2 (int numItems, void* data);
		static void Swap4 (void* datum);
		static void Swap4 (int numItems, void* data);
		static void Swap8 (void* datum);
		static void Swap8 (int numItems, void* data);
		static void Swap (size_t itemSize, void* datum);
		static void Swap (size_t itemSize, int numItems, void* data);

	private:
		static bool msIsLittle;
	};

}

#endif
