/*
*
* �ļ�����	��	PX2LogOutputWindowHandler.hpp
*
*/

#ifndef PX2LOGOUTPUTWINDOWHANDLER_HPP
#define PX2LOGOUTPUTWINDOWHANDLER_HPP

#include "PX2Log.hpp"

namespace PX2
{

	/// ��������Դ��ھ��
	class OutputWindowHandler : public LogHandler
	{
	public:
		OutputWindowHandler (unsigned int levels);
		virtual ~OutputWindowHandler ();

		virtual bool Handle (const char *filename, int line,
			unsigned int level,	const char *str);
	};

}

#endif