#include "Main_HOG.h"
#include "Mem_Ram.h"
#include <stdio.h>
#include <fstream>

#include <mc_scverify.h>

CCS_MAIN(unsigned int argc, char *argv[])
{
  /*ac_int<17,false> mem_Ram_Addr; 
  ac_int<8,false>  mem_Ram_Data;
  ac_int<13,false> mem_Hog_Addr;
  ac_int<16,false> mem_Hog_Data;
  bool       mem_Hog_WE;*/
  ac_int<8,false> image[WIDTH_IMAGE*HEIGHT_IMAGE];
  ac_int<13,false> cell[CELL_SIZE];
  unsigned int i;
  unsigned int j;
  std::string magic_number;
  int useless;
  std::ifstream fichier("../../img/empire.pgm", std::ios::in);
//  if(!fichier) {
//    std::cout << "ça marche pas" << std::endl;
//  }
  fichier >> magic_number >> useless >> useless >> useless;
 Ram_X : for(j = 0; j < HEIGHT_IMAGE; j++) {
  Ram_Y : for(i = 0; i < WIDTH_IMAGE; i++) {
      fichier >> useless;
      image[i+WIDTH_IMAGE*j] = useless;
    }
  }
  fichier.close();
  CCS_DESIGN(Main_HOG)(image, cell);
  CCS_RETURN(0);
}
