#include <iostream>
#include <fstream>
#include "Image.h"
#include "Histo.h"

using namespace std;

unsigned char * func(int* width, int* height){
    ifstream fichier("../img/groupe1_160x120a.pgm", ios::in);
    if(!fichier) {
        cerr << "ça marche pas" << endl;
    }
    string line1;
    int line3;

    fichier >> line1;
    cout << line1 << endl;

    fichier >> *width;
    fichier >> *height;
    cout << *width << " " << *height << endl;

    fichier >> line3;
    cout << line3 << endl;

    int i = 0;
    unsigned char img[(*width)*(*height)];
    while(i < (*width)*(*height)) {
        fichier >> img[i];
        i++;
    }
    fichier.close();
    return img;
}

int main()
{
    int large, haut;
    unsigned char* tab;
    tab = func(&large, &haut);

    Histo histo(large,haut,tab);
    histo.affiche();
}
