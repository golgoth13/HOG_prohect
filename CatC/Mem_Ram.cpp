////////////////////////////////////////////////////////////////////////////////
// Company:        ENSIMAG
// Engineer:       Hans Julien, Perraud Frédéric
// 
// Create Date:    08:11:44 11/10/2015 
// Design Name: 
// Module Name:    Mémoire RAM for test Catapult C 
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
#include "Mem_Ram.h"
#include "stdio.h"
#include "ac_int.h"
// Enlever pour la synthèse
#include <fstream>
//#include <iostream>

static ac_int<8,false> m_image[WIDTH_IMAGE*HEIGHT_IMAGE];

void mem_Ram_Init(ac_int<8,false> v) {
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
      m_image[i+WIDTH_IMAGE*j] = useless;
    }
  }
  fichier.close();
}
 

void mem_Ram_Read(ac_int<17,false> addr, ac_int<8,false> *data){
  *data = m_image[addr];
}

void mem_Ram_Write(ac_int<17,false> addr, ac_int<8,false> value){
  m_image[addr] = value;

}
