#ifndef ACP_H
#define ACP_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <math.h>

#define Eps pow(10,-5)

using namespace std;

///Declaration des types
typedef double **matrix;
typedef double *vecteur;

class ACP
{

    public:
        matrix READ_DATA(char*,int*,int*);///Fonction permet la lecture des donneés à partir d'un fichier binaire
        int lig_Data,col_Data;///Dimension de la table des donnees
        int lig_V,col_V;///Dimension des matrices V,D1_S2 et D1_S
        int lig_R,col_R;///Dimension de la matrice de correlation
        int lig_Z,col_Z;///Dimension de la matrice centrer reduite
        int lig_C,col_C;///Dimension de la matrice resultat d'ACP
        vecteur g;///Vecteur des moyennes arithmitiques
        matrix Data_Table;///Tableau des Donnees
        matrix Y;///Matrice centrer
        matrix V;///Matrice de variance
        matrix D1_S2;///Matrice diagonale des variances
        matrix D1_S;///Matrice diagonale des ecartes types
        matrix R;///Matrice de correlation
        matrix Z;///Matrice Centrer Reduite
        matrix C;///Matrice resultat d'ACP
        vecteur Vector_Moyenne();///Fonction permet de calculer la vecteur de la moyenne g
        void Scann_Data();///Procedure permet de lire les donneés
        void Matrix_Centrer();///Fonction permet de calculer la matrice centrer
        void Matrix_Variance();///Fonction permet de calculer la matrice de variance
        void Matrix_Diagonale_Inverse_Varionce();///Fonction permet de calculer la matrice diagonale des invers des variance
        void Matrix_Diagonale_Inverse_Ecarte_Type();///Fonction permet de calculer la matrice diagonale d'invers d'ecarts types
        void Matrix_Centrer_Reduite();///Fonction permet de calculer la matrice centrer reduite
        void Matrix_Correlation();///Fonction permet de calculer la matrice de correlation
        void Serch_Matrix_ACP();///Fonction permet de calculer la matrice resultat d'ACP
        char* ACP_Data_fil;///Pointeur sur un fichier binaire pour stocker les donnees resultat d'acp
        char* Data_fil;///Pointeur sur un fichier binaire pour stocker la table de donnees d'entré
        void Delete_Matrix(matrix,int);///Fonction permet de libérer l'espace memoire aloué pour une matrice

        ACP();
        virtual ~ACP();

    protected:
        ///
    private:
        double Norme_Eclud(vecteur,int);///Fonction return la norme eculidienne d'un vecteur
        double Norme_Inf(vecteur,int);///Fonction return la norme infini d'un vecteur
        double Calcule_Valeur_Propre(vecteur,vecteur,int);///Fonction return la valeur propre
        vecteur Produit_Vecteur_Matrix(vecteur,matrix,int,int);///Fonction permet de calculer le produit d'un vecteur avec une matrice
        vecteur Produit_Matrix_Vecteur(matrix,vecteur,int,int);///Fonction permet de calculer le produit d'une matrice avec un vecteur
        vecteur Vecteur_Soustraction(vecteur,vecteur,int);///Fonction permet de calculer la soustraction de deux vecteurs
        matrix Matrix_Transpose(matrix,int,int,int*,int*);///Fonction permet de calculer le transposer d'une matrice
        matrix Matrix_Produit(matrix,matrix,int,int,int,int*,int*);///Fonction permet de calculer le produite de deux matrices
        matrix Calcul_newR(matrix,vecteur,double,int,int);///Fonction permet de calculer la nouvelle R calculer
};

#endif // ACP_H
