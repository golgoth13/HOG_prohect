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

const int mysqrt[]   = {0,1,1,2,3,4,6,8,11,16,23,32,45,64,91,128,181,256,362};
const int arctan[] = {256,25,78,137,210,312,479,844,2599};

void norme_pixel(ac_int<8> *norme,
		 ac_int<16> grad) {

	
        ac_int<8> grad_h, grad_v, result = 0;
	// (x*x+y*y);
	int two_square=0;
	int i = 1;
	int incr = 1;

	grad_v = grad.slc<8>(0) ;    //bit de poid faible
	grad_h = grad.slc<8>(7) ;   //bit poid fort

	two_square = grad_v*grad_v + grad_h*grad_h;

	//sqrt(two_square)
	if (two_square <= incr) {
	        result = mysqrt[0];
	} else {
	     	for (i = 2; i <= PRECISION_RACINE; i++) {
		       if (two_square <= (incr<<2)) {
			 result = mysqrt[i-1] + 
			          (((mysqrt[i] - mysqrt[i-1])>>(two_square - incr))<<incr);
		       }
		       incr = incr<<2;
		}

	}
	if (i == PRECISION_RACINE) {
	        result = mysqrt[two_square]; 
	}

	*norme = result;


}

void arg_pixel(ac_int<4> *arg, 
	       ac_int<16> grad) {

        ac_int<8> grad_h,grad_v,result = 0;
	int i, val;
	grad_v = (ac_int<8>)grad;    //bit de poid faible
	grad_h = (ac_int<8>)grad>>8; //bit poid fort

	if(grad_v == 0) { // Evite la division par 0
	     if (grad_h == 0) {
                 result = 0;
             } else {
                 result = N_CLASSES>>2;
             }
	} else {
	     val = (grad_v<<PRECISION_ATAN)>>grad_h;
	     if (val >0) {
	          for (i = N_CLASSES>>2; i > 0; i--) {
		      if (val >= arctan[i-1])
			result = i;
		  }
	     }
	     if (val >= -arctan[0]) {
                  result = 0;
	     } else {
	          for (i = -1; i > -N_CLASSES>>2; i--) {
		      if (val >= -arctan[-i])
		         result = i+N_CLASSES;
		  }
		  
		  if (i ==  -N_CLASSES>>2) {
		      result = N_CLASSES>>2;
		  }
	     }
	}

	*arg = (ac_int<4>)result;
}
