#ifndef GUI_COMMANDPANE_H
#define GUI_COMMANDPANE_H

#include "ui_CommandPane.h"

#include "cmd_commandHandler.h"

namespace GUI
{

class CommandPane : public QDockWidget
{
	Q_OBJECT
public:
	CommandPane(QWidget* pParent = nullptr);

	void setCommandHandler(std::shared_ptr<CMD::CommandHandler> pCommandHandler);
	
protected:
	void logCommandResult(CMD::CommandResult const& oResult);

protected slots:
	void onCommandEntered();

private:
	void scrollTextEdit(QTextCursor::MoveOperation op) const;

private:
	Ui::CommandDockWidget ui;
	std::shared_ptr<CMD::CommandHandler> m_pCommandHandler;
};

}

#endif