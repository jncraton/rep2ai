#include "Action.h"

Action::Action() {
    /**
     * Action
     */
	time = 0;
	type = 0;
}

Action::~Action() {
    /**
     * ~Action
     */
}

int Action::set(void * address, int t) {
    /**
     * set
     */
	int chunkBytes = 2; //1 byte(player) + 1 byte(type)
	player = *((unsigned char*)(address));
	type = *((unsigned char*)(address)+1);
	time = t;

	switch(type) {
		case 0x09: //Select
			chunkBytes += 1 + (2 * int((*((unsigned char*)(address)+2))));
			break;
		case 0x0A: //Shift Select
			chunkBytes += 1 + (2 * int((*((unsigned char*)(address)+2))));
			break;
		case 0x0B: //Deselect
			chunkBytes += 1 + (2 * int((*((unsigned char*)(address)+2))));
			break;
		case 0x0C: //Build
			recipient = (int)*((unsigned char*)(address)+7);
            sprintf(asString,"Player %d: Build %s\n",player, unitToString[recipient].c_str());
			x = *((char*)address+3);
			y = *((char*)address+5);
			chunkBytes += 7;
			break;
		case 0x0D:	
			chunkBytes += 2;
			break;			
		case 0x0E: //attack move?
			chunkBytes += 4;
			break;
		case 0x12: //use cheat
			chunkBytes += 4;
			break;
		case 0x13:
			chunkBytes += 2;
			break;
		case 0x14:
			chunkBytes += 9;
			break;
		case 0x15:	
			chunkBytes += 10;
			break;
		case 0x18:	//cancel
			chunkBytes += 0;
			break;			
		case 0x19:	
			chunkBytes += 0;
			break;			
		case 0x1A: //stop
			chunkBytes += 1;
			break;
		case 0x1B: //carrier stop?
			chunkBytes += 0;
			break;
		case 0x1C: //reaver stop?
			chunkBytes += 0;
			break;								
		case 0x1E:
			chunkBytes += 1;
			break;
		case 0x1F: //Train
			recipient = *((unsigned char*)(address)+2);
			chunkBytes += 2;
			break;
		case 0x20:
			chunkBytes += 2;
			break;
		case 0x21:
			chunkBytes += 1;
			break;
		case 0x22:
			chunkBytes += 1;
			break;
		case 0x23: //Hatch
			recipient = *((unsigned char*)(address)+2);
			chunkBytes += 2;
			break;						
		case 0x25:
			chunkBytes += 1;
			break;
		case 0x26:
			chunkBytes += 1;
			break;
		case 0x27:
			chunkBytes += 0;
			break;
		case 0x28:
			chunkBytes += 1;
			break;
		case 0x29:
			chunkBytes += 2;
			break;
		case 0x2A:
			chunkBytes += 0;
			break;						
		case 0x2B:
			chunkBytes += 1;
			break;						
		case 0x2C:
			chunkBytes += 1;
			break;						
		case 0x2D:
			chunkBytes += 1;
			break;						
		case 0x2E:
			chunkBytes += 0;
			break;						
		case 0x2F:
			chunkBytes += 4;
			break;
		case 0x30: //Research
			recipient = *((unsigned char*)(address)+2);
			chunkBytes += 1;
			break;						
		case 0x31:
			chunkBytes += 0;
			break;						
		case 0x32: //Upgrade
			recipient = *((unsigned char*)(address)+2);
			chunkBytes += 1;
			break;			
		case 0x35: //Morph
			recipient = *((unsigned char*)(address)+2);
			chunkBytes += 2;
			break;		
		case 0x36:
			chunkBytes += 0;
			break;
		case 0x57:
			chunkBytes += 1;
			break;
		case 0x5A:
			chunkBytes += 0;
			break;												
		default:
			printf("unknown action in replay 0x%X\n",type);
			chunkBytes += 0;
			system("pause");
			break;
	}

	return chunkBytes;
}	
