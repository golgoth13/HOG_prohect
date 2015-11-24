#include "Main_HOG.h"
#include "Mem_Ram.h"
#include <stdio.h>

#include <mc_scverify.h>

CCS_MAIN(int argc, char *argv[])
{
  int i;
  ac_int<17> mem_Ram_Addr; 
  ac_int<8>  mem_Ram_Data;
  ac_int<13> mem_Hog_Addr;
  ac_int<16> mem_Hog_Data;
  bool       mem_Hog_WE;
  CCS_DESIGN(Main_HOG)(&mem_Ram_Addr,
		       mem_Ram_Data,
		       &mem_Hog_Addr,
		       &mem_Hog_Data,
		       &mem_Hog_WE);
  for ( i = 0; i < WIDTH_IMAGE*HEIGHT_IMAGE-1; i++ ) {
    printf("g");
  }
  CCS_RETURN(0);
}
