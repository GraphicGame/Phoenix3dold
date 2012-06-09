/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2BtCollisionDebugLines.hpp
*
* �汾		:	1.0 (2011/03/08)
*
* ����		��	more
*
*/

#ifndef PX2BTCOLLISIONDEBUGLINES_HPP
#define PX2BTCOLLISIONDEBUGLINES_HPP

#include "PX2BtPreRequisites.hpp"

namespace TdBt
{

	class DebugLines
	{
	public:
		DebugLines ();
		virtual ~DebugLines ();

		// ����������ʵ�ʲ�����յ��Ч��
		void Clear ();

		void AddLine (const PX2::APoint &start, const PX2::APoint &end);
		void AddLine (float startX, float startY, float startZ, float endX,
			float endY,	float endZ);

		void Draw (PX2::Renderer *renderer);

	protected:
		PX2::VertexFormatPtr mVFormat;
		PX2::VertexColor4MaterialPtr mMaterial;
		PX2::VertexBufferPtr mVBuffer;
		PX2::PolysegmentPtr mSegment;

		typedef std::vector<PX2::APoint> Vector3fArray;
		Vector3fArray mPoints;
		int mMaxNumPoints;
		bool mDrawn;
	};
 
}

#endif