#include "IDataItem.h"
#include <memory>
IDataItem::IDataItem() : m_features(std::make_shared<FeaturesOfDataItem>())
{

}

IDataItem::~IDataItem()
{

}


