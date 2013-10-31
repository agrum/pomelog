#ifndef PLOGEXCEPTION_H
#define PLOGEXCEPTION_H

#include <exception>
#include <QString>

class pLogException : public std::exception
{
public:
	pLogException(const QString& p_msg) throw();
	pLogException(const pLogException& p_e) throw();
	pLogException& operator=(const pLogException& p_e) throw();

	~pLogException() throw() {}

	const char* what() const throw();

private:
	QString m_msg;
};

#endif // PLOGEXCEPTION_H
