#include <iostream>
#include "Image.h"
#include "Histo.h"

using namespace std;

int main()
{
    int size = 256, large = 16, haut = 16;
    int tab[size];
    for(int i = 0; i < size; i++) {
        tab[i] = i;
    }

    Histo histo(large,haut,tab);
    histo.affiche();
}
