#ifndef PLOGBEHAVIOR_H
#define PLOGBEHAVIOR_H

#include "pLog.h"

class pLogBehavior
{
public:
    pLogBehavior();
	pLogBehavior(const QString);
    virtual ~pLogBehavior();

	int logI(const QString& p_msg, bool p_waitTobeLogged = false);
	int logD(const QString& p_msg, bool p_waitTobeLogged = false);
	int logW(const QString& p_msg, bool p_waitTobeLogged = false);
	int logE(const QString& p_msg, bool p_waitTobeLogged = false);
};

#endif // PLOGBEHAVIOR_H
