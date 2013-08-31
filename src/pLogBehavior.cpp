#include "pLogBehavior.h"

pLogBehavior::pLogBehavior()
{
	pLog::sign(this, "no_name");
}

pLogBehavior::pLogBehavior(const QString p_name)
{
	pLog::sign(this, p_name);
}

pLogBehavior::~pLogBehavior(){
	pLog::unsign(this);
}

int pLogBehavior::logI(int p_msg, const QString& p_ext, bool p_waitTobeLogged){
    return pLog::logI(this, p_msg, p_ext, p_waitTobeLogged);
}

int pLogBehavior::logD(int p_msg, const QString& p_ext, bool p_waitTobeLogged){
    return pLog::logD(this, p_msg, p_ext, p_waitTobeLogged);
}

int pLogBehavior::logW(int p_msg, const QString& p_ext, bool p_waitTobeLogged){
    return pLog::logW(this, p_msg, p_ext, p_waitTobeLogged);
}

int pLogBehavior::logE(int p_msg, const QString& p_ext, bool p_waitTobeLogged){
    return pLog::logE(this, p_msg, p_ext, p_waitTobeLogged);
}
