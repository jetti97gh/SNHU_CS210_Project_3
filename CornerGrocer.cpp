/*
 * CornerGrocer.cpp
 *
 * Date: June 18, 2026
 * Developer: Albert Savage
 */

#include "CornerGrocer.h"
#include <string>

GroceryItem::GroceryItem(const std::string& t_name, int t_quantity)
{
	this->m_name = t_name;
	this->m_quantity = t_quantity;
}

GroceryItem::~GroceryItem()
{
}

std::string GroceryItem::getName() const
{
	return this->m_name;
}
int GroceryItem::getQuantity() const
{
	return this->m_quantity;
}

void GroceryItem::addItem()
{
	this->m_quantity += 1;
}
