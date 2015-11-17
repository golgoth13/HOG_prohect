#include "Histo.h"
using namespace std;


//Constructeurs
Histo::Histo(int width, int height, int image[])
        :m_width(width), m_height(height), m_histo_width(width/CELL_SIZE), m_histo_height(height/CELL_SIZE), m_img(Image(m_width, m_height, image))
{
    // Supprimer le if pour la synthèse
    if (m_width%CELL_SIZE!=0 || m_height%CELL_SIZE!=0) {
        cout << "Taille non divisible par " << CELL_SIZE << endl;
        exit(1);
    }
    m_histo = new int[m_histo_width*m_histo_height];
    m_histo_norme = new int[m_histo_width*m_histo_height];

    //m_img.affiche();

    calcul_histo_no_ram();
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

void Histo::affiche_ascii()
{
    int i, j;
    char c;
    for(j = 0; j < m_histo_height; j++) {
        for(i = 0; i < m_histo_width; i++) {
            switch(((m_histo[i+m_histo_width*j]+2)%16)/4) {
                case 1:
                    c = '\\';
                    break;
                case 2:
                    c = '-';
                    break;
                case 3:
                    c = '/';
                    break;
                default:
                    c = '|';
                    break;
            }

            cout << c << " ";
        }
        cout << endl;
    }
}

void Histo::affiche_graphique(string nom, int pattern[N_CLASSES][CELL_SIZE*CELL_SIZE])
{
    ofstream fichier_out(("../res/"+nom+"_histo.pgm").c_str(), ios::out);
    if(!fichier_out) {
        cerr << "ça marche pas" << endl;
        exit(1);
    }

    fichier_out << "P2" << endl << m_width << " " << m_height << endl << "255" << endl;

    int i, j;
    for(j = 0; j < m_histo_height; j++) {
        for(int occur = 0; occur < 4; occur++) {
            for(i = 0; i < m_histo_width; i++) {
                //int val = log(m_histo_norme[i+m_histo_width*j])/log(2);
                int val = m_histo_norme[i+m_histo_width*j];
                if (val > 1024)
                    val = 1024;

                int classe = m_histo[i+m_histo_width*j];
                //classe = (classe + 8)%16;

                fichier_out << val*pattern[classe][0+occur*CELL_SIZE]/1024 << " ";
                fichier_out << val*pattern[classe][1+occur*CELL_SIZE]/1024 << " ";
                fichier_out << val*pattern[classe][2+occur*CELL_SIZE]/1024 << " ";
                fichier_out << val*pattern[classe][3+occur*CELL_SIZE]/1024 << " ";
            }
            fichier_out << endl;
        }
    }
    fichier_out.close();
}

void Histo::gradient_pixel(int* grad_h, int* grad_v, int image[], int x, int y)
{
    if(x!=0 && x!=m_width-1 && y!=0 && y!=m_height-1) { // Si on n'est pas au bord de l'image
        *grad_h = image[(x+1)+m_width*y] - image[(x-1)+m_width*y];
        *grad_v = image[x+m_width*(y+1)] - image[x+m_width*(y-1)];
    } else {
        *grad_h = 0;
        *grad_v = 0;
    }
}

void Histo::calcul_norme_pixel(float* norme, int x, int y)
{
    *norme = sqrt(x*x+y*y);
}

void Histo::calcul_arg_pixel(float* arg, int x, int y)
{
    if(x == 0) { // Evite la division par 0
        if (y == 0) {
            *arg = 0;
        } else {
            *arg = M_PI/2;
        }
    } else {
        *arg = atan(y/x);
    }
}

void Histo::calcul_histo_no_ram()
{
    int i, j, k, m, n, x, y, classe, val;
    int grad_h;
    int grad_v;

    float norme;
    float arg;
    float cell[N_CLASSES];

    // Parcours des cellules
    for(j = 0; j < m_histo_height; j++) {
        for(i = 0; i < m_histo_width; i++) {
            // Init cell
            for(k = 0; k < N_CLASSES; k++) {
                cell[k] = 0;
            }
            classe = 0; // Gradient horizontal
            val = 0;

            // Parcours des pixels de la cellule
            for(n = 0; n < CELL_SIZE; n++) {
                for(m = 0; m < CELL_SIZE; m++) {
                    x = i*CELL_SIZE+m;
                    y = j*CELL_SIZE+n;

                    // Calcul gradients
                    gradient_pixel(&grad_h, &grad_v, m_img.getImage(), x, y);

                    // Calcul norme et argument
                    calcul_norme_pixel(&norme, grad_h, grad_v);
                    calcul_arg_pixel(&arg, grad_h, grad_v);

                    // Vote
                    if (arg < 0) {
                        arg += M_PI;
                    }
                    k = arg*16/M_PI;
                    cell[k] += norme;
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
            m_histo_norme[i+m_histo_width*j] = val;
        }
    }
}
