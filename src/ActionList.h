#ifndef ACTIONLIST_H
#define ACTIONLIST_H

#include <stdio.h>
#include <stdlib.h>
#include "Action.h"

using namespace std;

class ActionList
{
	public:
		ActionList();
		~ActionList();
		void reset();
		void build(char * address,  int size);
		Action next();
		Action previous();
		Action removeCurrent();
		bool hasNext();
		void cleanSpam();
		
		Action * p_first;
		Action * p_current;
		int numActions;
	
	private:
		int append(char * address, int time);
};

#endif
