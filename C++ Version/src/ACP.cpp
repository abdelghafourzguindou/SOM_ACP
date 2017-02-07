#include "ACP.h"

ACP::ACP()
{
    //ctor
}

///Fonction return la norme eculidienne d'un vecteur
double ACP::Norme_Eclud(vecteur t,int dim_t){
    double som=0;
    for(int i=0;i<dim_t;i++)som+=pow(t[i],2);
    return sqrt(som);
}

///Fonction return la norme infini d'un vecteur
double ACP::Norme_Inf(vecteur t,int dim_t){
    double max=0;
    for(int i=0;i<dim_t;i++){
        if(fabs(t[i+1])>fabs(t[i]))max=fabs(t[i+1]);
    }
    return max;
}

///Fonction return la valeur propre
double ACP::Calcule_Valeur_Propre(vecteur v1,vecteur v2,int dim){
    double som=0;
    for(int i=0;i<dim;i++)som+=v1[i]*v2[i];
    return som;
}

///Fonction permet de libérer l'espace memoire aloué pour une matrice
void ACP::Delete_Matrix(matrix t,int lig_t){
    if(t){
        for(int i=0;i<lig_t;i++)delete[] t[i];
        delete[] t;
    }
 }

///Fonction permet de calculer le transposer d'une matrice
matrix ACP::Matrix_Transpose(matrix t,int lig_t,int col_t,int *lig_resu,int *col_resu){
    matrix resultat = new double*[col_t];
    for(int i=0;i<col_t;i++)resultat[i] = new double[lig_t];
    for(int i=0;i<lig_t;i++){
        for(int j=0;j<col_t;j++)resultat[j][i]=t[i][j];
    }
    ///L'envoi des neveaux dimensions
    *lig_resu=col_t;
    *col_resu=lig_t;
    return resultat;
}

///Fonction permet de calculer le produite de deux matrices
matrix ACP::Matrix_Produit(matrix t1,matrix t2,int lig_t1,int lig_t2,int col_t2,int *lig_resu,int *col_resu){
    matrix resultat = new double*[lig_t1];
    for(int i=0;i<lig_t1;i++)resultat[i] = new double[col_t2];
    double som=0;
    for(int i=0;i<lig_t1;i++ ){
        for(int j=0;j<col_t2;j++){
            for(int k=0;k<lig_t2;k++)som+=t1[i][k]*t2[k][j];
            resultat[i][j]=som;
            som=0;
        }
    }
    ///L'envoi des neveaux dimensions
    *lig_resu=lig_t1;
    *col_resu=col_t2;
    return resultat;
}

///Fonction permet de calculer la soustraction de deux vecteurs
vecteur ACP::Vecteur_Soustraction(vecteur t1,vecteur t2,int dim){
    vecteur resultat = new double[dim];
    for(int i=0;i<dim;i++)resultat[i]=t1[i]-t2[i];
    return resultat;
}

///Fonction permet de calculer le produit d'une matrice avec un vecteur
vecteur ACP::Produit_Matrix_Vecteur(matrix t,vecteur v,int lig_t,int dim_v){
    vecteur resultat = new double[lig_t];
    for(int i=0;i<lig_t;i++){
        resultat[i]=0;
        for(int j=0;j<dim_v;j++)resultat[i]+=t[i][j]*v[j];
    }
    return resultat;
}

///Fonction permet de calculer le produit d'un vecteur avec une matrice
vecteur ACP::Produit_Vecteur_Matrix(vecteur v,matrix t,int dim_v,int col_t){
    vecteur resultat = new double[col_t];
    for(int i=0;i<col_t;i++){
        resultat[i]=0;
        for(int j=0;j<dim_v;j++)resultat[i]+=v[j]*t[j][i];
    }
    return resultat;
}

