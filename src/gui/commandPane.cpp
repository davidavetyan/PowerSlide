#include "commandPane.h"

namespace GUI
{
	
CommandPane::CommandPane(QWidget* pParent)
	: QDockWidget(pParent)
{
	ui.setupUi(this);

	ui.textEdit->setReadOnly(true);
	ui.textEdit->setAcceptRichText(true);
	ui.textEdit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

	connect(ui.lineEdit, &QLineEdit::returnPressed, this, &CommandPane::onCommandEntered);

	m_pCommandHandler = std::make_shared<CMD::CommandHandler>();
}

void CommandPane::setCommandHandler(std::shared_ptr<CMD::CommandHandler> pCommandHandler)
{
	m_pCommandHandler = std::move(pCommandHandler);
}

void CommandPane::logCommandResult(CMD::CommandResult const& oResult)
{
	QTextCharFormat oFormat;
	oFormat.setForeground(QBrush(QColor(Qt::black)));
	
	switch (oResult.getType())
	{
	case CMD::CommandResult::Type::Normal:
		ui.textEdit->append("<font color=\"blue\"> # " + oResult.getReply() + "</font>");
		break;
	case CMD::CommandResult::Type::Warn:
		ui.textEdit->append("<font color=\"#FFAA00\"># Warning: " + oResult.getReply() + "</font>");
		break;
	case CMD::CommandResult::Type::Error:
		ui.textEdit->append("<font color=\"Red\">#!-> Error: " + oResult.getReply() + "</font>");
		break;
	default:
		break;
	}
	
	scrollTextEdit(QTextCursor::End);
	ui.textEdit->setCurrentCharFormat(oFormat);
}

void CommandPane::onCommandEntered()
{
	QString sText = ui.lineEdit->text();
	if (sText.isEmpty())
		return;

	ui.lineEdit->clear();

	CMD::CommandResult oResult;
	try
	{
		ui.textEdit->append(sText);
		
		m_pCommandHandler->execute(sText, &oResult);
	}
	catch(std::exception& exception)
	{
		oResult.setReply(exception.what());
		oResult.setType(CMD::CommandResult::Type::Error);
	}

	logCommandResult(oResult);
}

void CommandPane::scrollTextEdit(QTextCursor::MoveOperation op) const
{
	QTextCursor c = ui.textEdit->textCursor();
	c.movePosition(op);
	ui.textEdit->setTextCursor(c);
}
	
}
