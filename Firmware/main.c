




#include <16F84A.h>
#fuses HS,NOWDT,NOPROTECT,PUT

#use fast_io(A)
#use fast_io(B)
#use delay(clock=10000000)

BYTE CONST XREIHE_1[5] = { 0b00000000,
0b10110101,
0b11010110,
0b01011010,
0b00000001 }; 

BYTE CONST XREIHE_2[5] = { 0b00011111,
0b01001010,
0b00101001,
0b10100101,
0b00000010 }; 

BYTE CONST XAUS[5] = { 0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b00000000 }; 

BYTE CONST XAN[5] = { 0b11111111,
0b11111111,
0b11111111,
0b11111111,
0b11111111 }; 

BYTE CONST XAUSSEN[5] = { 0b00011111,
0b00000000,
0b00000000,
0b00000000,
0b00000000 }; 

BYTE CONST XSTERN[5] = { 0b00011111,
0b11111111,
0b11111111,
0b11111111,
0b00000001 }; 

BYTE CONST XINNEN[5] = { 0b11100000,
0b00000000,
0b00000000,
0b00000000,
0b11100010 }; 

BYTE CONST XMITTEGELB[5] = { 0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b00000010 }; 

BYTE CONST XMITTEGRUEN[5] = { 0b11100000,
0b00000000,
0b00000000,
0b00000000,
0b00000000 }; 

BYTE CONST XMITTEROT[5] = { 0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b11100000 }; 

BYTE CONST XSTERNROT[5] = { 0b00000000,
0b11111111,
0b11111111,
0b11111111,
0b00000001 }; 

BYTE CONST XSTERNGRUEN[5] = { 0b00011111,
0b00000000,
0b00000000,
0b00000000,
0b00000000 }; 

BYTE CONST XFERN[5] = { 0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b00011100 }; 

BYTE CONST XLINIE1[5] = { 0b00000101,
0b10000111,
0b00000011,
0b00000000,
0b00000000 }; 

BYTE CONST XLINIE2[5] = { 0b00010100,
0b00000000,
0b00011100,
0b00001110,
0b00000000 }; 

BYTE CONST XLINIE3[5] = { 0b00010010,
0b00011100,
0b00000000,
0b01110000,
0b00000000 }; 

BYTE CONST XLINIE4[5] = { 0b00001010,
0b11100000,
0b01110000,
0b00000000,
0b00000000 }; 

BYTE CONST XLINIE5[5] = { 0b00001001,
0b00000000,
0b10000000,
0b11000011,
0b00000001 }; 



#define CHANNEL_COUNT 5
 
#define LAST_PROGRAM 4

#define PRESCALE_SET 20
//#define PRESCALE_SET 80

unsigned int8 segmentmask[CHANNEL_COUNT];
unsigned int8 mask[CHANNEL_COUNT];

unsigned int8 last_step = 10;
unsigned int8 programcounter = 0;
unsigned int8 stepcounter = 0;
unsigned int8 stepprescale = PRESCALE_SET;

