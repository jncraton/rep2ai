#include "AI.h"

////////////////////////////////////////////////////////////////////////////////

AI::AI() {
	cursor = -1;
	for(int i = 0; i <= 255; i++) {
		totalUnits[i] = 0;
		upgradeLevel[i] = 0;
		researchComplete[i] = false;
	}
	totalUnits[probe] = 4;
	totalUnits[nexus] = 1;
	totalUnits[scv] = 4;
	totalUnits[command_center] = 1;
	totalUnits[drone] = 4;
	totalUnits[hatchery] = 1;
	totalUnits[overlord] = 1;
	debugOn=false;
}

////////////////////////////////////////////////////////////////////////////////

AI::~AI() {
}

////////////////////////////////////////////////////////////////////////////////

void AI::debugMode() {
	debugOn = true;
}
	
////////////////////////////////////////////////////////////////////////////////

void AI::setRace(char newRace) {
	race = newRace;
	setRaceDefaults();
}

////////////////////////////////////////////////////////////////////////////////

void AI::setRaceDefaults() {
	if(race == 'P') {
		worker = probe;
		townhall = nexus;
		farm = pylon;
	}
	if(race == 'T') {
		worker = scv;
		townhall = command_center;
		farm = supply_depot;
	}
	if(race == 'Z') {
		worker = drone;
		townhall = hatchery;
		farm = overlord;
	}
}

////////////////////////////////////////////////////////////////////////////////

bool AI::write() {
	int length = cursor + 1 + 4; // the standard intro is added
	char closeToss[20] = {'P','M','C','x',0x04,0x00,0x00,0x00,0x40,0x05,0x00,0x00,
			0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00}; 
	char closeTerran[20] = {'T','M','C','x',0x04,0x00,0x00,0x00,0x3F,0x05,0x00,0x00,
			0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00}; 
	char closeZerg[20] = {'Z','M','C','x',0x04,0x00,0x00,0x00,0x41,0x05,0x00,0x00,
			0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00}; 
	FILE * aifile;
	aifile = fopen("aiscript.bin","wb");
	fwrite(&length, sizeof(int), 1, aifile); //length of the script
	fwrite(script, sizeof(char), cursor + 1, aifile); //then the script
	switch(race) {	//then script info	
		case 'P':
			fwrite(closeToss, sizeof(char), 20, aifile);
		break;
		case 'T':
			fwrite(closeTerran, sizeof(char), 20, aifile);
		break;
		case 'Z':
			fwrite(closeZerg, sizeof(char), 20, aifile);
		break;
	}	
	fclose(aifile);
	return true;
}

////////////////////////////////////////////////////////////////////////////////

bool AI::run() {
	cout << "Patching the script into the game..." << endl;
	system("copy airun.dat airun.exe");
	system("mpq2k a airun.exe AI.bin \\scripts\\AI.bin");
	if(!debugOn) system("del AI.bin");
	system("airun.exe");
	system("del airun.exe");
	return true;
}

////////////////////////////////////////////////////////////////////////////////

void AI::build(char number, int building, char priority) {
	if(number > maxUnits[building]) number = maxUnits[building];
	if(building == char(photon_cannon)) waitBuild(1, forge);
	add(0x06); //build command
	add(number);
	add(building);
	add(0x00); //building is expecting a word?
	add(priority);
}

////////////////////////////////////////////////////////////////////////////////

void AI::train(char number, int unit) {
	if(number > maxUnits[unit]) number = maxUnits[unit];
	 add(0x4C); //train command
	 add(number);
	 add(unit);
	 add(0x00); //unit is expecting a word?
}

////////////////////////////////////////////////////////////////////////////////

void AI::attackAdd(char number, int unit) {
	if(number > maxUnits[unit]) number = maxUnits[unit];
	add(attack_add);
	add(number);
	add(unit);
	add(0x00); //unit is expecting a word?
}

////////////////////////////////////////////////////////////////////////////////

