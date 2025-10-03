#include <stdio.h>
#include <stdarg.h>

#include "LogManager.h"

df::LogManager::LogManager() {	// Private, only called by getInstance()
	setType("LogManager");
	setFlush(false);
	startUp();
}

df::LogManager::~LogManager()
{
	shutDown();
}

df::LogManager &df::LogManager::getInstance()
{
	static LogManager lm;	// Static variable persists after running
	return lm;
}

int df::LogManager::startUp() {
	m_p_f = fopen(LOGFILE_NAME.c_str(), "w");
	return 0;
}

void df::LogManager::shutDown() {
	fclose(m_p_f);
}

void df::LogManager::setFlush(bool do_flush)
{
	m_do_flush = do_flush;
}

int df::LogManager::writeLog(const char* fmt, ...)
{	// Uses printf notation
	fprintf(m_p_f, "Message : ");
	va_list args;
	va_start(args, fmt);
	vfprintf(m_p_f, fmt, args);
	va_end(args);

	if (m_do_flush) fflush(m_p_f); // Flushes if and only if m_do_flush has been set to true

	return 0;
}