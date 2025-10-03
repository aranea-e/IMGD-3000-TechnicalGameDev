#pragma once

// System includes
#include <string>

// Engine includes
#include "Manager.h"

#define LM df::LogManager::getInstance()

namespace df {

	const std::string LOGFILE_NAME = "dragonfly.log";

	class LogManager : public Manager {
	private:
		LogManager();						// Private (singleton)
		LogManager(LogManager const&);		// Don't allow copy
		void operator=(LogManager const&);	// Don't allow assignment

		bool m_do_flush;	// True flushes after each write
		FILE *m_p_f;		// Pointer to logfile 

	public:
		~LogManager();		// Closes logfile before shutdown
		static LogManager& getInstance(); // Get only instance 
		
		int startUp();		// Start up the LogManager and open dragonfly.log
		void shutDown();	// Shut down the LogManager and close logfile

		void setFlush(bool do_flush=true);	// Sets whether or not to flush file after each write

		int writeLog(const char *fmt, ...);	// Write to logfile (printf formatting)
											// Returns # of bytes written, or -1 if error
	};
}