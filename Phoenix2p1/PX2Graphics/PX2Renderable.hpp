/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Renderable.hpp
*
* �汾		:	1.0 (2011/02/01)
*
* ����		��	more
*
*/

#ifndef PX2RENDERABLE_HPP
#define PX2RENDERABLE_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Movable.hpp"
#include "PX2IndexBuffer.hpp"
#include "PX2VertexBuffer.hpp"
#include "PX2VertexFormat.hpp"
#include "PX2MaterialInstance.hpp"
#include "PX2Light.hpp"

namespace PX2
{

	/// ��Ⱦ������
	/**
	* ������Ⱦ���󶼴Ӵ���������
	*/
	class Renderable : public Movable
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(Renderable);

	public:
		enum PrimitiveType
		{
			PT_NONE,  //< default constructor
			PT_POLYPOINT,
			PT_POLYSEGMENTS_DISJOINT,
			PT_POLYSEGMENTS_CONTIGUOUS,
			PT_TRIANGLES,  //< abstract
			PT_TRIMESH,
			PT_TRISTRIP,
			PT_TRIFAN,
			PT_MAX_QUANTITY
		};

	protected:
		/**
		* �������
		*/
		Renderable (PrimitiveType type = PT_NONE);
		Renderable (PrimitiveType type, VertexFormat* vformat, VertexBuffer* vbuffer,
			IndexBuffer* ibuffer);
	public:
		virtual ~Renderable ();

		inline PrimitiveType GetPrimitiveType () const;

		inline void SetVertexFormat (VertexFormat* vformat);
		inline const VertexFormat* GetVertexFormat () const;
		inline VertexFormat* GetVertexFormat ();

		inline void SetVertexBuffer (VertexBuffer* vbuffer);
		inline const VertexBuffer* GetVertexBuffer () const;
		inline VertexBuffer* GetVertexBuffer ();

		inline void SetIndexBuffer (IndexBuffer* ibuffer);
		inline const IndexBuffer* GetIndexBuffer () const;
		inline IndexBuffer* GetIndexBuffer ();

		inline const Bound& GetModelBound () const;
		inline Bound& GetModelBound ();

		// ��Ⱦ����
		enum RenderUsage
		{
			RU_UI,
			RU_GENERAL,
			RU_REFLECT,
			RU_SHADOWMAP,
			RU_QUANTITY
		};

		void AddRenderUsage (RenderUsage usage);
		void RemoveRenderUsage (RenderUsage usage);
		unsigned int GetRenderUsage ();

		/// ��Ⱦ�㼶
		enum RenderLayer
		{
			RL_BACKGROUND = 0,
			RL_TERRAIN,
			RL_SCENE,
			RL_FRONT
		};

		void SetRenderLayer (RenderLayer layer);
		unsigned int GetSortIndex ();

		// ���Ƽ���ͼ�ε�Ч��ʵ��
		inline void SetMaterialInstance (MaterialInstance* material);
		inline MaterialInstance* GetMaterialInstance () const;
		
		// �ƹ�
		/*
		* ��ǰ��Ⱦ���յ�Ӱ��ĵƹ�
		*/
		bool AddLight (Light *light);
		bool RemoveLight (Light *light);		
		void ClearLights ();
		int GetNumLights ();
		Light *GetLight (int i);

		// ����ͼ�θ�������
		enum UpdateType
		{
			GU_MODEL_BOUND_ONLY = -3,
			GU_NORMALS = -2,
			GU_USE_GEOMETRY = -1,
			GU_USE_TCOORD_CHANNEL = 0
		};

		/// ���Ӷ���ģ�͸���
		/**
		* ������Ӷ����VertexBuffer���޸��ˣ�����Ҫ���£�normals,tangents,
		* bitangents���������type�������µĹ������£�
		* GU_MODEL_BOUND_ONLY
		*	����Ŀռ�λ�øı��ˣ�ֻ���°�Χ�С�
		* �����������£���Χ��Ҳ������¡�������Ӷ����Ǵ�Triangles�����Ļ���
		* ����з�����Ϣ�������ȸ��·�����Ϣ��
		* GU_NORMALS
		*	�����귨����Ϣ�������ٸ�����������ռ䡣
		* GU_USE_GEOMETRY
		* GU_USE_TCOORD_CHANNEL + nonnegative_integer
		*	ʹ�õ�nonnegative_integer���������������������ռ䡣
		* Ϊ�˽�ʡ�Դ棬����Կ���ֻ����normals��tangents��Ȼ��ʹ��������ɫ��
		* ����bitangent��
		*	bitangent = Cross(normal, tangent)			
		*/
		virtual void UpdateModelSpace (UpdateType type);

public_internal:
		float mEyeDistance; // �������
		static bool LessThan (const Renderable *renderable0,
			const Renderable *renderable1);

	protected:
		void AdjustTransparent ();
		void SetTransparent (bool transparent);
		bool IsTransparent () const;

	protected:
		// ����ͼ�θ���
		virtual void UpdateWorldBound ();
		virtual void UpdateModelBound ();

		// �����ü�
		virtual void GetVisibleSet (Culler& culler, bool noCull);

	protected:
		// ��Ⱦ����
		unsigned int mRenderUsageBits;
		unsigned int mSortIndex; //(layer<<16)|current

		// ����ͼ������
		PrimitiveType mType;
		VertexFormatPtr mVFormat;
		VertexBufferPtr mVBuffer;
		IndexBufferPtr mIBuffer;
		Bound mModelBound;

		// ���Ƽ���ͼ�ε�Ч��
		MaterialInstancePtr mMaterial;

		// ��ǰ������Ӱ��ĵƹ�
		/*
		* �ƹⲻ�ó־û�����ÿ����Ⱦ֮ǰ������Ӱ��ĵƹ⡣
		*/
		std::vector<LightPtr> mInfulencedLights; 

		// Begin load/save
	public:
		// created properly unless we have a Load for each instantiable primitive.
		// ʹ�ó־û�ϵͳfrom/to *.tdvf Load/Save��Ⱦ������ΪRenderable�Ǿ��弸��
		// ͼ��һ��������࣬�������ǲ���ͨ���˺������أ�����������һ��Renderable��
		static void LoadPX2VF (const std::string& name, PrimitiveType& type,
			VertexFormat*& vformat, VertexBuffer*& vbuffer, IndexBuffer*& ibuffer,
			int mode = FileIO::FM_DEFAULT_READ);

		void SavePX2VF (const std::string& name,
			int mode = FileIO::FM_DEFAULT_WRITE);

	private:
		static VertexFormat* LoadVertexFormat (FileIO& inFile);
		static VertexBuffer* LoadVertexBuffer (FileIO& inFile,
			VertexFormat* vformat);
		static IndexBuffer* LoadIndexBuffer (FileIO& inFile);
		void SaveVertexFormat (FileIO& outFile);
		void SaveVertexBuffer (FileIO& outFile);
		void SaveIndexBuffer (FileIO& outFile);
		// End load/save
	};

	PX2_REGISTER_STREAM(Renderable);
	typedef Pointer0<Renderable> RenderablePtr;
#include "PX2Renderable.inl"

}

#endif
