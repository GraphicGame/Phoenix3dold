/*
*
* �ļ�����	��	PX2LogFileHandler.hpp
*
*/

#ifndef PX2LOGFILEHANDLER_HPP
#define PX2LOGFILEHANDLER_HPP

#include "PX2Log.hpp"

namespace PX2
{

	/// �ļ���־���
	class FileLogHandler : public LogHandler
	{
	public:
		FileLogHandler (unsigned int levels, const char *filename);
		virtual ~FileLogHandler ();

		virtual bool Handle (const char *filename, int line, 
			unsigned int level,	const char *str);

	private:
		FILE *mFile;
	};

}

#endif