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

const int sqrt[]   = {0,1,1,2,3,4,6,8,11,16,23,32,45,64,91,128,181,256,362};
const int arctan[] = {256,25,78,137,210,312,479,844,2599};

void norme_pixel(ac_int<8> *norme,
		 ac_int<16> grad) {

	// *norme = m_calcul.racine2(x*x+y*y);
	ac_int<8> grad_h,grad_v;
	grad_v = (ac_int<8>)grad;    //bit de poid faible
	grad_h = (ac_int<8>)grad>>8; //bit poid fort


}

void arg_pixel(ac_int<4> *arg, 
	       ac_int<16> grad) {

	/*if(x == 0) { // Evite la division par 0
	     if (y == 0) {
                 *arg = 0;
             } else {
                 *arg = M_PI/2;
             }
	} else {
           *arg = m_calcul.arctangeante2(y, x);
	   }*/

}
