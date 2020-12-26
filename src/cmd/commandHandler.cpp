#include "commandHandler.h"

#include "core_slideEditor.h"

namespace CMD
{
	
CommandHandler::CommandHandler(std::shared_ptr<Core::SlideEditor> pSlideEditor)
	: m_pSlideEditor(pSlideEditor)
{
}

void CommandHandler::setSlideEditor(std::shared_ptr<Core::SlideEditor> pSlideEditor)
{
	m_pSlideEditor = pSlideEditor;
}

void CommandHandler::execute(QString const& sCommand, CommandResult* pResult)
{
	std::unique_ptr<Command> pCommand = m_oCommandParser.parse(sCommand);

	assert(pCommand);

	pCommand->execute(m_pSlideEditor.get(), pResult);

	m_oCommandHistory.addCommand(sCommand);
}

}