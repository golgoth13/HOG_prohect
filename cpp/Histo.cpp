#include "Histo.h"
using namespace std;


//Constructeurs
Histo::Histo(int width, int height, int image[])
        :m_width(width), m_height(height), m_histo_width(width/CELL_SIZE), m_histo_height(height/CELL_SIZE), m_img(Image(m_width, m_height, image))
{
    if (m_width%CELL_SIZE!=0 || m_height%CELL_SIZE!=0) {
        cout << "Taille non divisible par " << CELL_SIZE << endl;
        exit(1);
    }
    m_histo = new int[m_histo_width*m_histo_height];
    //m_img = new Image(m_width, m_height, image);

    calcul_histo();
}

void Histo::affiche()
{
    for(int j = 0; j < m_histo_height; j++) {
        for(int i = 0; i < m_histo_width; i++) {
            cout << m_histo[i+m_histo_width*j] << " ";
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

void Histo::calcul_norme(int grad_h[], int grad_v[], float norme[])
{
    for(int j = 0; j < m_height; j++) {
        for(int i = 0; i < m_width; i++) {
            int x = grad_h[i+m_width*j];
            int y = grad_v[i+m_width*j];
            norme[i+m_width*j] = sqrt(x*x+y*y);
        }
    }
}

void Histo::calcul_arg(int grad_h[], int grad_v[], float arg[])
{
   for(int j = 0; j < m_height; j++) {
        for(int i = 0; i < m_width; i++) {
            int x = grad_h[i+m_width*j];
            int y = grad_v[i+m_width*j];
            if(x == 0) { // Evite la division par 0
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

void Histo::calcul_histo()
{
    int gradient_h[m_width*m_height];
    int gradient_v[m_width*m_height];

    float norme[m_width*m_height];
    float arg[m_width*m_height];

    m_img.gradient_h(gradient_h);
    m_img.gradient_v(gradient_v);

    calcul_norme(gradient_h, gradient_v, norme);
    calcul_arg(gradient_h, gradient_v, arg);

    int i, j, k, m, n, classe, val, indice;
    float cell[N_CLASSES];
    for(j = 0; j < m_histo_height; j++) {
        for(i = 0; i < m_histo_width; i++) {
            // Init cell
            for(k = 0; k < N_CLASSES; k++) {
                cell[k] = 0;
            }
            classe = 9; // Direction horizontale
            val = 0;

            // Vote
            for(n = 0; n < CELL_SIZE; n++) {
                for(m = 0; m < CELL_SIZE; m++) {
                    indice = i*CELL_SIZE+m + m_width*(j*CELL_SIZE+n);
                    k = (arg[indice]+M_PI/2)*16/M_PI;
                    cell[k] += norme[indice];
                }
            }

            // Resultat du vote
            for(k = 0; k < N_CLASSES; k++) {
                if (cell[k] > val) {
                    val = cell[k];
                    classe = k;
                }
            }
            m_histo[i+m_histo_width*j] = classe;
        }
    }
}
