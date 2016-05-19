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
map<Order, vector<Task>> reducer;
int orders_delivered = 0;
int total_processed_orders = 0;

int main() {

	char ans;
	orders = Order::read_Orders();
	Order::print_Orders(orders);

	tasks = Task::getTasks(&orders);
	Task::printTasks(tasks);

	Kitchen* kitchen = new Kitchen;
	//inventory

	//Inventory::getItems(LETTUCE,1);
	while (true) {
	Inventory::scanInventory();
	Inventory::showInventory();

	for (int i = 0; i < tasks.size(); i++) {

		if (!tasks[i].getStatus().compare(INCOMPLETE)) {
			vector<Chef*> section = Kitchen::getASection(
					tasks[i].getTaskType());
			if (section[Kitchen::getAChef(tasks[i].getTaskType())]->cook())
				tasks[i].changeStatus(COMPLETE);
			else
				tasks[i].changeStatus(INCOMPLETE);
		}
	}

	for (int i = 0; i < tasks.size(); i++) {
		cout << " \n OUTER DEBUG with task id" << tasks[i].getTaskId();
		cout << "\n STATUS OF CURRENT TASK " << tasks[i].getStatus();
		if (!tasks[i].getStatus().compare(COMPLETE)) {

			reducer[orders[tasks[i].getOrderId()]].push_back(tasks[i]);
			cout << "Task considering " << i;
			//	reducer.insert(reducer[orders[tasks[i].getOrderId()]],reducer[orders[tasks[i].getOrderId()]);

			if (reducer[orders[tasks[i].getOrderId()]].size()
					== orders[tasks[i].getOrderId()].getTaskCount()) {
				cout << "DEBUG 1\n" << tasks[i].getOrderId();
				cout << " DEBUG 2 ";

				cout << reducer[orders[tasks[i].getOrderId()]].size();
				cout << " DEBUG 3 ";

				cout << orders[tasks[i].getOrderId()].getTaskCount();
				cout << " DEBUG 4 ";

				orders[tasks[i].getOrderId()].changeStatus(COMPLETE);
				cout << " DEBUG 5 ";

				orders_delivered++;
				cout << tasks[i].getTaskId();
				cout << "\n";
			}

		}
	}

	cout << "\nPrinting finally" << endl;
	Inventory::showInventory();
	cout << "Task status as of now" << endl;
	Task::printTasks(tasks);
	Order::print_Orders(orders);
//Chefs::chefr1[1]->cook();

	cout << "OVERALL STATUS : " << orders_delivered << "/" << orders.size()
			<< " orders delivered" << endl;

	cout<< "Do you want to replenish?" << endl;
	cin >> ans;

		if (ans != 'Y')
			break;
}
	cout << "End";

	return 0;
}
