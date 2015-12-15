#include "Main_HOG.h"
//a virer pour catapultc
//#include "Mem_Ram.h"
#include <stdio.h>
#include <fstream>
#include <sstream>
using namespace std;

#define WIDTH_IMAGE_T  320
#define WIDTH_RAM_T  512
#define HEIGHT_IMAGE_T 240
#define CELL_WIDTH_T   4
#define CELL_HEIGHT_T  4
#define CELL_SIZE_T    16

//simultate input and output memory
static ac_int<8,false> image[WIDTH_RAM_T*HEIGHT_IMAGE_T];
static ac_int<8,false> hog[WIDTH_RAM_T*HEIGHT_IMAGE_T];

#include <mc_scverify.h>

CCS_MAIN(unsigned int argc, char *argv[])
{

    unsigned int i;
  unsigned int j;

  //write test file in input memory
  string file = "barbara3";
  string magic_number;
  int useless;
  ifstream fichier(("../../img/" + file + ".pgm").c_str(), ios::in);
  if(!fichier) {
    cout << "impossible de lire : ../../img/" << file << ".pgm" << endl;
  }
  fichier >> magic_number >> useless >> useless >> useless;
 Ram_X : for(j = 0; j < HEIGHT_IMAGE_T; j++) {
  Ram_Y : for(i = 0; i < WIDTH_IMAGE_T; i++) {
      fichier >> useless;
      image[i+WIDTH_RAM_T*j] = useless;
    }
  }
  fichier.close();

  //call main program
  CCS_DESIGN(Main_HOG)(image, hog);

   //write output memory into output file
  ofstream fichier_out((file + "_histo.pgm").c_str(), ios::out);
  if(!fichier_out) {
    cerr << "impossible d'écrire : " << file << "_histo.pgm" << endl;
    CCS_RETURN(1);
  }
  fichier_out << "P2" << endl
	      << WIDTH_IMAGE_T << " " << HEIGHT_IMAGE_T << endl
	      << "255" << endl;
 Hog_X : for(j = 0; j < HEIGHT_IMAGE_T; j++) {
  Hog_Y : for(i = 0; i < WIDTH_IMAGE_T; i++) {
      fichier_out << hog[j*WIDTH_RAM_T+i] << " ";
    }
    fichier_out << endl;
  }
  fichier_out.close();

  CCS_RETURN(0);
}
