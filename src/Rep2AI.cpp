#include "Rep2AI.h"

Rep2AI::Rep2AI(Replay* replay) {
    /**
     * Rep2AI
     */
	this->replay = replay;
	for(int i = 0; i < 256; i++) {
		attacks[i] = 0;
		for(int j = 0; i < 350; i++) {
			buildingAtLocation[i][j] = false;
			inBase[i][j] = false;
		}
	}
	numWorkers = 4;
	numExpansions = 0;
	usableGameLength = 900;
	attackSensitivity = .3;
	totalAttacks = 0;
	totalActions = 0;
	playerName = "none";
	playerID = -1;
	playerRace = 'N';
	debugOn = false;
	buildOrder[0] = 0x00;
	path = "C:\\Program Files\\Starcraft\\Rep2AI\\";
	
	replay->actionList.cleanSpam();
}

bool Rep2AI::makeAI() {
	if(!findAttack()) return 0;
	printf("Attack search completed successfully.\n");
	if(!convertActionsToAI()) return 0;
	printf("Actions converted to AI successfully.\n");
	if(!ai.write()) return 0;
	printf("AI written to aiscript.bin successfully.\n");
	return true;
}

bool Rep2AI::runAI() {
    /**
     * runAI
     */
	if(!ai.run()) return 0;
	return true;
}

void Rep2AI::debugMode() {
    /**
     * debugMode
     */
	debugOn = true;
	ai.debugMode();
}	

bool Rep2AI::findPlayer(char* searchPlayer) {
    /**
     * findPlayer
     */
	char* playersByID[8];
	int numPlayers = 0;
	if(!strcmp(searchPlayer,"")) searchPlayer = "because no player name was given";
	for(int i = 0; i < 8; i++) {
		if(replay->playerID[i] > -1) {
			playersByID[replay->playerID[i]] = replay->playerName[i];
			numPlayers++;
		}
		if(!strcmp(replay->playerName[i],searchPlayer)) {
			playerID = replay->playerID[i];
			playerName = replay->playerName[i];
			playerRace = replay->playerRace[i];
				
			printf("Using player %d, %s(%c).\n",playerID,playerName,playerRace);
		}
	}
	if(playerID == -1) {
		printf("Unable to find player %s. Available players are:\n",searchPlayer);
		for(int i = 0; i < numPlayers; i++) {
			printf("(%d) %s\n",i,playersByID[i]);
		}
		printf("Select a player number:");
		scanf("%d",&playerID);
		if(playerID < 0 || playerID > numPlayers) {
			printf("Invalid Player ID.");
			exit(0);
		} else {
			for(int i = 0; i < 8; i++) {
				if(replay->playerID[i] == playerID) {
					playerName = replay->playerName[i];
					playerRace = replay->playerRace[i];
					printf("Using player %d, %s(%c).\n",playerID,playerName,playerRace);
				}
			}
		}
	}
	ai.setRace(playerRace);
	return true;
}

bool Rep2AI::findAttack() {
    /**
     * findAttack
     */
	int attackInsertLocation[300];
	bool attackFound = false;
	
	for(int i = 0; i < totalActions; i++) {
		if(actions[i].type == Attack) {
			int currentMinute = int(actions[i].time / ticksPerSecond / 60) + 1;
			if(currentMinute > 15) break;
			attacks[currentMinute]++;
			attackInsertLocation[currentMinute] = i;
		}
	}
	for(int i = 4; i <= 15; i++) {
		totalAttacks += attacks[i];
	}
	int weightedAttacks = int((totalAttacks/(15 - 3))*(1+attackSensitivity));
	firstAttack = -1;
	for(int i = 4; i <= 15; i++) {
		if(!attackFound) {
			if(attacks[i] > weightedAttacks) {
				firstAttack = i;
				printf("First attack detected at %d minutes.\n",firstAttack);
				attackFound = true;
			}
		}
	}
	if(attackFound) actions[attackInsertLocation[firstAttack]].type = DoAttack;		
	else printf("No rush was detected.\n");
	return true;
}

