#include "Menu.h"

Menu::Menu()
{
    //ctor
}

Menu::~Menu()
{
    //dtor
}

void Menu::Menu_Projet(int *choix){
    system("color 1F");
    system("title Projet De Fine d'Etude");
    cls;
    cout<<"\n\n\n\n\n\n\n\n\t\t################ MENU DE PROJET #################\n\t\t#\t\t\t\t\t\t#"<<endl;
    cout<<"\t\t#\t1.NOUVEAU PROJET\t\t\t#"<<endl;
    cout<<"\t\t#\t2.OUVRIR UN PROJET\t\t\t#"<<endl;
    cout<<"\t\t#\t3.SUPPRIMER UN PROJET\t\t\t#"<<endl;
    cout<<"\t\t#\t4.RETURN\t\t\t\t#\n\t\t#\t\t\t\t\t\t#"<<endl;
    cout<<"\t\t#################################################\n"<<endl;
    cout<<"\t\tVotre choix : ";cin>>*choix;
}

void Menu::Menu_Open_Projet(int *choix){
    system("color 1F");
    system("title Projet De Fine d'Etude");
    cls;
    cout<<"\n\n\n\n\n\n\n\n\t\t############## MENU OUVRIR PROJET ###############\n\t\t#\t\t\t\t\t\t#"<<endl;
    cout<<"\t\t#\t1.LIRE LES DONNEES\t\t\t#"<<endl;
    cout<<"\t\t#\t2.TRAITEMENT PAR L'ACP\t\t\t#"<<endl;
    cout<<"\t\t#\t3.TRAITEMENT PAR SOM\t\t\t#"<<endl;
    cout<<"\t\t#\t4.AFFICHER LES DONNEES INITIALES\t#"<<endl;
    cout<<"\t\t#\t5.AFFICHER LES DONNEES D'ACP\t\t#"<<endl;
    cout<<"\t\t#\t6.AFFICHER LE RESULTAT DE SOM\t\t#"<<endl;
    cout<<"\t\t#\t7.RETURN\t\t\t\t#\n\t\t#\t\t\t\t\t\t#"<<endl;
    cout<<"\t\t#################################################\n"<<endl;
    cout<<"\t\tVotre choix : ";cin>>*choix;
}


///Menu Principale
void Menu::Menu_NOUVEAU_PROJET(int *choix){
    system("color 1F");
    system("title Projet De Fine d'Etude");
    cls;
    cout<<"\n\n\n\n\n\n\n\n\t\t############## MENU NOUVEAU PROJET ##############\n\t\t#\t\t\t\t\t\t#"<<endl;
    cout<<"\t\t#\t1.LIRE LES DONNEES\t\t\t#"<<endl;
    cout<<"\t\t#\t2.TRAITEMENT PAR L'ACP\t\t\t#"<<endl;
    cout<<"\t\t#\t3.TRAITEMENT PAR SOM\t\t\t#"<<endl;
    cout<<"\t\t#\t4.RETURN\t\t\t\t#\n\t\t#\t\t\t\t\t\t#"<<endl;
    cout<<"\t\t#################################################\n"<<endl;
    cout<<"\t\tVotre choix : ";cin>>*choix;
}

///Menu suivi la classe ACP
void Menu::Menu_Matrix(int *choix){
    system("color 1F");
    system("title Analyse En Compossant Principale");
    cls;
    cout<<"\n\n\n\n\n\t#################### MENU TRAITEMENT PAR ACP ####################\n\t#\t\t\t\t\t\t\t\t#"<<endl;
    cout<<"\t#\t1.MOYENNE ARITHMITIQUE (g)\t\t\t\t#"<<endl;
    cout<<"\t#\t2.MATRICE CENTREE (Y)\t\t\t\t\t#"<<endl;
    cout<<"\t#\t3.MATRICE DE VARIANCE (V)\t\t\t\t#"<<endl;
    cout<<"\t#\t4.MATRICE DIAGONALE DE L'INVERSE DE VARIANCE (D1/S2)\t#"<<endl;
    cout<<"\t#\t5.MATRICE DIAGONALE DE L'INVERSE D'ECARTE TYPE (D1/s)\t#"<<endl;
    cout<<"\t#\t6.MATRICE CENTREE REDUITE (Z)\t\t\t\t#"<<endl;
    cout<<"\t#\t7.MATRICE DE CORRELATION (R)\t\t\t\t#"<<endl;
    cout<<"\t#\t8.MATRICE RESULTAT D'ACP (C)\t\t\t\t#"<<endl;
    cout<<"\t#\t9.RETURN\t\t\t\t\t\t#\n\t#\t\t\t\t\t\t\t\t#"<<endl;
    cout<<"\t#################################################################\n"<<endl;
    cout<<"\tVotre choix : ";cin>>*choix;
}
void Menu::Menu_SOM(int *choix){
    system("color 1F");
    system("title La Carte Auto-Organisatrice de Kohanen");
    cls;
    cout<<"\n\n\n\n\n\n\n\n\t#################### MENU TRAITEMENT PAR SOM ####################\n\t#\t\t\t\t\t\t\t\t#"<<endl;
    cout<<"\t#\t1.CREER LA CARTE DE KOHANEN\t\t\t\t#"<<endl;
    cout<<"\t#\t2.FAIRE UN APPRENTISSAGE\t\t\t\t#"<<endl;
    cout<<"\t#\t3.AFFICHER LES RESULTATS\t\t\t\t#"<<endl;
    cout<<"\t#\t4.RETURN\t\t\t\t\t\t#\n\t#\t\t\t\t\t\t\t\t#"<<endl;
    cout<<"\t#################################################################\n"<<endl;
    cout<<"\tVotre choix : ";cin>>*choix;
}

