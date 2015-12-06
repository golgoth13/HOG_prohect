#include "Main_HOG.h"
//a virer pour catapultc
#include "Mem_Ram.h"
#include <stdio.h>
#include <fstream>
#include <sstream>
using namespace std;

//simultate input and output memory
static ac_int<8,false> image[WIDTH_IMAGE*HEIGHT_IMAGE];
static ac_int<8,false> hog[WIDTH_IMAGE*HEIGHT_IMAGE];

#include <mc_scverify.h>

CCS_MAIN(unsigned int argc, char *argv[])
{

    unsigned int i;
  unsigned int j;

  //write test file in input memory
  string magic_number;
  int useless;
  ifstream fichier("../../img/empire.pgm", ios::in);
  if(!fichier) {
    cout << "impossible de lire : ../../img/empire.pgm" << endl;
  }
  fichier >> magic_number >> useless >> useless >> useless;
 Ram_X : for(j = 0; j < HEIGHT_IMAGE; j++) {
  Ram_Y : for(i = 0; i < WIDTH_IMAGE; i++) {
      fichier >> useless;
      image[i+WIDTH_IMAGE*j] = useless;
    }
  }
  fichier.close();

  //call main program
  CCS_DESIGN(Main_HOG)(image, hog);

   //write output memory into output file
  ofstream fichier_out("_histo.pgm", ios::out);
  if(!fichier_out) {
    cerr << "impossible d'écrire : _histo.pgm" << endl;
    CCS_RETURN(1);
  }
  fichier_out << "P2" << endl
	      << WIDTH_IMAGE << " " << HEIGHT_IMAGE << endl
	      << "255" << endl;
 Hog_X : for(j = 0; j < HEIGHT_IMAGE; j++) {
  Hog_Y : for(i = 0; i < WIDTH_IMAGE; i++) {
      fichier_out << hog[j*WIDTH_IMAGE+i] << " ";
    }
    fichier_out << endl;
  }
  fichier_out.close();

  CCS_RETURN(0);
}
