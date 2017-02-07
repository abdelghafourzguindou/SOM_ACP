#include "SOM.h"

SOM::SOM()
{
    //ctor
}

/**
 *FONCTION PERMIT A L'AIDE DE LA MATRICE RESULTAT DE LAMETHODE
 *ACP PERMIT DE CRIER LA CARTE AUTO-ORGANISATRICE DE KOHENON
 */
void SOM::Creat_MAP(int lig_Matrix_ACP,int col_Matrix_ACP){
    cout<<"\n\n\n\n\n\n"<<endl;
    cout<<"\n\t\tENTRER LA DIMENSION DE VOTRE CARTE SOM : ";cin>>this->Dim_Map;
    cout<<"\n\t\tENTRER LE NOMBRE MAXIMALE D'ITERATIONS : ";cin>>this->Max_Iteration;
    cout<<"\n\t\tENTRER L'EREUR D'APPRENTISAGE MINIMALE : ";cin>>this->LEARNING_EREUR;
    cout<<"\n\t\tENTRER LE TAUX D'APPRENTISAGE INITIALE : ";cin>>this->Start_Learning_Rate;
    this->Number_of_Node = Dim_Map*Dim_Map;
    this->GridSize = Dim_Map/2;
    this->size_of_Weight_And_Input_Vector=col_Matrix_ACP;
    Map=new Node[Number_of_Node];
    int j=0;
    int k=0;
    for(int i=0;i<Number_of_Node;i++){
        Map[i].Initial_Weight(size_of_Weight_And_Input_Vector);
        Map[i].Node_Position(j,k);
        k++;
        if(k==Dim_Map){
            k=0;
            j++;
        }
    }
    system("cls");
    /************************************** POUR VERIFIER ****************************************/
    cout<<setw(45)<<"SOM IS CREATED BY "<<Number_of_Node<<" NODE"<<endl;
    cout<<"\t\t\t______________________________\n\n"<<endl;
    for(int i=0;i<Number_of_Node;i++){
        if(i<9)cout<<setw(22)<<"Node "<<i+1<<" ->("<<Map[i].x_Node<<","<<Map[i].y_Node<<") : ";
        else cout<<setw(22)<<"Node "<<i+1<<"->("<<Map[i].x_Node<<","<<Map[i].y_Node<<") : ";
        for(int j=0;j<size_of_Weight_And_Input_Vector;j++)cout<<setw(13)<<Map[i].Weight_of_Node[j];
        cout<<endl;
    }
    /*********************************************************************************************/
}
/**
 *FONCTION PERMIT A L'AIDE DE LA VECTEUR D'ENTRER DE RECHERCHER LE
 *NEURONE VANCEUR ASSOCIER ON UTILISON LA DISTANCE EUCLUDIENNE
*/
Node* SOM::Serch_Winning_Node(vecteur t){
    Node* winner = NULL;///Tableux des nerones vanceur
    double LowestDistance = 999999;///La distance de Map maximale
    for(int i=0;i<Number_of_Node;i++){
        double dist = Map[i].Distance_Eclud(t,size_of_Weight_And_Input_Vector);
        if(dist < LowestDistance){
            LowestDistance = dist;
            winner = &Map[i];
        }
    }
  return winner;
}
///Fonction permit de diminu le temps d'apprentisage
double SOM::Reduce_of_Learning_Rate(int Iteration){
    return Start_Learning_Rate*exp(-((double)(Iteration)/Max_Iteration));
}
///Fonction return le rayon
double SOM::Determine_Radius(int iteration){
    return GridSize*exp(-((double)(iteration*log(GridSize))/Max_Iteration));
}
///Fonction return l'influence
double SOM::H_function(double dis,double radius){
    return exp(-(double)dis/(2*pow(radius,2)));
}
///Fonction permit de determiner la distance entrer le neuron vanqueur et les autres neurones
double SOM::Determine_Dis_With_Neighbours(Node* winner,int i){
    double dist = pow((winner->x_Node - Map[i].x_Node),2) + pow((winner->y_Node - Map[i].y_Node),2);
    return dist;
}
/**
 *FONCTION PERMET A L'AIDE DE LA MATRICE D'ENTRER (MATRICE RESULTAT D'ACP)
 *DE FAIRE L'APPRENTISSAGE POUR LA CARTE AUTO-ORGANISATRICE
 */
