#include <iostream>
#include <string>
#include "order.h"
#include "configuration_constants.h"
#include <omp.h>
#include "configuration_constants.h"
#include <fstream>
#include <vector>
#include "Task.h"
#include "inventory.h"
#include <boost/chrono.hpp>
#include "Kitchen.h"
#include "Chef.h"
#include <boost/array.hpp>

using namespace std;
using namespace boost::chrono;

//vector<Kitchen> kitchens;

int orders_delivered = 0;
int total_processed_orders = 0;
double initial_time, end_time;
double revenue;
int main() {

	Kitchen::readKitchenConfiguration();
	vector<Kitchen> kitchens(Kitchen::NUM_OF_KITCHENS);
	vector<double> v(10);
	vector<Order> orders;
	vector<Task> tasks;
	map<Order, vector<Task>> reducer;

	char ans;
	int num_of_task_distribution_threads;
	int num_of_reducer_threads;
	orders = Order::read_Orders();
	Order::print_Orders(orders);

	tasks = Task::getTasks(&orders);
	//Task::printTasks(tasks);	k
	//Kitchen::getKitchen();

	//inventory

	//Inventory::getItems(LETTUCE,1);
	cout << "\nNUMBER OF PROCESSORS AVAILABLE FOR PARALLELISATION "
			<< omp_get_num_procs();
	omp_set_num_threads(Kitchen::NUM_OF_KITCHENS);

	int dummy;

	while (true) {

		Inventory::scanInventory();
		Inventory::showInventory();
		Kitchen::showKitchens(kitchens);
		auto dt_s = high_resolution_clock::now();

		initial_time = omp_get_wtime();

#pragma omp parallel
		{
#pragma omp  for nowait
			for (int i = 0; i < tasks.size(); i++) {

				if (i == 0) {
					num_of_task_distribution_threads = omp_get_num_threads();

				}

				if (!tasks[i].getStatus().compare(INCOMPLETE)) {
					vector<Chef*> section =
							kitchens[omp_get_thread_num()].getASection(
									tasks[i].getTaskType());

					if (section.size() != 0
							&& section[kitchens[omp_get_thread_num()].getAChef(
									tasks[i].getTaskType())]->cook())
						tasks[i].changeStatus(COMPLETE);
					else
						tasks[i].changeStatus(INCOMPLETE);
				}

			}

#pragma omp  for reduction(+:revenue)
			for (int i = 0; i < tasks.size(); i++) {

				if (i == 0) {
					num_of_reducer_threads = omp_get_num_threads();

				}

				if (tasks[i].getStatus().compare(DELIVERED)
						&& !tasks[i].getStatus().compare(COMPLETE)) {

#pragma omp critical
					{

						reducer[orders[tasks[i].getOrderId()]].push_back(
								tasks[i]);
						tasks[i].changeStatus(DELIVERED);
					}
					//	reducer.insert(reducer[orders[tasks[i].getOrderId()]],reducer[orders[tasks[i].getOrderId()]);

					if (orders[tasks[i].getOrderId()].getStatus().compare(
					COMPLETE)
							&& (reducer[orders[tasks[i].getOrderId()]].size()
									== orders[tasks[i].getOrderId()].getTaskCount())) {

						orders_delivered++;
						//	cout << tasks[i].getTaskId();
						orders[tasks[i].getOrderId()].changeStatus(COMPLETE);
						revenue += Task::getTaskCost(tasks[i]);
					}

				}

			}
		}
		auto dt = duration_cast<milliseconds>(
				high_resolution_clock::now() - dt_s);
		Inventory::showInventory();
		//	Task::printTasks(tasks);

		end_time = omp_get_wtime();
		// or miliseconds

		Order::print_Orders(orders);
		cout << "OVERALL STATUS : " << orders_delivered << "/" << orders.size()
				<< " orders delivered" << endl;
		cout << "\nNUMBER OF THREADS SET IN THIS TASK DISTRIBUTION TEAM ="
				<< num_of_task_distribution_threads << endl;

		cout << "\nNUMBER OF THREADS SET IN THIS TASK REDUCER TEAM ="
				<< num_of_reducer_threads << endl;

		cout << "\nREVENUE =" << revenue;
		cout << "\nTask assignment and execution time =" << dt.count() << endl;

		cout << "Do you want to replenish?" << endl;
		cin >> ans;
		initial_time = omp_get_wtime();
		if (ans != 'Y')
			break;

		cout << "End";

	}
	return 0;
}
