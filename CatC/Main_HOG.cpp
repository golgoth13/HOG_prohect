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
// Revision 2.01 - FIle compile and produce output
// Additional Comments:
//
////////////////////////////////////////////////////////////////////////////////
#include "Main_HOG.h"

#pragma design top

void Main_HOG (ac_int<8,false> mem_Ram_Data[WIDTH_VGA*HEIGHT_VGA],
	       ac_int<8,false> mem_Ram_Hog[WIDTH_VGA*HEIGHT_VGA],
	       ac_int<1,false> actived,
	       ac_int<1,false> *mode) {
 
	ac_int<10,false>  x, cell_x;
	ac_int<9,false>  y, cell_y;
	ac_int<9,true>   gradient_h;
	ac_int<9,true>   gradient_v;
	ac_int<13,false> histo, addr_Hog_Ram;
	ac_int<17,false> mem_Hog_addr;
	unsigned int     cpt,val,classe,k;

 
	if (actived == 1) {
		*mode = 0;
   
		//traitement HOG
	top_loop_y : for (y = 0; y < WIDTH_VGA-CELL_HEIGHT; y+= 4) {
		top_loop_x : for (x = 0; x < 321-CELL_WIDTH; x+= CELL_WIDTH) {
				//remise à zéro des celulles etudiées
			top_init_cell : for(k = 0; k < 16; k++) {
					cell[k] = 0;
				}
				//calcule des valeurs des 
			top_cell_y : for ( cell_y = 0; cell_y < CELL_HEIGHT; cell_y++){
				top_cell_x : for ( cell_x = 0; cell_x < CELL_WIDTH; cell_x++){
						gradient_pixel(cell_x+x,
							       cell_y+y, 
							       &gradient_h, 
							       &gradient_v, 
							       mem_Ram_Data);
						arg_norme_pixel(&histo, gradient_v, gradient_h);

						val           = histo.slc<9>(0);
						classe        = histo.slc<4>(9);
						cell[classe] += val;

					}
				}

				//vote
				val = 0;
				classe = 0;
			top_hog_cell_vote : for(k = 0; k < 16; k++) {
					if (cell[k] >= val) {
						val    = cell[k];
						classe = k;
					}
				}

				cpt = 0;
				if (val*COEFF_LUM > 1024)
					val = 1024;

				//write result with normalisation
			top_hog_y : for ( cell_y = 0; cell_y < CELL_HEIGHT; cell_y++){
				top_hog_x : for ( cell_x = 0; cell_x < CELL_WIDTH; cell_x++){
						mem_Hog_addr = (cell_y+y)*WIDTH_VGA + cell_x+x;
						mem_Ram_Hog[mem_Hog_addr] = ((COEFF_LUM*val*patern[classe][cpt])>>10);
						cpt++;
					}
				}

			}
		}

	} else {
		*mode = 1;
		//recopie de la caméra sans traitement
	top_vid_y : for (y = 0; y < WIDTH_VGA-1; y++) {
		top_vid_x : for (x = 0; x < WIDTH_IMAGE; x++) {
				mem_Hog_addr = y*WIDTH_IMAGE + x;
				mem_Ram_Hog[mem_Hog_addr] = mem_Ram_Data[mem_Hog_addr] ;
			}
		}
    
	}
 
}
