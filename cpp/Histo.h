#ifndef HISTO_H_INCLUDED
#define HISTO_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <fstream>
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
    void affiche_ascii();
    void affiche_graphique();

private:

    int* m_histo;
    int m_width;
    int m_height;
    int m_histo_width;
    int m_histo_height;
    Image m_img;

    //Calcul des gradients
    //void gradient_h(unsigned char grad[], unsigned char image[]); // Calcule le gradient horizontal et le stocke dans grad
    //void gradient_v(unsigned char grad[], unsigned char image[]); // Calcule le gradient vertical et le stocke dans grad
    //void gradient_cell(unsigned char grad_h[], unsigned char grad_v[], unsigned char image[], int x_cell, int y_cell); // Calcule les gradients de la cellule et les stocke dans grad_h et grad_v
    void gradient_pixel(int* grad_h, int* grad_v, int image[], int x, int y); // Calcule les gradients du pixel et les stocke dans grad_h et grad_v

    // Calcule la norme à partir de grad_h et grad_v et la stocke dans norme
    //void calcul_norme(unsigned char grad_h[], unsigned char grad_v[], float norme[]);
    void calcul_norme_pixel(float* norme, int x, int y);

    // Calcule l'argument à partir de grad_h et grad_v et le stocke dans arg
    //void calcul_arg(unsigned char grad_h[], unsigned char grad_v[], float arg[]);
    void calcul_arg_pixel(float* arg, int x, int y);

    // Calcule l'histogramme
    //void calcul_histo();
    void calcul_histo_no_ram();
};

#endif // HISTO_H_INCLUDED
