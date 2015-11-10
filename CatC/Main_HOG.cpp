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
#include "Main_HOG.h"
#include "Mem_Ram.h"
#include "HOG_Gradient.h"

#pragma design top
void Main_HOG (void){
    int i;
    for (i=0;i<12;i++){
        init_m();   
        gradient_h();
    }
}
