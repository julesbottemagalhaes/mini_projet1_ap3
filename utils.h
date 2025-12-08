#ifndef UTILS_H
#define UTILS_H
#define LARGEUR 900
#define HAUTEUR 600
#define X1 -2.0
#define Y1 1.0
#define X2 1.0
#define Y2 -1.0

typedef struct 
{
    unsigned char r; // red
    unsigned char g; // green
    unsigned char b; // blue
}Pixel;


typedef struct 
{
    char signature[3]; // "P6"
    int largeur; // width
    int hauteur; // height
    int intensite; // max color value
    Pixel *pixel; // array of pixels
}Pixmap;

void ouvrir_fichier_write_1_1(const char *nom_fichier, Pixmap *p); //fonction pour faire le carré bleu
void ouvrir_fichier_write_1_2(const char *nom_fichier, Pixmap *p); //fonction pour faire le cercle rouge avec un fond vert
int convergence(double x, double y); // fonction pour vérifier la convergence entre deux chiffres
void image_fractale(const char *nom_fichier, Pixmap *p); // fonction pour faire l'image fractale 
void images_independantes(Pixmap *p); // fonction pour faire les images indépendantes

#endif