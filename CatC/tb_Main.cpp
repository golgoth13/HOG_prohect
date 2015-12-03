#include "Main_HOG.h"
//a virer pour catapultc
#include "Mem_Ram.h"
#include <stdio.h>
#include <fstream>

#include <mc_scverify.h>

CCS_MAIN(unsigned int argc, char *argv[])
{
  
  ac_int<8,false> image[WIDTH_IMAGE*HEIGHT_IMAGE];
  ac_int<8,false> hog[WIDTH_IMAGE*HEIGHT_IMAGE];
  unsigned int i;
  unsigned int j;

  //ecriture du fichier de test
  std::string magic_number;
  int useless;
  std::ifstream fichier("../../img/empire.pgm", std::ios::in);
  if(!fichier) {
    std::cout << "ça marche pas" << std::endl;
  }
  fichier >> magic_number >> useless >> useless >> useless;
 Ram_X : for(j = 0; j < HEIGHT_IMAGE; j++) {
  Ram_Y : for(i = 0; i < WIDTH_IMAGE; i++) {
      fichier >> useless;
      image[i+WIDTH_IMAGE*j] = useless;
    }
  }
  fichier.close();

  //appel du programme principal
  CCS_DESIGN(Main_HOG)(image, hog);

  //ecriture du resultat
  std::ofstream fichier_out("_histo.pgm", std::ios::out);
  if(!fichier_out) {
    std::cerr << "ça marche pas" << std::endl;
    CCS_RETURN(1);
  }
  fichier_out << "P2" << std::endl 
	      << WIDTH_IMAGE << " " << HEIGHT_IMAGE << std::endl 
	      << "255" << std::endl;
 Hog_X : for(j = 0; j < HEIGHT_IMAGE; j++) {
  Hog_Y : for(i = 0; i < WIDTH_IMAGE; i++) {
      fichier_out << hog[j*HEIGHT_IMAGE+i] << " ";
    }
  }
  fichier_out << std::endl;
  fichier_out.close();
  CCS_RETURN(0);
}
