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
double initial_time, end_time;

int main() {

	char ans;
	orders = Order::read_Orders();
	Order::print_Orders(orders);

	tasks = Task::getTasks(&orders);
	//Task::printTasks(tasks);

	Kitchen* kitchen = new Kitchen;
	//inventory
	omp_set_num_threads(3);
	initial_time = omp_get_wtime();
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
			if (!tasks[i].getStatus().compare(COMPLETE)) {

				reducer[orders[tasks[i].getOrderId()]].push_back(tasks[i]);

				//	reducer.insert(reducer[orders[tasks[i].getOrderId()]],reducer[orders[tasks[i].getOrderId()]);

				if (reducer[orders[tasks[i].getOrderId()]].size()
						== orders[tasks[i].getOrderId()].getTaskCount()) {

					orders_delivered++;
					//cout << tasks[i].getTaskId();
					orders[tasks[i].getOrderId()].changeStatus(COMPLETE);

				}

			}
		}

		Inventory::showInventory();
		//Task::printTasks(tasks);
		end_time = omp_get_wtime();
		Order::print_Orders(orders);

		cout << "OVERALL STATUS : " << orders_delivered << "/" << orders.size()
				<< " orders delivered" << endl;

		cout << "\nTask assignment and execution time ="
				<< end_time - initial_time << endl;
		initial_time = omp_get_wtime();
		cout << "Do you want to replenish?" << endl;
		cin >> ans;

		if (ans != 'Y')
			break;
	}
	cout << "End";

	return 0;
}
