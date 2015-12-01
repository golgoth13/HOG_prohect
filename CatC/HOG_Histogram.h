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

void norme_pixel(ac_int<8,false> *norme,
		 ac_int<9,true>  gradient_v,
		 ac_int<9,true>  gradient_h);

void arg_pixel(ac_int<4,false> *arg,
	       ac_int<9,true>  gradient_v,
	       ac_int<9,true>  gradient_h);

void arg_norme_pixel(ac_int<13,false> *res,
		     ac_int<9,true>  gradient_v,
		     ac_int<9,true>  gradient_h);
