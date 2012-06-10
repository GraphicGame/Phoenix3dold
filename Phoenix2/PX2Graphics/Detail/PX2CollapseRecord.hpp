/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2CollapseRecord.hpp
*
* �汾		:	1.0 (2011/03/17)
*
* ����		��	more
*
*/

#ifndef PX2COLLAPSERECORD_HPP
#define PX2COLLAPSERECORD_HPP

#include "PX2GraphicsPrerequisites.hpp"

namespace PX2
{

	class PX2_GRAPHICS_ENTRY CollapseRecord
	{
	public:
		CollapseRecord (int vKeep = -1, int vThrow = -1, int numVertices = 0,
			int numTriangles = 0);

		~CollapseRecord ();

		// Edge <VKeep,VThrow>�����VThrow�ᱻVKeep�滻��
		int VKeep, VThrow;

		// �������ݵ��󣬶��������
		int NumVertices;

		// �������ݵ�������������
		int NumTriangles;

		// ����[0..NumTriangles-1]֮�ڱ��ӵ��Ķ��������
		int NumIndices;
		int* Indices;
	};

}

#endif