///Fonction permet de calculer la nouvelle R calculer apres chaque iteration
matrix ACP::Calcul_newR(matrix R,vecteur y,double VP,int lig_R,int col_R){
    matrix INTER=new double*[lig_R];
    for(int i=0;i<lig_R;i++)INTER[i]=new double[col_R];
    for(int i=0;i<lig_R;i++){
        for(int j=0;j<col_R;j++)INTER[i][j]=(R[i][j]-(VP*y[i]*y[j]));
    }
    for(int i=0;i<lig_R;i++){
        for(int j=0;j<col_R;j++){
            R[i][j]=0;///Vider l'encienne R
            R[i][j]=INTER[i][j];
        }
    }
    Delete_Matrix(INTER,lig_R);
    return R;
}
///Fonction permet la lecture des donneés à partir d'un fichier binaire
matrix ACP::READ_DATA(char* FIL,int *lig_X,int *col_X){
    vecteur Data;///la taille est lig*col
    matrix X;
    int lig,col;
    ifstream File(FIL, ios::in|ios::binary|ios::ate); ///Ouverture du fichier
    cout<<"\n\n\n\n\n\n\n"<<endl;
    if (File.is_open()){
        File.seekg(0, ios::beg);///debut de fichier
        File.read((char *)&lig, sizeof(int));///pour lire la ligne
        File.seekg(sizeof(int), ios::beg);
        File.read((char *)&col, sizeof(int));///pour lire la colonne
        Data=new double[lig*col];
        X=new double*[lig];///Allocation de la 1ere dimension
        for(int i=0;i<lig;i++)X[i]=new double[col];///Alocation de la 2eme dimension
        File.seekg(sizeof(double), ios::beg);
        int i=0;
        while(File.read((char *)&Data[i],sizeof(double)))i++;
        int k=0;
        for(int i=0;i<lig;i++)for(int j=0;j<col;j++){
            X[i][j]=Data[k];
            k++;
        }
        *lig_X=lig;
        *col_X=col;
        delete[] Data;
        File.close();
        ///cout<<setw(55)<<"LES DONNEES SONT LIT AVEC SECCEE"<<"\n\n\n"<<endl;
        ///cout<<setw(55)<<"APPEZ SUR UNE TOUCHE POUR CONTUNU"<<endl;
    }
    ///else cout<<setw(47)<<"FILE EREUR"<<endl;
    return X;
}

///Fonction permet de lire les donneés
void ACP::Scann_Data(){
    system("cls");
    system("color 1F");
    ofstream Data;
    Data.open(Data_fil,ios::out|ios::binary|ios::ate);///Overture du fichie pour l'ecriture des donnees
    cout<<"\n\n\tENTRER LE NOMBRE DE LIGNES  DE LA MATRICE DE DONNEES : ";cin>>lig_Data;
    cout<<"\n\tENTRER LE NOMBRE DE COLONES DE LA MATRICE DE DONNEES : ";cin>>col_Data;
    Data.write((char*)&lig_Data, sizeof(int));
    Data.write((char*)&col_Data, sizeof(int));
    Data_Table=new double*[lig_Data];///Allocation de la 1ere dimension
    for(int i=0;i<lig_Data;i++)Data_Table[i]=new double[col_Data];///Alocation de la 2eme dimension
    cout<<"\n\n"<<endl;
    ///Stockage de la table des donnees
    for(int i=0;i<lig_Data;i++){
        for(int j=0;j<col_Data;j++){
            cout<<"\n"<<setw(35)<<"ENTRER x("<<i<<","<<j<<") : ";
            cin>>Data_Table[i][j];
            Data.write((char *)&Data_Table[i][j], sizeof(double));///Stockage des donnee dans le fichie binaire
        }
        cout<<"\n"<<endl;
    }
    Data.close();///Fermeture du fichier
}

