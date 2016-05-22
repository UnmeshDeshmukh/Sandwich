/*
 * Kitchen.h
 *
 *  Created on: May 21, 2016
 *      Author: vinit
 */

#ifndef KITCHEN_H_
#define KITCHEN_H_

#include <string>
#include <vector>
#include "Chef.h"
#include <boost/array.hpp>

using namespace std;
typedef map<string, int> KitchenCfg;

class Kitchen {

	int kitchen_id;
	static int number_of_kitchens;

//static Kitchen* kitchen_instance;
public:
	static  unsigned long int NUM_OF_KITCHENS;
	Kitchen();
	vector<Chef*> section_1;
	vector<Chef*> section_2;

	vector<Chef*> section_3;

	int section_1_pointer;
	int section_2_pointer;
	int section_3_pointer;
	static KitchenCfg kitchenCfg;
//	virtual ~Kitchen();

//	static Kitchen* getKitchen();
	int getAChef(string speciality);
	vector<Chef*> getASection(string speciality);
	static void showKitchens(
			vector<Kitchen> kitchens);
	static void readKitchenConfiguration();

};

#endif /* KITCHEN_H_ */

