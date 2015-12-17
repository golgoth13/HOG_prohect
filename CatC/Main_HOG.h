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

/*for test catapult : 
void Main_HOG (ac_int<8,false> mem_Ram_Data[WIDTH_VGA*HEIGHT_VGA],
	       ac_int<8,false> mem_Ram_Hog[WIDTH_VGA*HEIGHT_VGA],
	       ac_int<1,false> actived,
	       ac_int<1,false> *mode);
 */
void Main_HOG (ac_int<8,false> *mem_Ram_Data,
	       ac_int<8,false> *mem_Ram_Hog,
	       ac_int<1,false>  actived,
	       ac_int<1,false> *mode);
