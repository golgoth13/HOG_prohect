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

#define PRECISION_RACINE 18
#define PRECISION_ATAN   256
#define N_CLASSES        16

const unsigned int mysqrt[]   = {0,1,1,2,3,4,6,8,11,16,23,32,45,64,91,128,181,256,362};
const unsigned int arctan[] = {256,25,78,137,210,312,479,844,2599};

void norme_pixel(ac_int<8,false> *norme,
		 ac_int<16,false> grad) {

	
        ac_int<8,true> grad_h, grad_v;
        ac_int<8,false> result = 0;
	// (x*x+y*y);
	unsigned int two_square=0;
	unsigned int i = 1;
	unsigned int incr = 2;

	grad_v = grad.slc<8>(0) ;    //bit de poid faible
	grad_h = grad.slc<8>(8) ;   //bit poid fort

	two_square = grad_v*grad_v + grad_h*grad_h;

	//sqrt(two_square)
	if (two_square <= incr) {
	        result = mysqrt[two_square];
	} else {
	     	for (i = 3; i <= PRECISION_RACINE; i++) {
		       if (two_square <= (incr<<1)) {
			 result = mysqrt[i-1] + 
			          (((mysqrt[i] - mysqrt[i-1])*(two_square - incr))/incr);
		       }
		       incr = incr<<1;
		}

	}

	*norme = result;


}

void arg_pixel(ac_int<4,false> *arg, 
	       ac_int<16,false> grad) {

        ac_int<8,true> grad_h,grad_v;
        ac_int<4,false>  result = 0;
	int i, val;
	grad_v = grad.slc<8>(0) ;    //bit de poid faible
	grad_h = grad.slc<8>(8) ;   //bit poid fort
	
	if(grad_v == 0) { // Evite la division par 0
	     if (grad_h == 0) {
                 result = 0;
             } else {
                 result = N_CLASSES>>1;
             }
	} else {
	     val = (grad_v*PRECISION_ATAN)/grad_h;
	     if (val >0) {
	          for (i = N_CLASSES>>1; i > 0; i--) {
		      if (val >= arctan[i-1])
			result = i;
		  }
	     }
	     if (val >= -1*(arctan[0])) {
                  result = 0;
	     } else {
	       for (i = -1; i > -1*(N_CLASSES>>1); i--) {
		 if (val >= -1*(arctan[-i]))
		         result = i+N_CLASSES;
		  }
		  
		  if (result == 0) {
		      result = N_CLASSES>>1;
		  }
	     }
	}

	*arg = result ;
}
