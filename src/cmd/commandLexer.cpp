#include "commandLexer.h"

namespace CMD
{

void CommandLexer::setInput(QString const& sInput)
{
	m_nPos = 0;
	m_nPrevPos = 0;
	m_sInput = sInput;
}

QString CommandLexer::getToken()
{
	QString sToken;

	skipWhiteSpaces();
	fixCurrentPos();

	while (m_nPos < m_sInput.size() && /*!isSpace(m_sInput.at(m_nPos).toLatin1())*/ isAlphaNum(m_sInput.at(m_nPos)))
		sToken.push_back(m_sInput.at(m_nPos++));

	if (getCurrentPos() == getPreviousPos() && !isFinished())
		sToken.push_back(getChar(true));

	return sToken;
}

char CommandLexer::getChar(bool bSkipWhiteSpaces)
{
	char ch = 0;

	if (bSkipWhiteSpaces)
		skipWhiteSpaces();

	fixCurrentPos();

	if (!isFinished())
	{
		ch = m_sInput.at(m_nPos).toLatin1();
		++m_nPos;
	}
	return ch;
}

void CommandLexer::skip(int nCharCount)
{
	if (m_nPos + nCharCount < m_sInput.size())
		m_nPos += nCharCount;
	else
		m_nPos = m_sInput.size();
}

void CommandLexer::skipWhiteSpaces()
{
	while (isWhiteSpace())
		++m_nPos;
}

}