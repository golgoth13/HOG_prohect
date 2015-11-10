////////////////////////////////////////////////////////////////////////////////
// Company:        ENSIMAG
// Engineer:       Hans Julien, Perraud Frédéric
// 
// Create Date:    08:11:44 11/10/2015 
// Design Name: 
// Module Name:    Gradient calculation 
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
#include "Mem_Ram.h"

void gradient_h(void){

  int i, j;  
  yolo:for( j = 0; j < HEIGHT_IMAGE; j++) {
    yala:for(i = 0; i < WIDTH_IMAGE; i++) {
      if(i!=0 && i!=WIDTH_IMAGE-1 && j!=0 && j!=HEIGHT_IMAGE-1) {
	write_m(i+WIDTH_IMAGE*j,read_m(i+WIDTH_IMAGE*j+1) - read_m(i+WIDTH_IMAGE*j-1));
      } else {
	  write_m(i+WIDTH_IMAGE*j,0);
      }
    }
  }

}
