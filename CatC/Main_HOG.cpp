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
// Revision 1.01 - FIle compile and produce output
// Additional Comments:
//
////////////////////////////////////////////////////////////////////////////////
#include "Main_HOG.h"
#include "Mem_Ram.h"
#include "HOG_Gradient.h"
#include "HOG_Histogram.h"
#include "ac_int.h"

//a cell
static ac_int<12, false> cell[CELL_SIZE];

//a virer pour la synthese
#include <iostream>
using namespace std;


#pragma design top

void Main_HOG (ac_int<8,false> *mem_Ram_Data,
	       ac_int<8,false> *mem_Ram_Hog) {

  ac_int<9,false> x, cell_x;
  ac_int<8,false> y, cell_y;
  ac_int<9,true> gradient_h;
  ac_int<9,true> gradient_v;
  ac_int<13,false> histo, addr_Hog_Ram;
  ac_int<17,false> mem_Hog_addr;
  unsigned int cpt,val,classe,k;


 top_loop_y : for (y = 0; y <= HEIGHT_IMAGE-1; y+= CELL_HEIGHT) {
  top_loop_x : for (x = 0; x <= WIDTH_IMAGE-1; x+= CELL_WIDTH) {
      for(k = 0; k < 16; k++) {
        cell[k] = 0;
      }
           
    top_cell_y : for ( cell_y = y; cell_y < y+CELL_HEIGHT; cell_y++){
      top_cell_x : for ( cell_x = x; cell_x < x+CELL_WIDTH; cell_x++){
	  gradient_pixel(cell_x, cell_y, &gradient_h, &gradient_v, mem_Ram_Data);
	  arg_norme_pixel(&histo, gradient_h, gradient_v);

          val = histo.slc<9>(0);
	  classe = histo.slc<4>(9);
	  cell[classe] += val;

	  //pour debug
	  /*cout << cell_x << " "
	    << cell_y << " "
	    <<  histo.slc<9>(0) << " "
	    << histo.slc<4>(9) << " " << endl;
	  */
	}
      }

      //vote
      val = 0;
      classe = 0;
      for(k = 0; k < 16; k++) {
        if (cell[k] >= val) {
          val = cell[k];
          classe = k;
        }
      }


      cpt = 0;
      if (val > 1024)
        val = 1024;

      //write result with normalisation
    top_hog_y : for ( cell_y = y; cell_y < y+CELL_HEIGHT; cell_y++){
      top_hog_x : for ( cell_x = x; cell_x < x+CELL_WIDTH; cell_x++){
	  mem_Hog_addr = (cell_y)*WIDTH_IMAGE + cell_x;
	  mem_Ram_Hog[mem_Hog_addr] = (val*patern[classe][cpt])>>10; // %1024
	  cpt++;

	}
      }


    }
  }

}

