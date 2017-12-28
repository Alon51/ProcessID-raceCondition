#pragma once
#include < iostream >
#include < mutex>
using namespace std;

#ifndef PID_h
#define PID_h

template <class xtype>
struct node {

	node * next;
	int id;
	bool used = false;// determine if the current id is in use at a specific time
	unsigned char * b = NULL;
	int timeToSleep;
};

template <class xtype>
class Pid {

public:

	Pid();  // Constructor
	~Pid(); // Destructor

	int allocate_map();
	int allocate_pid();
	void release_pid(int pid);
	void display();
	void sleepSimulation();
	void sleepTime(int);

private:

	node<xtype> * head;
	int id_Counter;
	mutex mtx;           // mutex for critical section
};
#endif