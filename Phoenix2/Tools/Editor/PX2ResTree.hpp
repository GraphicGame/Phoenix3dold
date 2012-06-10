/*
* Phoenix2 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2ResTree.hpp
*
* �汾		:	1.0 (2011/05/04)
*
* ����		��	more
*
*/

#ifndef PX2RESTREE_HPP
#define PX2RESTREE_HPP

#include "PX2EditorPrerequisites.hpp"
#include "PX2ResTreeItem.hpp"

namespace PX2Editor
{

	class ResTree : public wxTreeCtrl, public PX2::EventHandler, public PX2::Singleton<ResTree>
	{
	public:
		ResTree (wxWindow *parent);
		~ResTree ();

		// wx Event
		void OnItemActivated(wxTreeEvent& event);
		void OnSelChanged(wxTreeEvent& event);
		void OnSelChanging(wxTreeEvent& event);

		void UpdateOnPath (std::string pathName);
		ResTreeItem *GetItem (wxTreeItemId id);

		// �¼�
		virtual void DoEnter ();
		virtual void DoUpdate ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

	protected:
		ResTreeItemPtr mRootItem;

		DECLARE_EVENT_TABLE()
	};

}

#endif