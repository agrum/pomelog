#ifndef PLOGBEHAVIOR_H
#define PLOGBEHAVIOR_H

#include "pLog.h"

class pLogBehavior
{
public:
    pLogBehavior();
	pLogBehavior(const QString);
    virtual ~pLogBehavior();

    int logI(int, const QString& p_ext = "", bool p_waitTobeLogged = false);
    int logD(int, const QString& p_ext = "", bool p_waitTobeLogged = false);
    int logW(int, const QString& p_ext = "", bool p_waitTobeLogged = false);
    int logE(int, const QString& p_ext = "", bool p_waitTobeLogged = false);
};

#endif // PLOGBEHAVIOR_H
