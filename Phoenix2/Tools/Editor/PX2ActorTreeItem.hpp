/*
* Phoenix2 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2TreeItem.hpp
*
* �汾		:	1.0 (2011/04/27)
*
* ����		��	more
*
*/

#ifndef PX2TREEITEM_HPP
#define PX2TREEITEM_HPP

#include "PX2EditorPrerequisites.hpp"

namespace PX2Editor
{
	
	class ActorTreeItem
	{
	public:
		ActorTreeItem (wxTreeCtrl *treeCtrl, wxTreeItemId parentId,
			PX2::Actor *actor);
		~ActorTreeItem ();

		void SetName (std::string name);
		inline PX2::Actor *GetActor () {return mActor;}
		inline wxTreeItemId GetItemID () {return mItemID;}
		inline wxTreeItemId GetParentItemID () {return mParentItemID;}

	protected:
		ActorTreeItem ();

		wxTreeCtrl *mTreeCtrl;
		PX2::ActorPtr mActor;
		wxTreeItemId mParentItemID;
		wxTreeItemId mItemID;
	};
}

#endif