#include "Histo.h"
using namespace std;


//Constructeurs
Histo::Histo(int width, int height)
        :m_width(width), m_height(height)
{
    m_histo = new int[m_width*m_height];
    init();
}

Histo::Histo(int width, int height, int image[])
        :m_width(width), m_height(height)
{
    m_histo = new int[m_width*m_height];
    //calcul histo
}

void Histo::affiche()
{
    for(int j = 0; j < m_height; j++) {
        for(int i = 0; i < m_width; i++) {
            cout << m_histo[i+m_width*j] << " ";
        }
        cout << endl;
    }
}

void Histo::init()
{
    for(int j = 0; j < m_height; j++) {
        for(int i = 0; i < m_width; i++) {
            m_histo[i+m_width*j] = 0;
        }
    }
}

void Histo::calcul_norme(int grad_h[], int grad_v[], int norme[])
{
    for(int j = 0; j < m_height; j++) {
        for(int i = 0; i < m_width; i++) {
            int x = grad_h[i+m_width*j];
            int y = grad_v[i+m_width*j];
            norme[i+m_width*j] = sqrt(x*x+y*y);
        }
    }
}

void Histo::calcul_arg(int grad_h[], int grad_v[], int arg[])
{
   for(int j = 0; j < m_height; j++) {
        for(int i = 0; i < m_width; i++) {
            int x = grad_h[i+m_width*j];
            int y = grad_v[i+m_width*j];
            if(x == 0) {
                if (y == 0) {
                    arg[i+m_width*j] = 0;
                } else {
                    arg[i+m_width*j] = M_PI/2;
                }
            } else {
                arg[i+m_width*j] = atan(y/x);
            }
        }
    }
}
