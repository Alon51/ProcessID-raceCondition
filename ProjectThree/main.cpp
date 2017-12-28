#include "Pid.cpp"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <iostream>
using namespace std;

void menu();
//void Simulation();

void main() {

	Pid<int> obj;
	int selection = 0;

	//Menu for user selection:
	cout << "Hello user, this is a demonstration of processes and IDs\n" << endl;
	menu();
	cin >> selection;

	do {
		if (selection == 0)
		{
			exit(0);
		}
		else if (selection == 1)
		{
			obj.allocate_map();
		}
		else if (selection == 2)
		{
			int ans = 0;
			cout << "What process ID would you like to release? ";
			cin >> ans;
			obj.release_pid(ans);
		}
		else if (selection == 3)
		{
			obj.display();
		}
		else if (selection == 4)
		{
			cout << "\nSimulation starts: \n" << endl;
			obj.sleepSimulation();

			//Creating 2 threads: 
			//cout << "Two random threads was created and their random IDs:\n" << endl;
			
			//thread th1(Simulation);
			

			//cout << "Thread 1: " << th1.get_id() << endl;
			//thread th2(Simulation);
			//cout << "Thread 2: \n" << th2.get_id() << endl;
			
			//cout << "The above threads will try to enter the critical section of generating processes"<< endl;
			//Simulation();
			
			//th1.join(); // End the thread
			//th2.join();// End the thread

			//cout << "Simulation ended, no race condition occur\n" << endl;
		}

		cout << "\nEnter another option from the menu or 0 to exit" << endl;
		menu();
		cin >> selection;

	} while (selection == 1 || selection == 2 || selection == 3 || selection == 4);

	cout << "\nThank you for your cooperation.\n" << endl;
}

void menu() {

	cout << "Please follow the menu:" << endl;
	cout << "To create a new process enter 1" << endl;
	cout << "To delete a process enter 2" << endl;
	cout << "To display the IDs that currently are occupied enter 3" << endl;
	cout << "To simulate pid management press 4" << endl;

	cout << "\nEnter your selection: ";
}

// Simulation to be modified 
/**
void Simulation() {
	
	// Critical section (exclusive access to processes simulation, signaled by locking mtx):
	 
	Pid<int> objSimulation; // an object for the simulation 
	
	mutex mtx;              // mutex for critical section

	mtx.lock(); // Locking the section 
	for (int i = 0; i < 2; i++)
	{
		objSimulation.allocate_map();
		//release_pid(300);
	}
	mtx.unlock();



	
	
	//mtx.lock();
	for (int i = 0; i<n; ++i){ 
		std::cout << c;
	}

	std::cout << '\n';
	//mtx.unlock();
	
}*/