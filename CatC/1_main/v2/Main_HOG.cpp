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
#define PRECISION_RACINE 18
#define PRECISION_ATAN   256
#define N_CLASSES        16


//linear approximation of sqrt
const unsigned int mysqrt[]  = {0,1,1,2,3,4,6,8,11,16,23,32,45,64,91,128,181,
				256,362};
//value for main arctan
const unsigned int arctan[]  = {25,78,137,210,312,479,844,2599};

//linear approximation of division
const unsigned int inverse[] = {1024,512,341,256,204,170,146,128,113,102,93,85,
				78,73,68,64,60,56,53,51,48,46,44,42,40,39,37,36,
				35,34,33,32,31,30,29,28,27,26,26,25,24,24,23,
				23,22,22,21,21,20,20,20,19,19,18,18,18,17,17,
				17,17,16,16,16,16,15,15,15,15,14,14,14,14,14,
				13,13,13,13,13,12,12,12,12,12,12,12,11,11,11,
				11,11,11,11,11,10,10,10,10,10,10,10,10,10,9,9,
				9,9,9,9,9,9,9,9,9,8,8,8,8,8,8,8,8,8,8,8,8,
				8,8,8,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
				6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
				6,6,6,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
				5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,4,4,4,4,4,
				4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
				4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
				4,4,4,4};


//a cell
static ac_int<12, false> cell[CELL_SIZE];

//a virer pour la synthese
#include <iostream>
using namespace std;


void norme_pixel(ac_int<9,false> *norme,
		 ac_int<9,true>  gradient_v,
		 ac_int<9,true>  gradient_h) {

  // (x*x+y*y);
  unsigned int two_square = 0;
  unsigned int i          = 1;
  unsigned int incr       = 2;
  ac_int<9,false> result  = 511;

  two_square = gradient_v*gradient_v + gradient_h*gradient_h;

  //sqrt(two_square)
  if (two_square <= incr) {
    result = mysqrt[two_square];
  } else {
  norm_loop : for (i = 3; i <= PRECISION_RACINE; i++) {
      if (result == 511 && two_square <= (incr<<1)) {
	result = mysqrt[i-1] +
	  (((mysqrt[i] - mysqrt[i-1])*(two_square - incr))>>(i-2));
      }
      incr = incr<<1;
    }

  }

  *norme = result;
}

void divide(ac_int<9,true>  gradient_h,
	    int *result) {

  if (gradient_h.slc<8>(0) > 0 ){
    *result = inverse[gradient_h.slc<8>(0)-1];

  } else {
    *result = -1*inverse[-1*gradient_h.slc<8>(0)-1];
  }

}

//calculate argument of pixel
void arg_pixel(ac_int<4,false> *arg,
	       ac_int<9,true>  gradient_v,
	       ac_int<9,true>  gradient_h) {

  ac_int<5,false>  result = 31;
  int i, val, val2 = 0;

  if(gradient_h == 0) {        // case of divide by 0
    if (gradient_v == 0) {
      result = 0;
    } else {
      result = N_CLASSES>>1;
    }
  } else {
    divide(gradient_h,&val);
    val  = (gradient_v *val)>>2;
    
    if (val >0) {
      arg_loop_1 : for (i = N_CLASSES>>1; i > 0; i--) {
	if (result == 31 && val >= arctan[i-1])
	  result = i;
      }
    }
    if (result == 31 && val >= -1*(arctan[0])) {
      result = 0;
    } else {
       arg_loop_2 : for (i = -1; i > -1*(N_CLASSES>>1); i--) {
	if (result == 31 && val >= -1*(arctan[-i]))
	  result = i+N_CLASSES;
      }

      if (result == 31) {
	result = N_CLASSES>>1;
      }
    }
  }
  *arg = result.slc<4>(0) ;
}