bool Rep2AI::convertActionsToAI() {
    /**
     * convertActionsToAI
     */
	short BOLength = 18;

	short BOSupply = 4;
	bool farmsDone = false;
	bool noGasYet = true;
	bool noComsatYet = true;
	bool saidGreeting = false;

	buildOrder[0] = 0x00;
	
	replay->actionList.reset();

	setLimits();
	ai.jump(0);
	ai.multiWorkers();
	ai.multiExpand();
	//replace the first jump loacation with the value of the main script
	ai.replace(1, char((ai.getCursorAddress() + 1 + 4) & 0x000000FF)); 
	ai.replace(2, char(((ai.getCursorAddress() + 1 + 4) & 0x0000FF00) >> 8));
	ai.standardIntro();
	ai.say("I was created using jncraton's Rep2AI converter");
	while(replay->actionList.hasNext()) {
		Action action = replay->actionList.next();
		if(action.time > 1000 && !saidGreeting) {
			ai.say("GL HF"); 
			saidGreeting = true;
		}	
		if(usableGameLength*ticksPerSecond < action.time) {
			printf("Done grabbing actions at %f seconds\n",action.time/ticksPerSecond);
			break;
		}
        //selects the action type
        if(action.type == Train || action.type == Hatch) {
            //if its a worker, deal with it appropriately
            if(action.recipient == scv || action.recipient == drone || action.recipient == probe) {
                if(numWorkers < 11) {
                    numWorkers++;
                    ai.safeBuildOne(action.recipient, 1);
                    BOSupply = numWorkers;
                }	
                else if(numWorkers == 11) {
                    ai.multirun(-1);
                    numWorkers = 255;
                }
                else {
                    if(BOSupply > BOLength || BOSupply == 0) BOSupply = 0;
                    else BOSupply++;
                }
            }	
            //if its an ovie, build it instead of training it	
            else if(action.recipient == overlord) {
                action.type = Build;
            }	
            //otherwise just add the train opcode and increment the number of that unit
            else {
                ai.safeTrainOne(action.recipient);
            }	
        }
        if(action.type == Build || action.type == Morph) { //covers build, warp, morph, etc...
            if(action.recipient == ignoredAction) {
            }
            //expand if the building is a townhall
            else if(action.recipient == nexus || action.recipient == command_center) {
                numExpansions++;
                ai.expand(numExpansions,-1);
            }
            // treat hatcheries special because they aren't neccessarily an expansion
            else if(action.recipient == hatchery) {
                if(!isBase(action.x, action.y)) {
                    numExpansions++;
                    ai.expand(numExpansions,-1);
                } else {
                    ai.safeBuildOne(action.recipient, 80);
                }
                defineBase(action.x, action.y);
            }	
            //make sure the script doesn't accidentally create more than one gas or comsat
            else if(action.recipient == assimilator || action.recipient == refinery || action.recipient == extractor) {
                if(noGasYet) {
                    ai.safeBuildOne(action.recipient, 80);
                    noGasYet = false;
                }
            }
            else if(action.recipient == comsat_station) {
                if(noComsatYet) {
                    ai.safeBuildOne(action.recipient, 80);
                    noComsatYet = false;
                }
            }
            //check if farms timing needs to be started when they build a farm
            else if(action.recipient == pylon || action.recipient == supply_depot || action.recipient == overlord) {
                if(!farmsDone) {
                    if(action.time > 5000) {
                        ai.add(farms_timing);
                        printf("Automatic farms construction initialized at %f seconds.\n",action.time/ticksPerSecond);
                        farmsDone = true; //there's no reason to keep manually building farms after farms_timing
                    } 
                    else {
                        ai.safeBuildOne(action.recipient, 80);
                    }	
                }
            }
            //otherwise just build the unit	
            else {
                ai.safeBuildOne(action.recipient, 80);
            }
            
            // Store the build order
            if(BOSupply > 0) {
                sprintf(buildOrder,"%s%d %s\n",buildOrder, BOSupply, unitToString[action.recipient].c_str());
            }
        }                                                                              
        if(action.type == Merge_archon) {
                ai.safeTrainOne(archon);
        }
        if(action.type == Research) {
                ai.safeTech(action.recipient,2);
        }
        if(action.type == DoAttack) {
                ai.doAttack();
                printf("First attack inserted at action %f seconds.\n",action.time/ticksPerSecond);
        }
	}
	int finalLoop = ai.getCursorAddress() + 1 + 4;
	ai.expand(99, -1);
	ai.doAttack();
	ai.wait(500);
	ai.jump(finalLoop);
	return true;
}

