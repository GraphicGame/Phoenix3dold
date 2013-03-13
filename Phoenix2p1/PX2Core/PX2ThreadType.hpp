/*
*
* �ļ�����	��	PX2ThreadType.hpp
*
*/

#ifndef PX2THREADTYPE_HPP
#define PX2THREADTYPE_HPP

#include "PX2CorePre.hpp"

#if (defined(_WIN32) || defined(WIN32)) && !defined(PX2_USE_PTHREAD)
//----------------------------------------------------------------------------
// ��Windows�У�Mutex��һ��HANDLE����Ҫ����<windows.h>�������ᱩ¶����
// Windows�ӿڡ�����������void*����HANDLE��
//----------------------------------------------------------------------------
namespace PX2
{
	typedef void* ThreadType;
}
//----------------------------------------------------------------------------
#elif defined(__LINUX__) || defined(__APPLE__) || defined(__ANDROID__) || defined(PX2_USE_PTHREAD)
//----------------------------------------------------------------------------
// ��Linux/Apple�У�pthread.h���������ԭʼ�������ݣ�����pthread.h���ᱩ¶
// ����Ľӿڡ�
//----------------------------------------------------------------------------
#include <pthread.h>
namespace PX2
{
	typedef pthread_t ThreadType;
}
//----------------------------------------------------------------------------
#else
//----------------------------------------------------------------------------
// ����ƽ̨���߳�û��֧��
//----------------------------------------------------------------------------
#error Other platforms not yet implemented.
#endif

#endif
