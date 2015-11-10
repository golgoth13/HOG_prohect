#include "Histo.h"
using namespace std;


//Constructeurs
Histo::Histo(int width, int height, unsigned char image[])
        :m_width(width), m_height(height), m_histo_width(width/CELL_SIZE), m_histo_height(height/CELL_SIZE), m_img(Image(m_width, m_height, image))
{
    // Supprimer le if pour la synthèse
    if (m_width%CELL_SIZE!=0 || m_height%CELL_SIZE!=0) {
        cout << "Taille non divisible par " << CELL_SIZE << endl;
        exit(1);
    }
    m_histo = new int[m_histo_width*m_histo_height];

    calcul_histo();
}

// Supprimer cette fonction pour la synthèse
void Histo::affiche()
{
    int i, j;
    for(j = 0; j < m_histo_height; j++) {
        for(i = 0; i < m_histo_width; i++) {
            cout << m_histo[i+m_histo_width*j] << " ";
        }
        cout << endl;
    }
}

void Histo::gradient_h(unsigned char grad[], unsigned char image[])
{
    int i, j;
    for(j = 0; j < m_height; j++) {
        for(i = 0; i < m_width; i++) {
            if(i!=0 && i!=m_width-1 && j!=0 && j!=m_height-1) { // Si on n'est pas au bord de l'image
                grad[i+m_width*j] = image[i+m_width*j+1] - image[i+m_width*j-1];
            } else {
                grad[i+m_width*j] = 0;
            }
        }
    }
}

void Histo::gradient_v(unsigned char grad[], unsigned char image[])
{
    int i, j;
    for(j = 0; j < m_height; j++) {
        for(i = 0; i < m_width; i++) {
            if(i!=0 && i!=m_width-1 && j!=0 && j!=m_height-1) { // Si on n'est pas au bord de l'image
                grad[i+m_width*j] = image[i+m_width*(j+1)] - image[i+m_width*(j-1)];
            } else {
                grad[i+m_width*j] = 0;
            }
        }
    }
}

void Histo::calcul_norme(unsigned char grad_h[], unsigned char grad_v[], float norme[])
{
    int i, j, x, y;
    for(j = 0; j < m_height; j++) {
        for(i = 0; i < m_width; i++) {
            x = grad_h[i+m_width*j];
            y = grad_v[i+m_width*j];
            norme[i+m_width*j] = sqrt(x*x+y*y);
        }
    }
}

void Histo::calcul_arg(unsigned char grad_h[], unsigned char grad_v[], float arg[])
{
    int i, j, x, y;
    for(j = 0; j < m_height; j++) {
        for(i = 0; i < m_width; i++) {
            x = grad_h[i+m_width*j];
            y = grad_v[i+m_width*j];
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
    int i, j, k, m, n, classe, val, indice;
    unsigned char grad_h[m_width*m_height];
    unsigned char grad_v[m_width*m_height];

    float norme[m_width*m_height];
    float arg[m_width*m_height];
    float cell[N_CLASSES];

    gradient_h(grad_h, m_img.getImage());
    gradient_v(grad_v, m_img.getImage());

    calcul_norme(grad_h, grad_v, norme);
    calcul_arg(grad_h, grad_v, arg);

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
