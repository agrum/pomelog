/*
	Copyright 2012 Thomas Le Guerroué-Drévillon
	This file is part of lemonGL.

	lemonGL is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	lemonGL is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with lemonGL.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PLOG_H_
#define PLOG_H_

#include <QThread>
#include <QMap>
#include <QQueue>
#include <QMutex>
#include <QWaitCondition>
#include <QTime>
#include <QFile>
#include <QDebug>

#define PLog_SIGN_LENGTH 10
#define PLog_LOG_LENGTH 30

class pLog : public QThread {

public:
	enum Code{
		INFO = 1,
		DEBUG = 2,
		WARNING = 4,
		ERROR = 8,
		ALL = 15
	};

	static void init(const QString&, int);

	static int sign(const void*, const QString&);
	static void unsign(const void*);

	static int logI(const void*, const QString& p_msg, bool p_waitTobeLogged = false);
	static int logD(const void*, const QString& p_msg, bool p_waitTobeLogged = false);
	static int logW(const void*, const QString& p_msg, bool p_waitTobeLogged = false);
	static int logE(const void*, const QString& p_msg, bool p_waitTobeLogged = false);

private:
	void run();

	static int check(const void*);
	int log(const void*, Code, const QString& p_msg, bool p_waitTobeLogged = false);

	pLog();
	~pLog();

private:
	static pLog m_log;

	QFile m_logFile;
	int m_logLvl;
	QMap<const void*, QString> m_signatoryMap;
	QMap<int, QString> m_codeMap;
	QQueue<QString> m_pendingLog;
	QMutex m_mutex;
	QWaitCondition m_waitEntryLogged;
	QWaitCondition m_waitQueueNonEmpty;
};

#endif /* PLog_H_ */
