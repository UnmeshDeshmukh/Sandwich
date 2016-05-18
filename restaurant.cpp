#include <iostream>
#include <string>
#include "chef.h"
#include "order.h"
#include "configuration_constants.h"
#include <omp.h>
#include "configuration_constants.h"
#include <fstream>
#include <vector>
#include "Task.h"
#include "inventory.h"
//

using namespace std;

vector<Order> orders;
vector<Task> tasks;
//map<Order,vector<Task>> reducer

int main() {

	orders = Order::read_Orders();
	Order::print_Orders(orders);

	tasks = Task::getTasks(orders);
	Task::printTasks(tasks);

	Kitchen* kitchen = new Kitchen;

	//inventory
	Inventory::scanInventory();
	Inventory::showInventory();

	//Inventory::getItems(LETTUCE,1);

	for (int i = 0; i < tasks.size(); i++) {

		vector<Chef*> section = Kitchen::getASection(tasks[i].getTaskType());
		if (section[Kitchen::getAChef(tasks[i].getTaskType())]->cook())
			tasks[i].changeStatus(COMPLETE);
		else
			tasks[i].changeStatus(INCOMPLETE);



	}

	for (int i = 0; i < tasks.size(); i++){

	}


	cout << "\nPrinting finally" << endl;
	Inventory::showInventory();
	cout << "Task status as of now" << endl;
	Task::printTasks(tasks);
	Order::print_Orders(orders);
//Chefs::chefr1[1]->cook();

	cout << "End";

	return 0;
}
