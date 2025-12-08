#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include "utils.h"

int main () {
    Pixmap p;
    //p.largeur = 10; // Pour exo 1.1 (carré)
    //p.hauteur = 10; // Pour exo 1.1 (carré)
    //p.largeur = 600; // Pour exo 1.2 (cercle)
    //p.hauteur = 400; // Pour exo 1.2 (cercle)
    p.pixel = (Pixel*)malloc(LARGEUR * HAUTEUR * sizeof(Pixel));

    //ouvrir_fichier_write_1_1("carre_image.ppm", &p); // pour exo 1.1
    //ouvrir_fichier_write_1_2("cercle_image.ppm", &p); // pour exo 1.2
    //int resultat; // pour exo 1.3 (convergence fonction)
    //resultat = convergence(-1.0, 1.0); // pour exo 1.3 (convergence fonction)
    //printf("resultat: %d\n", resultat); // pour exo 1.3 (convergence fonction)
    //image_fractale("fractale_image.ppm", &p); // pour exo 1.3 (image fractale)
    images_independantes(&p); // pour exo 1.4 (images indépendantes avec effet zoom)
    free(p.pixel);
    return 0;
}