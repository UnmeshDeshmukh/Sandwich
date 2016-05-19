#include <iostream>
#include <string>
#include "configuration_constants.h"
#include <fstream>
//#include <stdlib>
#include <vector>

using namespace std;

class OrderItem {
	int order_item_id;
	string order_item_name;
	int order_item_count;

public:

	OrderItem(int order_item_id, string order_item_name, int order_item_count) {
		this->order_item_id = order_item_id;
		this->order_item_name = order_item_name;
		this->order_item_count = order_item_count;

	}

	OrderItem() {

	}

	int getOrderItemCount() {
		return order_item_count;
	}

	void setOrderItemCount(int orderItemCount) {
		order_item_count = orderItemCount;
	}

	int getOrderItemId() {
		return order_item_id;
	}

	void setOrderItemId(int orderItemId) {
		order_item_id = orderItemId;
	}

	string getOrderItemName() {
		return order_item_name;
	}

	void setOrderItemName(string orderItemName) {
		order_item_name = orderItemName;
	}
};

class Order {

	int order_id;
	string customer_name;
	vector<OrderItem> orderitems;
	string order_status;
	int task_count;

public:

	Order(int id, string name, vector<OrderItem> orderitems) {
		this->order_id = id;
		this->customer_name = name;
		this->orderitems = orderitems;
		this->order_status = INCOMPLETE;
		this->task_count = 0;

		cout << "Order recorded with id (" << order_id << ")";

	}
	Order() {

	}

	bool operator <(const Order& rhs) const {
		return order_id < rhs.order_id;
	}
	void updateTaskCount(int task_count) {
		this->task_count = task_count;
	}

	int getTaskCount() {
		return task_count;
	}
	void changeStatus(string new_status) {
		order_status = new_status;
	}

	string getStatus() {
		return order_status;
	}

	static vector<Order> read_Orders() {

		string ID, name, receipe_1, receipe_2, receipe_3, count;
		int index = 0;
		int index_order_item = 0;

		vector<Order> orders_local;

		std::ifstream csv_Orders("order.csv");
		//Order* optr = orders;
		while (csv_Orders.good()) {
			vector<OrderItem> orderitems;
			index_order_item = 0;
			getline(csv_Orders, ID, ',');
			cout << "ID: " << ID << " ";

			getline(csv_Orders, name, ',');
			cout << "Name: " << name << " ";

			getline(csv_Orders, receipe_1, ',');
			cout << "Receipe_1: " << receipe_1 << " ";

			if (stoi(receipe_1) != 0) {
				OrderItem* orderitem = new OrderItem(1, RECIPE_1,
						stoi(receipe_1));
				orderitems.push_back(*orderitem);
			}

			getline(csv_Orders, receipe_2, ',');
			cout << "Receipe_2: " << receipe_2 << " ";

			if (stoi(receipe_2) != 0) {
				OrderItem* orderitem = new OrderItem(2, RECIPE_2,
						stoi(receipe_2));
				orderitems.push_back(*orderitem);
			}

			getline(csv_Orders, receipe_3);
			cout << "Receipe_3: " << receipe_3 << " ";

			if (stoi(receipe_3) != 0) {
				OrderItem* orderitem = new OrderItem(3, RECIPE_3,
						stoi(receipe_3));
				orderitems.push_back(*orderitem);
			}

//		    getline(csv_Orders, count) ; //diff
//		    cout << "Count: " <<  count; // diff

			Order* order = new Order(stoi(ID), name, orderitems);
			orders_local.push_back(*order);
			//Order  *optr = order;
			//orders_local[index].order_id = ID;
			//orders_local[index].customer_name = name;
			//orders_local[index].orderitems = orderitems;
			//index++;
			cout << endl;

		}

		//	print_Orders(orders);
		return orders_local;
	}

	static void print_Orders(vector<Order> orders) {
		cout << "\n---ORDERS---\n";
		for (int i = 0; i < orders.size(); i++) {

			cout << "Order ID :" << orders[i].getOrderId()
					<< orders[i].customer_name << "\tTASK COUNT:"
					<< orders[i].getTaskCount() << "\tORDER STATUS:"
					<< orders[i].getStatus() << endl;
		}
		cout << "\n---ORDERS---\n";

	}
	/*
	 void cook(string recipe){
	 cout<<"Chef with id ("<<chef_id<<")is cooking "<<recipe<<endl;

	 }*/

	string getCustomerName() {
		return customer_name;
	}

	void setCustomerName(string customerName) {
		customer_name = customerName;
	}

	int getOrderId() {
		return order_id;
	}

	void setOrderId(int orderId) {
		order_id = orderId;
	}

	vector<OrderItem> getOrderitems() {
		return orderitems;
	}

	void setOrderitems(vector<OrderItem> orderitems) {
		this->orderitems = orderitems;
	}
};

