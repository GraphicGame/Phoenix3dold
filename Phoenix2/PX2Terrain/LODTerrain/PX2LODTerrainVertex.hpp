/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2LODTerrainVertex.hpp
*
* �汾		:	1.0 (2011/03/03)
*
* ����		��	more
*
*/

#ifndef PX2LODTERRAINVERTEX_HPP
#define PX2LODTERRAINVERTEX_HPP

#include "PX2TerrainPrerequisites.hpp"
#include "PX2Assert.hpp"

namespace PX2
{
	/// LOD���ζ�����
	class PX2_TERRAIN_ENTRY LODTerrainVertex
	{
	public:
		LODTerrainVertex ();

		void SetDependent (int i, LODTerrainVertex *pkDependent);
		LODTerrainVertex *GetDependent (int i);
		bool IsEnabled () const;
		void Enable ();
		void Disable ();

	protected:
		LODTerrainVertex *mDependent[2];
		bool mEnabled; //< �ö����Ƿ������������
	};

#include "PX2LODTerrainVertex.inl"
}

#endif