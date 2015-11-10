#include "Image.h"
using namespace std;

//Constructeurs
Image::Image(int width, int height)
        :m_width(width), m_height(height)
{
    m_image = new int[m_width*m_height];
    init();
}

Image::Image(int width, int height, int image[])
        :m_width(width), m_height(height)
{
    m_image = new int[m_width*m_height];
    for(int j = 0; j < m_height; j++) {
        for(int i = 0; i < m_width; i++) {
            m_image[i+m_width*j] = image[i+m_width*j];
        }
    }
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

void Image::gradient_h(int grad[])
{
    for(int j = 0; j < m_height; j++) {
        for(int i = 0; i < m_width; i++) {
            if(i!=0 && i!=m_width-1 && j!=0 && j!=m_height-1) {
                grad[i+m_width*j] = m_image[i+m_width*j+1] - m_image[i+m_width*j-1];
            } else {
                grad[i+m_width*j] = 0;
            }
        }
    }
}

void Image::gradient_v(int grad[])
{
    for(int j = 0; j < m_height; j++) {
        for(int i = 0; i < m_width; i++) {
            if(i!=0 && i!=m_width-1 && j!=0 && j!=m_height-1) {
                grad[i+m_width*j] = m_image[i+m_width*(j+1)] - m_image[i+m_width*(j-1)];
            } else {
                grad[i+m_width*j] = 0;
            }
        }
    }
}
