#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include <iomanip> ///PARA TRABAJAR CON SETW

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
        cout<<"02 LISTAR LOTES ACTIVOS POR PRODUCTO SELECCIONADO      "<<endl;
        cout<<"03 LISTAR LOTES POR COMPLETO                           "<<endl;
        cout<<"04 CARGAR LOTE NUEVO                                   "<<endl;
        cout<<"05 MODIFICAR UN REGISTRO DE UN LOTE ESPECIFICO         "<<endl;
        cout<<"00 SALIR                                               "<<endl;
        cout<<"====================================================== "<<endl;
        cout<<" Opcion:  "<<endl;
        cin>>Opcion;
        switch(Opcion){
        case 1:{
            Encab_Lote();
            lot.Leer_Lotes_Prod(-1);}
        break;
        case 2:{
            int CodProd;
            cout<<"Ingrese el Código del Producto: "; cin>>CodProd;
            Encab_Lote();
            lot.Leer_Lotes_Prod(CodProd);
            system("pause");}
        break;
        case 3:{
            Encab_Lote();
            lot.Leer_Lotes_Prod(-2);}
        break;
        case 4:{
            lot.Cargar_Lotes_Prod();
            lot.Grabar_Lotes_Prod(-1);}
        break;
        case 5:{
            int Lote;
            cout<<"INGRESE LOTE A MODIFICAR: "; cin>>Lote;
            lot.ModificarLote(Lote);}
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
    int Nuevo;
    if(N == NULL) {
        cout<<"error lote.dat";
        system("pause");
        return 1;
    }
    fseek(N, -1 * sizeof(*this), SEEK_END);
    while(fread(this, sizeof *this, 1, N)){
        Nuevo = getLId()+1;
    }
    fclose(N);
    return Nuevo;
}

void Lotes_Prod::ModificarLote(int Lote){
    FILE *L= fopen("archivos/Lotes.dat", "rb");
    if(L==NULL){ return;}
    int posic=-1, Encontro=0;
    while(fread(this, sizeof *this, 1, L)){
        posic++;
        if(getLId() == Lote){
            Encontro=1;
            cout<<"ENETRE"; system("pause");
            while(true){
                int op;
                system("cls");
                Encab_Lote();
                MuestroLote();
                cout<<"==================================================="<<endl<<endl;

                cout<<"==================================================="<<endl;
                cout<<"===INDIQUE EL CAMPO A MODIFICAR DESEA MODIFICAR:==="<<endl;
                cout<<"==================================================="<<endl;
                cout<<"1= Codigo del Producto============================="<<endl;
                cout<<"2= Cantidad de Producto============================"<<endl;
                cout<<"3= Fecha del Vencimiento==========================="<<endl;
                cout<<"4= Estado del Producto============================="<<endl;
                cout<<"5= Terminar========================================"<<endl;
                cout<<"==================================================="<<endl;
                cout<<"Ingrese: "; cin>>op;
                switch(op){
                case 1:
                    int CodProd;
                    cout<<"Codigo del Producto: ";
                    cin>>CodProd;
                    setLCodProd(CodProd);
                break;
                case 2:
                    int Cant;
                    cout<<"Cantidad de Producto: ";
                    cin>>Cant;
                    setLCantidad(Cant);
                break;
                case 3:
                    cout<<"Fecha Vencimiento: ";
                    LFe_Vto.Cargar_Fecha_Vencimiento();
                break;
                case 4:
                    bool estado;
                    cout<<"Estado 1=ACTIVO, 0=NO ACTIVO";
                    cin>>estado;
                    if(estado){
                        setLEstado_true();
                    }else{
                        setLEstado_false();
                    }
                break;
                case 5:
                    return;
                break;
                default:

                break;
                }
            }
        }
    }
    if(Encontro >0){
        if(Grabar_Lotes_Prod(posic)){
            cout<<">>>>Se modificó correctamente<<<<"<<endl;
            system("pause");
        }
    }else{
        cout<<"NO ESXISTE LOTE DE PRODUCTO";
        system("pause");
    }
}

void Encab_Lote(){

    cout <<"==================================================="<<endl;
    cout << left;
    cout << "========MUESTRA DE LOTE=============================="<<endl;
    cout << setw(5)<<" LId  "<<setw(9)<<"Cod_Prod"<<setw(5)<<"Cant  "<<setw(14)<<" Fecha     "<<setw(8)<<"Estado"<<setw(9)<<"Id Pedido"<<endl;
    cout << "====================================================="<<endl;
}

void Lotes_Prod::MuestroLote(){   ///     CONSTRUCTOR
    cout << right;
    cout << setw(4)<<LId;
    cout << setw(7)<<LCodProd;
    cout << setw(8)<<LCantidad;
    cout << setw(5);
    cout << getLFe_Vto().getDia();
    cout << "/";
    cout << setw(2);
    cout << getLFe_Vto().getMes();
    cout << "/";
    cout << setw(4);
    cout << getLFe_Vto().getAnio();
    cout << setw(7)<<LEstado;
    cout << setw(7)<<LPedidoId<<endl;

}

void Lotes_Prod::Cargar_Lotes_Prod(){
    cout<<"Lote_ID: ";
    setLid(NuevoID());
    cout<<getLId()<<endl;
    cout<<"Lote CodProducto: "; cin>>LCodProd;
    cout<<"Lote Cantidad: "; cin>>LCantidad;
    cout<<"Fecha Vto: ";
    LFe_Vto.Cargar_Fecha();
    cout<<"Estado: "; cin>>LEstado;

}

bool Lotes_Prod::Grabar_Lotes_Prod(int pos){
    bool grabo;
    if(pos==-1){
        FILE *L= fopen("archivos/Lotes.dat", "ab");
        if(L==NULL){ return false;}
        bool grabo = fwrite(this, sizeof *this, 1, L);
        fclose(L);
        return grabo;
    }else{
        FILE *L= fopen("archivos/Lotes.dat", "rb+");
        if(L==NULL){ return false;}
        fseek(L, pos * sizeof *this, SEEK_SET);
        bool grabo = fwrite(this, sizeof *this, 1, L);
        fclose(L);
        return grabo;
    }
    return grabo;
}

bool Lotes_Prod::Leer_Lotes_Prod(int CodProd=-1){ ///-1 LOTES ACTIVOS, -2 TOTAL, >=0 POR CODPROD
    FILE *L= fopen("archivos/Lotes.dat", "rb");
    if(L==NULL){ return false;}
    if(CodProd == -1){
        while(fread(this, sizeof *this, 1, L)){
            if(getLEstado() == 1){
                MuestroLote();
            }
        }
        cout<<"==================================================="<<endl;
        cout<<"Mostro lotes Activos del archivo.";
        system("pause");
    }else{
        if(CodProd == -2){
            while(fread(this, sizeof *this, 1, L)){
                MuestroLote();
            }
            cout<<"==================================================="<<endl;
            cout<<"Mostro lotes del archivo completo.";
            system("pause");
            return true;
        }else{
            while(fread(this, sizeof *this, 1, L)){
                if(getLEstado() == 1 && getLCodProd()==CodProd){
                    MuestroLote();
                }
            }
            cout<<"==================================================="<<endl;
            cout<<"Mostro lotes del PRODUCTO seleccionado del archivo.";
            system("pause");
            return true;
        }
    }
    return true;
}


