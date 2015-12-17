#include "Main_Comp_H.h"
#include "Mem_Ram.h"
#include <stdio.h>
#include <fstream>

#include <mc_scverify.h>

CCS_MAIN(unsigned int argc, char *argv[])
{
  
  //TODO : Voir la différence sur CatapultC entre un tableau de tableaux
  //		et un gros tableau.
  ac_int<8,false> image[256*512];
  ac_int<8,false> comp[256*512];
  unsigned int i;
  unsigned int j;

  int useless;
  std::string magic_number;
  std::ifstream fichier("image/lena2.pgm", std::ios::in);
  
  //ecriture du fichier de test
  if(!fichier) {
    std::cout << "ça ne lit pas le fichier" << std::endl;
    CCS_RETURN(1);
  }
  getline(fichier, magic_number);
  getline(fichier, magic_number);
  fichier >> useless >> useless;
  std::cout << " img " << magic_number << useless << std::endl;
  Ram_Y : for(i = 0; i < HEIGHT_IMAGE; i++) {
 Ram_X : for(j = 0; j < WIDTH_IMAGE; j++) {
    fichier >> useless;
     image[i*512 + j]  = useless;
     //image[i*512 + j] = i %201;
    }
  }
  //fichier.close();
std::cout << " fichier OK" << std::endl;
  //appel du programme principal
  CCS_DESIGN(Comp_H)(image, comp);

  //ecriture du resultat
  std::ofstream fichier_out("histo.pgm", std::ios::out);
  if(!fichier_out) {
    std::cerr << "ça n'ecrit pas le fichier" << std::endl;
    CCS_RETURN(1);
  }
  fichier_out << "P2" << std::endl 
	      << WIDTH_IMAGE << " " << HEIGHT_IMAGE << std::endl 
	      << "255" << std::endl;
  Ond_Y : for(i = 0; i < HEIGHT_IMAGE; i++) {
 Ond_X : for(j = 0; j < WIDTH_IMAGE; j++) {
      fichier_out << comp[i*512 + j] << " ";
    }
  }
  fichier_out << std::endl;
  fichier_out.close();
  
  CCS_RETURN(0);
}
