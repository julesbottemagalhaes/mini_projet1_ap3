#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include "utils.h"

double X1_1 = X1;
double X2_1 = X2;
double Y1_1 = Y1;
double Y2_1 = Y2;

void ouvrir_fichier_write_1_1(const char *nom_fichier, Pixmap *p) {
    FILE* fichier = NULL;
    p->intensite = 255;
    fichier = fopen(nom_fichier, "w");
    if (fichier != NULL) {
        fprintf(fichier, "P6\n%d %d\n%d\n", p->largeur, p->hauteur, p->intensite);

        int taille = p->largeur * p->hauteur;
        for (int i = 0; i < taille; i++) {
        p->pixel[i].r = 0; 
        p->pixel[i].g = 0;   
        p->pixel[i].b = 255; 
        }

        fwrite(p->pixel, sizeof(Pixel), taille, fichier);
        fclose(fichier);
    } else {
        printf("error\n");
        // voir pourquoi mon fichier fait 315 octets au lieu de 313 octets
    }
}

void ouvrir_fichier_write_1_2(const char *nom_fichier, Pixmap *p) {
    FILE* fichier = NULL;
    p->intensite = 255;
    fichier = fopen(nom_fichier, "w");
    if (fichier != NULL) {
        fprintf(fichier, "P6\n %d %d\n %d\n", p->largeur, p->hauteur, p->intensite);
        int centre_largeur = p->largeur / 2;
        int centre_hauteur = p->hauteur / 2;
        int rayon = 100;
        int taille = p->largeur * p->hauteur;

        for (int i = 0; i < p->largeur; i++)
        {
            for (int j = 0; j < p->hauteur; j++)
            {
                int index = j * p->largeur + i;
                int distance_centre = (i - centre_largeur) * (i - centre_largeur) + (j - centre_hauteur) * (j - centre_hauteur);
                if (distance_centre <= rayon * rayon)
                {
                    p->pixel[index].r = 255; 
                    p->pixel[index].g = 0;   
                    p->pixel[index].b = 0; 
                }
                else
                {
                    p->pixel[index].r = 0; 
                    p->pixel[index].g = 255;   
                    p->pixel[index].b = 0; 
                }
            }
        }
        
        fwrite(p->pixel, sizeof(Pixel), taille, fichier);
        fclose(fichier);
    } else {
        printf("error\n");
    }
}

int convergence(double x, double y) {
    complex float Z = x + I*y;
    complex float U = Z;

    for (int n = 0; n <= 85; n++)
    {
        if (cabsf(U) >= 2.0) {
            return n;
        }
        U = U * U + Z;
    }
    return 0;
}

void image_fractale(const char *nom_fichier, Pixmap *p) {
    FILE* fichier = NULL;
    p->intensite = 255;
    fichier = fopen(nom_fichier, "w");
    if (fichier != NULL) {
        fprintf(fichier, "P6\n %d %d\n %d\n", LARGEUR, HAUTEUR, p->intensite);
        for (int i = 0; i < LARGEUR; i++)
        {
            for (int j = 0; j < HAUTEUR; j++)
            {
                double x = X1_1 + i*(X2_1 - X1_1)/LARGEUR;
                double y = Y1_1 + j*(Y2_1 - Y1_1)/HAUTEUR;
                int c = convergence(x, y);
                int index = j * LARGEUR + i;

                int couleur_convergence = 3*c;
                if (couleur_convergence > 255) {
                    couleur_convergence = 255;
                }
                p->pixel[index].r = couleur_convergence;
                p->pixel[index].g = 0;
                p->pixel[index].b = 255;
            }
        }
        fwrite(p->pixel, sizeof(Pixel), LARGEUR * HAUTEUR, fichier);
        fclose(fichier);
        
    } else {
        printf("error\n");
    }
}

void images_independantes(Pixmap *p) {
    char *noms_fichiers[] = {"im0.ppm", "im1.ppm", "im2.ppm", "im3.ppm", "im4.ppm", "im5.ppm", "im6.ppm", "im7.ppm", "im8.ppm", "im9.ppm"};

    double objectif_x = -0.99;
    double objectif_y = 0.3;
    double zoom = 0.7;
    
    double largeur_courante = X2 - X1; 
    double hauteur_courante = Y1 - Y2; 
    
    double centre_x = (X1 + X2) / 2.0;
    double centre_y = (Y1 + Y2) / 2.0;

    for (int i = 0; i < 10; i++) {
        X1_1 = centre_x - largeur_courante / 2.0;
        X2_1 = centre_x + largeur_courante / 2.0;
        Y1_1 = centre_y + hauteur_courante / 2.0;
        Y2_1 = centre_y - hauteur_courante / 2.0;

        image_fractale(noms_fichiers[i], p);

        largeur_courante = largeur_courante * zoom;
        hauteur_courante = hauteur_courante * zoom;

        centre_x = centre_x + (objectif_x - centre_x) * 0.3;
        centre_y = centre_y + (objectif_y - centre_y) * 0.3;
    }
}