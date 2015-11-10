#include <iostream>
#include "Image.h"
#include "Histo.h"

using namespace std;

int main()
{
    int tab[12];
    for(int i = 0; i < 12; i++) {
        tab[i] = i;
    }
    Image img(4,3,tab);
    cout << "Image :" << endl;
    img.affiche();

    int gradient_h[12];
    int gradient_v[12];

    img.gradient_h(gradient_h);
    img.gradient_v(gradient_v);
    Image grad_h(4,3,gradient_h);
    Image grad_v(4,3,gradient_v);

    cout << "Gradient horizontal :" << endl;
    grad_h.affiche();
    cout << "Gradient vertical :" << endl;
    grad_v.affiche();

    int norme[12];
    int arg[12];

    Histo histo(4,3,tab);
    histo.calcul_norme(gradient_h, gradient_v, norme);
    histo.calcul_arg(gradient_h, gradient_v, arg);
    Image n(4,3,norme);
    Image a(4,3,arg);

    cout << "Norme :" << endl;
    n.affiche();
    cout << "Argument :" << endl;
    a.affiche();
}
