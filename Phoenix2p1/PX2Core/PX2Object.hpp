/*
* Phoenix 3D ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Object.hpp
*
* �汾		:	1.0 (2011/01/30)
*
* ����		��	more
*
*/

#ifndef PX2OBJECT_HPP
#define PX2OBJECT_HPP

#include "PX2CorePre.hpp"
#include "PX2Names.hpp"
#include "PX2Rtti.hpp"
#include "PX2SmartPointer.hpp"
#include "PX2InStream.hpp"
#include "PX2OutStream.hpp"

namespace PX2
{

	/// ����ϵͳ����
	/** 
	* ��ϵͳ�ṩ������ʶ����ƣ�������ϵͳ������ϵͳ������IDϵͳ,�Լ�Ӳ�̳־û�
	* ϵͳ֧�֡�
	*/
	class Object
	{
		// ����ʶ����Ϣ
	public:
		virtual const Rtti& GetRttiType () const;
		bool IsExactly (const Rtti& type) const;
		bool IsDerived (const Rtti& type) const;
		bool IsExactlyTypeOf (const Object* object) const;
		bool IsDerivedTypeOf (const Object* object) const;
		static const Rtti TYPE;

		// ��Դ·��
	public:
		void SetResourcePath (const std::string& name);
		const std::string& GetResourcePath () const;

	private:
		std::string mResourcePath;

		// ����
	public:
		void SetName (const std::string& name);
		const std::string& GetName () const;
		virtual Object* GetObjectByName (const std::string& name);
		virtual void GetAllObjectsByName (const std::string& name,
			std::vector<Object*>& objects);
	private:
		std::string mName;

		// �־û�
	public:
		typedef Object* (*FactoryFunction)(InStream& stream);
		typedef std::map<std::string, FactoryFunction> FactoryMap;
		static bool RegisterFactory ();
		static void InitializeFactory ();
		static void TerminateFactory ();
		static FactoryFunction Find (const std::string& name);
		static Object* Factory (InStream& source);
		virtual void Load (InStream& source);
		virtual void Link (InStream& source);
		virtual void PostLink ();
		virtual bool Register (OutStream& target) const;
		virtual void Save (OutStream& target) const;
		virtual int GetStreamingSize () const;
		Object* Copy (const std::string& uniqueNameAppend) const;
		Object* ShareCopy (const std::string& uniqueNameAppend,
			bool f=true, bool v=true, bool i=true, bool m=true);
		static void SetCurIOFlag (int flag); // 1write otherwise read
		static int GetCurIOFlag ();
		const std::string &GetCurSaveVersion() const;
		const std::string &GetVersion() const;
	protected:
		static int msCurIOFlag;
		// �����ȷ��mCurSaveVersion��mVersion��С��һ����
		std::string mCurSaveVersion;
		std::string mVersion;

		// Constructor used by the loading system.
		enum LoadConstructor { LC_LOADER };
		Object (LoadConstructor value);
		static FactoryMap* msFactories;
	private:
		static bool msStreamRegistered;

		// �������
	protected:
		Object ();
	public:
		virtual ~Object ();
	};

	static bool gsStreamRegistered_Object = Object::RegisterFactory();
	typedef Pointer0<Object> ObjectPtr;
#include "PX2Object.inl"

}

#endif
