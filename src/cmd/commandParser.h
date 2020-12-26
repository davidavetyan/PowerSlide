#ifndef CMD_COMMANDPARSER_H
#define CMD_COMMANDPARSER_H

#include "command.h"
#include "commandLexer.h"

namespace CMD
{

class CommandParser
{
	class Error : public std::exception
	{
	public:
		Error() = default;
		Error(QString const& sError)
			: std::exception(sError.toStdString().c_str())
		{}
	};
	
public:
	std::unique_ptr<Command> parse(QString const& sCommand);

protected:
	void parseAddCommand(AddCommand* pAddCommand);

private:
	CommandLexer m_oLexer;
};

}

#endif