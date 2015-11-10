#include "main.h"
#include <stdio.h>

#include <mc_scverify.h>

CCS_MAIN(int argc, char *argv[])
{
  int i,
  CCS_DESIGN(main_HOG)();
  for ( i = 0; i < WIDTH_IMAGE*HEIGHT_IMAGE-1; i++ ) {
        printf("%d",m_image[i]);
  }
  CCS_RETURN(0);
}
