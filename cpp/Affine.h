#ifndef AFFINE_H
#define AFFINE_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <fstream>
#include "HOG_Parameters.h"
#define PRECISION_RACINE 18
#define PRECISION_INVERSE 256

class Affine
{
    public:
        Affine();
        int racine2(int x);
        int arctangeante2(int num, int denom); // Calcule Arctan(num/denom)
        int inverse(int x);

        void writeRacine2(); // Supprimer cette fonction pour la synthèse
        void writeArctangeante2(int precision); // Supprimer cette fonction pour la synthèse
        void writeInverse();
    private:
        int m_racine[PRECISION_RACINE+1];
        int m_arctangeante[N_CLASSES];
        int m_inverse[255];
        int m_precision_atan;
        int m_precision_sqrt;

        void readRacine2();
        void readArctangeante2();
        void readInverse();
};

#endif // AFFINE_H
