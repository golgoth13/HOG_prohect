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
    Histo(int width, int height, unsigned char* image); // La taille de l'image

    //Affichage
    void affiche();

private:

    int* m_histo;
    int m_width;
    int m_height;
    int m_histo_width;
    int m_histo_height;
    Image m_img;

    //Calcul des gradients
    void gradient_h(unsigned char grad[], unsigned char image[]); // Calcule le gradient horizontal et le stocke dans grad
    void gradient_v(unsigned char grad[], unsigned char image[]); // Calcule le gradient vertical et le stocke dans grad

    // Calcule la norme à partir de grad_h et grad_v et la stocke dans norme
    void calcul_norme(unsigned char grad_h[], unsigned char grad_v[], float norme[]);

    // Calcule l'argument à partir de grad_h et grad_v et le stocke dans arg
    void calcul_arg(unsigned char grad_h[], unsigned char grad_v[], float arg[]);

    // Calcule l'histogramme
    void calcul_histo();
};

#endif // HISTO_H_INCLUDED
