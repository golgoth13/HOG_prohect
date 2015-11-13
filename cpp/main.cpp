#include <iostream>
#include <fstream>
#include "Image.h"
#include "Histo.h"

using namespace std;

int main()
{
    int large, haut;

    ifstream fichier("../img/barbara.pgm", ios::in);
    if(!fichier) {
        cerr << "ça marche pas" << endl;
    }
    string line1;
    int line3;

    fichier >> line1;
    cout << line1 << endl;

    fichier >> large;
    fichier >> haut;
    cout << large << " " << haut << endl;

    fichier >> line3;
    cout << line3 << endl;

    int i = 0;
    int tab[large*haut];
    while(!fichier.eof()) {
        fichier >> tab[i];
        i++;
    }
    cout << "Fin du fichier" << endl;
    fichier.close();



    Histo histo(large,haut,tab);
    //histo.affiche();
    histo.affiche_ascii();
    histo.affiche_graphique();
}