void AI::upgrade(char level, char upgrade, char priority) {
    add(0x07); //upgrade command
	add(level);
	add(upgrade);
	add(0x00); //number is expecting a word?
	add(priority);
}

////////////////////////////////////////////////////////////////////////////////

void AI::tech(int technology, char priority) {
	if(!(researchComplete[technology])) {
		add(0x08); //tech command
		add(technology);
		add(0x00); //number is expecting a word?
		add(priority);
		researchComplete[technology] = true;
	}
}

////////////////////////////////////////////////////////////////////////////////

void AI::jump(int address) {
	add(0x00);
	char lowByte, highByte;
	lowByte = address & 0x000000FF;
	highByte = (address & 0x0000FF00) >> 8;
	add(lowByte);
	add(highByte);
}

////////////////////////////////////////////////////////////////////////////////

void AI::jump(char blockNum) { //overloaded jump to support labeled blocks someday
}

////////////////////////////////////////////////////////////////////////////////

void AI::debugJump(int address, string message) {
	add(debug_jump);
	char lowByte, highByte;
	lowByte = address & 0x000000FF;
	highByte = (address & 0x0000FF00) >> 8;
	add(lowByte);
	add(highByte);
	for(unsigned int i = 0; i < message.length(); i++) {
		add(message[i]);	
	}
	add(0x00);
}

////////////////////////////////////////////////////////////////////////////////

void AI::say(string message) {
	//don't display in game messages in debug mode so SCAIEdit can handle the script
	if(!debugOn) debugJump(cursor + message.length() + 4 + 1 + 4, message);
}

//////////////////////// ////////////////////////////////////////////////////////

void AI::multirun(int address) {
	if(address == -1) address = multiWorkersAddress;
	add(0x48);
	char lowByte, highByte;
	lowByte = address & 0x000000FF;
	highByte = (address & 0x0000FF00) >> 8;
	add(lowByte);
	add(highByte);
}

////////////////////////////////////////////////////////////////////////////////

void AI::expand(char expansion, int address) {
	if(address == -1) address = multiExpandAddress;
	add(0x05);
	add(expansion);
	add(address & 0x000000FF);
	add((address & 0x0000FF00) >> 8);
}

////////////////////////////////////////////////////////////////////////////////

void AI::waitBuild(char number, int building) {
	if(number > maxUnits[building]) number = maxUnits[building];
	add(0x09); //wait_build command
	add(number);
	add(building);
	add(0x00);
}

////////////////////////////////////////////////////////////////////////////////

void AI::buildWaitBuild(char number, int building, char priority) {
	build(number, building, priority);
	waitBuild(number, building);
}

////////////////////////////////////////////////////////////////////////////////

void AI::waitBuildStart(char number, int building) {
	if(number > maxUnits[building]) number = maxUnits[building];
	add(0x0A); //wait_buildstart command
	add(number);
	add(building);
	add(0x00);
}

////////////////////////////////////////////////////////////////////////////////

void AI::waitTrain(char number, int unit) {
	if(number > maxUnits[unit]) number = maxUnits[unit];
	add(wait_train);
	add(number);
	add(unit);
	add(0x00);
}


////////////////////////////////////////////////////////////////////////////////

void AI::wait(int duration) {
	add(0x02);
	char lowByte, highByte;
	lowByte = duration & 0x000000FF;
	highByte = (duration & 0x0000FF00) >> 8;
	add(lowByte);
	add(highByte);
}
////////////////////////////////////////////////////////////////////////////////

void AI::defineMax(char number, int unit) {
	add(0x4B);
	add(number);
	add(unit);
	add(0x00);
	maxUnits[unit] = number;
}
////////////////////////////////////////////////////////////////////////////////

void AI::defenseUse(char offset, char number, int unit) {
	add(defenseuse + offset); //offset tells it which type (gg, ag, etc)
	add(number);
	add(unit);
	add(0x00);
}

////////////////////////////////////////////////////////////////////////////////