void Rep2AI::setLimits() {
    /**
     * setLimits
     */
	ai.setMax(100, scv);
	ai.setMax(1, command_center);
	ai.setMax(1, refinery);
	ai.setMax(1, comsat_station);
	ai.setMax(25, supply_depot);
	ai.setMax(6, barracks);
	ai.setMax(5, factory);
	ai.setMax(5, machine_shop);
	ai.setMax(4, starport);
	ai.setMax(4, control_tower);
	ai.setMax(2, armory);
	ai.setMax(1, academy);
	ai.setMax(2, engineering_bay);
	ai.setMax(1, bunker);
	ai.setMax(4, missile_turret);
	ai.setMax(2, science_facility);
	ai.setMax(1, covert_ops);
	ai.setMax(1, physics_lab);

	ai.setMax(100, drone);
	ai.setMax(25, overlord);
	ai.setMax(4, hatchery);
	ai.setMax(2, lair);
	ai.setMax(1, hive);
	ai.setMax(1, extractor);
	ai.setMax(0, nydus_canal);
	ai.setMax(1, spawning_pool);
	ai.setMax(1, hydralisk_den);
	ai.setMax(1, defiler_mound);
	ai.setMax(3, evolution_chamber);
	ai.setMax(1, ultralisk_cavern);
	ai.setMax(1, greater_spire);
	ai.setMax(1, queen_nest);
	ai.setMax(2, spire);
	ai.setMax(1, defiler_mound);
	ai.setMax(1, creep_colony);
	ai.setMax(1, sunken_colony);
	ai.setMax(1, spore_colony);
	
	ai.setMax(100, probe);
	ai.setMax(25, pylon);
	ai.setMax(1, nexus);	
	ai.setMax(1, assimilator);	
	ai.setMax(6, gateway);
	ai.setMax(1, cybernetics_core);	
	ai.setMax(3, forge);	
	ai.setMax(2, robotics_facility);	
	ai.setMax(1, robotics_support_bay);	
	ai.setMax(1, observatory);	
	ai.setMax(4, stargate);	
	ai.setMax(1, fleet_beacon);	
	ai.setMax(1, arbiter_tribunal);
	ai.setMax(4, photon_cannon);
	ai.setMax(1, citadel_of_adun);	
	ai.setMax(1, templar_archives);	
}

void Rep2AI::defineBase(int x, int y) {
    /**
     * defineBase
     */
	for(int i = 0; i < baseSize; i++) {
		for(int j = 0; j < baseSize; j++) {
			inBase[x-(baseSize/2)+i][y-(baseSize/2)+j] = true;
		}
	}
}

bool Rep2AI::isBase(int x, int y) {
    /**
     * isBase
     */
	return inBase[x][y];
}

char* Rep2AI::getBuildOrderAsText() {
    /**
     * getBuildOrderAsText
     */
    return buildOrder;
}

bool Rep2AI::saveToAiscript(char* filename) {
    /**
     * saveToAiscript
     */
    ai.saveToAiscript(filename);
    return true;
}
