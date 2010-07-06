#include "ActionList.h"

////////////////////////////////////////////////////////////////////////////////

ActionList::ActionList() {
	numActions = 0;
}

////////////////////////////////////////////////////////////////////////////////

ActionList::~ActionList() {
}	

////////////////////////////////////////////////////////////////////////////////

void ActionList::build(char * address,  int size) {
	for(int pos = 0; pos < size;) {
		int time = *(int*)((int(address) + pos));
		char numBytes = *((char*)(address) + 4 + pos);
		pos += 5;
		int chunkEnd = pos + numBytes;
		while(pos < chunkEnd) {
			pos += append(((char*)address + pos), time);
		}
	}
	p_current = p_first;
}

////////////////////////////////////////////////////////////////////////////////

int ActionList::append(char * chunk, int time) {
	if(numActions == 0) {
		p_first = new Action;
		p_current = p_first;
	} else {	
		p_current->p_next = new Action;
		p_current = p_current->p_next;
	}
	numActions++;
	return p_current->set(chunk, time);	
}

////////////////////////////////////////////////////////////////////////////////

Action ActionList::next() {
	if(p_current->p_next == 0) {
		return Action();
	} else {
		p_current = p_current->p_next;
		return *p_current;
	}
}

////////////////////////////////////////////////////////////////////////////////

bool ActionList::hasNext() {
	return p_current->p_next;
}
