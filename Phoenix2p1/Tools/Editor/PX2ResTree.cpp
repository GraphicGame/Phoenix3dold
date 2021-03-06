/*
*
* �ļ�����	��	PX2ResTree.cpp
*
*/

#include "PX2ResTree.hpp"
#include "PX2ResourceManager.hpp"
#include "PX2EditSystem.hpp"
using namespace PX2Editor;
using namespace PX2;

//-----------------------------------------------------------------------------
#define ID_RESTREE wxID_HIGHEST + 4001
//-----------------------------------------------------------------------------
BEGIN_EVENT_TABLE(ResTree, wxTreeCtrl)
EVT_TREE_SEL_CHANGED(ID_RESTREE, ResTree::OnSelChanged)
EVT_TREE_ITEM_ACTIVATED(ID_RESTREE, ResTree::OnItemActivated)
EVT_TREE_SEL_CHANGING(ID_RESTREE, ResTree::OnSelChanging)
END_EVENT_TABLE()
//-----------------------------------------------------------------------------
ResTree::ResTree (wxWindow *parent)
	:
wxTreeCtrl(parent, ID_RESTREE)
{
}
//-----------------------------------------------------------------------------
ResTree::~ResTree ()
{

}
//-----------------------------------------------------------------------------
void ResTree::OnItemActivated(wxTreeEvent& event)
{
	wxTreeItemId id = event.GetItem();

	ResTreeItemPtr item = GetItem(id);

	if (!item)
		return;

#if defined(_WIN32) || defined(WIN32)
	WCHAR wszPath[MAX_PATH];
	GetCurrentDirectoryW(sizeof(wszPath), wszPath);
	std::wstring fullPath = wszPath + std::wstring(_T("\\")) + item->GetPathName();

	ShellExecute(0, _T("open"), fullPath.c_str(), 0, 0, SW_SHOW);
#endif
}
//-----------------------------------------------------------------------------
void ResTree::OnSelChanged(wxTreeEvent& event)
{
	wxTreeItemId id = event.GetItem();

	ResTreeItemPtr item = GetItem(id);

	if (!item)
		return;

	std::string resPath = item->GetPathName();
	if (resPath.find(".wav")!=std::string::npos ||
		resPath.find(".mp3")!=std::string::npos)
	{
	}
	else if (resPath.find(".")!=std::string::npos)
	{
		EditSystem::GetSingleton().SetSelectedResourceName(resPath);

		PX2::Object* object = ResourceManager::GetSingleton().BlockLoad(
			resPath.c_str());
		if (object)
		{
			object->SetResourcePath(resPath);

			EditSystem::GetSingleton().SetSelectedResource(object);
		}

		EditSystem::GetSingleton().SetPreViewObject(object);
	}
}
//-----------------------------------------------------------------------------
void ResTree::OnSelChanging(wxTreeEvent& event)
{
	PX2_UNUSED(event);
}
//-----------------------------------------------------------------------------
void ResTree::UpdateOnPath (std::string pathName)
{
	mRootItem = new0 ResTreeItem("Data", pathName);
	mRootItem->SetRoot();
}
//-----------------------------------------------------------------------------
ResTreeItem *ResTree::GetItem (wxTreeItemId id)
{
	if (mRootItem)
	{
		if (id == mRootItem->GetItemID())
			return mRootItem;
		else
			return mRootItem->GetChildItem(id);
	}

	return 0;
}
//-----------------------------------------------------------------------------
void ResTree::DoEnter ()
{
}
//-----------------------------------------------------------------------------
void ResTree::DoExecute (PX2::Event *event)
{
	PX2_UNUSED(event);
}
//-----------------------------------------------------------------------------
void ResTree::DoLeave ()
{
}
//-----------------------------------------------------------------------------