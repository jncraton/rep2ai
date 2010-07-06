#ifndef AI_H
#define AI_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class AI
{

	public:
		AI();
		~AI();
		void debugMode();
		void setRaceDefaults();
		void setRace(char newRace);
		void build(char number, char building, char priority);
		void upgrade(char level, char upgrade, char priority);
		void tech(char upgrade, char priority);
		void train(char number, char unit);
		void attackAdd(char number, char unit);
		void waitBuild(char number, char building);
		void buildWaitBuild(char number, char building, char priority);
		void waitBuildStart(char number, char building);
		void waitTrain(char number, char unit);
		void wait(int duration);
		void defineMax(char number, char unit);
		void defenseUse(char offset, char number, char unit);
		void jump(int address);
		void jump(char block);
		void debugJump(int address, string message);
		void say(string message);
		void multirun(int address);
		void expand(char expansion, int address);
		void safeBuild(char number, char building, char priority);
		void safeBuildOne(char building, char priority);
		void safeTrain(char number, char unit);
		void safeTrainOne(char unit);
		void safeTech(char technology, char priority);
		void creep(char byte);
		void stop();
		void setMax(char number, char unit);
		void standardIntro();
		bool write();
		bool run();
		void display();
		void add(char hexVal);
		void replace(int address, char hexVal);	
		int getCursorAddress();	
		void multiWorkers();
		void multiExpand();
		void doAttack();
	
	private:
		
		char script[10000]; //holds the hex opcodes for aiscript.bin
		
		//these allow more racially portable code
		int worker;
		int townhall;
		int farm;
		
		//address used by mulitun commands
		int multiWorkersAddress;
		int multiExpandAddress;
		int multiAttackAddress;
		int mainAddress;
		
		int totalUnits[256]; //count of current units under AI control
		bool researchComplete[256]; //keeps track of what has been researched so it isn't accidentally repeated
		int upgradeLevel[256]; //keeps track of upgrades so they don't go over their maximum
		int maxUnits[256]; //holds the maximum amount to be built or trained
		
		int cursor;
		char race;
		
		bool debugOn; 
};

//ai opcodes
const char start_town = 0x03;
const char tech = 0x08;
const char wait_build = 0x09;
const char wait_buildstart = 0x0A;
const char attack_clear = 0x0B;
const char attack_add = 0x0C;
const char attack_prepare = 0x0D;
const char attack_do = 0x0E;
const char defenseuse_gg = 0x17;
const char defenseuse_ag = 0x18;
const char defenseuse_ga = 0x19;
const char defenseuse_aa = 0x1A;
const char defenseclear_gg = 0x1B;
const char defenseclear_ag = 0x1C;
const char defenseclear_ga = 0x1D;
const char defenseclear_aa = 0x1E;
const char send_suicide = 0x1F;
const char wait_train = 0x4E;
const char farms_timing = 0x33;
const char debug_jump = 0x27;
const char debug = 0x27;
const char stop = 0x24;
const char creep = 0x43;

const char defenseuse = 0x17;
const char defenseclear = 0x1B;

const char gg = 0;
const char ag = 1;
const char ga = 2;
const char aa = 3;

const string unitToString[256] = {
"Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", //16
"Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", //32
"Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", //48
"Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", //64
"Probe", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", //80
"Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", //96
"Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", //112
"Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", //128
"Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", //144
"Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Nexus", "Robotics Facility", "Pylon", "Assimilator", "Unknown Unit", "Observatory", //160
"Gateway", "Unknown Unit", "Photon Cannon", "Citadel of Adun", "Cybernetics Core", "Templar Archives", "Forge", "Stargate", "Unknown Unit", "Fleet Beacon", "Arbiter Tribunal", "Robotics Support Bay", "Shield Battery", "Unknown Unit", "Unknown Unit", "Unknown Unit", //176
"Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", //192
"Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", //208
"Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", //224
"Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", //240
"Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit" //256
};

//Protoss
const char nexus = 154;
const char probe = 64;
const char pylon = 156;
const char assimilator = 157;
const char forge = 166;
const char gateway = 160;
const char photon_cannon = 162;
const char cybernetics_core = 164;
const char citadel_of_adun = 163;
const char templar_archives = 165;
const char robotics_facility = 155;
const char robotics_support_bay = 171;
const char observatory = 159;
const char stargate = 167;
const char arbiter_tribunal = 170;
const char fleet_beacon = 169;

const char p_armor = 5;

const char zealot = 65;
const char dragoon = 66;
const char dark_templar = 61;
const char high_templar = 67;
const char archon = 68;
const char dark_archon = 63;
const char shuttle = 69;
const char reaver = 83;
const char observer = 84;
const char corsair = 60;
const char scout = 70;
const char carrier = 72;
const char arbiter = 71;

const char protossUnits[11] = {zealot, dragoon, dark_templar, high_templar, archon,
	dark_archon, reaver, corsair, scout, carrier, arbiter};
const int protossTotalUnits = 11;

//Terran
const char command_center = 106;
const char scv = 7;
const char supply_depot = 109;
const char refinery = 110;
const char comsat_station = 107;
const char barracks = 111;
const char academy = 112;
const char factory = 113;
const char starport = 114;
const char control_tower = 115;
const char science_facility = 116;
const char covert_ops = 117;
const char physics_lab = 118;
const char machine_shop = 120;
const char engineering_bay = 122;
const char armory = 123;
const char missile_turret = 124;
const char bunker = 125;

const char marine = 0;
const char ghost = 1;
const char vulture = 2;
const char goliath = 3;
const char siege_tank = 5;
const char wraith = 8;
const char science_vessel = 9;
const char dropship = 11;
const char battlecruiser = 12;
const char nuclear_missile = 14;
const char firebat = 32;
const char medic = 34;
const char valkyrie = 58;

const char terranUnits[11] = {marine, firebat, ghost, medic, siege_tank,
	vulture, goliath, wraith, valkyrie, battlecruiser};
const int terranTotalUnits = 10;

//Zerg
const char drone = 41;
const char overlord = 42;
const char infested_command_center = 130;
const char hatchery = 131;
const char lair = 132;
const char hive = 133;
const char nydus_canal = 134;
const char hydralisk_den = 135;
const char defiler_mound = 136;
const char greater_spire = 137;
const char queen_nest = 138;
const char evolution_chamber = 139;
const char ultralisk_cavern = 140;
const char spire = 141;
const char spawning_pool = 142;
const char creep_colony = 143;
const char spore_colony = 144;
const char sunken_colony = 146;
const char extractor = 149;

const char zergling = 37;
const char hydralisk = 38;
const char ultralisk = 39;
const char mutalisk = 43;
const char guardian = 44;
const char queen = 45;
const char defiler = 46;
const char scourge = 47;
const char infested_terran = 50;
const char devourer = 62;
const char lurker = 103;

const char zergUnits[8] = {zergling, hydralisk, mutalisk, lurker, scourge, guardian,
	devourer, ultralisk};
const int zergTotalUnits = 8;

#endif
