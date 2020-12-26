#include "shapeFactory.h"

namespace Core
{

ShapeFactory::ShapeFactory()
{
	m_mapNameToPtr["line"] = std::make_unique<Line>(0, 0, 0, 0);
	m_mapNameToPtr["rect"] = std::make_unique<Rectangle>(0, 0, 0, 0);
	m_mapNameToPtr["ellipse"] = std::make_unique<Ellipse>(QPoint(0, 0), 0, 0);
}

std::unique_ptr<IShape> ShapeFactory::create(QString const& sType)
{
	if (m_mapNameToPtr.find(sType.toLower()) != m_mapNameToPtr.end())
		return m_mapNameToPtr[sType.toLower()]->clone();

	return nullptr;
}

std::unique_ptr<IShape> ShapeFactory::create(QString const& sType, QVector<int> const& vData)
{
	if (m_mapNameToPtr.find(sType.toLower()) == m_mapNameToPtr.end())
		throw std::exception(QString("Invalid shape type: %1").arg(sType).toStdString().c_str());

	QString sTypeLower = sType.toLower();
	if (sType.toLower() == "line")
	{
		if (vData.size() != 4)
			throw std::exception("Invalid data provided for shape creation");
		return std::make_unique<Line>(vData[0], vData[1], vData[2], vData[3]);
	}
	if (sType.toLower() == "rect")
	{
		if (vData.size() != 4)
			throw std::exception("Invalid data provided for shape creation");
		return std::make_unique<Rectangle>(vData[0], vData[1], vData[2], vData[3]);
	}
	if (sType.toLower() == "ellipse")
	{
		if (vData.size() != 4)
			throw std::exception("Invalid data provided for shape creation");
		return std::make_unique<Ellipse>(QPoint(vData[0], vData[1]), vData[2], vData[3]);
	}

	return nullptr;
}

bool ShapeFactory::registerShape(QString const& sType, std::shared_ptr<IShape> pShape)
{
	QString sTypeLower = sType.toLower();
	if (m_mapNameToPtr.find(sTypeLower) != m_mapNameToPtr.end())
		return false;

	m_mapNameToPtr[sTypeLower] = pShape->clone();
	
	return true;
}

ShapeFactory& ShapeFactory::getInstance()
{
	static ShapeFactory shapeFactory;
	return shapeFactory;
}
	
}
