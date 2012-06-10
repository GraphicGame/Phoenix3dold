/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2CollapseRecordArray.hpp
*
* �汾		:	1.0 (2011/03/17)
*
* ����		��	more
*
*/

#ifndef PX2COLLAPSERECORDARRAY_HPP
#define PX2COLLAPSERECORDARRAY_HPP

#include "PX2GraphicsPrerequisites.hpp"
#include "PX2Object.hpp"
#include "PX2CollapseRecord.hpp"

namespace PX2
{

	class PX2_GRAPHICS_ENTRY CollapseRecordArray : public Object
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(CollapseRecordArray);

	public:
		CollapseRecordArray (int numRecords = 0, CollapseRecord* records = 0);
		virtual ~CollapseRecordArray ();

		inline int GetNumRecords () const;
		inline CollapseRecord* GetRecords () const;

	protected:
		int mNumRecords;
		CollapseRecord* mRecords;
	};

	PX2_REGISTER_STREAM(CollapseRecordArray);
	typedef Pointer0<CollapseRecordArray> CollapseRecordArrayPtr;
#include "PX2CollapseRecordArray.inl"

}

#endif
