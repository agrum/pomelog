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

#include "pLog.h"

pLog pLog::m_log;

pLog::pLog(){
	m_logLvl = ALL;
	sign(this, "pLog");

	m_codeMap.insert(1, "II");
	m_codeMap.insert(2, "DD");
	m_codeMap.insert(4, "WW");
	m_codeMap.insert(8, "EE");
}

pLog::~pLog(){
	m_logFile.close();
	terminate();
	wait();
}

void pLog::init(const QString& p_logPath, int p_logLvl){
	m_log.m_logFile.setFileName(p_logPath);
	m_log.m_logLvl = p_logLvl;

	if (!m_log.m_logFile.open(QIODevice::WriteOnly | QIODevice::Text))
		pLog::logE(&m_log, "Can't open log file");

	m_log.start();
}

int pLog::sign(const void* p_key, const QString& p_value){
	if(p_key == NULL || p_value.isNull())
		return logE(&m_log, "Try to sign in log registry with empty signature");

	QString value = p_value;
	while(value.length() < PLog_SIGN_LENGTH)
		value = ' ' + value;
	if(value.length() > PLog_SIGN_LENGTH)
		value = value.left(PLog_SIGN_LENGTH);

	m_log.m_signatoryMap.insert(p_key, value);

	return 1;
}

void pLog::unsign(const void* p_key){
	m_log.m_signatoryMap.remove(p_key);
}

int pLog::logI(const void* p_sign, const QString& p_msg, bool p_waitTobeLogged){
	if(check(p_sign) != 1)
		return -1;

	return m_log.log(p_sign, INFO, p_msg, p_waitTobeLogged);
}

int pLog::logD(const void* p_sign, const QString& p_msg, bool p_waitTobeLogged){
	if(check(p_sign) != 1)
		return -1;

	return m_log.log(p_sign, DEBUG, p_msg, p_waitTobeLogged);
}

int pLog::logW(const void* p_sign, const QString& p_msg, bool p_waitTobeLogged){
	if(check(p_sign) != 1)
		return -1;

	return m_log.log(p_sign, WARNING, p_msg, p_waitTobeLogged);
}

int pLog::logE(const void* p_sign, const QString& p_msg, bool p_waitTobeLogged){
	if(check(p_sign) != 1)
		return -1;

	return m_log.log(p_sign, ERROR, p_msg, p_waitTobeLogged);
}

int pLog::check(const void* p_sign){
	if(p_sign == NULL)
		return logE(&m_log, "Try to log with empty signature");
	else if(!m_log.m_signatoryMap.contains(p_sign))
		return logE(&m_log, "Try to log with non recorded signature");

	return 1;
}

int pLog::log(const void* p_signKey, Code p_code, const QString& p_msg, bool p_waitTobeLogged){
	if((p_code & m_log.m_logLvl) == 0)
		return 0;

    QString addr = QString("%1").arg((long) p_signKey, 16, 16);
    QString sign = m_signatoryMap.value(p_signKey);
	QString code = m_codeMap.value(p_code);
	QString logMsg = QString("(%1) %2 | %3 | %4 | %5")
							.arg(code)
							.arg(QTime::currentTime().toString("hh:mm:ss.zzz"))
							.arg(sign)
							.arg(addr)
							.arg(p_msg);

	qDebug() << logMsg;
    m_mutex.lock();
        m_pendingLog.enqueue(logMsg + "\n");
        m_waitQueueNonEmpty.wakeAll();
        if(p_waitTobeLogged)
            m_waitEntryLogged.wait(&m_mutex);
    m_mutex.unlock();

	return 0;
}

void pLog::run(){
	while(true){
		m_mutex.lock();
            while(!m_pendingLog.empty()){
                if(m_logFile.write(m_pendingLog.dequeue().toLatin1()) == -1){
					exit(0);
                }
                m_logFile.flush();
            }
            m_waitEntryLogged.wakeAll();
			m_waitQueueNonEmpty.wait(&m_mutex);
        m_mutex.unlock();
	}
}