///Fonction permet de calculer la matrice de la moyenne g
vecteur ACP::Vector_Moyenne(){
    vecteur g=new double[this->col_Data];///Allocation de la dimension de vecteur
    int k=0;
    double som=0;
    for(int i=0;i<col_Data;i++){
        for(int j=0;j<lig_Data;j++)som+=Data_Table[j][i];
        g[k]=som/lig_Data;
        k++;
        som=0;
    }
    return g;
}

///Fonction permet de calculer la matrice centrer
void ACP::Matrix_Centrer(){
    this->g = Vector_Moyenne();
    Y=new double*[lig_Data];///Allocation de la 1ere dimension
    for(int i=0;i<lig_Data;i++)Y[i]=new double[col_Data];///Alocation de la 2eme dimension
    for(int i=0;i<lig_Data;i++){
        for(int j=0;j<col_Data;j++)Y[i][j]=Data_Table[i][j]-g[j];
    }
}

///Fonction permet de calculer la matrice de variance
void ACP::Matrix_Variance(){
    Matrix_Centrer();///Appel de Y
    matrix T;
    int lig_T,col_T;
    T = Matrix_Transpose(Y,lig_Data,col_Data,&lig_T,&col_T);///Transposer de Y=T
    matrix A;///Matrice intermedaire A=Trans(Y)*Y
    A = Matrix_Produit(T,Y,lig_T,lig_Data,col_Data,&lig_V,&col_V);
    V=new double*[lig_V];///Allocation de la 1ere dimension
    for(int i=0;i<lig_V;i++)V[i]=new double[col_V];///Alocation de la 2eme dimension
    ///On divise sur le nombre de ligne car V=(1/n)*Trans(Y)*Y
    for(int i=0;i<lig_V;i++){
        for(int j=0;j<col_V;j++)V[i][j]=A[i][j]/lig_Data;
    }
    Delete_Matrix(A,lig_T);
    Delete_Matrix(T,lig_T);
}

///Fonction permet de calculer la matrice diagonale des invers des variance
void ACP::Matrix_Diagonale_Inverse_Varionce(){
    Matrix_Variance();///Appel de V
    D1_S2=new double*[lig_V];///Allocation de la 1ere dimension
    for(int i=0;i<lig_V;i++)D1_S2[i]=new double[col_V];///Alocation de la 2eme dimension
    for(int i=0;i<lig_V;i++){
        for(int j=0;j<col_V;j++){
            D1_S2[i][j]=0;///Inisialisation par 0
            if(i==j)D1_S2[i][i]=(1/V[i][i]);///On remplit le diag par l'inverse des variances
        }
    }
}

///Fonction permet de calculer la matrice diagonale d'invers d'ecarts types
void ACP::Matrix_Diagonale_Inverse_Ecarte_Type(){
    Matrix_Diagonale_Inverse_Varionce();///Appele de D1/S2
    D1_S=new double*[lig_V];///Allocation de la 1ere dimension
    for(int i=0;i<lig_V;i++)D1_S[i]=new double[col_V];///Alocation de la 2eme dimension
    for(int i=0;i<lig_V;i++){
        for(int j=0;j<col_V;j++){
            D1_S[i][j]=0;///Inisialisation par 0
            if(i==j)D1_S[i][i]=(sqrt(D1_S2[i][i]));///On remplit le diag par l'inverse d'ecarte types
        }
    }
}

///Fonction permet de calculer la matrice centrer reduite
void ACP::Matrix_Centrer_Reduite(){
    Matrix_Centrer();///Appel de Y
    Matrix_Diagonale_Inverse_Ecarte_Type();///Appel de D1/s
    Z = Matrix_Produit(Y,D1_S,lig_Data,lig_V,col_V,&lig_Z,&col_Z);///Z=Y*D1/s
}

