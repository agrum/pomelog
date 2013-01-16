#ifndef PLOGBEHAVIOR_H
#define PLOGBEHAVIOR_H

#include "pLog.h"

class pLogBehavior
{
public:
    pLogBehavior();
	pLogBehavior(const QString);
	~pLogBehavior();

	int logI(int, const QString& p_ext = "");
	int logD(int, const QString& p_ext = "");
	int logW(int, const QString& p_ext = "");
	int logE(int, const QString& p_ext = "");
};

#endif // PLOGBEHAVIOR_H
