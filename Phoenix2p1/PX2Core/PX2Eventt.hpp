/*
*
* �ļ�����	��	PX2Eventt.hpp
*
*/

#ifndef PX2EVENTT_HPP
#define PX2EVENTT_HPP

#include "PX2CorePre.hpp"

#if (defined(_WIN32) || defined(WIN32))
typedef void* EventtType;
#elif defined(__LINUX__) || defined(__APPLE__) || defined(__ANDROID__)
#include <pthread.h>
#endif

namespace PX2
{

	/// �ź�
	/**
	* �ź���һ���߳�ͬ���ṹ��ͨ��һ���̼߳�������źţ������̵߳ȴ�
	* ����źű�����
	*/
	class Eventt
	{
	public:
		/// ����һ���¼������autoResetΪtrue����Wait()�ɹ����¼��Զ�Reset��
		/// ��Ϊδ����״̬��
		Eventt (bool autoReset=true);
		~Eventt ();

		/// �����¼������autoResetΪtrue��ֻ��һ���ȴ����̱߳��������У����Ϊ
		/// false�����еȴ����Դ涼���������С�
		void Set ();

		/// �ȴ��¼�������
		void Wait ();

		/// ��һ��ʱ���ڵȴ��¼��������������˷���true�����򷵻�false
		bool Wait (long milliseconds);

		/// �����¼���δ����״̬
		void Reset ();

	protected:
		bool mIsAutoReset;

#if (defined(_WIN32) || defined(WIN32))
		EventtType mEvent;
#elif defined(__LINUX__) || defined(__APPLE__) || defined(__ANDROID__)
		volatile bool mState;
		pthread_mutex_t mMutex;
		pthread_cond_t mCond;
#endif

	private:
		Eventt (const Eventt&);
		Eventt& operator = (const Eventt&);
	};

}

#endif