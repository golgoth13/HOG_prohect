#include <iostream>
#include <fstream>
#include <iomanip>
#include "Image.h"
#include "Histo.h"
#include "Affine.h"

using namespace std;

void hog(string nom_fichier, int pattern[N_CLASSES][CELL_SIZE*CELL_SIZE])
{
    int large, haut;
    string magic_number;
    int header;
    int i;

    // Lecture image
    ifstream fichier(("../img/"+nom_fichier+".pgm").c_str(), ios::in);
    if(!fichier) {
        cerr << "ça marche pas" << endl;
    }
    fichier >> magic_number >> large >> haut >> header;

    i = 0;
    int tab[large*haut];
    while(!fichier.eof() && i < large*haut) {
        fichier >> tab[i];
        if (tab[i] > 255)
            cout << i << " " << tab[i] << " " << large << " " << haut << endl;
        i++;
    }
    fichier.close();

    Histo histo(large,haut,tab);
    histo.affiche_graphique(nom_fichier, pattern);
}

int main()
{
    // Lecture patterns histogramme
    string magic_number;
    int header;
    int pattern[N_CLASSES][CELL_SIZE*CELL_SIZE];
    for(int k = 0; k < N_CLASSES; k++) {
        stringstream ks;
        ks << k;

        ifstream fichier(("histo/"+ks.str()+".pgm").c_str(), ios::in | ios::binary);
        if(!fichier) {
            cerr << "ça marche pas" << endl;
        }

        fichier >> magic_number >> header >> header >> header;

        int i = 0;
        unsigned char buffer;
        fichier.read((char *)&buffer, sizeof(unsigned char));
        while(i < CELL_SIZE*CELL_SIZE) {
            fichier.read((char *)&buffer, sizeof(unsigned char));
            pattern[k][i] = buffer;
            i++;
        }
        fichier.close();

    }

    // Initialisation fonctions approximations
    {
        Affine calcul;
        calcul.writeRacine();
        calcul.writeArctangeante(256);
        calcul.writeInverse();
    }

    hog("barbara", pattern);
    hog("empire", pattern);
    hog("groupe", pattern);
    hog("lena", pattern);
}
