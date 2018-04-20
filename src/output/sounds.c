#include "../lib/allcode_api.h"
#include "sounds.h"

//#define HAPPY 1
#define RAINBOW 1
   
void musicPlayer(){

	#define C 261
	#define D 293
	#define E 329
	#define F 349
	#define FS 370
	#define G 392
	#define A 440
	#define B 466
	#define BF 493
	#define C2 523
	#define D2 587
	#define E2 659
	#define F2 698
	#define p 0;

	#ifdef HAPPY
	#define L 500
	#define songLength 25
	int notes[songLength][2] = {
		{D,L/2},  {D,L/2},  {E,L},    {D,L},  {G,L},  {FS,2*L},
		{D,L/2},  {D,L/2},  {E,L},    {D,L},  {A,L},  {G,2*L},
		{D,L/2},  {D,L/2},  {D2,L},   {b,L},  {G,L},  {FS,L},
		{E,L},    {C2,L/2}, {C2,L/2}, {b,L},  {G,L},  {A,L},  
		{G,2*L}
	};
	#endif
	#ifdef RAINBOW
	#define songLength 23
	#define L 300
	int notes [songLength][2] = {
		{F,2*L},{F2,2*L},
		{E2,L},{C2,L/2},{D2,L/2},{E2,L},{F2,L},
		{F,2*L},{D2,2*L},
		{C2,4*L},
		{D,L*2},{BF,2*L},
		{A,L},{F,L/2},{G,L/2},{A,L},{BF,L},
		{A,L},{E,L/2},{F,L/2},{G,L},{A,L},
		{F,L*4}
	};
	#endif

	int i = 0;
    for(i = 0; i < songLength; i++){
		FA_PlayNote(notes[i][0],notes[i][1]);
		FA_DelayMillis(20);
	}
}

