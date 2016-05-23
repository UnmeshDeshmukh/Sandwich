/*
 * Inventory.cpp
 *
 *  Created on: May 17, 2016
 *      Author: Vinit, Unmesh, Faisal
 */

#include "inventory.h"
#include <omp.h>
#include "omp_sync.h"

std::ifstream input_kitchen_inventory("./config/kitchen_inventory.config");
InventoryCfg Inventory::config;

Inventory::Inventory() {
	// TODO Auto-generated constructor stub

}

Inventory::~Inventory() {
	// TODO Auto-generated destructor stub
}

void Inventory::showInventory() {

	for (map<string, int>::const_iterator it = config.begin();
			it != config.end(); ++it) {
		std::cout << "INGREDIENT NAME =" << it->first << " INGREDIENT STOCK ="
				<< it->second << " " << "\n";	// Printing inventory details

	}

}

void Inventory::scanInventory() {
	string s;
	input_kitchen_inventory.clear();
	input_kitchen_inventory.seekg(0, std::ios::beg);
	while (getline(input_kitchen_inventory, s)) {
		config[s.substr(0, s.find(':'))] = stoi(s.substr(s.find(':') + 1));	// Scanning inventory from kitchen-inventory.config file
	}

}

bool Inventory::isItemAvailable(map<string, int> recipe) {

	Mutex::getMutex()->lock();								// Acquiring lock

	for (map<string, int>::const_iterator it = recipe.begin();
			it != recipe.end(); ++it) {
		if ((it->second) <= config[it->first]) {// Checking if items required is available in the stock
			continue;
		} else {
			Mutex::getMutex()->unlock();					// Releasing lock
			return false;
		}

	}
	Mutex::getMutex()->unlock();							// Releasing lock

	return true;

}
bool Inventory::getItems(map<string, int> recipe) {
	Mutex::getMutex()->lock();								// Acquiring lock
	bool getavailableItems = false;
	for (map<string, int>::const_iterator it = recipe.begin();
			it != recipe.end(); ++it) {
		if ((config[it->first] - it->second) > 0) {	// If items available in the stock then retrieving them from the inventory
			config[it->first] = config[it->first] - it->second;
			getavailableItems = true;
		}
	}
	Mutex::getMutex()->unlock();							// Releasing lock
	return getavailableItems;
}
