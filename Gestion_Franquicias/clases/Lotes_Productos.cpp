#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>

using namespace std;
#include "Lotes_Productos.h"

void MenuLotes(){
    Lotes_Prod lot;
    int Opcion;
    while(true){
        system("cls");
        cout<<"====================================================== "<<endl;
        cout<<"              MENU LOTES                               "<<endl;
        cout<<"====================================================== "<<endl;
        cout<<"01 LISTAR LOTES ACTIVOS                                "<<endl;
        cout<<"02 LISTAR LOTES POR PRODUCTO SELECCIONADO              "<<endl;
        cout<<"03 LISTAR LOTES POR COMPLETO                           "<<endl;
        cout<<"04 CARGAR LOTE NUEVO                                   "<<endl;
        cout<<"00 SALIR                                               "<<endl;
        cout<<"====================================================== "<<endl;
        cout<<" Opcion                                                "<<endl;
        cin>>Opcion;


        switch(Opcion){
        case 1:
            lot.Leer_Lotes_Prod(-1);
        break;
        case 2:
            int Lote;
            cout<<"Ingrese el lote: "; cin>>Lote;
            lot.Leer_Lotes_Prod(Lote);
            system("pause");
        break;
        case 3:

        break;
        case 4:
            lot.Cargar_Lotes_Prod();
        break;
        case 0:
            return;
        break;
        default:
            cout<<"INGRESE UN VALOR DEL MENU";
            system("pause");
        break;
        }
    }
}

void Lotes(){
    MenuLotes();
}

int Lotes_Prod::NuevoID(){
    FILE *N= fopen("archivos/Lotes.dat", "rb");
    if(N == NULL) cout<<"error lote.dat"; return 1;
    fseek(N, (-1) * sizeof * this, SEEK_END);
    fread(this, sizeof *this, 1, N);
    fclose(N);
    return LId;
}


void Lotes_Prod::MuestroLote(){   ///     CONSTRUCTOR

    cout<<"==================================================="<<endl;
    cout<<"Lote LId  "<<LId<<endl;
    cout<<"Lote Cod: "<<LCodProd<<endl;
    cout<<"Fecha Vto: "<<getLFe_Vto().getDia()<<"/"<<getLFe_Vto().getMes()<<"/"<<getLFe_Vto().getAnio()<<endl;
    cout<<"Lote Estado: "<<LEstado<<endl<<endl;

}

void Lotes_Prod::Cargar_Lotes_Prod(){
    cout<<"Lote_ID: "; NuevoID();
    cout<<"Lote CodProducto: "; cin>>LCodProd;
    cout<<"Lote Cantidad: "; cin>>LCantidad;
    cout<<"Fecha Vto: ";
    LFe_Vto.Cargar_Fecha();
    cout<<"Estado: "; cin>>LEstado;

}

bool Lotes_Prod::Grabar_Lotes_Prod(){
    FILE *L= fopen("archivos/Lotes.dat", "ab");
    if(L==NULL){ return false;}
    bool grabo = fwrite(this, sizeof *this, 1, L);
    fclose(L);
    return grabo;
}

bool Lotes_Prod::Leer_Lotes_Prod(int pos=-1){
    FILE *L= fopen("archivos/Lotes.dat", "rb");
    if(L==NULL){ return false;}
    if(pos == -1){
        while(fread(this, sizeof *this, 1, L)){
            if(getLEstado() == 1){
                MuestroLote();
            }
        }
        cout<<"==================================================="<<endl;
        cout<<"Mostro el archivo completo";
        system("pause");
    }else{
        fseek(L, pos * sizeof (*this), SEEK_SET);
        bool Leyo = fread(this, sizeof *this, 1, L);
        MuestroLote();
        cout<<"==================================================="<<endl;
    }



    return true;
}


