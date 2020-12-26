#ifndef CMD_COMMANDLEXER_H
#define CMD_COMMANDLEXER_H

#include <QString>

namespace CMD
{
	
	class CommandLexer
	{
	public:
		inline CommandLexer(QString const& sInput = "");

		void setInput(QString const& sInput);

		inline int getCurrentPos() const;
		inline int getPreviousPos() const;
		inline QString const& input() const;

		QString getToken();
		
		inline char peekChar(int nOffset = 0) const;
		char getChar(bool bSkipWhiteSpaces);

		inline void fixCurrentPos();
		inline void setCurrentPos(int nPos);

		inline bool isFinished() const;
		inline bool isFinished(bool bSkipWhiteSpaces);
		inline bool isWhiteSpace() const; 

		void skip(int nCharCount);
		void skipWhiteSpaces();

	public:
		// Static helpers
		inline static bool isSpace(char const ch);
		inline static bool isAlphaNum(char const ch);
		inline static bool isAlpha(char const ch);
		inline static bool isNum(char const ch);

		inline static bool isAlphaNum(QString const& str);
		inline static bool isAlpha(QString const& str);
		inline static bool isNum(QString const& str);

	private:
		int m_nPos;
		int m_nPrevPos;
		QString	m_sInput;
	};

	inline CommandLexer::CommandLexer(QString const& sInput)
		: m_nPos(0), m_nPrevPos(0), m_sInput(sInput)
	{
	}

	inline int CommandLexer::getCurrentPos() const
	{
		return m_nPos;
	}

	inline int CommandLexer::getPreviousPos() const
	{
		return m_nPrevPos;
	}

	inline QString const& CommandLexer::input() const
	{
		return m_sInput;
	}

	inline bool CommandLexer::isFinished() const
	{
		return (m_nPos >= m_sInput.size());
	}

	inline bool CommandLexer::isFinished(bool bSkipWhiteSpaces)
	{
		if (bSkipWhiteSpaces)
			skipWhiteSpaces();
		return (m_nPos >= m_sInput.size());
	}

	inline bool CommandLexer::isWhiteSpace() const
	{
		return m_nPos < m_sInput.size() && isSpace(m_sInput.at(m_nPos).toLatin1());
	}

	inline char CommandLexer::peekChar(int nOffset) const
	{
		char ch = 0;
		if (m_nPos + nOffset < m_sInput.size())
			ch = m_sInput.at(m_nPos + nOffset).toLatin1();
		return ch;
	}

	inline void CommandLexer::fixCurrentPos()
	{
		m_nPrevPos = m_nPos;
	}

	inline void CommandLexer::setCurrentPos(int nPos)
	{
		m_nPos = nPos;
	}

	// helper methods
	
	inline bool CommandLexer::isSpace(char const ch)
	{
		return (std::isspace(ch) != 0);
	}

	inline bool CommandLexer::isAlphaNum(char const ch)
	{
		return ((ch >= 'a' && ch <= 'z') ||
			(ch >= 'A' && ch <= 'Z') ||
			(ch >= '0' && ch <= '9') ||
			(ch == '_'));
	}

	inline bool CommandLexer::isAlpha(char const ch)
	{
		return ((ch >= 'a' && ch <= 'z') ||
			(ch >= 'A' && ch <= 'Z') ||
			(ch == '_'));
	}

	inline bool CommandLexer::isNum(char const ch)
	{
		return ((ch >= '0' && ch <= '9'));
	}

	inline bool CommandLexer::isAlphaNum(QString const& str)
	{
		std::string s = str.toStdString();
		for (auto ch : s)
		{
			if (!isAlphaNum(ch))
				return false;
		}

		return true;
	}

	inline bool CommandLexer::isAlpha(QString const& str)
	{
		std::string s = str.toStdString();
		for (auto ch : s)
		{
			if (!isAlpha(ch))
				return false;
		}

		return true;
	}

	inline bool CommandLexer::isNum(QString const& str)
	{
		std::string s = str.toStdString();
		for (auto ch : s)
		{
			if (!isNum(ch))
				return false;
		}

		return true;
	}

}

#endif