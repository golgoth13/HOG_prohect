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
// Revision 1.01 - File debuged
// Additional Comments:
//
////////////////////////////////////////////////////////////////////////////////
#include "HOG_Histogram.h"
//#include "Mem_Ram.h"

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
