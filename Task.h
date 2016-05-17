/*
 * Task.h

 *
 *  Created on: May 15, 2016
 *      Author: vinit
 */
#include <string>
#include <vector>

#ifndef TASK_H_
#define TASK_H_

class Tasks {

};

class Task {

	int task_id;
	int order_id;
	string task_type;

public:

	Task(int task_id, int order_id, string task_type) {
		this->task_id =task_id;
		this->order_id= order_id;
		this->task_type=task_type;
	}

	static vector<Task> getTasks(vector<Order> orders) {
		int task_count = 0;
		vector < Task > tasks;
		for (int i = 0; i < orders.size(); i++) {
			for (int j = 0; j < orders[i].getOrderitems().size(); j++) {

				for (int k = 0;
						k < orders[i].getOrderitems()[j].getOrderItemCount();
						k++) {

					Task* task = new Task(task_count++, orders[i].getOrderId(),
							orders[i].getOrderitems()[j].getOrderItemName());
					tasks.push_back(*task);
				}
			}
		}
		return tasks;
	}

	static void printTasks(vector<Task> tasks) {

		for (int i = 0; i < tasks.size(); i++) {

			cout << "Task ID : " << tasks[i].getTaskId() << "\tTask Type : "
					<< tasks[i].getTaskType() << "\tOrder ID : "
					<< tasks[i].getOrderId() << endl;
		}
	}

	int getOrderId() const {
		return order_id;
	}

	void setOrderId(int orderId) {
		order_id = orderId;
	}

	int getTaskId() const {
		return task_id;
	}

	void setTaskId(int taskId) {
		task_id = taskId;
	}

	const string& getTaskType() const {
		return task_type;
	}

	void setTaskType(const string& taskType) {
		task_type = taskType;
	}
};

#endif /* TASK_H_ */
