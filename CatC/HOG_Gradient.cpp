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
#include "HOG_Gradient.h"

void gradient_ver(ac_int<9> coord_x,
		  ac_int<8> coord_y,
		  ac_int<8> *gradient_v){

  ac_int<8> val_b, val_a;
  ac_int<17> mem_Ram_addr;
 
  if(coord_x > 0 && 
     coord_x < (WIDTH_IMAGE-1) && 
     coord_y > 0 && 
     coord_y < HEIGHT_IMAGE-1) {
        mem_Ram_addr = (coord_y+1)*WIDTH_IMAGE + coord_x;
        mem_Ram_Read(mem_Ram_addr,&val_b);
        mem_Ram_addr = (coord_y-1)*WIDTH_IMAGE + coord_x;
        mem_Ram_Read(mem_Ram_addr,&val_a);
        *gradient_v = val_a  - val_b ;
  } else {
    *gradient_v = 0;
  }
		
	
}

void gradient_hor(ac_int<9> coord_x,
		  ac_int<8> coord_y,
		  ac_int<8> *gradient_h){

  ac_int<8> val_b, val_a;
  ac_int<17> mem_Ram_addr;

  if(coord_x > 0 && 
     coord_x < WIDTH_IMAGE-1 && 
     coord_y > 0 && 
     coord_y < HEIGHT_IMAGE-1) {
        mem_Ram_addr = (coord_y)*WIDTH_IMAGE + coord_x+1;
        mem_Ram_Read(mem_Ram_addr,&val_b);
        mem_Ram_addr = (coord_y)*WIDTH_IMAGE + coord_x-1;
        mem_Ram_Read(mem_Ram_addr,&val_a);
        *gradient_h = val_b - val_a;
  } else {
    *gradient_h = 0;
  }

}

void gradient_pixel(ac_int<9> coord_x,
		    ac_int<8> coord_y,
		    ac_int<16> *gradient_p) {

	
	ac_int<8> gradient_h, gradient_v;
	gradient_hor(coord_x, coord_y, &gradient_h);
	gradient_ver(coord_x, coord_y, &gradient_v);
	*gradient_p = (gradient_h<<8) | gradient_v;

}
