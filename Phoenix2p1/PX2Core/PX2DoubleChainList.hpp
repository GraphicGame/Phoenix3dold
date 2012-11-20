/*
* Phoenix 3D ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2DoubleChainList.hpp
*
* �汾		:	1.0 (2011/03/19)
*
* ����		��	more
*
*/

#ifndef PX2DOUBLECHAINLIST_HPP
#define PX2DOUBLECHAINLIST_HPP

#include "PX2Memory.hpp"

namespace PX2
{

	class ChainListNode
	{
	public:
		ChainListNode *NextNode;
		ChainListNode *PrevNode;
	};

	template <class T>
	class ChainList
	{
	public:
		ChainList ();

		//�õ���ǰ�����node��Ŀ
		int GetNumNodes ();
		bool IsEmpty ();
		void Clear ();

		void PushFront (ChainListNode *node);
		void PushBack (ChainListNode *node);
		void PopFront ();
		void PopBack ();

		void InsertBefore (ChainListNode *node, ChainListNode *ref);
		void InsertAfter (ChainListNode *node, ChainListNode *ref);

		T *Remove (ChainListNode *node);

		bool IsNodeInList(ChainListNode *node);

		void DeleteAllNodes ();
		void ReleaseAllNodes ();
		T *BeginIterate ();
		T *Iterate (ChainListNode *pnode);
		T *Front();
		T *Back();

	private:
		ChainListNode mEndNode;
		int mNumNodes;
	};

#include "PX2DoubleChainList.inl"

}

#endif