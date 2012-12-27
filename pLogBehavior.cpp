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
