#include "pLogBehavior.h"

#include "pLogException.h"

pLogBehavior::pLogBehavior()
{
	pLog::sign(this, "no_name");
}

pLogBehavior::pLogBehavior(const QString& p_name)
{
	pLog::sign(this, p_name);
}

pLogBehavior::~pLogBehavior(){
	pLog::unsign(this);
}

int
pLogBehavior::logI(const QString& p_msg, bool p_waitTobeLogged) const
{
	return pLog::logI(this, p_msg, p_waitTobeLogged);
}

int
pLogBehavior::logD(const QString& p_msg, bool p_waitTobeLogged) const
{
	return pLog::logD(this, p_msg, p_waitTobeLogged);
}

int
pLogBehavior::logW(const QString& p_msg, bool p_waitTobeLogged) const
{
	return pLog::logW(this, p_msg, p_waitTobeLogged);
}

int
pLogBehavior::logE(const QString& p_msg, bool p_waitTobeLogged) const
{
	//throw pLogException(p_msg);
	return pLog::logE(this, p_msg, p_waitTobeLogged);
}
