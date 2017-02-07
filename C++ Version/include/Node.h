#ifndef NODE_H
#define NODE_H

#include "ACP.h"

class Node
{

    public:
        vecteur Weight_of_Node;///Vecteur des poids
        double Distance_Eclud(vecteur,int);///Fonction return la distance ecludienne entre deux vecteurs
        void Initial_Weight(int);///Fonction permet l'initialisation des poids
        void Adjust_Weights(vecteur,double,double,int);///Fonction permet la modification des poids
        void Node_Position(int,int);///Fonction permet la reperation d'un node dans un espace bidimentionel
        int x_Node;///l'abscisse de Node
        int y_Node;///l'ordonne de Node

        Node();
        virtual ~Node();

    protected:
        ///
    private:
        double Rand_Weight();///Fonction utilisé pour initialiser les vecteurs des poids
};

#endif // NODE_H
