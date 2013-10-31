#ifndef PLOGBEHAVIOR_H
#define PLOGBEHAVIOR_H

#include "pLog.h"

class pLogBehavior
{
public:
    pLogBehavior();
	pLogBehavior(const QString&);
    virtual ~pLogBehavior();

protected:
	int logI(const QString& p_msg, bool p_waitTobeLogged = false) const;
	int logD(const QString& p_msg, bool p_waitTobeLogged = false) const;
	int logW(const QString& p_msg, bool p_waitTobeLogged = false) const;
	int logE(const QString& p_msg, bool p_waitTobeLogged = false) const;
};

#endif // PLOGBEHAVIOR_H
