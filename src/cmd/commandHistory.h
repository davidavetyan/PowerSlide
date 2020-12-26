#ifndef CMD_COMMANDHISTORY_H
#define CMD_COMMANDHISTORY_H

#include <QStringList>

class CommandHistory
{
public:
	void addCommand(QString const& sCommand);

private:
	QStringList m_lstCommands;
};

inline void CommandHistory::addCommand(QString const& sCommand)
{
	m_lstCommands.append(sCommand);
}

#endif