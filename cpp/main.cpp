#include <iostream>
#include <fstream>
#include "Image.h"
#include "Histo.h"

using namespace std;

int main()
{
    string nom_fichier = "lena.ascii";

    int large, haut;
    string magic_number;
    int useless;
    int i;
    int pattern[N_CLASSES][CELL_SIZE*CELL_SIZE];

    // Lecture image
    ifstream fichier(("../img/"+nom_fichier+".pgm").c_str(), ios::in);
    if(!fichier) {
        cerr << "ça marche pas" << endl;
    }

    fichier >> magic_number >> large >> haut >> useless;

    i = 0;
    int tab[large*haut];
    while(!fichier.eof()) {
        fichier >> tab[i];
        i++;
    }
    fichier.close();

    // Lecture patterns histogramme
    for(int k = 0; k < N_CLASSES; k++) {
        stringstream ks;
        ks << k;

        ifstream fichier(("histo/"+ks.str()+".pgm").c_str(), ios::in | ios::binary);
        if(!fichier) {
            cerr << "ça marche pas" << endl;
        }

        fichier >> magic_number >> useless >> useless >> useless;

        i = 0;
        unsigned char buffer;
        fichier.read((char *)&buffer, sizeof(unsigned char));
        while(i < CELL_SIZE*CELL_SIZE) {
            fichier.read((char *)&buffer, sizeof(unsigned char));
            pattern[k][i] = buffer;
            i++;
        }
        fichier.close();

    }

    /*for(int k = 0; k < N_CLASSES; k++) {
        i = 0;
        cout << k << " ";
        while(i < CELL_SIZE*CELL_SIZE) {
            cout << pattern[k][i] << " ";
            i++;
        }
        cout << endl;
    }*/

    Histo histo(large,haut,tab);
    //histo.affiche();
    //histo.affiche_ascii();
    histo.affiche_graphique(nom_fichier, pattern);
}
