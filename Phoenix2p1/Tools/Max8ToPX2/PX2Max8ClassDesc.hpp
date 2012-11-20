/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Max8ClassDesc.hpp
*
* �汾		:	1.0 (2011/04/18)
*
* ����		��	more
*
*/

#ifndef PX2MAX8CLASSDESC_HPP
#define PX2MAX8CLASSDESC_HPP

#include "PX2Max8ToTdPluginPre.hpp"

class PX2Max8ClassDesc : public ClassDesc2
{
public:
	PX2Max8ClassDesc ();

	virtual int IsPublic ();
	virtual void *Create (BOOL loading = FALSE);

	virtual const TCHAR* ClassName ();
	virtual SClass_ID SuperClassID ();
	virtual Class_ID ClassID ();
	virtual const TCHAR* Category ();
	virtual const TCHAR* InternalName ();
	virtual HINSTANCE HInstance();

	static HINSTANCE msInstance;

	static Class_ID ID;
	static PX2Max8ClassDesc TheClassDesc;
};

#endif