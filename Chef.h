/*
 * Chef.h
 *
 *  Created on: May 22, 2016
 *      Author: Vinit, Unmesh,	Faisal
 */

// Variables, getters and setters for Chef.cpp
#ifndef CHEF_H_
#define CHEF_H_

#include <unistd.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <omp.h>
#include "configuration_constants.h"
#include "inventory.h"

using namespace std;

class Kitchen;
class Chef {

	int chef_id;
	static int number_of_chef;
protected:
	map<string, int> reciepe;
	Kitchen* kitchen;

public:
	Chef(Kitchen* kitchen);
	static vector<Chef*> hireChef(string speciality, int number_of_position,
			Kitchen* kitchen);

	virtual bool cook() = 0;

};

class VeggieChef: public Chef {
public:
	VeggieChef(Kitchen* kitchen);
	bool cook();
};

class ChickenChef: public Chef {

public:
	ChickenChef(Kitchen* kitchen);
	bool cook();
};

class HamChef: public Chef {

public:
	HamChef(Kitchen* kitchen);
	bool cook();
};

#endif /* CHEF_H_ */
