#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <windows.h>
#include <ctype.h>

#include "ACP.h"

#define cls system("cls")
#define pause system("PAUSE>null")

using namespace std;

class Menu
{

    public:
        void Menu_Clasterisation(int*);///Le menu suivi les choix de quelle carte tu peut traiter votre donnees
        void Menu_Open_Projet(int*);///Le menu suivre l'ouvruture d'un projet
        void Menu_Projet(int*);///Le menu suivre le traitement des projet
        void Menu_NOUVEAU_PROJET(int*);///Le menu principale de programme
        void Menu_Matrix(int*);///Le menu de la class Matrice
        void Menu_SOM(int*);///Le menu du traitement de SOM
        void Menu_Create_Carte(int*);///Le menu pour crier la carte SOM
        void Menu_Return(bool*);///Pour returne
        void Menu_End();///Pour finir le programe
        void Menu_Scan_DATA(int*);///Pour lire les donnees
        void REMARQUE(string,int);
        void PRINT(matrix,int,int,string,int);
        void Loading(int,int,int);
        bool repet=true;///Variable pour repeter le programme
        bool repet_ACP=true;///Variable pour repeter le menu de class Matrice
        bool repet_SOM=true;///Variable pour repeter le menu de class Matrice
        bool repet_new_projet = true;///Variable pour repeter le menu de neveau projet
        bool repet_open_projet = true;///Variable pour repeter le menu d'ovriture d'un projet

        Menu();
        virtual ~Menu();

    protected:
        ///
    private:
        string Answer;///Une variable pour stocker les reponces des questions
};

#endif // MENU_H
