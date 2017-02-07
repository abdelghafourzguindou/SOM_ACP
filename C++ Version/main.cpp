#include <iostream>

using namespace std;

#include "Menu.h"   ///Appel de class Menu
#include "ACP.h"    ///Appel de class ACP
#include "SOM.h"    ///Appel de class SOM

ACP  O_ACP;     ///New Objet ACP
Menu O_menu;    ///New Objet Menu
SOM  O_som;     ///New Objet SOM

/**< FONCTION POUR LE TRAITEMENT PAR LA METHODE ACP */
void Tratitement_Par_ACP(){
    int choix_ACP;
    O_menu.repet_ACP=true;
    while(O_menu.repet_ACP){
    start:
    O_menu.Menu_Matrix(&choix_ACP);
    switch(choix_ACP){
    case 1:cls;
        O_ACP.g = O_ACP.Vector_Moyenne();
        cout<<"\n"<<endl;
        cout<<setw(60)<<"LE VECTEUR DE MOYENNES ARITHMETIQUES EST"<<endl;
        cout<<"\t_______________________________________________________________\n\n\n"<<endl;
        for(int i=0;i<O_ACP.col_Data;i++)cout<<setw(10)<<O_ACP.g[i];
        pause;
    break;
    case 2:cls;
        O_ACP.Matrix_Centrer();
        O_menu.PRINT(O_ACP.Y,O_ACP.lig_Data,O_ACP.col_Data,"LA MATRICE CENTREE Y EST",55);
        pause;
    break;
    case 3:cls;
        O_ACP.Matrix_Variance();
        O_menu.PRINT(O_ACP.V,O_ACP.lig_V,O_ACP.col_V,"LA MATRICE DE VARIANCE V EST",55);
        pause;
    break;
    case 4:cls;
        O_ACP.Matrix_Diagonale_Inverse_Varionce();
        O_menu.PRINT(O_ACP.D1_S2,O_ACP.lig_V,O_ACP.col_V,"LA MATRICE DE L'INVERSE DE VARIANCE D1/S2 EST",65);
        pause;
    break;
    case 5:cls;
        O_ACP.Matrix_Diagonale_Inverse_Ecarte_Type();
        O_menu.PRINT(O_ACP.D1_S,O_ACP.lig_V,O_ACP.col_V,"LA MATRICE DE L'INVERSE D'ECARTE TYPE D1/S EST",65);
        pause;
    break;
    case 6:cls;
        O_ACP.Matrix_Centrer_Reduite();
        O_menu.PRINT(O_ACP.Z,O_ACP.lig_Z,O_ACP.col_Z,"LA MATRICE CENTREE REDUITE Z EST",55);
        pause;
    break;
    case 7:cls;
        O_ACP.Matrix_Correlation();
        O_menu.PRINT(O_ACP.R,O_ACP.lig_R,O_ACP.col_R,"LA MATRICE DE CORRELATION R EST",55);
        pause;
    break;
    case 8:cls;
        O_ACP.Serch_Matrix_ACP();
        O_menu.PRINT(O_ACP.C,O_ACP.lig_C,O_ACP.col_C,"LA MATRICE RESULTAT DE LA METHODE ACP C EST",60);
        pause;
    break;
    case 9:O_menu.Menu_Return(&O_menu.repet_ACP);break;
    default:
        O_menu.REMARQUE("CHOIX INVALIDE RESSAYER",51);
        goto start;
    break;
    }
    }
}

