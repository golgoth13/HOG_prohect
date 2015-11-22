#include <iostream>
#include <fstream>
#include <iomanip>
#include "Image.h"
#include "Histo.h"
#include "Affine.h"

using namespace std;

int main()
{
    string nom_fichier = "test";

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

    //Affine calcul;
    //calcul.writeRacine();
    //calcul.writeArctangeante();


    // Calcul précision arctangeante
    /*for (int precision = 1; precision <= 2048; precision*=2) {
        {
            Affine calcul;
            calcul.writeArctangeante2(precision);
        }
        Affine calcul;
        cout << "Precision = " << setw(4) << precision;
        for (int borne = 2; borne <= 256; borne*=2) {
            int compare = 0;
            int cpt = 0;
            for (int j = borne; j >= -1*borne; j--) {
                for (i = -1*borne; i <= borne; i++) {
                    if (i != 0) {
                        if (calcul.arctangeante2(j, i) != round(8.0*atan(j/(double)i)/(M_PI/2)))
                            compare++;
                        cpt++;
                    }
                }
            }
            cout << ", borne = " << borne << " : " << setw(3) << 100 - (100*compare/cpt) << "%";
        }
        cout << endl;
    }*/


    // Affichage argument
    //int borne = 20;
    /*for (int j = borne; j >= -1*borne; j--) {
        for (i = -1*borne; i <= borne; i++) {
            if (i != 0) {
                int val = calcul.arctangeante(j, i);
                if (val >= 0)
                    cout << " ";
                cout << val << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
    for (int j = borne; j >= -1*borne; j--) {
        for (i = -1*borne; i <= borne; i++) {
            if (i != 0) {
                int val = calcul.arctangeante2(j, i);
                if (val >= 0)
                    cout << " ";
                cout << val << " ";
            }
        }
        cout << endl;
    }*/

    // Calcul précision racine
    /*{
        Affine calcul;
        calcul.writeRacine2();
    }
    Affine calcul;
    for (int borne = 1; borne <= 131072; borne *= 2) {
        double compare = 0;
        int cpt = 0;
        for (int i = borne/2; i <= borne; i++) {
            if (calcul.racine2(i) != round(sqrt(i)))
                compare += (round(sqrt(i)) - calcul.racine2(i)) / (double)round(sqrt(i));
            cpt++;
        }
        cout << "borne = " << setw(6) << borne << " : " << setw(3) << 100 - (100*compare/cpt) << "%" << endl;
    }*/

    // Affichage racine
    /*int borne = 32;
    for (int i = 0; i <= borne; i++) {
        cout << round(sqrt(i)) << " " << calcul.racine2(i) << endl;
    }*/

    {
        Affine calcul;
        calcul.writeRacine2();
        calcul.writeArctangeante2(256);
    }
    Histo histo(large,haut,tab);
    //histo.affiche();
    //histo.affiche_ascii();
    histo.affiche_graphique(nom_fichier, pattern);
}
