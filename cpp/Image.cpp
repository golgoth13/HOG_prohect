#include "Image.h"
using namespace std;

//Constructeurs
Image::Image(int width, int height)
        :m_width(width), m_height(height)
{
    m_image = new unsigned char[m_width*m_height];
    init();
}

Image::Image(int width, int height, unsigned char image[])
        :m_width(width), m_height(height)
{
    m_image = new unsigned char[m_width*m_height];
    for(int j = 0; j < m_height; j++) {
        for(int i = 0; i < m_width; i++) {
            m_image[i+m_width*j] = image[i+m_width*j];
        }
    }
}

unsigned char* Image::getImage()
{
    return m_image;
}

void Image::affiche()
{
    for(int j = 0; j < m_height; j++) {
        for(int i = 0; i < m_width; i++) {
            cout << m_image[i+m_width*j] << " ";
        }
        cout << endl;
    }
}

void Image::init()
{
    for(int j = 0; j < m_height; j++) {
        for(int i = 0; i < m_width; i++) {
            m_image[i+m_width*j] = 0;
        }
    }
}
