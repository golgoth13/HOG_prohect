#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include <iostream>

class Image
{
public:

    //Constructeurs
    Image(int width, int height);
    Image(int width, int height, unsigned char* image);

    //Accesseur
    unsigned char* getImage();

    //Affichage
    void affiche();
private:

    unsigned char* m_image;
    int m_width;
    int m_height;

    // Initialise toutes les cases à 0
    void init();
};


#endif // IMAGE_H_INCLUDED