void Menu::Menu_Create_Carte(int *choix){
    system("color 1F");
    system("title Creer la Carte Auto-Organisatrice de Kohanen");
    cls;
    cout<<"\n\n\n\n\n\n\n\n\t#################### MENU CREER LA CARTE SOM ####################\n\t#\t\t\t\t\t\t\t\t#"<<endl;
    cout<<"\t#\t1.CREER LA CARTE AVEC LES DONNEES INITIALES\t\t#"<<endl;
    cout<<"\t#\t2.CREER LA CARTE AVEC LES DONNEES D'ACP\t\t\t#"<<endl;
    cout<<"\t#\t3.RETURN\t\t\t\t\t\t#\n\t#\t\t\t\t\t\t\t\t#"<<endl;
    cout<<"\t#################################################################\n"<<endl;
    cout<<"\tVotre choix : ";cin>>*choix;
}

void Menu::Menu_Clasterisation(int *choix){
    system("color 1F");
    system("title Classification des donnees");
    cls;
    cout<<"\n\n\n\n\n\n\n\n\t\t############## MENU CLASSIFICATION ##############\n\t\t#\t\t\t\t\t\t#"<<endl;
    cout<<"\t\t#\t1.CLASSIFICATION DES DONNEES INITIALES\t#"<<endl;
    cout<<"\t\t#\t2.CLASSIFICATION DES DONNEES D'ACP\t#"<<endl;
    cout<<"\t\t#\t3.RETURN\t\t\t\t#\n\t\t#\t\t\t\t\t\t#"<<endl;
    cout<<"\t\t#################################################\n"<<endl;
    cout<<"\t\tVotre choix : ";cin>>*choix;
}

void Menu::REMARQUE(string mot,int x){
    cls;
    system("color 1F");
    cout<<"\n\n\n\n\n\n\n"<<endl;
    cout<<setw(x)<<mot<<"\n\n\n"<<endl;
    cout<<setw(55)<<"APPUYER SUR UNE TOUCHE POUR CONTINUER"<<endl;
    pause;
}

/**< FONCTION PERMET D'AFFICHER LES DONNEES */
void Menu::PRINT(matrix t,int lig,int col,string phrase,int x){
    cout<<"\n\n\t_______________________________________________________________"<<endl;
    cout<<"\n"<<setw(x)<<phrase<<endl;
    cout<<"\t_______________________________________________________________\n"<<endl;
    for(int i=0;i<lig;i++){
        cout<<"INDIVUDU-> ";
        for(int j=0;j<col;j++)cout<<setw(10)<<t[i][j];
        cout<<endl;
    }
}

void Menu::Menu_Return(bool *repet){
    cls;
    *repet=false;
}

void Menu::Menu_End(){
    system("color 0F");
    start:
    cls;
    cout<<"\n\n\n\n\n\n\n\n\n\n\t\tVEULLEZ VOUS VRAIMENT SORTIRE (oui/non)? : ";
    cin>>Answer;
    for(int i=0;i<3;i++)Answer[i]=tolower(Answer[i]);
    if(Answer=="oui"){
        cls;
        repet=false;
        cout<<"\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tFIN";
        for(int i=0;i<3;i++){
            cout<<".";
            Sleep(1500);
        }
        cout<<"\n\n\n\n\n\n\n\n\n"<<endl;
        system("EXIT");
    }
    else if(Answer=="non")repet=true;
    else goto start;
}

void Menu::Loading(int x,int y,int z){
    system("color 0E");
    for(int i=0;i<x;i++){
    cls;
    cout<<"\n\n\n\n\n\n\n\n\n\n\n"<<setw(43)<<"LOADING";
    for(int i=0;i<y;i++){
        cout<<".";
        Sleep(z);
    }
    }
    cls;
}
