#include "ActionList.h"

ActionList::ActionList() {
    /**
     * ActionList
     */
	numActions = 0;
}

ActionList::~ActionList() {
    /**
     * ~ActionList
     */
}

void ActionList::reset() {
    /**
     * reset
     */
    p_current = p_first; 
}

void ActionList::build(char * address,  int size) {
    /**
     * build
     */
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

int ActionList::append(char * chunk, int time) {
    /**
     * append
     */
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

Action ActionList::next() {
    /**
     * next
     */
	if(p_current->p_next == 0) {
		return Action();
	} else {
		p_current = p_current->p_next;
		return *p_current;
	}
}

bool ActionList::hasNext() {
    /**
     * hasNext
     */
	return p_current->p_next;
}

Action ActionList::previous() {
    /**
     * previous
     *
     * There is no pointer for this, so we have to search the list
     */

    Action * current = p_current;
    
    reset();
    
    while ( p_current->p_next != current ) {
        next();
    }
    
    return *p_current;
}

Action ActionList::removeCurrent() {
    /**              
     * removeCurrent
     *
     * removes the current action
     * the previous action becomes the new current action
     */
    
    previous();
    
    Action * current = p_current->p_next;
    
    p_current->p_next = p_current->p_next->p_next;
    
    free(current);
    
	return *p_current;
}

void ActionList::cleanSpam() {
    /**
     * cleanSpam
     */
    
    int num_units[256];
    float spam = 0.0;
    
    const float spam_threshold = 10.0;
    const int spam_interval = 10;
    const float spam_interval_weight = 15.0;
     
    Action * old_current = p_current; 
    
    reset();
    
    FILE * debug;
    debug = fopen("replay.txt","w");
    
    int last_build_time = 0;
    
    while(hasNext()) {
        spam = 0.0;
        
        next();

        if(p_current->isBuildOrTrain()) {
            if( p_current->time - last_build_time < spam_interval ) {
                spam += spam_interval_weight;
            }
            last_build_time = p_current->time;
        }
        
        if ( spam > spam_threshold ) {
            removeCurrent();
            fprintf(debug, "SPAM:");
        }
        fprintf(debug, p_current->asString);
    }
    
    fclose(debug);
    
    p_current = old_current;
     
	return;
}
