#ifndef HISTO_H_INCLUDED
#define HISTO_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
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
    void affiche_graphique(std::string nom, int pattern[N_CLASSES][CELL_SIZE*CELL_SIZE]);

private:

    int* m_histo;
    int* m_histo_norme;
    int m_width;
    int m_height;
    int m_histo_width;
    int m_histo_height;
    Image m_img;

    //Calcul des gradients
    void gradient_pixel(int* grad_h, int* grad_v, int image[], int x, int y); // Calcule les gradients du pixel et les stocke dans grad_h et grad_v

    // Calcule la norme à partir de grad_h et grad_v et la stocke dans norme
    void calcul_norme_pixel(float* norme, int x, int y);

    // Calcule l'argument à partir de grad_h et grad_v et le stocke dans arg
    void calcul_arg_pixel(float* arg, int x, int y);

    // Calcule l'histogramme
    void calcul_histo_no_ram();
};

#endif // HISTO_H_INCLUDED
