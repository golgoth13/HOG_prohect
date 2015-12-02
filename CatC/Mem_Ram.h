////////////////////////////////////////////////////////////////////////////////
// Company:        ENSIMAG
// Engineer:       Hans Julien, Perraud Frédéric
// 
// Create Date:    08:11:44 11/10/2015 
// Design Name: 
// Module Name:    Mémoire RAM for test Catapult C 
// Project Name:   pedestre detection HLS
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
////////////////////////////////////////////////////////////////////////////////
#include "ac_int.h"

#define WIDTH_IMAGE  320
#define HEIGHT_IMAGE 240
#define CELL_WIDTH   4
#define CELL_HEIGHT  4
#define CELL_SIZE    16

static  const ac_int<8,false> patern[CELL_SIZE][CELL_SIZE] = {
  {0,157,159,0,0,157,159,0,0,157,159,0,0,157,159,0},
  {6,255,64,0,1,204,116,0,0,119,202,0,0,66,255,4},
  {125,255,15,0,9,244,88,0,0,95,242,6,0,16,255,101},
  {255,235,1,0,63,255,71,0,0,81,255,47,0,2,239,255},
  {255,147,0,0,163,255,65,0,0,77,255,139,0,0,159,255},
  {255,49,0,0,246,255,69,3,6,85,255,226,0,0,62,255},
  {82,5,0,0,255,231,84,17,26,104,250,255,0,0,9,118},
  {3,0,0,0,239,184,108,60,82,134,212,255,0,0,0,6},
  {0,0,0,0,159,159,159,159,157,157,157,157,0,0,0,0},
  {0,0,0,4,64,116,202,255,255,204,119,66,6,1,0,0},
  {0,0,6,101,15,88,242,255,255,244,95,16,125,9,0,0},
  {0,0,47,255,1,71,255,239,235,255,81,2,255,63,0,0},
  {0,0,139,255,0,65,255,159,147,255,77,0,255,163,0,0},
  {0,3,226,255,0,69,255,62,49,255,85,0,255,246,6,0},
  {0,17,255,118,0,84,250,9,5,231,104,0,82,255,26,0},
  {0,60,255,6,0,108,212,0,0,184,134,0,3,239,82,0}};

/*#include "ac_int.h"

// Initialise toutes les cases 
void mem_Ram_Init(ac_int<8,false> v);

void mem_Ram_Read(ac_int<17,false> addr, ac_int<8,false> *data);

void mem_Ram_Write(ac_int<17,false> addr, ac_int<8,false> value);*/
