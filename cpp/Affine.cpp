#include "Affine.h"

using namespace std;

Affine::Affine()
{
    //readRacine();
    readRacine2();
    //readArctangeante();
    readArctangeante2();
}

/*int Affine::racine(int x)
{
    if (x < 0 || x > 130050) { // 255*255 *2 = 130 050
        cout << "Calcul de Racine impossible" << endl;
        exit(1);
    }
    return m_racine[x];
}*/

int Affine::racine2(int x)
{
    if (x < 0 || x > 131072) { // 256*256 *2 = 131 072
        cout << "Calcul de Racine impossible" << endl;
        exit(1);
    }

    int i = 1;
    //int incr = 131072/PRECISION_RACINE;
    int incr = 1;
    if (x <= incr) {
        return m_racine[i-1] + (m_racine[i] - m_racine[i-1]) * x / incr;
    }

    for (i = 2; i <= PRECISION_RACINE; i++) {
        if (x <= incr * 2) {
            return m_racine[i-1] + (m_racine[i] - m_racine[i-1]) * (x - incr) / incr;
        }
        incr *= 2;
    }
    return m_racine[x];
}

// Calcule Arctan(num/denom)
/*int Affine::arctangeante(int num, int denom)
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
        int m_racine[130050];
        y = 127;
    return m_arctangeante[x+127][y+127];
}*/

// Calcule Arctan(num/denom)
int Affine::arctangeante2(int num, int denom)
{
    int i, val;
    if (denom == 0) {
        cout << "Calcul de Arctangeante impossible" << endl;
        exit(1);
    }
    val = num * m_precision_atan / denom;
    if (val > 0) {
        for (i = N_CLASSES/2; i > 0; i--) {
            if (val >= m_arctangeante[i-1])
                return i;
        }
    }
    if (val >= -m_arctangeante[0])
        return 0;
    for (i = -1; i > -N_CLASSES/2; i--) {
        if (val >= -m_arctangeante[-i])
            return i+N_CLASSES;
    }
    return N_CLASSES/2;
}

// Supprimer cette fonction pour la synthèse
/*void Affine::writeRacine()
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
}*/

// Supprimer cette fonction pour la synthèse
void Affine::writeRacine2()
{
    ofstream fichier_out("affine/racine2.txt", ios::out);
    if(!fichier_out) {
        cerr << "ça marche pas" << endl;
        exit(1);
    }

    //int incr = 131072/PRECISION_RACINE;
    int incr = 0;
    fichier_out << round(sqrt(incr)) << " ";

    incr = 1;
    for (int i = 0; i < PRECISION_RACINE; i++) {
        fichier_out << round(sqrt(incr)) << " ";
        incr *= 2;
    }

    fichier_out.close();
}

// Supprimer cette fonction pour la synthèse
/*void Affine::writeArctangeante()
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
}*/

// Supprimer cette fonction pour la synthèse
void Affine::writeArctangeante2(int precision)
{
    ofstream fichier_out("affine/arctangeante2.txt", ios::out);
    if(!fichier_out) {
        cerr << "ça marche pas" << endl;
        exit(1);
    }
    double incr = M_PI/(N_CLASSES);
    double angle = incr/2;

    fichier_out << precision << " ";
    for (int i = 0; i < N_CLASSES/2; i++) {
        int val = round(tan(angle)*precision);
        fichier_out << val << " ";
        angle += incr;
    }

    fichier_out.close();
}

/*void Affine::readRacine()
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
}*/

void Affine::readRacine2()
{
    ifstream fichier_in("affine/racine2.txt", ios::in);
    if(!fichier_in) {
        cerr << "ça marche pas" << endl;
        exit(1);
    }

    int i;
    for (i = 0; i <= PRECISION_RACINE; i++) {
        fichier_in >> m_racine[i];
    }

    fichier_in.close();
}

/*void Affine::readArctangeante()
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
}*/

void Affine::readArctangeante2()
{
    ifstream fichier_in("affine/arctangeante2.txt", ios::in);
    if(!fichier_in) {
        cerr << "ça marche pas" << endl;
        exit(1);
    }

    fichier_in >> m_precision_atan;
    for (int i = 0; i < N_CLASSES; i++) {
        fichier_in >> m_arctangeante[i];
    }

    fichier_in.close();
}
