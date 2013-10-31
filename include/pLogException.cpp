#include "pLogException.h"

pLogException::pLogException(const QString& p_msg) throw():
	m_msg(p_msg)
{

}

pLogException::pLogException(const pLogException& p_e) throw():
	m_msg(p_e.m_msg)
{

}

pLogException&
pLogException::operator=(const pLogException& p_e) throw()
{
	m_msg = p_e.m_msg;

	return *this;
}

const char*
pLogException::what() const throw()
{
	return (m_msg + " (Pomelog)").toLatin1().constData();
}