/**< FONCTION POUR LE TRAITEMENT DE LA CARTE AUTO-ORGANISATRICE DE KOHENON */
void Traitement_Par_SOM(){
    int choix_SOM;
    int choix_Create;
    /**< Variable pour lire les donnees a partire d'un fichier */
    int lig,col;
    char fille_name[20];
    char* DataFil;
    matrix Data;
    ///*******************************************************//
    ///variables pour controler la clasterisation
    ///des donnees selone le cas soit la creation
    ///d'un nouvelle map on lecture a prtire d'un fichier
    bool choix_ClassterisationA = false;
    bool choix_ClassterisationB;
    O_menu.repet_SOM=true;
    while(O_menu.repet_SOM){
        start:
        O_menu.Menu_SOM(&choix_SOM);
        switch(choix_SOM){
            case 1:
                t:
                cls;
                O_menu.Menu_Create_Carte(&choix_Create);
                switch(choix_Create){
                    case 1:
                        cls;
                        O_som.Creat_MAP(O_ACP.lig_Data,O_ACP.col_Data);
                        choix_ClassterisationB = false;
                    break;
                    case 2:
                        cls;
                        O_som.Creat_MAP(O_ACP.lig_C,O_ACP.col_C);
                        choix_ClassterisationB = true;
                    break;
                    case 3:goto start;break;
                    default:goto t;break;
                }
                pause;
            break;
            case 2:cls;
                if(O_som.Map != NULL){
                    if(O_ACP.C != NULL && choix_ClassterisationB == true){
                        ///Normalisation
                        /**matrix C = new double*[O_ACP.lig_C];
                        for(int i=0;i<O_ACP.lig_C;i++){
                            C[i] = new double[O_ACP.col_C];
                            for(int j=0;j<O_ACP.col_C;j++)C[i][j] = O_ACP.C[i][j];
                        }
                        C = O_som.Normalis_Data(C,O_ACP.lig_C,O_ACP.col_C);
                        /**cls;
                        O_menu.PRINT(C,O_ACP.lig_C,O_ACP.col_C,"LES DONNEES NOR",55);
                        pause;
                        O_som.Learning(C,O_ACP.lig_C,O_som.Node_Fil_ACP);
                        O_ACP.Delete_Matrix(C,O_ACP.lig_C);
                        */
                        ///O_ACP.C = O_som.Normalis_Data(O_ACP.C,O_ACP.lig_C,O_ACP.col_C);
                        O_som.Learning(O_ACP.C,O_ACP.lig_C,O_som.Node_Fil_ACP);
                    }
                    else if(O_ACP.Data_Table != NULL && choix_ClassterisationB == false){
                        ///Normalisation
                        /**matrix Data_Table = new double*[O_ACP.lig_Data];
                        for(int i=0;i<O_ACP.lig_Data;i++){
                            Data_Table[i] = new double[O_ACP.col_Data];
                            for(int j=0;j<O_ACP.col_Data;j++)Data_Table[i][j] = O_ACP.Data_Table[i][j];
                        }
                        Data_Table = O_som.Normalis_Data(Data_Table,O_ACP.lig_Data,O_ACP.col_Data);
                        O_som.Learning(Data_Table,O_ACP.lig_Data,O_som.Node_Fil_Data);
                        O_ACP.Delete_Matrix(Data_Table,O_ACP.lig_Data);
                        */
                        ///O_ACP.Data_Table = O_som.Normalis_Data(O_ACP.Data_Table,O_ACP.lig_Data,O_ACP.col_Data);
                        O_som.Learning(O_ACP.Data_Table,O_ACP.lig_Data,O_som.Node_Fil_Data);
                    }
                    else{
                        O_menu.REMARQUE("ATTENTION D'ABORD IL FAUT CREER LA CARTE",60);
                        goto start;
                    }
                }
                else{
                    O_menu.REMARQUE("ATTENTION D'ABORD IL FAUT CREER LA CARTE",60);
                    goto start;
                }
                pause;
            break;
            case 3:cls;
                if(O_som.Map != NULL){
                    if(O_ACP.C != NULL && choix_ClassterisationB){
                        ///O_ACP.C = O_som.Normalis_Data(O_ACP.C,O_ACP.lig_C,O_ACP.col_C);
                        O_som.Clasterisation(O_ACP.C,O_ACP.lig_C);
                    }
                    if(O_ACP.Data_Table != NULL && choix_ClassterisationB == false){
                        ///O_ACP.Data_Table = O_som.Normalis_Data(O_ACP.Data_Table,O_ACP.lig_Data,O_ACP.col_Data);
                        O_som.Clasterisation(O_ACP.Data_Table,O_ACP.lig_Data);
                    }
                }
                else{
                    O_menu.REMARQUE("ATTENTION D'ABORD IL FAUT CREER LA CARTE",63);
                    goto start;
                }
                pause;
            break;
            case 4:cls;O_menu.Menu_Return(&O_menu.repet_SOM);break;
            default:
                O_menu.REMARQUE("CHOIX INVALIDE RESSAYER",51);
                goto start;
            break;
        }
    }
}

