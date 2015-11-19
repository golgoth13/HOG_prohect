#include "Affine.h"

using namespace std;

Affine::Affine()
{
    readRacine();
    readArctangeante();
}

int Affine::racine(int x)
{
    if (x < 0 || x > 130050) { // 255*255 *2 = 130 050
        cout << "Calcul de Racine impossible" << endl;
        exit(1);
    }
    return m_racine[x];
}

// Calcule Arctan(num/denom)
int Affine::arctangeante(int num, int denom)
{
    int x = num;
    int y = denom;
    if (y == 0) {
        cout << "Calcul de Arctangeante impossible" << endl;
        exit(1);
    }
    if (x < -127)
        x = -127;
    if (x > 127)
        x = 127;
    if (y < -127)
        y = -127;
    if (y > 127)
        y = 127;
    return m_arctangeante[x+127][y+127];
}

// Supprimer cette fonction pour la synthèse
void Affine::writeRacine()
{
    ofstream fichier_out("affine/racine.txt", ios::out);
    if(!fichier_out) {
        cerr << "ça marche pas" << endl;
        exit(1);
    }

    for (int i = 0; i <= 130050; i++) {
        int val = round(sqrt(i));
        fichier_out << val << " ";
    }

    fichier_out.close();
}

// Supprimer cette fonction pour la synthèse
void Affine::writeArctangeante()
{
    ofstream fichier_out("affine/arctangeante.txt", ios::out);
    if(!fichier_out) {
        cerr << "ça marche pas" << endl;
        exit(1);
    }

    for (int j = -127; j <= 127; j++) {
        if (j != 0) {
            for (int i = -127; i <= 127; i++) {
                int val = round(8.0*atan(i/(double)j)/(M_PI/2));
                fichier_out << val << " ";
            }
        }
    }

    fichier_out.close();
}

void Affine::readRacine()
{
    ifstream fichier_in("affine/racine.txt", ios::in);
    if(!fichier_in) {
        cerr << "ça marche pas" << endl;
        exit(1);
    }

    for (int i = 0; i <= 130050; i++) {
        fichier_in >> m_racine[i];
    }

    fichier_in.close();
}

void Affine::readArctangeante()
{
    ifstream fichier_in("affine/arctangeante.txt", ios::in);
    if(!fichier_in) {
        cerr << "ça marche pas" << endl;
        exit(1);
    }

    for (int j = -127; j <= 127; j++) {
        if (j != 0) {
            for (int i = -127; i <= 127; i++) {
                fichier_in >> m_arctangeante[i+127][j+127];
            }
        }
    }

    fichier_in.close();
}
