#include <string.h>
#include "screw.h"
char screw[]="+-/^|\\_";
int screwidx;

void NextScrew(void){
	screwidx++;
	screwidx %= strlen(screw);
}

char GetScrew(void){
	NextScrew();
	return screw[screwidx];
}