//calculate norme and argument of pixel
void arg_norme_pixel(ac_int<13,false> *res,
		     ac_int<9,true>  gradient_v,
		     ac_int<9,true>  gradient_h) {

  ac_int<9,false> norme;
  ac_int<4,false> arg;
  arg_pixel(&arg,gradient_v,gradient_h);
  *res = arg;
  norme_pixel(&norme,gradient_v,gradient_h);
  *res = (*res<<9) | norme ;

}



void gradient_ver(ac_int<9,false> coord_x,
		  ac_int<8,false> coord_y,
		  ac_int<9,true> *gradient_v,
		  ac_int<8,false> mem_Ram_Data[WIDTH_VGA*HEIGHT_VGA]){

  ac_int<8,false> val_b, val_a;
  ac_int<17,false> mem_Ram_addr;

  if(coord_x > 0               &&
     coord_x < (320-1) &&
     coord_y > 0               &&
     coord_y < 512-1) {

        mem_Ram_addr = (coord_y+1)*512 + coord_x;
        val_b        = mem_Ram_Data[mem_Ram_addr];
        mem_Ram_addr = (coord_y-1)*512 + coord_x;
        val_a        = mem_Ram_Data[mem_Ram_addr];
        *gradient_v  = val_a  - val_b ;

  } else {
    *gradient_v = 0;
  }


}

void gradient_hor(ac_int<9,false> coord_x,
		  ac_int<8,false> coord_y,
		  ac_int<9,true> *gradient_h,
		  ac_int<8,false> mem_Ram_Data[WIDTH_VGA*HEIGHT_VGA]){

  ac_int<8,false> val_b, val_a;
  ac_int<17,false> mem_Ram_addr;

  if(coord_x > 0             &&
     coord_x < 320-1 &&
     coord_y > 0             &&
     coord_y < 512-1) {

        mem_Ram_addr = (coord_y)*512 + coord_x+1;
        val_b        = mem_Ram_Data[mem_Ram_addr];
        mem_Ram_addr = (coord_y)*512 + coord_x-1;
        val_a        = mem_Ram_Data[mem_Ram_addr];
        *gradient_h  = val_b - val_a;

  } else {
    *gradient_h = 0;
  }

}

void gradient_pixel(ac_int<9,false> coord_x,
		    ac_int<8,false> coord_y,
		    ac_int<9,true>  *gradient_h,
		    ac_int<9,true>  *gradient_v,
		    ac_int<8,false> mem_Ram_Data[WIDTH_VGA*HEIGHT_VGA]) {


	gradient_hor(coord_x, coord_y, gradient_h, mem_Ram_Data);
	gradient_ver(coord_x, coord_y, gradient_v, mem_Ram_Data);

}

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
  top_loop_y : for (y = 0; y < 512-CELL_HEIGHT; y+= 4) {
    top_loop_x : for (x = 0; x < 321-CELL_WIDTH; x+= CELL_WIDTH) {
      top_init_cell : for(k = 0; k < 16; k++) {
	  cell[k] = 0;
	}

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
	if (val*8 > 1024)
	  val = 1024;

	//write result with normalisation
      top_hog_y : for ( cell_y = 0; cell_y < CELL_HEIGHT; cell_y++){
	top_hog_x : for ( cell_x = 0; cell_x < CELL_WIDTH; cell_x++){
	    mem_Hog_addr = (cell_y+y)*512 + cell_x+x;
	    mem_Ram_Hog[mem_Hog_addr] = ((8*val*patern[classe][cpt])>>10); // %1024
	    cpt++;
	  }
	}

      }
    }

  } else {
    *mode = 1;
    //recopie de la caméra sans traitement
  top_vid_y : for (y = 0; y < 511; y++) {
    top_vid_x : for (x = 0; x < WIDTH_IMAGE; x++) {
	mem_Hog_addr = y*WIDTH_IMAGE + x;
	mem_Ram_Hog[mem_Hog_addr] = mem_Ram_Data[mem_Hog_addr] ;
      }
    }
    
  }
  //}

}

