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

void gradient_hor(ac_int<9> coord_x,
		  ac_int<8> coord_y,
		  ac_int<8> *gradient){

  int i, j;
  ac_int<8> *val_b, *val_a;
  ac_int<17> mem_Ram_addr;
  Grad_hor_x : for( j = coord_y-1; j < coord_y+1; j++) {
    Grad_hor_y : for(i = coord_x-1; i < coord_x+1; i++) {
      if(i > 0 && 
	 i < WIDTH_IMAGE-1 && 
	 j > 0 && 
	 j < HEIGHT_IMAGE-1) {
	mem_Ram_addr = (j+1)<<9 + i;
	mem_Ram_Read(mem_Ram_addr,val_b);
	mem_Ram_addr = (j-1)<<9 +i;
	mem_Ram_Read(mem_Ram_addr,val_a);
	*gradient = *val_b - *val_a;
	//write_m(i+WIDTH_IMAGE*j,read_m(i+WIDTH_IMAGE*j+1) - read_m(i+WIDTH_IMAGE*j-1));
      } else {
	*gradient = 0;
	//write_m(i+WIDTH_IMAGE*j,0);
      }
    }
  }

}
