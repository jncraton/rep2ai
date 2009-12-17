#ifndef ACTION_H
#define ACTION_H

#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Action
{

	public:
		Action();
		~Action();
		int set(void * address, int t);
		
		char player; //player that executed the action
		char type; //command opcode
		int time;
		char recipient; //recipient of the action (unit trained, etc)
		short int x;
		short int y;
		
		Action * p_next;
	
	private:
		
};

//replay actions
const char Train = 31;
const char Hatch = 35;
const char Upgrade = 50;
const char Warp = 12;
const char Build = 12;
const char Morph = 53; //used when a building is upgraded
const char Research = 48;
const char Attack = 21;
const char Move = 20;
const char Merge_archon = 42;
const char DoAttack = 200; //action added to tell the script when to attack
const char ignoredAction = 201; //action won't be added

#endif
