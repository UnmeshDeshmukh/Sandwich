/*
 * Chef.cpp
 *
 *  Created on: May 22, 2016
 *      Author: Vinit,	Unmesh,	Faisal
 */

#include "Chef.h"
#include "Kitchen.h"

using namespace std;
int Chef::number_of_chef = 0;

Chef::Chef(Kitchen* kitchen) {
	// TODO Auto-generated constructor stub
	this->kitchen = kitchen;

}

VeggieChef::VeggieChef(Kitchen* kitchen) :
		Chef(kitchen) {
	//Required inventory for Veggie Sandwich
	reciepe[LETTUCE] = 3;
	reciepe[OLIVES] = 4;
	reciepe[ONIONS] = 2;
	reciepe[SOURDOUGH] = 1;

}

bool VeggieChef::cook() {
	bool isCookingDone = false; 						// Before cooking starts (Cooking is incomplete)
	if (Inventory::isItemAvailable(reciepe) && Inventory::getItems(reciepe)) {
		cout << "....Cooking Veggie..." << endl;
		if (kitchen->section_1.size() != 0) {
			usleep(RECIEPE_1_TIME / kitchen->section_1.size()); 	// Cooking time required for each unit //Time reduces if number of Chefs in the section are increased
			isCookingDone = true; 						// After cooking completes (Cooking is complete)
		} else {
			isCookingDone = false; 						// If unable to find or retrieve items from the inventory (Cooking is incomplete)
		}
	}

	return isCookingDone;
}
ChickenChef::ChickenChef(Kitchen* kitchen) :
		Chef(kitchen) {
	//Required inventory for Chicken Sandwich
	reciepe[OLIVES] = 8;
	reciepe[ONIONS] = 5;
	reciepe[TOMATOES] = 4;
	reciepe[CHICKEN] = 4;
	reciepe[MULTI_GRAIN] = 1;
}

bool ChickenChef::cook() {
//Atomic
	bool isCookingDone = false;							// Before cooking starts (Cooking is incomplete)
	if (Inventory::isItemAvailable(reciepe) && Inventory::getItems(reciepe)) {
		cout << "....Cooking Chicken..." << endl;
		usleep(RECIEPE_2_TIME / kitchen->section_2.size());		// Cooking time required for each unit //Time reduces if number of Chefs in the section are increased
		isCookingDone = true; 							// After cooking completes (Cooking is complete)
	} else {
		isCookingDone = false;							// If unable to find or retrieve items from the inventory (Cooking is incomplete)
	}
	return isCookingDone;
}

HamChef::HamChef(Kitchen* kitchen) :
		Chef(kitchen) {
	//Required inventory for Spicy Italian
	reciepe[HAM] = 2;
	reciepe[TURKEY] = 2;
	reciepe[LETTUCE] = 5;
	reciepe[TOMATOES] = 3;
	reciepe[ITALIAN_BREAD] = 1;
}

bool HamChef::cook() {
	bool isCookingDone = false;							// Before cooking starts (Cooking is incomplete)
	if (Inventory::isItemAvailable(reciepe) && Inventory::getItems(reciepe)) {
		cout << "....Cooking Ham..." << endl;
		if (kitchen->section_3.size() != 0) {
			usleep(RECIEPE_3_TIME / kitchen->section_3.size());	// Cooking time required for each unit //Time reduces if number of Chefs in the section are increased
			isCookingDone = true; 						// After cooking completes (Cooking is complete)
		}
	} else {
		isCookingDone = false;							// If unable to find or retrieve items from the inventory (Cooking is incomplete)
	}

	return isCookingDone;

}
vector<Chef*> Chef::hireChef(string speciality, int number_of_position,
		Kitchen* kitchen) {

	vector<Chef*> chef;									//Creating a chef vector
	if (!speciality.compare(RECIPE_1)) {
		for (int i = 1; i <= number_of_position; i++) {
			VeggieChef* veggieChef = new VeggieChef(kitchen);		// Instantiating a new VeggieChef
			chef.push_back(veggieChef);					// Adding the created VeggieChef to chef vector
		}
		return chef;

	} else if (!speciality.compare(RECIPE_2)) {
		for (int i = 1; i <= number_of_position; i++) {
			ChickenChef* chickenchef = new ChickenChef(kitchen);	// Instantiating a new ChickenChef
			chef.push_back(chickenchef);				// Adding the created ChickenChef to chef vector
		}
		return chef;
	} else if (!speciality.compare(RECIPE_3)) {
		for (int i = 1; i <= number_of_position; i++) {
			HamChef* hamchef = new HamChef(kitchen);				// Instantiating a new HamChef
			chef.push_back(hamchef);					// Adding the created HamChef to chef vector
		}
		return chef;
	}

}
