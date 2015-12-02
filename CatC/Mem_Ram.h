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
  {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
  {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
  {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
  {5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5},
  {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
  {7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7},
  {8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8}};

/*#include "ac_int.h"

// Initialise toutes les cases 
void mem_Ram_Init(ac_int<8,false> v);

void mem_Ram_Read(ac_int<17,false> addr, ac_int<8,false> *data);

void mem_Ram_Write(ac_int<17,false> addr, ac_int<8,false> value);*/
