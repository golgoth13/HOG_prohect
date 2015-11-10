#ifndef HISTO_H_INCLUDED
#define HISTO_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "Image.h"

#define CELL_SIZE 4
#define N_CLASSES 16

class Histo
{
public:

    //Constructeurs
    Histo(int width, int height, int* image); // La taille de l'image

    //Affichage
    void affiche();

    // Calcule la norme à partir de grad_h et grad_v et la stocke dans norme
    void calcul_norme(int grad_h[], int grad_v[], float norme[]);

    // Calcule l'argument à partir de grad_h et grad_v et le stocke dans arg
    void calcul_arg(int grad_h[], int grad_v[], float arg[]);

    // Calcule l'histogramme
    void calcul_histo();
private:

    int* m_histo;
    int m_width;
    int m_height;
    int m_histo_width;
    int m_histo_height;
    Image m_img;

    // Initialise toutes les cases à 0
    void init();
};

#endif // HISTO_H_INCLUDED
