#ifndef AFFINE_H
#define AFFINE_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <fstream>
#include "HOG_Parameters.h"
#define PRECISION_RACINE 18

class Affine
{
    public:
        Affine();
        //int racine(int x);
        int racine2(int x);
        //int arctangeante(int num, int denom); // Calcule Arctan(num/denom)
        int arctangeante2(int num, int denom); // Calcule Arctan(num/denom)

        //void writeRacine(); // Supprimer cette fonction pour la synthèse
        void writeRacine2(); // Supprimer cette fonction pour la synthèse
        //void writeArctangeante(); // Supprimer cette fonction pour la synthèse
        void writeArctangeante2(int precision); // Supprimer cette fonction pour la synthèse
    private:
        //int m_racine[130050];
        int m_racine[PRECISION_RACINE+1];
        //int m_arctangeante[255][255];
        int m_arctangeante[N_CLASSES];
        int m_precision_atan;
        int m_precision_sqrt;

        //void readRacine();
        void readRacine2();
        //void readArctangeante();
        void readArctangeante2();
};

#endif // AFFINE_H
