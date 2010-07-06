#ifndef REPLAY_H
#define REPLAY_H

#include <stdio.h>
#include <memory.h>
#include "ActionList.h"
#include "unpack.h"

using namespace std;

class Replay
{

	public:
		Replay(char * filename);
		~Replay();
		
		ActionList actionList;
		char header[0x279];
		char gameName[29];
		char playerName[8][26];
		char playerRace[8];
		char playerID[8];		

	private:
		
};

#endif
