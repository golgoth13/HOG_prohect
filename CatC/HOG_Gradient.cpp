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
//a virer pour la synthese
#include <iostream>
#include "HOG_Gradient.h"

//a virer pour la synthese
using namespace std;

void gradient_ver(ac_int<9,false> coord_x,
		  ac_int<8,false> coord_y,
		  ac_int<9,true> *gradient_v,
		  ac_int<8,false> *mem_Ram_Data){

  ac_int<8,false> val_b, val_a;
  ac_int<17,false> mem_Ram_addr;

  if(coord_x > 0 && 
     coord_x < (WIDTH_IMAGE-1) && 
     coord_y > 0 && 
     coord_y < HEIGHT_IMAGE-1) {
        mem_Ram_addr = (coord_y+1)*WIDTH_IMAGE + coord_x;
        val_b = mem_Ram_Data[mem_Ram_addr];
        mem_Ram_addr = (coord_y-1)*WIDTH_IMAGE + coord_x;
        val_a = mem_Ram_Data[mem_Ram_addr];
        *gradient_v = val_a  - val_b ;
	//a virer pour la synthese
	//cout << coord_x << endl;
  } else {
    *gradient_v = 0;
  }
		
	
}

void gradient_hor(ac_int<9,false> coord_x,
		  ac_int<8,false> coord_y,
		  ac_int<9,true> *gradient_h,
		  ac_int<8,false> *mem_Ram_Data){

  ac_int<8,false> val_b, val_a;
  ac_int<17,false> mem_Ram_addr;
  if(coord_x > 0 && 
     coord_x < WIDTH_IMAGE-1 && 
     coord_y > 0 && 
     coord_y < HEIGHT_IMAGE-1) {
        mem_Ram_addr = (coord_y)*WIDTH_IMAGE + coord_x+1;
        val_b = mem_Ram_Data[mem_Ram_addr];
        mem_Ram_addr = (coord_y)*WIDTH_IMAGE + coord_x-1;
        val_a = mem_Ram_Data[mem_Ram_addr];
        *gradient_h = val_b - val_a;
  } else {
    *gradient_h = 0;
  }

}

void gradient_pixel(ac_int<9,false> coord_x,
		    ac_int<8,false> coord_y,
		    ac_int<9,true>  *gradient_h,
		    ac_int<9,true>  *gradient_v,
		    ac_int<8,false> *mem_Ram_Data) {

	
	gradient_hor(coord_x, coord_y, gradient_h, mem_Ram_Data);
	gradient_ver(coord_x, coord_y, gradient_v, mem_Ram_Data);
	//a virer pour la synthese
	/*cout << *gradient_h  << " " 
	     << *gradient_v  << " " 
	     << coord_x     << " " 
	     << coord_y     << " " 
	     << endl;*/

}
