#include "command.h"
#include <QCoreApplication>

#include "core_action.h"
#include "core_shapeFactory.h"
#include "core_slideEditor.h"

namespace CMD
{
	
void CommandResult::setReply(QString sReply)
{
	m_sReply = sReply;
}

QString CommandResult::getReply() const
{
	return m_sReply;
}

void CommandResult::setType(Type eType)
{
	m_eType = eType;
}

CommandResult::Type CommandResult::getType() const
{
	return m_eType;
}

AddCommand::AddCommand()
	: m_oLineStyle(Qt::CustomDashLine),
	m_nLineWidth(-1)
{
}

void AddCommand::execute(Core::SlideEditor* pSlideEditor, CommandResult* pResult)
{
	Q_UNUSED(pResult);

	if (!pSlideEditor)
		return;

	auto pSlideCollection = pSlideEditor->getSlideCollection();
	if (!pSlideCollection)
		return;

	auto pActiveSlide = pSlideCollection->getActiveSlide();
	if (!pActiveSlide)
		return;
	
	auto pAction = std::make_unique<Core::AddAction>(pActiveSlide);

	Core::ShapeFactory& oShapeFactory = Core::ShapeFactory::getInstance();
	auto pShape = std::shared_ptr<Core::IShape>(oShapeFactory.create(m_sShapeType, m_vShapeData).release());

	Core::SShapeProperties& oShapeProperties = pShape->properties();
	if (m_clrLine.isValid())
		oShapeProperties.m_oPen.setColor(m_clrLine);
	
	if (m_clrFill.isValid())
		oShapeProperties.m_clrFill = m_clrFill;

	if (m_oLineStyle != Qt::CustomDashLine)
		oShapeProperties.m_oPen.setStyle(m_oLineStyle);

	if (m_nLineWidth != -1)
		oShapeProperties.m_oPen.setWidth(m_nLineWidth);
	
	pAction->setShape(pShape);

	pSlideEditor->run(std::move(pAction));
}

void ExitCommand::execute(Core::SlideEditor* pSlideEditor, CommandResult* pResult)
{
	Q_UNUSED(pSlideEditor);
	Q_UNUSED(pResult);
	QCoreApplication::instance()->quit();
}

void UndoCommand::execute(Core::SlideEditor* pSlideEditor, CommandResult* pResult)
{
	if (!pSlideEditor)
		return;

	bool bResult = pSlideEditor->undo();
	if (!bResult && pResult)
	{
		pResult->setType(CommandResult::Type::Warn);
		pResult->setReply("No action to undo");
	}
}

void RedoCommand::execute(Core::SlideEditor* pSlideEditor, CommandResult* pResult)
{
	if (!pSlideEditor)
		return;

	bool bResult = pSlideEditor->redo();
	if (!bResult && pResult)
	{
		pResult->setType(CommandResult::Type::Warn);
		pResult->setReply("No action to redo");
	}
}

}
