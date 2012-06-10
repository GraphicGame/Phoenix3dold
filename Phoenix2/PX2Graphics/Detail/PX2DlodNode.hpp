/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2DlodNode.hpp
*
* �汾		:	1.0 (2011/03/17)
*
* ����		��	more
*
*/

#ifndef PX2DLODNODE_HPP
#define PX2DLODNODE_HPP

#include "PX2SwitchNode.hpp"

namespace PX2
{

	class PX2_GRAPHICS_ENTRY DlodNode : public SwitchNode
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(DlodNode);

	public:
		DlodNode (int numLevelsOfDetail);
		virtual ~DlodNode ();

		// Level of detail(LOD)����
		inline APoint& ModelCenter ();
		inline const APoint& GetModelCenter () const;
		inline const APoint& GetWorldCenter () const;

		// �������
		inline int GetNumLevelsOfDetail () const;
		inline float GetModelMinDistance (int i) const;
		inline float GetModelMaxDistance (int i) const;
		inline float GetWorldMinDistance (int i) const;
		inline float GetWorldMaxDistance (int i) const;
		void SetModelDistance (int i, float minDist, float maxDist);

	protected:
		void SelectLevelOfDetail (const Camera* camera);

		virtual void GetVisibleSet (Culler& culler, bool noCull);

		APoint mModelLodCenter;
		APoint mWorldLodCenter;

		int mNumLevelsOfDetail;
		float* mModelMinDist;
		float* mModelMaxDist;
		float* mWorldMinDist;
		float* mWorldMaxDist;
	};

	PX2_REGISTER_STREAM(DlodNode);
	typedef Pointer0<DlodNode> DlodNodePtr;
#include "PX2DlodNode.inl"

}

#endif