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
//a virer pour la synthese
#include <iostream>

//a virer pour la synthese
using namespace std;

#pragma design top
void Main_HOG (ac_int<17,false> *mem_Ram_Addr, 
	       ac_int<8,false>  mem_Ram_Data,
	       ac_int<13,false> *mem_Hog_Addr,
	       ac_int<16,false> *mem_Hog_Data,
	       bool       *mem_Hog_WE){

  ac_int<9,false> x;
  ac_int<8,false> y;
  ac_int<8,false> tmp_value = 10 ;
  mem_Ram_Init(tmp_value);
  ac_int<8,true> *grad_hor;
 top_loop_y : for (y=1;y<=HEIGHT_IMAGE-2;y++){
  top_loop_x : for (x=1;x<=WIDTH_IMAGE-2;x++){
      //a virer pour la synthese
      cout << x << " " << y << endl ;
      gradient_hor(x,y,grad_hor);
      *mem_Hog_Data = *grad_hor;
      *mem_Hog_WE = 1;
      
    }
    *mem_Hog_WE = 0;
  }
  
}

//void mem_Hog_Write(ac_int<16> addr,ac_int<8> data){
  

//}
