/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2ResourceManager.hpp
*
* �汾		:	1.0 (2011/04/01)
*
* ����		��	more
*
*/

#ifndef PX2RESOURCEMANAGER_HPP
#define PX2RESOURCEMANAGER_HPP

#include "PX2UnityPrerequisites.hpp"

namespace PX2
{

	class ResourceManager : public Singleton<ResourceManager>
	{
	public:
		ResourceManager ();
		~ResourceManager ();

		/// ��Դ����״̬
		enum LoadState
		{
			LS_UNLOADED,
			LS_LOADQUE,
			LS_LOADING,
			LS_LOADED,
			LS_MAX_STATE
		};

		struct LoadRecord
		{
			std::string Filename;
			ObjectPtr Obj;
			LoadState State;

			// ����Դ���ü���Ϊ1�󣬳���һ��ʱ�䳤�Ⱥ���Դ����ϵͳ���ա�
			unsigned int LastTouchedTime;
		};

		typedef unsigned long ResHandle;

		// Load
		void DDSKeepCompressed (bool keep=true);
		bool IsDDSKeepCompressed ();
		Object *BlockLoad (const std::string &filename);
		ResHandle BackgroundLoad (const std::string &filename);
		Object *CheckRes (ResHandle handle);
		LoadState GetResLoadState (ResHandle handle);

		// Garbage
		void GarbageCollect ();

public_internal:
		unsigned int RunLoadingThread ();

	protected:
		LoadRecord &InsertRecord (const std::string &filename);
		void LoadTheRecord (LoadRecord &rec);
		Object *LoadObject (const std::string &filename);
		Texture2D *LoadTextureFromOtherImagefile (const std::string &filename);
		Texture2D *LoadTextureFromDDS (const std::string &filename);

		void StartThread ();
		
	private:
		bool mDDSKeepCompressed;
		typedef void *OSEventHandle;
		Mutex mLoadRecordMutex;
		Mutex mLoadingDequeMutex;
		Thread *mLoadingThread;
		std::deque<LoadRecord *>mLoadingDeque;
		bool mQuitLoading;
		OSEventHandle mLoadingDequeSemaphore;

		typedef std::map<std::string, LoadRecord> ResTable;
		typedef ResTable::iterator ResIterator;

		Mutex mResTableMutex;
		ResTable mResTable;

		unsigned int mTimeCounter;
	};

#include "PX2ResourceManager.inl"

}

#endif