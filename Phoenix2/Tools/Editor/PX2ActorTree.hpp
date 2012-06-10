/*
* Phoenix2 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2ActorTree.hpp
*
* �汾		:	1.0 (2011/05/04)
*
* ����		��	more
*
*/

#ifndef PX2ACTORTREE_HPP
#define PX2ACTORTREE_HPP

#include "PX2EditorPrerequisites.hpp"

namespace PX2Editor
{

	class ActorTreeItem;

	class ActorTree : public wxTreeCtrl, public PX2::EventHandler
	{
	public:
		ActorTree (wxWindow *parent);
		~ActorTree ();

		// �������ı��ˢ��
		void RefleshScene (); 

		ActorTreeItem *AddActor (wxTreeItemId parentID, PX2::Actor *actor);
		void RemoveActor (PX2::Actor *actor);
		void RemoveAllActors ();
		ActorTreeItem *GetItem (wxTreeItemId id);
		ActorTreeItem *GetItem (PX2::Actor *actor);

		void OnItemActivated (wxTreeEvent& event);
		void OnSelChanged (wxTreeEvent& event);
		void OnSelChanging (wxTreeEvent& event);

		// �¼�
		virtual void DoEnter ();
		virtual void DoUpdate ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

	protected:
		DECLARE_EVENT_TABLE()
		
		wxTreeItemId mRootItemId;
		wxTreeItemId mSkyItemId; // ���
		wxTreeItemId mTerrainItemId; // ����
		wxTreeItemId mWaterItemId; // ˮ��
		wxTreeItemId mObjectsItemId; // ���
		wxTreeItemId mLightsItemId; // �ƹ�
		std::vector<ActorTreeItem*> mItems;

		wxTreeItemId mEnvItemId;
	};
}

#endif