void fetch(int8 n, int8 operation)
{
 // 0 = set
 // 1 = or
 // 2 = xor
 // 3 = unset

 unsigned int i;


 if (n == 0) { mask[0] =XREIHE_1[0];mask[1] =XREIHE_1[1];mask[2] =XREIHE_1[2];mask[3] =XREIHE_1[3];mask[4] =XREIHE_1[4];}
 else if (n == 1) { mask[0] =XREIHE_2[0];mask[1] =XREIHE_2[1];mask[2] =XREIHE_2[2];mask[3] =XREIHE_2[3];mask[4] =XREIHE_2[4];}	
 else if (n == 2) { mask[0] =XAUS[0];mask[1] =XAUS[1];mask[2] =XAUS[2];mask[3] =XAUS[3];mask[4] =XAUS[4];}	
 else if (n == 3) { mask[0] =XAN[0];mask[1] =XAN[1];mask[2] =XAN[2];mask[3] =XAN[3];mask[4] =XAN[4];}	
 else if (n == 4) { mask[0] =XAUSSEN[0];mask[1] =XAUSSEN[1];mask[2] =XAUSSEN[2];mask[3] =XAUSSEN[3];mask[4] =XAUSSEN[4];}	
 else if (n == 5) { mask[0] =XSTERN[0];mask[1] =XSTERN[1];mask[2] =XSTERN[2];mask[3] =XSTERN[3];mask[4] =XSTERN[4];}	
 else if (n == 6) { mask[0] =XINNEN[0];mask[1] =XINNEN[1];mask[2] =XINNEN[2];mask[3] =XINNEN[3];mask[4] =XINNEN[4];}	

 else if (n == 7) { mask[0] =XMITTEGELB[0];mask[1] =XMITTEGELB[1];mask[2] =XMITTEGELB[2];mask[3] =XMITTEGELB[3];mask[4] =XMITTEGELB[4];}	
 else if (n == 8) { mask[0] =XMITTEGRUEN[0];mask[1] =XMITTEGRUEN[1];mask[2] =XMITTEGRUEN[2];mask[3] =XMITTEGRUEN[3];mask[4] =XMITTEGRUEN[4];}	
 else if (n == 9) { mask[0] =XMITTEROT[0];mask[1] =XMITTEROT[1];mask[2] =XMITTEROT[2];mask[3] =XMITTEROT[3];mask[4] =XMITTEROT[4];}	
 else if (n == 10) { mask[0] =XSTERNROT[0];mask[1] =XSTERNROT[1];mask[2] =XSTERNROT[2];mask[3] =XSTERNROT[3];mask[4] =XSTERNROT[4];}	
 else if (n == 11) { mask[0] =XSTERNGRUEN[0];mask[1] =XSTERNGRUEN[1];mask[2] =XSTERNGRUEN[2];mask[3] =XSTERNGRUEN[3];mask[4] =XSTERNGRUEN[4];}	
 else if (n == 12) { mask[0] =XFERN[0];mask[1] =XFERN[1];mask[2] =XFERN[2];mask[3] =XFERN[3];mask[4] =XFERN[4];}

 else if (n == 13) { mask[0] =XLINIE1[0];mask[1] =XLINIE1[1];mask[2] =XLINIE1[2];mask[3] =XLINIE1[3];mask[4] =XLINIE1[4];}
 else if (n == 14) { mask[0] =XLINIE2[0];mask[1] =XLINIE2[1];mask[2] =XLINIE2[2];mask[3] =XLINIE2[3];mask[4] =XLINIE2[4];}
 else if (n == 15) { mask[0] =XLINIE3[0];mask[1] =XLINIE3[1];mask[2] =XLINIE3[2];mask[3] =XLINIE3[3];mask[4] =XLINIE3[4];}
 else if (n == 16) { mask[0] =XLINIE4[0];mask[1] =XLINIE4[1];mask[2] =XLINIE4[2];mask[3] =XLINIE4[3];mask[4] =XLINIE4[4];}
 else if (n == 17) { mask[0] =XLINIE5[0];mask[1] =XLINIE5[1];mask[2] =XLINIE5[2];mask[3] =XLINIE5[3];mask[4] =XLINIE5[4];}
/*
else if (n == 20) { mask[0] = 0b11111111; mask[1] = 0b00000000; mask[2] = 0b00000000; mask[3] = 0b00000000; mask[4] = 0b00000000;}
else if (n == 21) { mask[0] = 0b00000000; mask[1] = 0b11111111; mask[2] = 0b00000000; mask[3] = 0b00000000; mask[4] = 0b00000000;}
else if (n == 22) { mask[0] = 0b00000000; mask[1] = 0b00000000; mask[2] = 0b11111111; mask[3] = 0b00000000; mask[4] = 0b00000000;}
else if (n == 23) { mask[0] = 0b00000000; mask[1] = 0b00000000; mask[2] = 0b00000000; mask[3] = 0b11111111; mask[4] = 0b00000000;}
else if (n == 24) { mask[0] = 0b00000000; mask[1] = 0b00000000; mask[2] = 0b00000000; mask[3] = 0b00000000; mask[4] = 0b11111111;}

else if (n == 25) { mask[0] = 0b00000001; mask[1] = 0b00000001; mask[2] = 0b00000001; mask[3] = 0b00000001; mask[4] = 0b00000001;}
else if (n == 26) { mask[0] = 0b00000010; mask[1] = 0b00000010; mask[2] = 0b00000010; mask[3] = 0b00000010; mask[4] = 0b00000010;}
else if (n == 27) { mask[0] = 0b00000100; mask[1] = 0b00000100; mask[2] = 0b00000100; mask[3] = 0b00000100; mask[4] = 0b00000100;}
else if (n == 28) { mask[0] = 0b00001000; mask[1] = 0b00001000; mask[2] = 0b00001000; mask[3] = 0b00001000; mask[4] = 0b00001000;}
else if (n == 29) { mask[0] = 0b00010000; mask[1] = 0b00010000; mask[2] = 0b00010000; mask[3] = 0b00010000; mask[4] = 0b00010000;}
else if (n == 30) { mask[0] = 0b00100000; mask[1] = 0b00100000; mask[2] = 0b00100000; mask[3] = 0b00100000; mask[4] = 0b00100000;}
else if (n == 31) { mask[0] = 0b01000000; mask[1] = 0b01000000; mask[2] = 0b01000000; mask[3] = 0b01000000; mask[4] = 0b01000000;}
else if (n == 32) { mask[0] = 0b10000000; mask[1] = 0b10000000; mask[2] = 0b10000000; mask[3] = 0b10000000; mask[4] = 0b10000000;}
*/
 if (operation == 0) {
   for(i=0;i < CHANNEL_COUNT; i++) segmentmask[i] = mask[i];
 } else if (operation == 1) {
   for(i=0;i < CHANNEL_COUNT; i++) segmentmask[i] |= mask[i];
 } else if (operation == 2) {
   for(i=0;i < CHANNEL_COUNT; i++) segmentmask[i] ^= mask[i];
 } else if (operation == 3) {
   for(i=0;i < CHANNEL_COUNT; i++) segmentmask[i] &= (~mask[i]);
 }
}