void SOM::Learning(matrix Input_Matrix,int lig_Input_Matrix,char* Node_Fil){
    double NeighbourhoodRadius=0;
    double dist=0;
    double Influence=0;
    double Learning_Rate=0;///Le taux d'apprentissage
    ofstream Stock_Node;
    Stock_Node.open(Node_Fil,ios::out|ios::binary|ios::ate);
    vecteur Input_Vector=new double[size_of_Weight_And_Input_Vector];
    int Cont_Iteration=0;
    int thisVector=0;
    double EREUR;
    double EREUR_MOY=999999;
    do{
        for(thisVector=0;thisVector<lig_Input_Matrix;thisVector++){
            for(int j=0;j<size_of_Weight_And_Input_Vector;j++)Input_Vector[j]=Input_Matrix[thisVector][j];
            Winning_Node=Serch_Winning_Node(Input_Vector);///Ditermination de nerone vanceur
            EREUR += Winning_Node->Distance_Eclud(Input_Vector,size_of_Weight_And_Input_Vector);
            NeighbourhoodRadius = Determine_Radius(Cont_Iteration);///Calcule du rayon
            Learning_Rate=Reduce_of_Learning_Rate(Cont_Iteration);///Calcule du Taux d'apprentissage
            for(int i=0;i<Number_of_Node;i++){
                dist = Determine_Dis_With_Neighbours(Winning_Node,i);///Calcule de la distance entre le neuron vanqueur et les autres neurons
                /**< SI LA DIST ENTRE LE VANQUEUR ET LE NEURON i < pow(NeighbourhoodRadius,2) ON MODIFIE SON POID */
                if(dist < pow(NeighbourhoodRadius,2)){
                    Influence=H_function(dist,NeighbourhoodRadius);///Calcule d'influence
                    Map[i].Adjust_Weights(Input_Vector,Learning_Rate,Influence,size_of_Weight_And_Input_Vector);///Modification des poids
                }
            }
            ++Cont_Iteration;
            /************************************** POUR VERIFIER ****************************************/
            system("cls");
            cout<<"\n\t\t\t     ITERATIONS     : "<<Cont_Iteration<<endl;
            cout<<"\t\t\t     TAUX D'APPREN  : "<<Learning_Rate<<endl;
            cout<<"\t\t\t     RAYONNE        : "<<NeighbourhoodRadius<<endl;
            cout<<"\t\t\t     INPUT VECTOR   : "<<thisVector<<endl;
            cout<<"\t\t\t     WINNING NODE   : ("<<Winning_Node->x_Node<<","<<Winning_Node->y_Node<<")"<<endl;
            cout<<"\t\t\t     EREUR MOYENNE  : "<<EREUR_MOY<<endl;
            /*cout<<"\n\t_______________________________________________________________\n"<<endl;
            for(int i=0;i<Number_of_Node;i++){
                if(i<9)cout<<setw(22)<<"Node "<<i+1<<" ->("<<Map[i].x_Node<<","<<Map[i].y_Node<<") : ";
                else cout<<setw(22)<<"Node "<<i+1<<"->("<<Map[i].x_Node<<","<<Map[i].y_Node<<") : ";
                for(int j=0;j<size_of_Weight_And_Input_Vector;j++)cout<<setw(13)<<Map[i].Weight_of_Node[j];
                cout<<endl;
            }*/
            /*********************************************************************************************/
        }
        EREUR_MOY = EREUR/lig_Input_Matrix;
        EREUR=0;
    }while(EREUR_MOY > LEARNING_EREUR || Cont_Iteration == Max_Iteration);

    /************************************** POUR VERIFIER ****************************************/
    system("cls");
    cout<<"\n\t\t\t     ITERATIONS     : "<<Cont_Iteration<<endl;
    cout<<"\t\t\t     TAUX D'APPREN  : "<<Learning_Rate<<endl;
    cout<<"\t\t\t     RAYONNE        : "<<NeighbourhoodRadius<<endl;
    cout<<"\t\t\t     INPUT VECTOR   : "<<thisVector<<endl;
    cout<<"\t\t\t     WINNING NODE   : ("<<Winning_Node->x_Node<<","<<Winning_Node->y_Node<<")"<<endl;
    cout<<"\t\t\t     EREUR MOYENNE  : "<<EREUR_MOY<<endl;
    cout<<"\n\n\t_______________________________________________________________\n"<<endl;
    for(int i=0;i<Number_of_Node;i++){
        if(i<9)cout<<setw(22)<<"Node "<<i+1<<" ->("<<Map[i].x_Node<<","<<Map[i].y_Node<<") : ";
        else cout<<setw(22)<<"Node "<<i+1<<"->("<<Map[i].x_Node<<","<<Map[i].y_Node<<") : ";
        for(int j=0;j<size_of_Weight_And_Input_Vector;j++)cout<<setw(13)<<Map[i].Weight_of_Node[j];
        cout<<endl;
    }
    /*********************************************************************************************/

    /**< STOCKAGE DU COMPOSANT DU NODE */
    Stock_Node.write((char*)&Dim_Map, sizeof(int));
    Stock_Node.write((char*)&size_of_Weight_And_Input_Vector, sizeof(int));
    for(int i=0;i<Number_of_Node;i++){
        Stock_Node.write((char*)&Map[i].x_Node, sizeof(int));
        Stock_Node.write((char*)&Map[i].y_Node, sizeof(int));
    }
    for(int i=0;i<Number_of_Node;i++){
        for(int j=0;j<size_of_Weight_And_Input_Vector;j++)Stock_Node.write((char*)&Map[i].Weight_of_Node[j], sizeof(double));
    }
    Stock_Node.close();
    delete[] Input_Vector;
}

