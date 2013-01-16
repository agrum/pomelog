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

	m_codeMap.insert(1, "I");
	m_codeMap.insert(2, "D");
	m_codeMap.insert(4, "W");
	m_codeMap.insert(8, "E");

	m_msgMap.insert(100, "");
	m_msgMap.insert(200, "");
	m_msgMap.insert(300, "");
	m_msgMap.insert(400, "");
	m_msgMap.insert(401, "Null pointer");
	m_msgMap.insert(402, "Log file");
	m_msgMap.insert(403, "Extension file");
	m_msgMap.insert(404, "Signature");
	m_msgMap.insert(405, "Message");
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
		pLog::logE(&m_log, pLog::ERROR_LOG_FILE, "Can't open file");

	m_log.start();
}

int pLog::sign(const void* p_key, const QString& p_value){
	if(p_key == NULL || p_value.isNull())
		return logE(&m_log, pLog::ERROR_SIGNATURE, "Signature empty");

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

int pLog::logI(const void* p_sign, int p_msg, const QString& p_ext){
	if(check(p_sign, p_msg) != 1)
		return -1;

	return m_log.log(p_sign, INFO, p_msg, p_ext);
}

int pLog::logD(const void* p_sign, int p_msg, const QString& p_ext){
	if(check(p_sign, p_msg) != 1)
		return -1;

	return m_log.log(p_sign, DEBUG, p_msg, p_ext);
}

int pLog::logW(const void* p_sign, int p_msg, const QString& p_ext){
	if(check(p_sign, p_msg) != 1)
		return -1;

	return m_log.log(p_sign, WARNING, p_msg, p_ext);
}

int pLog::logE(const void* p_sign, int p_msg, const QString& p_ext){
	if(check(p_sign, p_msg) != 1)
		return -1;

	return m_log.log(p_sign, ERROR, p_msg, p_ext);
}

int pLog::check(const void* p_sign, int p_msg){
	if(p_sign == NULL)
		return logE(&m_log, pLog::ERROR_SIGNATURE, "Signature null");
	else if(!m_log.m_signatoryMap.contains(p_sign))
		return logE(&m_log, pLog::ERROR_SIGNATURE, "Signature doesn't exist");
	else if(!m_log.m_msgMap.contains(p_msg))
		return logE(&m_log, pLog::ERROR_MESSAGE, "Message doesn't exist");

	return 1;
}

int pLog::log(const void* p_signKey, Code p_code, int p_msg, const QString& p_ext){
	if((p_code & m_log.m_logLvl) == 0)
		return 0;

	QString addr = QString("%1").arg((int) p_signKey, 16, 16);
	QString sign = m_log.m_signatoryMap.value(p_signKey);
	QString code = m_log.m_codeMap.value(p_code);
	QString msg = m_log.m_msgMap.value(p_msg);
	QString logMsg = QString("(%1) %2 | %3::%4 | %5 | %6")
							.arg(code)
							.arg(QTime::currentTime().toString("hh:mm:ss.zzz"))
							.arg(sign)
							.arg(msg)
							.arg(addr)
							.arg(p_ext);

	qDebug() << logMsg;
	m_log.m_mutex.lock();
	m_log.m_pendingLog.enqueue(logMsg);
	m_log.m_mutex.unlock();

	return 0;
}

void pLog::run(){
	while(true){
		m_mutex.lock();
		while(!m_pendingLog.empty()){
			if(m_logFile.write(m_pendingLog.dequeue().toAscii()) == -1){
				exit(log(&m_log, pLog::ERROR, pLog::ERROR_LOG_FILE, "Writing error"));
			}
			m_logFile.close();
		}
		m_mutex.unlock();

		msleep(1000);
	}
}
