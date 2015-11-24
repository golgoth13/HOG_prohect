////////////////////////////////////////////////////////////////////////////////
// Company:        ENSIMAG
// Engineer:       Hans Julien, Perraud Frédéric
// 
// Create Date:    08:11:44 11/10/2015 
// Design Name: 
// Module Name:    MAIN program for Catapult C 
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

void Main_HOG (ac_int<17,false> *mem_Ram_Addr, 
	       ac_int<8,false>  mem_Ram_Data,
	       ac_int<13,false> *mem_Hog_Addr,
	       ac_int<16,false> *mem_Hog_Data,
	       bool       *mem_Hog_WE
	       );
