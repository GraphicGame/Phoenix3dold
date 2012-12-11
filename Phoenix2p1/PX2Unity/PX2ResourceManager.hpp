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

#include "PX2UnityPre.hpp"

namespace PX2
{

	typedef unsigned long ResHandle;

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

		// ����
		Object *BlockLoad (const std::string &filename);
		ResHandle BackgroundLoad (const std::string &filename);
		Object *CheckRes (ResHandle handle);
		LoadState GetResLoadState (ResHandle handle);

		/// ���buffer,��Android�д�apk�л�ȡ
		/**
		* ����Ҫ����ʹ��delete1�ͷŻ�õ�buffer
		*/
		bool GetBuffer (const std::string &filename, int &bufferSize, 
			char* &buffer);

		/// ��ÿ�д·��
		/**
		* ��PC��Ϊ����ǰĿ¼�����ƶ��豸���ɸ��豸API���ء�
		*/
		std::string GetWriteablePath ();
		static const std::string GetResourcePath ();

		// ����ѡ��
		void DDSKeepCompressed (bool keep=true);
		bool IsDDSKeepCompressed ();

public_internal:
		struct LoadRecord
		{
			std::string Filename;
			ObjectPtr Obj;
			LoadState State;

			// ����Դ���ü���Ϊ1�󣬳���һ��ʱ�䳤�Ⱥ���Դ����ϵͳ���ա�
			unsigned int LastTouchedTime;
		};

		unsigned int RunLoadingThread ();
		void GarbageCollect ();
		
		// ������Դ·��.��Androidϵͳ�У�Ϊapk����Ŀ¼
		static void SetResourcePath (const std::string &resPath);

	protected:
		LoadRecord &InsertRecord (const std::string &filename);
		void _LoadTheRecord (LoadRecord &rec);
		Object *_LoadObject (const std::string &filename);
		bool _LoadBuffer (const std::string &filename, int &bufferSize,
			char* &buffer);
		Texture2D *LoadTextureFromOtherImagefile (const std::string &filename);
		Texture2D *LoadTextureFromDDS (const std::string &filename);
		bool GetFileDataFromZip (const std::string &packageName, 
			const std::string &filename, int &bufferSize, char* &buffer);

		void StartThread ();
		
	private:
		bool mDDSKeepCompressed;
		Mutex mLoadRecordMutex;
		Mutex mLoadingDequeMutex;
		Thread *mLoadingThread;
		std::deque<LoadRecord *>mLoadingDeque;
		bool mQuitLoading;
		ConditionType mLoadingDequeCondition;

		typedef std::map<std::string, LoadRecord> ResTable;
		typedef ResTable::iterator ResIterator;

		Mutex mResTableMutex;
		ResTable mResTable;

		bool mReadFromZip;
		static std::string msResPath;

		unsigned int mTimeCounter;
	};

#define PX2_RM ResourceManager::GetSingleton()

#include "PX2ResourceManager.inl"

}

#endif