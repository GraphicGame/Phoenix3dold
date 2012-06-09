/*
* Phoenix 3D ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Rtti.hpp
*
* �汾		:	1.0 (2011/01/30)
*
* ����		��	more
*
*/

#ifndef PX2RTTI_H
#define PX2RTTI_H

#include "PX2CorePrerequisites.hpp"

namespace PX2
{

	/// ����ʶ�������
	/**
	* ��ϵͳ���е�Object�У�acName���Ʊ��벻ͬ����PX2�����ֿռ��У�һ������Poo��
	* �������ΪPX2.Poo�����Ӧ�ó��������������ֿռ䣬��SomeName����ô�������
	* Ϊ"SomeName.Poo"��
	*/
	class PX2_CORE_ENTRY Rtti
	{
	public:
		Rtti (const char* name, const Rtti* baseType);
		~Rtti ();

		inline const char* GetName () const;
		inline bool IsExactly (const Rtti& type) const;
		bool IsDerived (const Rtti& type) const;

	private:
		const char* mName;
		const Rtti* mBaseType;
	};

#include "PX2Rtti.inl"

}

//----------------------------------------------------------------------------
#define PX2_DECLARE_RTTI \
public: \
	static const Rtti TYPE; \
	\
	virtual const Rtti& GetRttiType () const \
{ \
	return TYPE; \
}
//----------------------------------------------------------------------------
#define PX2_IMPLEMENT_RTTI(nsname, baseclassname, classname) \
	const Rtti classname::TYPE(#nsname"."#classname, &baseclassname::TYPE)
//----------------------------------------------------------------------------

#endif
