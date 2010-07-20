#include "Replay.h"

Replay::Replay(char * filename) {
    /**
     * Replay
     */
 	int repID ,cmdSize = 0;
	char * cmd;
	FILE * replayFile;
	const char raceList[3] = {'Z','T','P'}; 
	replayFile = fopen(filename, "rb");
	if(replayFile) {
		unpack_section(replayFile, (byte*)&repID, 4);
		unpack_section(replayFile, (byte*)&header, 0x279);
		unpack_section(replayFile, (byte*)&cmdSize, 4);
		cmd = (char *)malloc(cmdSize * sizeof(char));
		unpack_section(replayFile, (byte*)cmd, cmdSize);
	} else {
		printf("Failed to open file %s\n",filename);
		exit(0);
	}
	fclose(replayFile);
	memcpy(&gameName, &header[24], 28);
	gameName[28] = 0x00;
	for(int i = 0; i < 8; i++) {
		memcpy(playerName[i], &header[0xA1+11 + i*36], 28);
		playerName[i][26] = 0x00;
		playerID[i] = header[0xA1+4 + i*36];
		if((unsigned int)header[0xA1+9 + i*36] > 3) {
			playerRace[i] = 'N';
		} else { 
			playerRace[i] = raceList[(int)header[0xA1+9 + i*36]];
		}	
	}

	actionList.build(cmd, cmdSize);
	
	// count how many players we have
	numPlayers = 0;
	for(int i = 0; i < 8; i++) {
		if(playerID[i] > -1) {
			numPlayers++;
		}
	}
}

Replay::~Replay() {
    /**
     * ~Replay
     */
}