void init()
{
  set_tris_a(0b00000000);
  set_tris_b(0b00000000);
 
  output_a(0xFF);
  output_b(0xFF);
  
  fetch(3,0);
}

void programm00() // Laufende Reihe 
{
  last_step = 36;
  if (stepcounter%2) fetch(0,0);
  else fetch(1,0);
}

void programm01() // Alles an/aus
{
  last_step = 36;
  fetch(10,0);
  
  if (stepcounter%2) {
   fetch(11,1);
   fetch(7,1);
   fetch(9,1);
  }
  else {
   fetch(8,1);
  }
}

#define P02_STEPS 12 // an-aus-sequenz von innen nach aussen
void programm02()
{
  last_step = 36;
  if (stepcounter == 1) fetch(2,0);
  else if ((stepcounter%P02_STEPS) == 2) fetch(7,1);
  else if ((stepcounter%P02_STEPS) == 3) fetch(8,1);
  else if ((stepcounter%P02_STEPS) == 4) fetch(9,1);
  else if ((stepcounter%P02_STEPS) == 5) fetch(10,1);
  else if ((stepcounter%P02_STEPS) == 6) fetch(11,1);
  else if ((stepcounter%P02_STEPS) == 7) fetch(12,1);
  else if ((stepcounter%P02_STEPS) == 8) fetch(7,2);
  else if ((stepcounter%P02_STEPS) == 9) fetch(8,2);
  else if ((stepcounter%P02_STEPS) == 10) fetch(9,2);
  else if ((stepcounter%P02_STEPS) == 11) fetch(10,2);
  else if ((stepcounter%P02_STEPS) == 0) fetch(11,2);
  else if ((stepcounter%P02_STEPS) == 1) fetch(12,2);
}

#define P03_STEPS 5
void programm03()  // laufender punkt
{
  last_step = 30;
  fetch(7,0);
  if ((stepcounter%P03_STEPS) == 0) {
   segmentmask[0] = 0b00000010;
   segmentmask[1] = 0b00011111;
  }
  else if ((stepcounter%P03_STEPS) == 1) {
   segmentmask[0] = 0b00000100;
   segmentmask[1] = 0b11100000;
   segmentmask[2] = 0b00000011;
  }
  else if ((stepcounter%P03_STEPS) == 2) {
   segmentmask[0] = 0b00001000;
   segmentmask[2] = 0b01111100;
  }
  else if ((stepcounter%P03_STEPS) == 3) {
   segmentmask[0] = 0b00010000;
   segmentmask[2] = 0b10000000;
   segmentmask[3] = 0b00001111;
  }
  else if ((stepcounter%P03_STEPS) == 4) {
   segmentmask[0] = 0b00000001;
   segmentmask[3] = 0b11110000;
   segmentmask[4] = 0b00000001;
  }

}

#define P04_STEPS 6
void programm04()  // linien
{
  last_step = 32;
  if (stepcounter == 1) fetch(7,0);
  else if ((stepcounter%P04_STEPS) == 2) fetch(17,1);
  else if ((stepcounter%P04_STEPS) == 3) fetch(16,1);
  else if ((stepcounter%P04_STEPS) == 4) fetch(15,1);
  else if ((stepcounter%P04_STEPS) == 5) fetch(14,1);
  else if ((stepcounter%P04_STEPS) == 0) fetch(13,1);
  else if ((stepcounter%P04_STEPS) == 1) fetch(7,0);

}
/*
#define P05_STEPS 13
void programm05()  // test
{
  last_step = 13;
  fetch(20 + stepcounter,0);

}
*/
void displayloop()
{
    if (stepcounter == last_step) {
     stepcounter = 0;
     if (programcounter == LAST_PROGRAM) programcounter = 0;
     else programcounter++;
    } else {
     stepcounter++;
//     programm00();

     if (programcounter == 0) programm00();
     else if (programcounter == 1) programm01();
     else if (programcounter == 2) programm02();
     else if (programcounter == 3) programm03();
     else if (programcounter == 4) programm04();
  //   else if (programcounter == 5) programm05();

    }
}

/**********************************************************
/ MAIN
/**********************************************************/
void main () {

  unsigned int8 ziffer = 0;

  init();
 
 /**********************************************************
 / DISPLAY LOOP
 /**********************************************************/
  for(;;) {
   for(ziffer=0;ziffer < CHANNEL_COUNT; ziffer++)
    {
     output_a( ~(1 << (ziffer)));
     output_b(~(segmentmask[ziffer]));
     delay_ms(3);
    }
   stepprescale--;
   if (stepprescale == 0) {
    stepprescale = PRESCALE_SET;
    displayloop();
   }

  }

}
