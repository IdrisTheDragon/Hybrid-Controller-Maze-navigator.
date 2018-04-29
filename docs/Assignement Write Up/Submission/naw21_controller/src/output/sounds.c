#include "../lib/allcode_api.h"
#include "sounds.h"

//#define HAPPY 1
//#define RAINBOW 1
//#define SUN 1
#define Brahms


#define C 261
#define D 293
#define E 329
#define F 349
#define FS 370
#define G 392
#define A 440
#define BF 466
#define B 493
#define C2 523
#define D2 587
#define E2 659
#define F2 698
#define FS2 740
#define G2 784
#define A2 880
#define P 0


void musicPlayer(){
	#ifdef HAPPY
	#define L 500
	#define songLength 25
	const int notes[songLength][2] = {
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
	const int notes [songLength][2] = {
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

	#ifdef SUN
	#define songLength 37
	#define L 400
	const int notes[songLength][2] = {
		{P,L},{B,L},{A,L},{B,L},
		{G,L},{B,L/2},{G,L/2},{A,L},{B,L},
		{P,L},{B,L},{A,L},{B,L},
		{G,L*(3/2)},{G,L/2},{A,L},{G,L},
		{P,L},{B,L},{A,L},{G,L},
		{E2,L/2},{G2,L/2},{A2,L/2},
		{D2,L/2},{G2,L/2},{A2,L/2},
		{C2,L/2},{G2,L/2},{A2,L/2},
		{D2,L/2},{G2,L/2},{A2,L/2},
		{G2,L/2},{FS2,L/2},{E2,L/2},{D2,L/2},
	};
	#endif

	#ifdef Brahms
	#define songLength 47
	#define L 500
	const int notes[songLength][2] = {
		{E,L/2},{E,L/2},{G,2*L},
		{E,L/2},{E,L/2},{G,2*L},
		{E,L/2},{G,L/2},{C2,L},{B,L},
		{A,L},{A,L},{G,L},
		{D,L/2},{E,L/2},{F,2*L},
		{D,L/2},{F,L/2},{B,L/2},{A,L/2},{G,L},
		{B,L},{C2,2*L},
		{C,L/2},{C,L/2},{C2,2*L},
		{A,L/2},{F,L/2},{G,2*L},
		{E,L/2},{C,L/2},{F,L},{G,L},
		{A,L},{G,2*L},
		{C,L/2},{C,L/2},{C2,2*L},
		{A,L/2},{F,L/2},{G,2*L},
		{E,L/2},{C,L/2},{F,L},{E,L},
		{D,L},{C,2*L}
	};
	#endif

	//play the song stored in the array
	int i = 0;
    for(i = 0; i < songLength; i++){
		FA_PlayNote(notes[i][0],notes[i][1]);
		FA_DelayMillis(2);
	}
}

