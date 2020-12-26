#ifndef CORE_SHAPEFACTORY_H
#define CORE_SHAPEFACTORY_H

#include <memory>
#include <unordered_map>

#include "shape.h"

namespace Core
{

class ShapeFactory
{
public:
	ShapeFactory();
	ShapeFactory(ShapeFactory const&) = delete;
	ShapeFactory& operator=(ShapeFactory const&) = delete;
	
	std::unique_ptr<IShape> create(QString const& sType);
	std::unique_ptr<IShape> create(QString const& sType, QVector<int> const& vData);

	bool registerShape(QString const& sType, std::shared_ptr<IShape> pShape);

	static ShapeFactory& getInstance();

private:
	std::unordered_map<QString, std::unique_ptr<IShape>> m_mapNameToPtr;
};
	
}

#endif