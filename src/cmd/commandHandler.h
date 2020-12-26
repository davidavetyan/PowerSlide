#ifndef CMD_COMMANDHANDLER_H
#define CMD_COMMANDHANDLER_H

#include <QObject>

#include "commandHistory.h"
#include "commandParser.h"

namespace Core
{
	class SlideEditor;
}

namespace CMD
{
	
class CommandHandler : public QObject
{
public:
	CommandHandler(std::shared_ptr<Core::SlideEditor> pSlideEditor = nullptr);

	void setSlideEditor(std::shared_ptr<Core::SlideEditor> pSlideEditor);
	
	void execute(QString const& sCommand, CommandResult* pResult = nullptr);

private:
	CommandParser m_oCommandParser;
	CommandHistory m_oCommandHistory;
	std::shared_ptr<Core::SlideEditor> m_pSlideEditor;
};
	
}

#endif