#include "Pid.h"
#include <iostream>
#include <iostream>       // std::cout, std::endl
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <semaphore.h>
using namespace std;

//Constructor
template<class xtype>
Pid<xtype>::Pid() {

	head = NULL;
	id_Counter = 300;
}

//Destructor
template<class xtype>
Pid<xtype>::~Pid() {

	node<xtype> * p;

	while (head != NULL)
	{
		p = head;
		head = head->next;
		delete p;
	}
}

template<class xtype>
int Pid<xtype> ::allocate_map() {

	#define MIN_PID 300
	#define MAX_PID 5000
	#define cb CHAR_BIT
	int sz = MAX_PID - MIN_PID + 1;
	//sem_t sem;//---------------------------------------------------------------------------------------

	/* Create the semaphore and initialize it to 1 */
	//sem_init(&sem, 0, 1);//---------------------------------------------------------------------------

	if (head == NULL) { //Will happen only once at the first time the process will execute

		head = new node<xtype>; head->next = NULL;
		head->b = (unsigned char*)malloc((sz + cb - 1) / cb * sizeof(char));
		head->id = allocate_pid();
		head->used = true;

		head->timeToSleep = rand() % 10; // Give the process time to be executed 
		sleepTime(head->timeToSleep);//------------------------------------

		cout << "A process has been created and it's ID is: " << head->id << endl;
	}
	else
	{
		node<xtype> * p = head;

		if (id_Counter <= 5000) {//301 - 5000 assuming that the first ID already given

			//First check for available ID:
			while (p != NULL) {

				if (p->used == false)
				{
					p->b = (unsigned char*)malloc((sz + cb - 1) / cb * sizeof(char));
					p->used = true;
					cout << "\nThe new process reassign to ID number :" << p->id << "\n" << endl;

					p->timeToSleep = rand() % 10; // Give the process time to be executed
					sleepTime(p->timeToSleep);//------------------------------------

					break;
				}
				p = p->next;
			}

			//If no available ID create new node for the process:
			if (p == NULL)
			{
				p = head;
				while (p->next != NULL)
					p = p->next;

				p->next = new node<xtype>; p = p->next; p->next = NULL;
				p->b = (unsigned char*)malloc((sz + cb - 1) / cb * sizeof(char));
				p->id = allocate_pid();
				p->used = true;
				cout << "The new ID is: " << p->id << endl;

				p->timeToSleep = rand() % 10; // Give the process time to be executed
				sleepTime(p->timeToSleep);//------------------------------------
			}
		}
		else {

			while (p != NULL)
			{
				if (p->used == false)
				{
					delete p->b;
					p->b = (unsigned char*)malloc((sz + cb - 1) / cb * sizeof(char));
					p->used = true;

					p->timeToSleep = rand() % 10; // Give the process time to be executed
					sleepTime(p->timeToSleep);//------------------------------------

					break;
				}
				p = p->next;
			}

			cout << "The system cannot give a new ID due to insufficient IDs" << endl;
			cout << "The process has been terminated" << endl;
		}
	}
	return 0;// nothing to return
}

template<class xtype>
int Pid<xtype>::allocate_pid() {

	int i = id_Counter;
	id_Counter++;
	return i;
}

template<class xtype>
void Pid<xtype>::release_pid(int pid) {

	if (head == NULL) { //Empty list
		cout << "No processes to delete." << endl;
	}
	else if (!(pid < 300 || pid > 5000)) {
		node<xtype> * q = head;
		while (q != NULL) {

			if (q->id == pid && q->used == true) {
				delete q->b;
				q->used = false;
				cout << "ID number :" << q->id << " Is now free\n" << endl;
				break;
				//Keeping in the node the ID to give it to other process
			}
			q = q->next;
		}

		if (q == NULL)// Id is not in the list or id is already deleted
			cout << "The ID is not available to delete." << endl;
	}
	else
		cout << "The ID is not available to delete." << endl;
}

template<class xtype>
void Pid<xtype>::display(){

	if (head != NULL) {

		cout << "The following IDs are used:" << endl;
		node<xtype> * p = head;
		while (p != NULL) {
			if (p->used == true) {
				cout << p->id << endl;
			}
			p = p->next;
		}
	}
	else
		cout << "No IDs to display" << endl;
}

template<class xtype> 
void Pid<xtype>::sleepSimulation() {

	//mtx.lock(); // Locking the following code:
	//cout << 
	/*No need to create 100 processes for the simulation.*/
	for (int i = 0; i < 10; i++)
	{
		allocate_map();
		//release_pid(300);
	}

	//mtx.unlock();// Releasing the code
}

template<class xtype>
void Pid<xtype>::sleepTime(int t) {

	 // The parameter t is to represent the time to sleep in seconds.

	 /** The purpose of this function is to simulate the process execution,
	 *   therefore the locks suppose to insure that there won't be a
	 *   race condition during that time.
	 */

	mtx.lock(); // Locking the following code:
	cout << "MUTEX LOCK -------> ON" << endl;

	if (t != 0) {
		cout << "The process is executing now, " << t << " seconds to finish" << endl;

		for (int i = t; i > 0; --i) {
			cout << i << endl;
			this_thread::sleep_for(chrono::seconds(1));
		}
	}
	else
		cout << "The process is executing now, " << t << " seconds to finish" << endl;

	cout << "MUTEX LOCK -------> OFF" << endl;
	mtx.unlock();// Releasing the code
}