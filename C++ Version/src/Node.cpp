#include "Node.h"

Node::Node()
{
    //ctor
}

Node::~Node()
{
    //dtor
}

///Fonction permet la reperation d'un node dans un espace bidimentionel
void Node::Node_Position(int i,int j){
    this->x_Node=i;
    this->y_Node=j;
}
///Fonction utilisé pour initialiser les vecteurs des poids
double Node::Rand_Weight(){
    return double((rand())/(RAND_MAX+1.0));
}
///Fonction permet l'initialisation des poids
void Node::Initial_Weight(int _size){
    Weight_of_Node=new double[_size];
    for(int i=0;i<_size;i++)Weight_of_Node[i]=Rand_Weight();
}
///Fonction return la distance ecludienne
double Node::Distance_Eclud(vecteur x,int dim){
    double distance=0;
    for(int i=0;i<dim;i++)distance+=pow((x[i]-Weight_of_Node[i]),2);
    return sqrt(distance);
}
///Fonction Permet la modification des poids
void Node::Adjust_Weights(vecteur t,double LearningRate,double Influence,int _size){
    for(int i=0;i<_size;i++)Weight_of_Node[i] += (LearningRate*Influence)*(t[i]-Weight_of_Node[i]);
}