void New_Projet_Traitement(){
    int choix_Glob;

    char Projet[50];
    char Projet_Name[50];
    char Projet_Name_Data[50];
    char Projet_Name_ACP[50];
    char Projet_Name_SOM_DATA[50];
    char Projet_Name_SOM_ACP[50];
    char Projet_Name_EXIST[50];

    cls;
    cout<<"\n\n\n\n\t\t\tENTRER LE NOME DE PROJET : ";cin>>Projet_Name;

    strcpy(Projet,"MD ");
    strcat(Projet,Projet_Name);
    system(Projet);

    strcpy(Projet_Name_Data,Projet_Name);
    strcpy(Projet_Name_ACP,Projet_Name);
    strcpy(Projet_Name_SOM_DATA,Projet_Name);
    strcpy(Projet_Name_SOM_ACP,Projet_Name);
    strcpy(Projet_Name_EXIST,Projet_Name);

    strcat(Projet_Name_EXIST,"/");
    strcat(Projet_Name_EXIST,Projet_Name);

    ///POUR CACHER LE FICHIER IDENTIFICATEUR DE PROJET
    char Cacher[50];
    strcpy(Cacher,"ATTRIB +S +H ");
    strcat(Cacher,Projet_Name_EXIST);
    system(Cacher);


    strcat(Projet_Name_Data,"/Data.bin");
    strcat(Projet_Name_ACP,"/ACP.bin");
    strcat(Projet_Name_SOM_DATA,"/SOM_Data.bin");
    strcat(Projet_Name_SOM_ACP,"/SOM_ACP.bin");

    O_ACP.Data_fil      = Projet_Name_Data;
    O_ACP.ACP_Data_fil  = Projet_Name_ACP;
    O_som.Node_Fil_Data = Projet_Name_SOM_DATA;
    O_som.Node_Fil_ACP  = Projet_Name_SOM_ACP;

    O_menu.repet_new_projet = true;
    while(O_menu.repet_new_projet){
        debut1:
        O_menu.Menu_NOUVEAU_PROJET(&choix_Glob);
        switch(choix_Glob){
            case 1:O_ACP.Scann_Data();break;
            case 2:
                if(O_ACP.Data_Table == NULL){
                O_menu.REMARQUE("ATTENTION D'ABORD IL FAUT LIRE LES DONNEES",60);
                goto debut1;
                }
                else Tratitement_Par_ACP();
                break;
            case 3:Traitement_Par_SOM();break;
            case 4:O_menu.repet_new_projet = false;break;
            default:
                O_menu.REMARQUE("CHOIX INVALIDE RESSAYER",51);
                goto debut1;
                break;
        }
    }
}