/**< lire les informations du nodes à partir du fichier binaire */
void SOM::Read_MAP(char* Node_Fil){
    vecteur Data;
    int* POSITION;
    ifstream File(Node_Fil, ios::in|ios::binary|ios::ate);
    if (File.is_open()){
        File.seekg(0, ios::beg);///debut de fichier
        File.read((char*)&this->Dim_Map, sizeof(int));///pour lire la dimention de la carte

        File.seekg(sizeof(int), ios::beg);
        File.read((char*)&this->size_of_Weight_And_Input_Vector, sizeof(int));///pour lire la dim de vecteur d'entrer

        this->Number_of_Node = Dim_Map*Dim_Map;
        this->Map = new Node[Number_of_Node];
        POSITION=new int[2*Number_of_Node];

        for(int i=0;i<(2*Number_of_Node);i++){
            File.read((char*)&POSITION[i], sizeof(int));///Lecture des cordonnees de chaque neuron
        }

        Data=new double[size_of_Weight_And_Input_Vector*Number_of_Node];
        int i=0;
        File.seekg(sizeof(int)*(2*Number_of_Node+2), ios::beg);
        while(File.read((char*)&Data[i],sizeof(double)))i++;///Lecture des poids de chaque neuron
        int k=0;
        int l=0;
        ///Remplisage des coposants;
        for(int i=0;i<Number_of_Node;i++){
            Map[i].x_Node=POSITION[k];///Remplisage des X
            Map[i].y_Node=POSITION[k+1];///Remplisage des Y
            k += 2;
            Map[i].Weight_of_Node = new double[size_of_Weight_And_Input_Vector];
            for(int j=0;j<size_of_Weight_And_Input_Vector;j++){
                Map[i].Weight_of_Node[j]=Data[l];///Remplisage des poids
                l++;
            }
        }
        delete[] Data;
        delete[] POSITION;
        File.close();
        ///cout<<setw(57)<<"L'OPERATION EST TERMINEE AVEC SECCEE"<<"\n\n\n"<<endl;
        ///cout<<setw(55)<<"APPUYER SUR UNE TOUCHE POUR CONTINUER"<<endl;
    }
    else cout<<setw(50)<<"NODE FILE EREUR"<<endl;
}

void SOM::Clasterisation(matrix M_ACP,int lig_M_ACP){

    vecteur INPUT = new double[size_of_Weight_And_Input_Vector];///vecteur d'entre
    cout<<"\n\n\t_______________________________________________________________"<<endl;
    cout<<"\n"<<setw(51)<<"CLASSIFICATION DE DONNEES"<<endl;
    cout<<"\t_______________________________________________________________\n"<<endl;
    for(int i=0;i<lig_M_ACP;i++){
        for(int j=0;j<size_of_Weight_And_Input_Vector;j++)INPUT[j] = M_ACP[i][j];
        Winning_Node = Serch_Winning_Node(INPUT);
        cout<<setw(10)<<"ENTREE ("<<i<<") -> ";
        for(int j=0;j<size_of_Weight_And_Input_Vector;j++)cout<<setw(10)<<INPUT[j];
        cout<<endl;
        cout<<setw(10)<<"WINNER ("<<Winning_Node->x_Node<<","<<Winning_Node->y_Node<<")-> ";
        for(int j=0;j<size_of_Weight_And_Input_Vector;j++)cout<<setw(10)<<Winning_Node->Weight_of_Node[j];
        cout<<"\n"<<endl;
    }
    delete[] INPUT;
}

matrix SOM::Normalis_Data(matrix t,int lig,int col){
    double Norme;
    for(int i=0;i<lig;i++){
        Norme=0;
        for(int j=0;j<col;j++)Norme += pow(t[i][j],2);
        for(int j=0;j<col;j++)t[i][j] /= sqrt(Norme);
    }
    return t;
}

SOM::~SOM()
{
    //dtor
    if(Map)delete[] Map;
}
