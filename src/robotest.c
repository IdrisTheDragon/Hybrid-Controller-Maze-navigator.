#include "allcode_api.h"
   
void happyBirthday(){
	int c = 261;
	int d = 293;
	int e = 329;
	int f = 349;
	int fs = 370;
	int g = 392;
	int a = 440;
	int b = 493;
	int c2 = 523;
	int d2 = 587;

	int L = 400;

	int notes [25] = {d,d,e,d,g,fs,d,d,e,d,a,g,d,d,d2,b,g,fs,e,c2,c2,b,g,a,g};
	int lengths[25] = {L/2,L/2,L,L,L,2*L,L/2,L/2,L,L,L,2*L,L/2,L/2,L,L,L,L,L,L/2,L/2,L,L,L,2*L};
	int i = 0;
    while(1){

		FA_PlayNote(notes[i],lengths[i]);
		FA_PlayNote(0,20);
		i++;
		if(i > 24){i = 0;}
	}
}

