#include "commandParser.h"

#include <QHash>

namespace CMD
{
	QHash<QString, Qt::PenStyle> mapStrToLineType =
	{
		{"none", Qt::NoPen},
		{"solid", Qt::SolidLine},
		{"dash", Qt::DashLine},
		{"dot", Qt::DotLine},
		{"dashdot", Qt::DashDotLine},
		{"dashdotdot", Qt::DashDotDotLine}
	};
	
std::unique_ptr<Command> CommandParser::parse(QString const& sCommand)
{
	m_oLexer.setInput(sCommand);

	std::unique_ptr<Command> pCommand;

	QString sCommandType = m_oLexer.getToken();
	if (sCommandType == "add")
	{
		pCommand = std::make_unique<AddCommand>();

		AddCommand* pAddCommand = dynamic_cast<AddCommand*>(pCommand.get());

		parseAddCommand(pAddCommand);
	}
	else if (sCommandType == "undo")
	{
		pCommand = std::make_unique<UndoCommand>();

		m_oLexer.skipWhiteSpaces();
		if (!m_oLexer.isFinished())
			throw Error("Undo command shouldn't be followed by other symbols");
	}
	else if (sCommandType == "redo")
	{
		pCommand = std::make_unique<RedoCommand>();

		m_oLexer.skipWhiteSpaces();
		if (!m_oLexer.isFinished())
			throw Error("Redo command shouldn't be followed by other symbols");
	}
	else if (sCommandType == "exit")
	{
		pCommand = std::make_unique<ExitCommand>();

		m_oLexer.skipWhiteSpaces();
		if (!m_oLexer.isFinished())
			throw Error("Exit command shouldn't be followed by other symbols");
	}
	else
		throw Error(QString("Unrecognized command: %1").arg(sCommandType));

	return pCommand;
}

void CommandParser::parseAddCommand(AddCommand* pAddCommand)
{
	if (!pAddCommand)
		return;
	
	bool bShapeProvided = false;
	while (!m_oLexer.isFinished())
	{
		char ch = m_oLexer.getChar(true);
		if (ch != '-')
			throw Error("Missing \"-\" before an argument name");

		QString sArgument = m_oLexer.getToken();
		if (sArgument == "shape")
		{
			QString sShapeType = m_oLexer.getToken();
			pAddCommand->m_sShapeType = sShapeType;

			try
			{
				m_oLexer.skipWhiteSpaces();
				while (!m_oLexer.isFinished() && !m_oLexer.isWhiteSpace())
				{
					int nData = std::stoi(m_oLexer.getToken().toStdString());
					pAddCommand->m_vShapeData.append(nData);
					if (m_oLexer.peekChar() == ',')
					{
						Q_UNUSED(m_oLexer.getChar(false));
						m_oLexer.skipWhiteSpaces();
					}
				}
			}
			catch(...)
			{
				throw Error("Invalid data for \"shape\" argument");
			}
			
			bShapeProvided = true;
		}
		else if (!bShapeProvided)
		{
			throw Error("\"shape\" argument should be provided to the add command first");
		}
		else if (sArgument == "color")
		{
			QString sColor = m_oLexer.getToken();
			if (sColor == "#")
				sColor.append(m_oLexer.getToken());

			QColor clrLine(sColor);
			if (!clrLine.isValid())
				throw Error("Invalid data for \"color\" argument");

			pAddCommand->m_clrLine = clrLine;
		}
		else if (sArgument == "fill")
		{
			QString sColor = m_oLexer.getToken();
			if (sColor == "#")
				sColor.append(m_oLexer.getToken());

			QColor clrFill(sColor);
			if (!clrFill.isValid())
				throw Error("Invalid data for \"fill\" argument");

			pAddCommand->m_clrFill = clrFill;
		}
		else if (sArgument == "linetype")
		{
			QString sLineType = m_oLexer.getToken();
			if (mapStrToLineType.find(sLineType.toLower()) == mapStrToLineType.end())
				throw Error("Invalid data for \"linetype\" argument");

			pAddCommand->m_oLineStyle = mapStrToLineType[sLineType.toLower()];
		}
		else if (sArgument == "linewidth")
		{
			QString sLineWidth = m_oLexer.getToken();
			try
			{
				int nLineWidth = std::stoi(sLineWidth.toStdString());
				if (nLineWidth < 0 || nLineWidth > 20)
					throw Error(QString("Value for \"linewidth\" argument should be in range [0, 20]: %1").arg(nLineWidth));
				pAddCommand->m_nLineWidth = nLineWidth;
			}
			catch(...)
			{
				throw Error(QString("Invalid value for \"linewidth\" argument: %1").arg(sLineWidth));
			}
		}
		else
			throw Error(QString("Unknown argument name: %1").arg(sArgument));

		m_oLexer.skipWhiteSpaces();
	}
}
	
}
