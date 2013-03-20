/*
*
* �ļ�����	��	PX2ResourceManager.hpp
*
*/

#ifndef PX2RESOURCEMANAGER_HPP
#define PX2RESOURCEMANAGER_HPP

#include "PX2UnityPre.hpp"
#include "PX2TexPackData.hpp"
#include "PX2Runnable.hpp"

namespace PX2
{

	typedef unsigned long ResHandle;

	class ResourceManager : public Runnable, public Singleton<ResourceManager>
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
		void Clear ();
		Object *BlockLoad (const std::string &filename);
		ResHandle BackgroundLoad (const std::string &filename);
		Object *CheckRes (ResHandle handle);
		LoadState GetResLoadState (ResHandle handle);

		bool SaveCachedResource (const std::string &filename);
		bool LoadCachedResource (const std::string &filename);

		/// ���buffer,�����Android�豸��apk�л�ȡ
		/**
		* ����Ҫ����ʹ��delete1�ͷŻ�õ�buffer
		*/
		bool GetBuffer (const std::string &filename, int &bufferSize, 
			char* &buffer);

		// tex pack
		bool AddTexPack (const std::string &texPackPath);
		const TexPack &GetTexPack (const std::string &texPackPath);
		const TexPackElement &GetTexPackElement (
			const std::string &texPackPath, const std::string &eleName);

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

		virtual void Run ();

	protected:
		LoadRecord &InsertRecord (const std::string &filename);
		void _LoadTheRecord (LoadRecord &rec);
		Object *_LoadObject (const std::string &filename);
		bool _LoadBuffer (const std::string &filename, int &bufferSize,
			char* &buffer);
		Texture2D *LoadTexFormOtherImagefile (std::string outExt, 
			int bufferSize, const char*buffer);
		Texture2D *LoadTextureFromDDS (const std::string &filename);
		bool GetFileDataFromZip (const std::string &packageName, 
			const std::string &filename, int &bufferSize, char* &buffer);
		
	private:
		bool mDDSKeepCompressed;
		Mutex *mLoadRecordMutex;
		Mutex *mLoadingDequeMutex;
		Thread *mLoadingThread;
		std::deque<LoadRecord *>mLoadingDeque;
		bool mQuitLoading;
		ConditionType mLoadingDequeCondition;

		typedef std::map<std::string, LoadRecord> ResTable;
		typedef ResTable::iterator ResIterator;
		Mutex *mResTableMutex;
		ResTable mResTable;

		std::map<std::string, TexPack> mTexPacks;
		std::map<std::string, TexPackElement> mPackElements;

		bool mReadFromZip;
		static std::string msResPath;

		unsigned int mTimeCounter;
	};

#include "PX2ResourceManager.inl"

#define PX2_RM ResourceManager::GetSingleton()

}

#endif