///Fonction permet de calculer la matrice de correlation
void ACP::Matrix_Correlation(){
    Matrix_Variance();///Appel de V
    Matrix_Diagonale_Inverse_Ecarte_Type();///Appel de D1/S
    matrix A;///Matrice intermediaire
    int lig_Inter,col_Inter;
    A = Matrix_Produit(D1_S,V,lig_V,lig_V,col_V,&lig_Inter,&col_Inter);///On calcule la premiere partie A=D1/s*V
    R = Matrix_Produit(A,D1_S,lig_Inter,lig_V,col_V,&lig_R,&col_R);///On calcule le resultat finale R=D1/s*V*D1/s=A*D1/s
    Delete_Matrix(A,lig_Inter);
}

///Fonction permet de calculer la matrice resultat d'ACP
void ACP::Serch_Matrix_ACP(){
    system("cls");

    Matrix_Correlation();///Appel de R

    vecteur x    = new double[lig_R];///Vecteur initiale
    vecteur y0   = new double[lig_R];///Vecteur propre initiale
    vecteur y    = new double[lig_R];///L'encienne Vecteur propre
    vecteur y_y0;///Vecteur propre de soustraction

    vecteur Table_Valeur_Propre=new double[1];///Table pour stocker les valeur propre alloué initialement pour 1 valeur propre
    matrix Table_Vecteur_Propre;///Table pour stocker les vecteurs propres alloué initialement pour 1 vecteur
    Table_Vecteur_Propre    = new double*[1];
    Table_Vecteur_Propre[0] = new double[lig_R];
    matrix Table_Vecteur_Propre_Import;///Table pour sotcker les vecteurs propres qui verifient la condition >80%

    int size=0;///conteur des valeurs et vecteurs propres
    double Max_VP;///Variable pour stocker la valeur propre maximale
    ///Debut de traitement On a lig_R valeur propre
    for(int i=0;i<lig_R;i++){
        ///Initialisation
        for(int i=0;i<lig_R;i++){
            if(i==0)x[i]=1;
            else x[i]=0;
        }
        for(int i=0;i<lig_R;i++)y0[i]=x[i]/Norme_Eclud(x,lig_R);///Vecteur propre initiale

        do{
            for(int i=0;i<lig_R;i++)y[i]=y0[i];///sevgard de y0
            delete[] x;
            x = Produit_Matrix_Vecteur(R,y0,lig_R,lig_R);///Calcule de nouvelle x
            for(int i=0;i<lig_R;i++)y0[i]=x[i]/Norme_Eclud(x,lig_R);///Calcule de y0
            delete[] y_y0;
            y_y0 = Vecteur_Soustraction(y,y0,lig_R);///Calcule de y-y0
        }while(Norme_Inf(y_y0,lig_R)>Eps && Norme_Eclud(y_y0,lig_R)<(Norme_Eclud(y,lig_R)+Norme_Eclud(y0,lig_R)));
        ///Valeur propre = y0*R*trans(y0)
        vecteur A;///Vecteur intermediaire
        A=Produit_Vecteur_Matrix(y0,R,lig_R,col_R);
        Max_VP=Calcule_Valeur_Propre(A,y0,lig_R);
        delete[] A;

        size++;
        ///REDIMENSION DES TABLEAUX
        Table_Valeur_Propre =(double*)realloc(Table_Valeur_Propre,size*sizeof(double));
        Table_Vecteur_Propre=(double**)realloc(Table_Vecteur_Propre,size*sizeof(double));
        Table_Vecteur_Propre[size-1]=new double[lig_R];
        ///STOCKAGE DES DONNEES
        Table_Valeur_Propre[size-1]=Max_VP;
        for(int i=0;i<lig_R;i++)Table_Vecteur_Propre[size-1][i]=y0[i];

        this->R = Calcul_newR(this->R,y0,Max_VP,lig_R,col_R);///Calcule de neveau R
    }
    ///******************************* POUR VERIFIER ****************************************
    /**for(int i=0;i<size;i++)cout<<"Valeur propre "<<i+1<<" = "<<Table_Valeur_Propre[i]<<endl;
    cout<<"\n********************\n"<<endl;
    for(int i=0;i<size;i++){
        cout<<"Vecteur Propre "<<i+1<<" = (";
        for(int j=0;j<lig_R;j++)cout<<Table_Vecteur_Propre[i][j]<<"  ";
        cout<<")"<<endl;
    }
    ///***************************************************************************************/
    /**< Pour trouver les vecteurs Propres important (on utilisant la regle de 80%) */
    double som1=0;
    double som2=0;
    int Impo_sizeOf_VectP=0;
    for(int i=0;i<size;i++)som1+=Table_Valeur_Propre[i];
    for(int i=0;i<size;i++){
        som2+=Table_Valeur_Propre[i];
        Impo_sizeOf_VectP++;/// Nombre des vecteurs propres important
        if(som2/som1>=0.8){
            Table_Vecteur_Propre_Import=new double*[Impo_sizeOf_VectP];
            for(int i=0;i<Impo_sizeOf_VectP;i++)Table_Vecteur_Propre_Import[i]=new double[lig_R];
            for(int j=0;j<Impo_sizeOf_VectP;j++){
                for(int k=0;k<lig_R;k++)Table_Vecteur_Propre_Import[j][k]=Table_Vecteur_Propre[j][k];
            }
            ///******************************* POUR VERIFIER ****************************************
            /**cout<<"\n\n\tD'APRES LA CONDITION som(land)/som_Glob(land)>80% on va prendre\n\n\n"<<endl;
            for(int k=0;k<=i;k++)cout<<"Valeur propre "<<k+1<<" = "<<Table_Valeur_Propre[k]<<endl;
            for(int k=0;k<=i;k++){
                cout<<"Vecteur Propre "<<k+1<<" = (";
                for(int i=0;i<lig_R;i++){
                    cout<<Table_Vecteur_Propre_Import[k][i]<<"  ";
                }
                cout<<")"<<endl;
            }
            cout<<"\n\n\n"<<endl;*/
            ///****************************************************************************************
            Matrix_Centrer_Reduite();
            int lig_TTVPI,col_TTVPI;
            matrix Trans_Table_Vecteur_Propre_Import = Matrix_Transpose(Table_Vecteur_Propre_Import,Impo_sizeOf_VectP,lig_R,&lig_TTVPI,&col_TTVPI);
            ///C=Z*Y avec Y c'est le transposé de la table de vecteur propres important trouvé precedement
            this->C = Matrix_Produit(Z,Trans_Table_Vecteur_Propre_Import,lig_Z,lig_TTVPI,col_TTVPI,&lig_C,&col_C);
            Delete_Matrix(Trans_Table_Vecteur_Propre_Import,lig_TTVPI);
            ofstream ACP_Data;
            ACP_Data.open(ACP_Data_fil,ios::out|ios::binary|ios::ate);///Overture de fichier pour l'ecriture des donnees
            ACP_Data.write((char*)&lig_C, sizeof(int));
            ACP_Data.write((char*)&col_C, sizeof(int));
            for(int i=0;i<lig_C;i++){
                for(int j=0;j<col_C;j++)ACP_Data.write((char*)&C[i][j], sizeof(double));
            }
            ACP_Data.close();
            break;
        }
    }
    delete[] x;
    delete[] y0;
    delete[] y;
    delete[] y_y0;
    delete[] Table_Valeur_Propre;
    Delete_Matrix(Table_Vecteur_Propre,size);
    Delete_Matrix(Table_Vecteur_Propre_Import,Impo_sizeOf_VectP);
}

ACP::~ACP()
{
    //dtor
    Delete_Matrix(Data_Table,lig_Data);
    Delete_Matrix(Y,lig_Data);
    Delete_Matrix(V,lig_V);
    Delete_Matrix(D1_S2,lig_V);
    Delete_Matrix(D1_S,lig_V);
    Delete_Matrix(Z,lig_Z);
    Delete_Matrix(R,lig_R);
    Delete_Matrix(C,lig_C);
    if(g)delete[] g;
}
