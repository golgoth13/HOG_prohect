#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include <iostream>

class Image
{
public:

    //Constructeurs
    Image(int width, int height);
    Image(int width, int height, int* image);

    //Affichage
    void affiche();

    //Calcul des gradients
    void gradient_h(int grad[]); // Calcule le gradient horizontal et le stocke dans grad
    void gradient_v(int grad[]); // Calcule le gradient vertical et le stocke dans grad
private:

    int* m_image;
    int m_width;
    int m_height;

    // Initialise toutes les cases à 0
    void init();
};


#endif // IMAGE_H_INCLUDED
