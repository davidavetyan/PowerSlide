#ifndef CMD_COMMAND_H
#define CMD_COMMAND_H

#include <QColor>

namespace Core
{
	class SlideEditor;
}

namespace CMD
{

class CommandResult
{

public:
	enum class Type
	{
		None,
		Normal,
		Warn,
		Error
	};

	CommandResult();
	CommandResult(QString sReply, Type eType);

	void setReply(QString sReply);
	QString getReply() const;

	void setType(Type eType);
	Type getType() const;

private:
	QString m_sReply;
	Type m_eType;
};

class Command
{
public:
	virtual void execute(Core::SlideEditor* pSlideEditor, CommandResult* pResult = nullptr) = 0;
};

class AddCommand : public Command
{
public:
	AddCommand();
	void execute(Core::SlideEditor* pSlideEditor, CommandResult* pResult = nullptr) override;

	QString m_sShapeType;
	QVector<int> m_vShapeData;
	QColor m_clrLine;
	QColor m_clrFill;
	Qt::PenStyle m_oLineStyle;
	int m_nLineWidth;
};

class ExitCommand : public Command
{
public:
	void execute(Core::SlideEditor* pSlideEditor, CommandResult* pResult = nullptr) override;
};

class UndoCommand : public Command
{
public:
	void execute(Core::SlideEditor* pSlideEditor, CommandResult* pResult = nullptr) override;
};

class RedoCommand : public Command
{
public:
	void execute(Core::SlideEditor* pSlideEditor, CommandResult* pResult = nullptr) override;
};
	
inline CommandResult::CommandResult()
	: m_sReply(""),
	m_eType(Type::None)
{

}

inline CommandResult::CommandResult(QString sReply, Type eType)
	: m_sReply(sReply),
	m_eType(eType)
{

}

}

#endif