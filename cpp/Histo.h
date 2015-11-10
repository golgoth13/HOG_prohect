#ifndef HISTO_H_INCLUDED
#define HISTO_H_INCLUDED

#include <iostream>
#include <cmath>
#include "Image.h"

class Histo
{
public:

    //Constructeurs
    Histo(int width, int height);
    Histo(int width, int height, int* image);

    //Affichage
    void affiche();

    // Calcule la norme à partir de grad_h et grad_v et la stocke dans norme
    void calcul_norme(int grad_h[], int grad_v[], int norme[]);

    // Calcule l'argument à partir de grad_h et grad_v et le stocke dans arg
    void calcul_arg(int grad_h[], int grad_v[], int arg[]);
private:

    int* m_histo;
    int m_width;
    int m_height;

    // Initialise toutes les cases à 0
    void init();
};

#endif // HISTO_H_INCLUDED
