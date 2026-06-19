/*
 * CornerGrocer.h
 *
 * Date: June 18, 2026
 * Developer: Albert Savage
 */

#pragma once
#include <string>

class GroceryItem
{
public:
	// Creates a grocery item with a name and starting quantity.
	// @param t_name, Name of the grocery item.
	// @param t_quantity, Inital quantity of the item.
	// @returns, None.
	// @ throws, None.
	GroceryItem(const std::string& t_name, int t_quantity);

	// Destroys a GroceryItem object.
	// @returns, None.
	// @ throws, None.
	~GroceryItem();

	// Returns the name of the grocery item.
	// @returns Name of the grocery item.
	// @ throws, None.
	std::string getName() const;

	// Returns the quantity of the grocery item.
	// @returns Quantity of the grocery item.
	// @ throws, None.
	int getQuantity() const;

	// Increases the quantity of the grocery item by one.
	// @returns, None.
	// @throws, None.
	void addItem();

private:
	std::string m_name;
	int m_quantity;

};
