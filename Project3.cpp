/*
 * Project3.cpp
 *
 * Date: June 18, 2026
 * Developer: Albert Savage
 */

#include "CornerGrocer.h"
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <iomanip>

// Displays the main menu and validates user input.
// @returns Menu options.
// @throws std::ios_base::failure if invalid input is entered.
int displayMenu();

// Reads input file and builds the inventory map.
// Existing inventory data is cleared before rebuilding.
// @param t_items, Map containing grocery items and frequencies.
// @returns, None.
// @throws, None.
void buildInventory(std::map<std::string, GroceryItem*>& t_items);

// Creates a backup file containing grocery item frequencies.
// @param t_items, Map containing grocery items and frequencies.
// @returns, None.
// @throws, None.
void backupInventory(std::map<std::string, GroceryItem*>& t_items);

// Releases dynamically allocated GroceryItem objects and clears the map.
// @param t_items, Map containing grocery item pointers.
// @returns, None.
// @throws, None.
void clearInventory(std::map<std::string, GroceryItem*>& t_items);

// Converts a string to title case.
// @param t_text, String to convert.
// @returns, Title cased string.
// @throws, None.
std::string makeTitleCase(std::string t_text);

int main()
{
	// menu constants
	const int  FIND_AN_ITEM = 1;
	const int  ITEMS_PURCHASED_TODAY = 2;
	const int  HISTOGRAM_PURCHASED_TODAY = 3;
	const int  EXIT_PROGRAM = 4;

	std::map<std::string, GroceryItem*> items;
	
	std::string itemName;
	std::string findMe;
	
	int menuChoice = 0;

	// Display menu and take action
	while (menuChoice != 4)
	{
		std::map<std::string, GroceryItem*>::iterator it;
		const int TITLE_WIDTH = 30;
		const int COLUMN_WIDTH = 20; 
		const int SEP_WIDTH = 3;
		const std::string ITEM_1_TITLE = "Purchased Today";
		const std::string ITEM_2_TITLE = "All Items Purchased Today";
		const std::string ITEM_3_TITLE = "Histogram of Items Purchased Today";
		menuChoice = displayMenu();
		switch (menuChoice)
		{
		case FIND_AN_ITEM:
			
			buildInventory(items);

			backupInventory(items);

			std::cout << "Enter an item to check: ";
			std::cin.ignore(100, '\n');
			
			getline(std::cin, findMe);

			// Convert user input to match format used in the inventory file.
			findMe = makeTitleCase(findMe);

			if (items.count(findMe) == 1)
			{
				// Set color to green
				std::cout << "\033[32m";
				std::cout << std::endl
					<< ITEM_1_TITLE
					<< std::endl
					<< items.at(findMe)->getQuantity() << " "
					<< items.at(findMe)->getName()
					<< std::endl << std::endl;
				// Reset color to default
				std::cout << "\033[0m";
			}
			else
			{
				// Set color to green
				std::cout << "\033[32m";
				std::cout << std::endl
					<< findMe << " not purchased today."
					<< std::endl << std::endl;
				// Reset color to default
				std::cout << "\033[0m";
			}

			break;

		case ITEMS_PURCHASED_TODAY:
			
			buildInventory(items);

			backupInventory(items);

			// Write inventory purchased today
			// Set color to green
			std::cout << "\033[32m";
			std::cout
				<< std::right
				<< std::setw(TITLE_WIDTH)
				<< ITEM_2_TITLE
				<< std::endl
				<< std::setw(TITLE_WIDTH)
				<< std::string(ITEM_2_TITLE.size(), '-')
				<< std::endl;
			for (it = items.begin(); it != items.end(); it++)
			{ 
				std::cout 
					<< std::right
					<< std::setw(COLUMN_WIDTH)
					<< it->first 
					<< std::string(SEP_WIDTH, ' ')
					<< it->second->getQuantity()
					<< std::endl;
			}
			// Set color to default
			std::cout << "\033[0m";
			std::cout << std::endl;

			break;

		case HISTOGRAM_PURCHASED_TODAY:

			buildInventory(items);

			backupInventory(items);

			// Write histogram// Set color to green
			std::cout << "\033[32m";
			std::cout
				<< std::right
				<< std::setw(TITLE_WIDTH)
				<< ITEM_3_TITLE
				<< std::endl
				<< std::setw(TITLE_WIDTH)
				<< std::string(ITEM_3_TITLE.size(), '-')
				<< std::endl;
			for (it = items.begin(); it != items.end(); it++)
			{
				std::cout 
					<< std::right
					<< std::setw(COLUMN_WIDTH)
					<< it->first 
					<< std::string(SEP_WIDTH, ' ')
					// Creates a string of asterisks equal to the item frequency.
					<< std::string(it->second->getQuantity(), '*')
					<< std::endl;
			}
			// Reset color to default
			std::cout << "\033[0m";
			std::cout << std::endl;
			break;
		case EXIT_PROGRAM:
			// Set color to green
			std::cout << "\033[32m"
				<< "Thank you for using Corner Grocer Item Tracking" 
				<< std::endl
				// Reset color to default
				<< "\033[0m";
			break;

		default:
			std::cout << "Invalid menu choice" << std::endl;
			break;
		}
	}

	clearInventory(items);
	return 0;
}

