#include <stdio.h>

#include "Replay.h"
#include "AI.h"
#include "Rep2AI.h"

using namespace std;

int main(int argc, char *argv[])
{
	printf("rep2ai 0.7.3 by Jon Craton (joncraton.org)\n");
	printf("usage:  rep2ai -f [file] -p [player] -d -c\n \n");

	char* filename = "";
	char* player = "";
	bool badParameter = false;
	bool run = false;
	bool debug = false;
	bool cont = false;

	for(int i = 1; i < argc; i++) {
		if(string(argv[i]) == "-f") { //filename
			if(i < argc) {
				i++;
				filename = argv[i];
			} else {
				badParameter = true;
			}
		}
		else if(string(argv[i]) == "-p") { //player
			if(i < argc) {
				i++;
				player = argv[i];
			} else {
				badParameter = true;
			}
		}
		else if(string(argv[i]) == "-r") { //run the script
			run = true;
		}
		else if(string(argv[i]) == "-c") { //don't pause after successful rip
			cont = true;
		}			
		else if(string(argv[i]) == "-d") { //run in debug mode
			debug = true;
		}	
		//the param without a flag, or the first unrecognized one, becomes the filename
		else if(filename == "") { //filename
			filename = argv[i];
		}		
		else {
			badParameter = true;
			printf("Unrecognized: %s\n",argv[i]);
		}	
	}

	if(badParameter) {
		printf("Incorrect Paramters.\n");
		return 0;
	}		
	if(!strcmp(filename,"")) {
		free(filename);
		filename = (char*)malloc(512);
		printf("Enter replay filename:");
		scanf("%s",filename);
	}
	
	printf("Loading %s...\n", filename);
	
	Replay replay(filename);
	Rep2AI rep2ai(&replay);
	if(debug) rep2ai.debugMode();
	rep2ai.findPlayer(player);
	rep2ai.makeAI();

	if(!cont) system("PAUSE");
    return EXIT_SUCCESS;
}
