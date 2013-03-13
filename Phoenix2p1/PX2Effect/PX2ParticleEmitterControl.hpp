/*
*
* �ļ�����	��	PX2ParticleEmitterControl.hpp
*
*/

#ifndef PX2PARTICLEEMITTERCONTROL_HPP
#define PX2PARTICLEEMITTERCONTROL_HPP

#include "PX2EffectPre.hpp"
#include "PX2Controller.hpp"
#include "PX2Particle.hpp"
#include "PX2TRecyclingArray.hpp"
#include "PX2EffectModule.hpp"

namespace PX2
{

	/// ���ӷ�����������
	/**
	* �û�����Ҫ����AttachController(...)���������������ӷ�������
	* ���ӷ���������ʱ�򣬻�Ĭ�ϴ����ÿ�������
	*/
	class ParticleEmitterController : public Controller
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(ParticleEmitterController);

	public:
		ParticleEmitterController ();
		virtual ~ParticleEmitterController ();

		enum DrawType
		{
			DT_NORMAL,
			DT_OBJECT,
			DT_MAX_TYPE
		};
		void SetDrawType (DrawType type);
		DrawType GetDrawType ();

		enum PlacerType
		{
			PT_BOX,
			PT_SPHERE,
			PT_COLUMN,
			PT_MAX_TYPE
		};
		void SetPlacerType (PlacerType type);
		PlacerType GetPlacerType ();
		void SetPlacerInLength (float val);
		void SetPlacerOutLength (float val);
		void SetPlacerInWidth (float val);
		void SetPlacerOutWidth (float val);
		void SetPlacerInHeight (float val);
		void SetPlacerOutHeight (float val);
		float GetPlacerInLength ();
		float GetPlacerOutLength ();
		float GetPlacerInWidth ();
		float GetPlacerOutWidth ();
		float GetPlacerInHeight ();
		float GetPlacerOutHeight ();

		void SetMaxNumParticles (int num);
		int GetMaxNumParticles () const;
		TRecyclingArray<Particle>* &GetArray ();

		// Event
		void AddModule (EffectModule *module);
		void RemoveModule (EffectModule *module);
		EffectModule *GetModule (int i);
		int GetNumModules ();
		bool IsHasModule (std::string moduleRttiName);

		void Reset ();

		// ��
		virtual bool Update (double applicationTime);

public_internal:
		void SetCurEmitRate (float rate);
		float GetCurEmitRate ();

	protected:
		void NewAParticle (double ctrlTime);
		void UpdateEmitterEvents (double ctrlTime);
		void UpdateParticleEvents (Particle &particle, double ctrlTime);

		TRecyclingArray<Particle> *mParticleArray;
		int mMaxNumParticles; // ��Ҫ�־û�

		int mCreatedParticlesQuantity; //< �ܹ���������������(����+����ȥ)
		float mNumNewParticlesExcess;
		float mCurEmitRate;

		PlacerType mPlacerType;
		float mPlacerInLength;
		float mPlacerOutLength;
		float mPlacerInWidth;
		float mPlacerOutWidth;
		float mPlacerInHeight;
		float mPlacerOutHeight;

		typedef std::vector<EffectModulePtr> ModuleList;
		ModuleList mModules;
	};

	PX2_REGISTER_STREAM(ParticleEmitterController);
	typedef Pointer0<ParticleEmitterController> ParticleEmitterControllerPtr;
#include "PX2ParticleEmitterControl.inl"

}

#endif