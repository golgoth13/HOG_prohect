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
#include "ac_int.h"

#pragma design top
void Main_HOG (ac_int<17> *mem_Ram_Addr, 
	       ac_int<8>  mem_Ram_Data,
	       ac_int<13> *mem_Hog_Addr,
	       ac_int<16> *mem_Hog_Data){

  int i,j;
  //mem_Ram_Init(10);
  ac_int<8> *grad_hor;
  top_loop_x: for (j=1;j<HEIGHT_IMAGE-1;j++){
      top_loop_y: for (i=1;i<WIDTH_IMAGE-1;i++){
      gradient_hor(i,j,grad_hor);
      *mem_Hog_Data = *grad_hor;
      
    }
  }
  
}