void AI::creep(char byte) {
	add(0x43);
	add(byte);
}

////////////////////////////////////////////////////////////////////////////////

void AI::stop() {
	add(0x24);
}

////////////////////////////////////////////////////////////////////////////////

void AI::safeBuild(char number, int building, char priority) {
	if(building == gateway)
		buildWaitBuild(1, pylon, priority);
	if(building == cybernetics_core)
		buildWaitBuild(1, gateway, priority);
	if(building == robotics_facility)
		buildWaitBuild(1, cybernetics_core, priority);
	if(building == citadel_of_adun)
		buildWaitBuild(1, cybernetics_core, priority);
	if(building == templar_archives)
		buildWaitBuild(1, citadel_of_adun, priority);
	if(building == academy)
		buildWaitBuild(1, barracks, priority);
	if(building == factory)
		buildWaitBuild(1, barracks, priority);		
	if(building == creep_colony)
		creep(3);	
	if(building == photon_cannon) {
		buildWaitBuild(1, forge, priority);		
		creep(3);
	}		
	if(building == sunken_colony) {
		buildWaitBuild(1, spawning_pool, priority);		
		creep(3);
	}		
	if(building == spore_colony) {
		buildWaitBuild(1, evolution_chamber, priority);		
		creep(3);	
	}	

	build(number, building, priority);
	waitBuildStart(number, building);
}

////////////////////////////////////////////////////////////////////////////////

void AI::safeBuildOne(int building, char priority) {
	totalUnits[building]++;
	safeBuild(totalUnits[building], building, priority);
}

////////////////////////////////////////////////////////////////////////////////

void AI::safeTrain(char number, int unit) {
	switch (unit) {
		case dark_templar: case high_templar: case archon: case dark_archon:
			safeBuild(1, templar_archives, 80);
			break;
	}
	train(number, unit);
}

////////////////////////////////////////////////////////////////////////////////

void AI::safeTech(char technology, char priority) {
	switch (technology) {
	}
	tech(technology, priority);
}

////////////////////////////////////////////////////////////////////////////////

void AI::safeTrainOne(int unit) {
	totalUnits[unit]++;
	safeTrain(char(totalUnits[unit]), unit);
}

void AI::setMax(char number, int unit) {
	maxUnits[unit] = number;
}

////////////////////////////////////////////////////////////////////////////////

void AI::standardIntro() {
	add(0x03); //start_town
	add(0x2B); //transports_off
	add(0x32); //farms_notiming
	switch(race) {
		case 'P':
			defineMax(100, probe);
			defineMax(36, zealot);
			defineMax(36, dragoon);
			defineMax(12, dark_templar);
			defineMax(12, high_templar);
			defineMax(12, archon);
			defineMax(12, dark_archon);
			defineMax(3, shuttle);
			defineMax(6, observer);
			defineMax(12, reaver);
			defineMax(24, scout);
			defineMax(36, corsair);
			defineMax(24, carrier);
			defineMax(8, arbiter);
			defenseUse(gg, 1, zealot);
			defenseUse(ga, 1, zealot);
			defenseUse(gg, 1, dragoon);
			defenseUse(ag, 1, dragoon);
			defenseUse(ga, 1, dragoon);
			defenseUse(aa, 1, dragoon);
			break;
		case 'T':
			defineMax(100, scv);
			defineMax(36, marine);
			defineMax(36, siege_tank);
			defineMax(12, medic);
			defineMax(12, firebat);
			defineMax(16, vulture);
			defineMax(24, goliath);
			defineMax(3, dropship);
			defineMax(6, science_vessel);
			defineMax(12, battlecruiser);
			defineMax(12, valkyrie);
			defineMax(12, wraith);
			defineMax(12, ghost);
			defenseUse(gg, 1, marine);
			defenseUse(ag, 1, marine);
			defenseUse(ga, 1, marine);
			defenseUse(aa, 1, marine);
			defenseUse(gg, 1, siege_tank);
			defenseUse(ga, 1, siege_tank);
			defenseUse(gg, 1, vulture);
			defenseUse(ga, 1, vulture);
			defenseUse(gg, 1, goliath);
			defenseUse(ag, 1, goliath);
			defenseUse(ga, 1, goliath);
			defenseUse(aa, 1, goliath);
			break;
		case 'Z':
			defineMax(100, drone);
			defineMax(36, zergling);
			defineMax(36, hydralisk);
			defineMax(12, lurker);
			defineMax(36, mutalisk);
			defineMax(16, guardian);
			defineMax(24, devourer);
			defineMax(20, scourge);
			defineMax(16, ultralisk);
			defineMax(6, defiler);
			defineMax(6, queen);
			defenseUse(gg, 1, hydralisk);
			defenseUse(ag, 1, hydralisk);
			defenseUse(ga, 1, hydralisk);
			defenseUse(aa, 1, hydralisk);
			defenseUse(gg, 1, zergling);
			defenseUse(ga, 1, zergling);
		break;
	}
	build(5, worker, 1);
	waitBuildStart(5, worker);
}

