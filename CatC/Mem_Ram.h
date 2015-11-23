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

#define WIDTH_IMAGE 40
#define HEIGHT_IMAGE 20
#include "ac_int.h"

// Initialise toutes les cases 
void mem_Ram_Init(ac_int<8> v,ac_int<1> *ok);

void mem_Ram_Read(ac_int<17> addr, ac_int<8> *data);

void mem_Ram_Write(ac_int<17> addr, ac_int<8> value);
