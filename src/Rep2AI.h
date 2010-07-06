#ifndef REP2AI_H
#define REP2AI_H

#include <stdio.h>
#include <string.h>

#include "AI.h"
#include "Action.h"
#include "Replay.h"

using namespace std;

class Rep2AI {
	struct action {
		char type;
		char unit;
		int time;
		int x;
		int y;
	};
	
	public:
		Rep2AI(Replay* replay);
		void debugMode();
		bool runAI();
		bool findPlayer(char* searchPlayer);
		bool makeAI();
	private:
		bool notSpam();
		bool findAttack();
		bool convertActionsToAI();
		void setLimits();
		void defineBase(int x, int y);
		bool isBase(int x, int y);

		Replay * replay;
		AI ai;
		action actions[10000]; //actual replay actions
		int attacks[256]; //holds number of attack actions each minute
		int totalAttacks; //number of attack actions for the player
		float attackSensitivity; //threshold for detecting the first attack
		int firstAttack; //minute of the first attack
		int totalActions; //number of actions ripped from the replay
		int usableGameLength; //time to mimick replay
		
		bool buildingAtLocation[350][350]; //keeps track of where things have been built 
		bool inBase[350][350]; //keeps track of where bases are 

		int numWorkers;
		int numExpansions;
		
		bool debugOn;
		
		char* path;

		int playerID;
		char playerRace;
		char* playerName;
		char enemyRace;
		char* enemyName; 
};

const float ticksPerSecond = 23.8;
const int baseSize = 12;



#endif