// Functions 
int displayMenu()
{
	int userInput = 0;
	std::cin.exceptions(std::ios::failbit);

	std::cout << "Corner Grocer Item Tracking" << std::endl
		<< "Main Menu" << std::endl
		<< "1 - Check Item Purchased Today" << std::endl
		<< "2 - Display Items Purchased Today" << std::endl
		<< "3 - Display Histogram for Items Purchased Today" << std::endl
		<< "4 - Exit Program" << std::endl;

	while (userInput < 1 || userInput > 4)
	{
		try
		{
			std::cout << std::endl;
			std::cout << "Choose a Menu Item: ";
			std::cin >> userInput;
			std::cout << std::endl;

			if (userInput < 1 || userInput > 4)
			{
				std::cout << "Invalid Menu Item" << std::endl;
			}

		}
		catch (std::ios_base::failure&)
		{
			std::cout << "Invalid Menu Item" << std::endl;
			std::cin.clear();
			std::cin.ignore(100, '\n');
		}
	}
	return userInput;
}

void buildInventory(std::map<std::string, GroceryItem*>& t_items)
{
	const std::string INPUT_FILE = "daily_sales_inventory.txt";
	std::ifstream inFS;

	inFS.open(INPUT_FILE);
	if (!inFS.is_open())
	{
		std::cout << "Error: could not open input file" << std::endl;
		return;
	}

	std::string itemName;

	inFS >> itemName;

	clearInventory(t_items);

	while (!inFS.eof())
	{
		if (t_items.count(itemName) == 1)
		{
			t_items.at(itemName)->addItem();
		}
		else
		{
			t_items.emplace(itemName, new GroceryItem(itemName, 1));
		}
		inFS >> itemName;

	}
	inFS.close();
}

void backupInventory(std::map<std::string, GroceryItem*>& t_items)
{
	const std::string BACKUP_FILE = "frequency.dat";
	std::ofstream outFS;

	outFS.open(BACKUP_FILE);
	if (!outFS.is_open())
	{
		std::cout << "Error: could not create backup file" << std::endl;
		return;
	}

	std::map<std::string, GroceryItem*>::iterator it;

	for (it = t_items.begin(); it != t_items.end(); it++)
	{
		outFS << it->first << " "
			<< it->second->getQuantity()
			<< std::endl;
	}

	outFS.close();
}

void clearInventory(std::map<std::string, GroceryItem*>& t_items)
{
	std::map<std::string, GroceryItem*>::iterator it;

	for (it = t_items.begin(); it != t_items.end(); it++)
	{
		// Releases dynamically allocated GroceryItem objects before clearing 
		// the map to prevent memory leaks.
		delete it->second;
		it->second = nullptr;
	}
	t_items.clear();
}

std::string makeTitleCase(std::string t_item)
{
	for (int i = 0; i < t_item.size(); ++i)
	{
		if (i == 0)
		{
			t_item[i] = std::toupper(t_item[i]);
		}
		else
		{
			t_item[i] = std::tolower(t_item[i]);
		}
	}
	return t_item;
}