void Open_Projet_Traitement(){

    int choix_Open;
    int choix_Clas;
    char Projet_Name[50];
    char Projet_Name_Data[50];
    char Projet_Name_ACP[50];
    char Projet_Name_SOM_DATA[50];
    char Projet_Name_SOM_ACP[50];
    char Projet_Name_EXIST[50];

    cls;
    cout<<"\n\n\n\n\t\t\tENTRER LE NOME DE PROJET : ";cin>>Projet_Name;

    strcpy(Projet_Name_EXIST,Projet_Name);

    strcat(Projet_Name_EXIST,"/");
    strcat(Projet_Name_EXIST,Projet_Name);

    char Cacher[50];
    strcpy(Cacher,"ATTRIB -S -H ");
    strcat(Cacher,Projet_Name_EXIST);
    system(Cacher);

    char *control = Projet_Name_EXIST;
    ofstream Data;
    Data.open(control,ios::out|ios::binary|ios::ate);
    if(Data.is_open()){

    char Cacher[50];
    strcpy(Cacher,"ATTRIB +S +H ");
    strcat(Cacher,Projet_Name_EXIST);
    system(Cacher);

    strcpy(Projet_Name_Data,Projet_Name);
    strcpy(Projet_Name_ACP,Projet_Name);
    strcpy(Projet_Name_SOM_DATA,Projet_Name);
    strcpy(Projet_Name_SOM_ACP,Projet_Name);

    strcat(Projet_Name_Data,"/Data.bin");
    strcat(Projet_Name_ACP,"/ACP.bin");
    strcat(Projet_Name_SOM_DATA,"/SOM_Data.bin");
    strcat(Projet_Name_SOM_ACP,"/SOM_ACP.bin");

    O_ACP.Data_fil      = Projet_Name_Data;
    O_ACP.ACP_Data_fil  = Projet_Name_ACP;
    O_som.Node_Fil_Data = Projet_Name_SOM_DATA;
    O_som.Node_Fil_ACP  = Projet_Name_SOM_ACP;

    O_ACP.Data_Table = O_ACP.READ_DATA(O_ACP.Data_fil,&O_ACP.lig_Data,&O_ACP.col_Data);
    O_ACP.C = O_ACP.READ_DATA(O_ACP.ACP_Data_fil,&O_ACP.lig_C,&O_ACP.col_C);

    O_menu.repet_open_projet = true;
    while(O_menu.repet_open_projet){
    debut:
    O_menu.Menu_Open_Projet(&choix_Open);
    switch(choix_Open){
        case 1:cls;O_ACP.Scann_Data();break;
        case 2:cls;Tratitement_Par_ACP();break;
        case 3:cls;Traitement_Par_SOM();break;
        case 4:cls;
            O_ACP.Data_Table = O_ACP.READ_DATA(O_ACP.Data_fil,&O_ACP.lig_Data,&O_ACP.col_Data);
            O_menu.PRINT(O_ACP.Data_Table,O_ACP.lig_Data,O_ACP.col_Data,"LES DONNEES INITIALES DE VOTRE PROJET SONT",60);
            pause;
        break;
        case 5:cls;
            O_ACP.C = O_ACP.READ_DATA(O_ACP.ACP_Data_fil,&O_ACP.lig_C,&O_ACP.col_C);
            O_menu.PRINT(O_ACP.C,O_ACP.lig_C,O_ACP.col_C,"LES DONNEES D'ACP DE VOTRE PROJET SONT",56);
            pause;
        break;
        case 6:{cls;
            debut2:
            O_menu.Menu_Clasterisation(&choix_Clas);
            if(choix_Clas == 1){
                cls;
                O_som.Read_MAP(O_som.Node_Fil_Data);
                ///O_ACP.Data_Table = O_som.Normalis_Data(O_ACP.Data_Table,O_ACP.lig_Data,O_ACP.col_Data);
                O_som.Clasterisation(O_ACP.Data_Table,O_ACP.lig_Data);
            }
            else if(choix_Clas == 2){
                cls;
                O_som.Read_MAP(O_som.Node_Fil_ACP);
                ///O_ACP.C = O_som.Normalis_Data(O_ACP.C,O_ACP.lig_C,O_ACP.col_C);
                O_som.Clasterisation(O_ACP.C,O_ACP.lig_C);
            }
            else if(choix_Clas == 3)goto debut;
            else goto debut2;
            pause;
        break;}
        case 7:O_menu.repet_open_projet = false;
               break;
        default : goto debut;break;
    }
    }
    }
    else O_menu.REMARQUE("PROJET N'EXIST PAS",47);
}

/**< L'EXECUTION DE PROGRAMME PRINCIPALE */
main(){

    int choix_Projet;
    char Projet[50];
    char Projet_Name[50];

    while(O_menu.repet){
    Entrer:
    O_menu.Menu_Projet(&choix_Projet);
    switch(choix_Projet){
        case 1:cls;
            New_Projet_Traitement();
        break;
        case 2:cls;
            Open_Projet_Traitement();
        pause;
        break;
        case 3:cls;
            cout<<"\n\n\n\n\t\t\tENTRER LE NOME DE PROJET : ";cin>>Projet_Name;
            strcpy(Projet,"RMDIR /S ");
            strcat(Projet,Projet_Name);
            cout<<"\n\n\n\n\n\n\n\t\t\t";

            system(Projet);
            pause;
        break;
        case 4:O_menu.Menu_End();break;
        default : goto Entrer;break;
    }}
}
