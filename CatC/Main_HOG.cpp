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
#include "HOG_Histogram.h"
#include "ac_int.h"

#define CELL_WIDTH  4
#define CELL_HEIGHT 4
#define CELL_SIZE   16                     //bloc de 4x4

//a virer pour la synthese
#include <iostream>
using namespace std;

//sauvegarde d'une cellule
static ac_int<13,false> cell[CELL_SIZE];  //4 bits de poid fort pour arg et 
                                          //9 pour la norme 

#pragma design top
void Main_HOG (ac_int<17,false> *mem_Ram_Addr, 
	       ac_int<8,false>  mem_Ram_Data,
	       ac_int<13,false> *mem_Hog_Addr,
	       ac_int<16,false> *mem_Hog_Data,
	       bool             *mem_Hog_WE) {

  ac_int<9,false>  x, cell_x;
  ac_int<8,false>  y, cell_y;
  ac_int<8,false>  tmp_value = 10 ;
  ac_int<9,true> gradient_h;
  ac_int<9,true> gradient_v;
  ac_int<13,false> *histo;
  unsigned int cpt;

  mem_Ram_Init(tmp_value);

 top_loop_y : for (y = 0; y <= HEIGHT_IMAGE-1; y+= CELL_HEIGHT) {
  top_loop_x : for (x = 0; x <= WIDTH_IMAGE-1; x+= CELL_WIDTH) {
      cpt = 0;
    top_cell_y : for ( cell_y = y; cell_y <= y+CELL_HEIGHT; cell_y++){
      top_cell_x : for ( cell_x = x; cell_x <= x+CELL_WIDTH; cell_x++){
	  gradient_pixel(cell_x, cell_y, &gradient_h, &gradient_v);
	  arg_norme_pixel(histo, gradient_h,gradient_v);
	  cell[cpt] = *histo;
	  cpt++;
	}
      } 
      //a virer pour la synthese
      //cout << x << " " << y << endl ;
      //pour la simu : 
      //gradient_hor(x,y,grad_hor);
      *mem_Hog_Data = gradient_h;
      *mem_Hog_WE = 1;
      
    }
    *mem_Hog_WE = 0;
  }
  
}

//void mem_Hog_Write(ac_int<16> addr,ac_int<8> data){
  

//}
