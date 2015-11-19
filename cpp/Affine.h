#ifndef AFFINE_H
#define AFFINE_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <fstream>

class Affine
{
    public:
        Affine();
        int racine(int x);
        int arctangeante(int num, int denom); // Calcule Arctan(num/denom)

        void writeRacine(); // Supprimer cette fonction pour la synthèse
        void writeArctangeante(); // Supprimer cette fonction pour la synthèse
    private:
        int m_racine[130050];
        int m_arctangeante[255][255];

        void readRacine();
        void readArctangeante();
};

#endif // AFFINE_H
