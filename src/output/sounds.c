#include "../lib/allcode_api.h"
#include "sounds.h"

//#define HAPPY 1
#define RAINBOW 1
   
void musicPlayer(){

	int c = 261;
	int d = 293;
	int e = 329;
	int f = 349;
	int fs = 370;
	int g = 392;
	int a = 440;
	int bf = 466;
	int b = 493;
	int c2 = 523;
	int d2 = 587;
	int e2 = 659;
	int f2 = 698;
	int p = 0;

	#ifdef HAPPY
	#define L 500
	#define songLength 25
	int notes[songLength][2] = {
		{d,L/2},  {d,L/2},  {e,L},    {d,L},  {g,L},  {fs,2*L},
		{d,L/2},  {d,L/2},  {e,L},    {d,L},  {a,L},  {g,2*L},
		{d,L/2},  {d,L/2},  {d2,L},   {b,L},  {g,L},  {fs,L},
		{e,L},    {c2,L/2}, {c2,L/2}, {b,L},  {g,L},  {a,L},  
		{g,2*L}
	};
	#endif
	#ifdef RAINBOW
	#define songLength 23
	#define L 300
	int notes [songLength][2] = {
		{f,2*L},{f2,2*L},
		{e2,L},{c2,L/2},{d2,L/2},{e2,L},{f2,L},
		{f,2*L},{d2,2*L},
		{c2,4*L},
		{d,L*2},{bf,2*L},
		{a,L},{f,L/2},{g,L/2},{a,L},{bf,L},
		{a,L},{e,L/2},{f,L/2},{g,L},{a,L},
		{f,L*4}
	};
	#endif

	int i = 0;
    for(i = 0; i < songLength; i++){
		FA_PlayNote(notes[i][0],notes[i][1]);
		FA_DelayMillis(20);
	}
}

