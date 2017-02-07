#ifndef SOM_H
#define SOM_H

#include "Node.h"

class SOM
{
    public:
        void Creat_MAP(int,int);///Fonction permet de creer la carte SOM
        void Learning(matrix,int,char*);///Fonction d'apprentissage
        void Clasterisation(matrix,int);///Fonction genirale de la Clastiresation
        void Read_MAP(char*);///Fonction permit la lecture d'une carte a partire d'une fichier
        char* Node_Fil_Data;///le nome du fichier ou on va stocker les composants du node qui suivant les donnees initiale
        char* Node_Fil_ACP;///le nome du fichier ou on va stocker les composants du node qui suivant les donnees d'acp
        matrix Normalis_Data(matrix,int,int);///Fonction permit la normalisation des compassent d'un matrice

        Node* Map;/// table des nodes

        SOM();
        virtual ~SOM();

    protected:
        ///
    private:
        Node* Winning_Node;///neurone vanqueur
        Node* Serch_Winning_Node(vecteur);///Fonction return le neurone vanqueur
        double Determine_Radius(int);///Fonction return le rayon
        double H_function(double,double);///Fonction return l'influence
        double Determine_Dis_With_Neighbours(Node*,int);///Fonction return la distance entre le nerone vanqueur et les autre
        int size_of_Weight_And_Input_Vector;///La taille de la vecteur d'entre et poid
        double Reduce_of_Learning_Rate(int);///Fonction permet de deminue le taux d'apprentissage
        int Max_Iteration;///Le nombre maximale des iterations
        double Start_Learning_Rate;///Valeur initiale du taux d'apprentissage
        double LEARNING_EREUR;///L'ereur minimale d'apprentissage (test d'arret)
        int Number_of_Node;///Le nombre des neurones
        int Dim_Map;///dimension de la carte
        int GridSize;///le rayonne maximale
};

#endif // SOM_H
