////////////////////////////////////////////////////////////////////////////////
// Company:        ENSIMAG
// Engineer:       Hans Julien, Perraud Frédéric
//
// Create Date:    08:11:44 23/10/2015
// Design Name:
// Module Name:    Histogram calculation in cellular
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
#include "ac_int.h"
#include "HOG_Histogram.h"
//a virer pour la synthese
#include <iostream>
using namespace std;

#define PRECISION_RACINE 18
#define PRECISION_ATAN   255
#define N_CLASSES        16

//linear approximation of sqrt
const unsigned int mysqrt[]  = {0,1,1,2,3,4,6,8,11,16,23,32,45,64,91,128,181,
				256,362};
//value for main arctan
const unsigned int arctan[]  = {25,78,137,210,312,479,844,2599};

//linear approximation of division
const unsigned int inverse[] = {255,127,85,63,51,42,36,31,28,25,23,21,20,18,17,
                                16,15,14,13,13,12,11,11,10,10,9,9,9,8,8,8,8,7,
                                7,7,7,6,6,6,6,6,6,5,5,5,5,5,5,5,5,5,4,4,4,4,4,
                                4,4,4,4,4,4,4,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
                                3,3,3,3,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
                                2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
                                2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

//calculate norme of pixel1
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
    for (i = 3; i <= PRECISION_RACINE; i++) {
      if (result == 511 && two_square <= (incr<<1)) {
	result = mysqrt[i-1] +
	  (((mysqrt[i] - mysqrt[i-1])*(two_square - incr))>>(i-2));
      }
      incr = incr<<1;
    }

  }

  *norme = result;
}

//calculate argument of pixel
void arg_pixel(ac_int<4,false> *arg,
	       ac_int<9,true>  gradient_v,
	       ac_int<9,true>  gradient_h) {

  ac_int<5,false>  result = 31;
  int i, val, val2,val3;

  if(gradient_h == 0) {        // case of divide by 0
    if (gradient_v == 0) {
      result = 0;
    } else {
      result = N_CLASSES>>1;
    }
  } else {
    divide(gradient_h,&val3);
    val = gradient_v *val3;
    /*val3  = (gradient_v*PRECISION_ATAN)/gradient_h;
    val2 = gradient_v * inverse[gradient_h];
    if (val != val3) {
      cout << gradient_h << " " << gradient_v << " " << val << " " << val3 << endl;
    } else {
      cout << "ok" << " " << gradient_h << " " << gradient_v << endl;
      }*/
    if (val >0) {
      for (i = N_CLASSES>>1; i > 0; i--) {
	if (result == 31 && val >= arctan[i-1])
	  result = i;
      }
    }
    if (result == 31 && val >= -1*(arctan[0])) {
      result = 0;
    } else {
      for (i = -1; i > -1*(N_CLASSES>>1); i--) {
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


void divide(ac_int<9,true>  gradient_h,
	    int *result) {

  if (gradient_h > 0 ){
    *result = inverse[gradient_h.slc<8>(0)-1];

  } else {   
    *result = -1*inverse[-1*gradient_h.slc<8>(0)-1];
  }

}

