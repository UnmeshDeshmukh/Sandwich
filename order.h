#include <iostream>
#include <string>

using namespace std;


class OrderItem
{
	string order_item_id;
	string order_item_name;
	string order_item_count;


	public:

		OrderItem(string order_item_id,string order_item_name,string order_item_count){
			this->order_item_id=order_item_id;
			this->order_item_name=order_item_name;
			this->order_item_count=order_item_count;
		}

};

class Order
{
	 
	string order_id;
	string order_name;
	OrderItem orderitems[RECIEPE_TYPES];



public:

	Order(string id,string name,string receipe,string count){
		this->order_id = id;
		this->name = name;
		this->receipe = receipe; 
		this->count = count; 
		
		cout<<"Order recorded with id ("<<order_id<<")";

		
	}
	Order(){

	}

	static void read_Orders(){

	string ID,name,receipe_1,receipe_2,receipe_3,count;
	int index=0;
			while(csv_Orders.good())
		{
			
			
		    getline(csv_Orders, ID, ',');
		    cout << "ID: " << ID << " " ; 

		    getline(csv_Orders, name, ',') ;
		    cout << "Name: " << name << " " ;

		    getline(csv_Orders, receipe_1, ',') ;
		    cout << "Receipe_1: " << receipe_1 << " "  ; 

		    getline(csv_Orders, receipe_2, ',') ;
		    cout << "Receipe_1: " << receipe_1 << " "  ; 

		    getline(csv_Orders, receipe_3, ',') ;
		    cout << "Receipe_1: " << receipe_1 << " "  ; 


		    getline(csv_Orders, count) ; //diff
		    cout << "Count: " <<  count; // diff

		    Order order(ID,name,receipe,count);
		    orders[index++] = order;
		    cout<<endl;
		}
}
/*
	void cook(string recipe){
		cout<<"Chef with id ("<<chef_id<<")is cooking "<<recipe<<endl;

	}*/


};