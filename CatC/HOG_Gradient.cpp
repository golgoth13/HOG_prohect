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

void gradient_hor(ac_int<9> coord_x,
		  ac_int<8> coord_y,
		  ac_int<8> *gradient_h){

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
			} else {
				*gradient = 0;
			}
		}
	}
}

void gradient_ver(ac_int<9> coord_x,
		  ac_int<8> coord_y,
		  ac_int<8> *gradient_v){

	int i, j;
	ac_int<8> *val_b, *val_a;
	ac_int<17> mem_Ram_addr;
Grad_hor_x : for( j = coord_y-1; j < coord_y+1; j++) {
	Grad_hor_y : for(i = coord_x-1; i < coord_x+1; i++) {
			if(i > 0 && 
			   i < WIDTH_IMAGE-1 && 
			   j > 0 && 
			   j < HEIGHT_IMAGE-1) {
				mem_Ram_addr = (j)<<9 + i+1;
				mem_Ram_Read(mem_Ram_addr,val_b);
				mem_Ram_addr = (j)<<9 + i-1;
				mem_Ram_Read(mem_Ram_addr,val_a);
				*gradient = *val_b - *val_a;
			} else {
				*gradient = 0;
			}
		}
	}
}

void gradient_pixel(ac_int<9> coord_x,
		    ac_int<8> coord_y,
		    ac_int<16> *gradient_p) {

	
	ac_int<8> gradient_h, gradient_v;
	gradient_hor(coord_x, coord_y, &gradient_h);
	gradient_hor(coord_x, coord_y, &gradient_v);
	*gradient_p = (gradient_h<<8) | gradient_v;

}
