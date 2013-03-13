/*
*
* �ļ�����	��	PX2SkinController.hpp
*
*/

#ifndef PX2SKINCONTROLLER_HPP
#define PX2SKINCONTROLLER_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Controller.hpp"
#include "PX2Node.hpp"
#include "PX2Vector3.hpp"

namespace PX2
{

	class SkinController : public Controller
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(SkinController);

	public:
		SkinController (int numVertices, int numBones);
		virtual ~SkinController ();

		inline int GetNumVertices () const;
		inline int GetNumBones () const;
		inline Node** GetBones () const;
		inline float** GetWeights () const;
		inline APoint** GetOffsets () const;

		virtual bool Update (double applicationTime);

	protected:
		int mNumVertices;   // nv
		int mNumBones;      // nb
		Node** mBones;      // bones[nb]
		float** mWeights;   // weight[nv][nb], index b+nb*v
		APoint** mOffsets;  // offset[nv][nb], index b+nb*v
	};

	PX2_REGISTER_STREAM(SkinController);
	typedef Pointer0<SkinController> SkinControllerPtr;
#include "PX2SkinController.inl"

}

#endif
