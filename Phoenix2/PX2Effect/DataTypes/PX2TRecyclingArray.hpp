/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2TRecyclingArray.hpp
*
* �汾		:	1.0 (2011/12/17)
*
* ����		��	more
*
*/

#ifndef PX2TRECYCLINGARRAY_HPP
#define PX2TRECYCLINGARRAY_HPP

#include "PX2EffectPrerequisites.hpp"

namespace PX2
{

	/// �ɻ�������
	template <class T>
	class TRecyclingArray
	{
	public:
		TRecyclingArray (int quantity);
		~TRecyclingArray ();

		T* New ();
		int GetLastNewIndex ();

		bool Delete (int index);
		bool Delete (T *element);
		void DeleteAll ();

		int GetUsedQuantity ();
		int GetFreeQuantity ();
		int GetQuantity ();

		T &GetAt (int index);

		bool IsUsed (int index);

	protected:
		T *mElements;
		bool *mUseds;
		int mQuantity;
		int mUsedQuantity;
		int mIndexLastNew;
		T mNewTemplate;
	};

#include "PX2TRecyclingArray.inl"

}

#endif