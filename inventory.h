/*
 * inventory.h
 *
 *  Created on: May 17, 2016
 *      Author: vinit
 */

#ifndef INVENTORY_H_
#define INVENTORY_H_

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <string>
using namespace std;


typedef map< string, int> InventoryCfg;

class Inventory {

	static InventoryCfg config;

public:
	Inventory();
	static void showInventory();
	static void scanInventory();
	static void getItems(map <string,int> recipe);
	static bool isItemAvailable(map <string,int> recipe);
	virtual ~Inventory();
};



#endif /* INVENTORY_H_ */
