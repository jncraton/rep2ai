#ifndef AI_H
#define AI_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

typedef int unit;

class AI
{

	public:
		AI();
		~AI();
		void debugMode();
		void setRaceDefaults();
		void setRace(char newRace);
		void build(char number, int building, char priority);
		void upgrade(char level, char upgrade, char priority);
		void tech(int upgrade, char priority);
		void train(char number, int unit);
		void attackAdd(char number, int unit);
		void waitBuild(char number, int building);
		void buildWaitBuild(char number, int building, char priority);
		void waitBuildStart(char number, int building);
		void waitTrain(char number, int unit);
		void wait(int duration);
		void defineMax(char number, int unit);
		void defenseUse(char offset, char number, int unit);
		void jump(int address);
		void jump(char block);
		void debugJump(int address, string message);
		void say(string message);
		void multirun(int address);
		void expand(char expansion, int address);
		void safeBuild(char number, int building, char priority);
		void safeBuildOne(int building, char priority);
		void safeTrain(char number, int unit);
		void safeTrainOne(int unit);
		void safeTech(char technology, char priority);
		void creep(char byte);
		void stop();
		void setMax(char number, int unit);
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
		
		char script[8192]; //holds the hex opcodes for aiscript.bin
		
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
"Marine", "Ghost", "Vulture", "Goliath", "Unknown Unit", "Tank", "Unknown Unit", "SCV", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", //16
"Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", //32
"Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Drone", "Overlord", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", //48
"Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", //64
"Probe", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", //80
"Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", //96
"Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Command Center", "Comsat", "Unknown Unit", "Supply Depot", "Refinery", "Barracks", //112
"Academy", "Factory", "Starport", "Control Tower", "Science Facility", "Covert Ops", "Physics Lab", "Unknown Unit", "Machine Shop", "Unknown Unit", "Engineering Bay", "Armory", "Missile Turret", "Bunker", "Unknown Unit", "Unknown Unit", //128
"Unknown Unit", "Unknown Unit", "Unknown Unit", "Hatchery", "Lair", "Hive", "Nydus Canal", "Hydralisk Den", "Defiler Mound", "Greater Spire", "Queen's Nest", "Evolution Chamber", "Ultralisk Cavern", "Spire", "Spawning Pool", "Creep Colony", //144
"Spore Colony", "Unknown Unit", "Sunken Colony", "Unknown Unit", "Unknown Unit", "Extractor", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Nexus", "Robotics Facility", "Pylon", "Assimilator", "Unknown Unit", "Observatory", //160
"Gateway", "Unknown Unit", "Photon Cannon", "Citadel of Adun", "Cybernetics Core", "Templar Archives", "Forge", "Stargate", "Unknown Unit", "Fleet Beacon", "Arbiter Tribunal", "Robotics Support Bay", "Shield Battery", "Unknown Unit", "Unknown Unit", "Unknown Unit", //176
"Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", //192
"Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", //208
"Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", //224
"Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", //240
"Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit", "Unknown Unit" //256
};

//Protoss
const int nexus = 154;
const int probe = 64;
const int pylon = 156;
const int assimilator = 157;
const int forge = 166;
const int gateway = 160;
const int photon_cannon = 162;
const int cybernetics_core = 164;
const int citadel_of_adun = 163;
const int templar_archives = 165;
const int robotics_facility = 155;
const int robotics_support_bay = 171;
const int observatory = 159;
const int stargate = 167;
const int arbiter_tribunal = 170;
const int fleet_beacon = 169;

const int p_armor = 5;

const int zealot = 65;
const int dragoon = 66;
const int dark_templar = 61;
const int high_templar = 67;
const int archon = 68;
const int dark_archon = 63;
const int shuttle = 69;
const int reaver = 83;
const int observer = 84;
const int corsair = 60;
const int scout = 70;
const int carrier = 72;
const int arbiter = 71;

const int protossUnits[11] = {zealot, dragoon, dark_templar, high_templar, archon,
	dark_archon, reaver, corsair, scout, carrier, arbiter};
const int protossTotalUnits = 11;

//Terran
const int scv = 7;
const int command_center = 106;
const int comsat_station = 107;
const int supply_depot = 109;
const int refinery = 110;
const int barracks = 111;
const int academy = 112;
const int factory = 113;
const int starport = 114;
const int control_tower = 115;
const int science_facility = 116;
const int covert_ops = 117;
const int physics_lab = 118;
const int machine_shop = 120;
const int engineering_bay = 122;
const int armory = 123;
const int missile_turret = 124;
const int bunker = 125;

const int marine = 0;
const int ghost = 1;
const int vulture = 2;
const int goliath = 3;
const int siege_tank = 5;
const int wraith = 8;
const int science_vessel = 9;
const int dropship = 11;
const int battlecruiser = 12;
const int nuclear_missile = 14;
const int firebat = 32;
const int medic = 34;
const int valkyrie = 58;

const int terranUnits[11] = {marine, firebat, ghost, medic, siege_tank,
	vulture, goliath, wraith, valkyrie, battlecruiser};
const int terranTotalUnits = 10;

//Zerg
const int drone = 41;
const int overlord = 42;
const int infested_command_center = 130;
const int hatchery = 131;
const int lair = 132;
const int hive = 133;
const int nydus_canal = 134;
const int hydralisk_den = 135;
const int defiler_mound = 136;
const int greater_spire = 137;
const int queen_nest = 138;
const int evolution_chamber = 139;
const int ultralisk_cavern = 140;
const int spire = 141;
const int spawning_pool = 142;
const int creep_colony = 143;
const int spore_colony = 144;
const int sunken_colony = 146;
const int extractor = 149;

const int zergling = 37;
const int hydralisk = 38;
const int ultralisk = 39;
const int mutalisk = 43;
const int guardian = 44;
const int queen = 45;
const int defiler = 46;
const int scourge = 47;
const int infested_terran = 50;
const int devourer = 62;
const int lurker = 103;

const int zergUnits[8] = {zergling, hydralisk, mutalisk, lurker, scourge, guardian,
	devourer, ultralisk};
const int zergTotalUnits = 8;

#endif
