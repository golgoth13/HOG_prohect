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
#define PRECISION_ATAN   256
#define N_CLASSES        16

const unsigned int mysqrt[]   = {0,1,1,2,3,4,6,8,11,16,23,32,45,64,91,128,181,256,362};
const unsigned int arctan[] = {256,25,78,137,210,312,479,844,2599};

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
		       if (two_square <= (incr<<1) && result == 511) {
			 result = mysqrt[i-1] + 
			          (((mysqrt[i] - mysqrt[i-1])*(two_square - incr))>>(i-2));
		       }
		       incr = incr<<1;
		}

	}

	*norme = result;


}

void arg_pixel(ac_int<4,false> *arg,
	       ac_int<9,true>  gradient_v,
	       ac_int<9,true>  gradient_h) {

        ac_int<5,false>  result = 31;
	int i, val;
	if(gradient_h == 0) { // Evite la division par 0
	     if (gradient_v == 0) {
                 result = 0;
             } else {
                 result = N_CLASSES>>1;
             }
	} else {
	     val = (gradient_v*PRECISION_ATAN)/gradient_h;
	     if (val >0) {
	          for (i = N_CLASSES>>1; i > 0; i--) {
		      if (val >= arctan[i-1] && result == 31)
			result = i;
		  }
	     }
	     if (val >= -1*(arctan[0]) && result == 31) {
                  result = 0;
	     } else {
	       for (i = -1; i > -1*(N_CLASSES>>1); i--) {
		 if (val >= -1*(arctan[-i]) && result == 31)
		         result = i+N_CLASSES;
		  }
		  
		  if (result == 31) {
		      result = N_CLASSES>>1;
		  }
	     }
	}
	*arg = result.slc<4>(0) ;
}

void arg_norme_pixel(ac_int<13,false> *res,
		     ac_int<9,true>  gradient_v,
		     ac_int<9,true>  gradient_h) {

        ac_int<9,false> norme;
	ac_int<4,false> arg;
	arg_pixel(&arg,gradient_v,gradient_h);
	*res = arg;
	norme_pixel(&norme,gradient_v,gradient_h);
	*res = (*res<<9) | norme ;
	//cout << gradient_h << " " << gradient_v << " " << arg << " " << norme << endl;
}