////////////////////////////////////////////////////////////////////////////////

void AI::add(char hexVal) {
	cursor++;
	script[cursor] = char(hexVal);
}

////////////////////////////////////////////////////////////////////////////////

void AI::replace(int address, char hexVal) {
	script[address] = char(hexVal);
}

////////////////////////////////////////////////////////////////////////////////

int AI::getCursorAddress() {
	return cursor;
}

////////////////////////////////////////////////////////////////////////////////

void AI::display() {
	for(int i = 0; i <= cursor; i++) {
		cout << int(script[i]) << " ";
	}
}

////////////////////////////////////////////////////////////////////////////////

void AI::multiWorkers() {
	multiWorkersAddress = cursor + 1 + 4;
	for(int i = 1; i <= 25; i++) {
		build(i,worker,1);
		waitBuild(i,worker);
	}
	stop();
}

////////////////////////////////////////////////////////////////////////////////

void AI::multiExpand() {
	multiExpandAddress = cursor + 1 + 4;
	add(start_town); 
	build(1, townhall, 2);
	waitBuild(1, townhall);
	for(int i = 1; i <= 20; i++) {
		build(i,worker,1);
		waitBuild(i,worker);
	}
	stop();
}

////////////////////////////////////////////////////////////////////////////////

void AI::doAttack() {
	//attacks with all the military units it thinks it has
	//it first runs train and wait_train to make sure it really has them
	//it then runs attack_add
	//after all units have been trained and added, it runs attack_prepare followed by attack_do
	add(attack_clear);
	switch(race) {
		case 'P':
			for(int i = 0; i <= protossTotalUnits - 1; i++) {
				if(totalUnits[protossUnits[i]] > 0) {
					train(totalUnits[protossUnits[i]], protossUnits[i]);
					waitTrain(totalUnits[protossUnits[i]], protossUnits[i]);
					attackAdd(totalUnits[protossUnits[i]], protossUnits[i]);
				}						
			}
		break;
		case 'T':
			for(int i = 0; i <= terranTotalUnits - 1; i++) {
				if(totalUnits[terranUnits[i]] > 0) {
					train(totalUnits[terranUnits[i]], terranUnits[i]);
					waitTrain(totalUnits[terranUnits[i]], terranUnits[i]);
					attackAdd(totalUnits[terranUnits[i]], terranUnits[i]);
				}						
			}
		break;
		case 'Z':
			for(int i = 0; i <= zergTotalUnits - 1; i++) {
				if(totalUnits[zergUnits[i]] > 0) {
					train(totalUnits[zergUnits[i]], zergUnits[i]);
					waitTrain(totalUnits[zergUnits[i]], zergUnits[i]);
					attackAdd(totalUnits[zergUnits[i]], zergUnits[i]);
				}						
			}
		break;
	}
	add(attack_prepare);
	add(attack_do);
}

