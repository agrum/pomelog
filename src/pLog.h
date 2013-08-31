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
#define PLog_EXT_LENGTH 30

class pLog : public QThread {

public:
	enum Code{
		INFO = 1,
		DEBUG = 2,
		WARNING = 4,
		ERROR = 8,
		ALL = 15
	};

	enum Msg{
		INFO_NONE = 100,
		DEBUG_NONE = 200,
		WARNING_NONE = 300,
		ERROR_NONE = 400,
		ERROR_NULL = 401,
		ERROR_LOG_FILE = 402,
		ERROR_EXTEND_FILE = 403,
		ERROR_SIGNATURE = 404,
		ERROR_MESSAGE = 405
	};

	static void init(const QString&, int);
	static void extendMap(const QMap<int, QString>&);

	static int sign(const void*, const QString&);
	static void unsign(const void*);

	static int logI(const void*, int, const QString& p_ext = "", bool p_waitTobeLogged = false);
	static int logD(const void*, int, const QString& p_ext = "", bool p_waitTobeLogged = false);
	static int logW(const void*, int, const QString& p_ext = "", bool p_waitTobeLogged = false);
	static int logE(const void*, int, const QString& p_ext = "", bool p_waitTobeLogged = false);

private:
	void run();

	static int check(const void*, int);
	int log(const void*, Code, int, const QString& p_ext = "", bool p_waitTobeLogged = false);

	pLog();
	~pLog();

private:
	static pLog m_log;

	QFile m_logFile;
	int m_logLvl;
	QMap<const void*, QString> m_signatoryMap;
	QMap<int, QString> m_codeMap;
	QMap<int, QString> m_msgMap;
	QQueue<QString> m_pendingLog;
	QMutex m_mutex;
	QWaitCondition m_waitEntryLogged;
	QWaitCondition m_waitQueueNonEmpty;
};

#endif /* PLog_H_ */
