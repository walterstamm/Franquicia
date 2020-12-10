#include <iostream>
using namespace std;
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include "Pedido.h"
#include "Fecha.h"
#include "Producto.h"

Pedido::Pedido(){
    Estado=true;
}
Pedido::~Pedido(){
}

bool Pedido::Cargar_Pedido(){
    char respuesta;
    int CodigoProd,NumPedido;
    Producto prod;
    ID=NumeroPedido()+1;
    NumPedido=ID;
    cout<<endl<<"Pedido Numero "<<ID<<endl;
    cout<<"Codigo de Producto: ";
    cin>>CodigoProd;
    while(prod.Buscar_Producto_ID(CodigoProd)==-1){
        cout<<endl<<"Codigo de Producto invalido.....";
        cout<<endl<<"Codigo de Producto: ";
        cin>>CodigoProd;
    }
    Codigo_Producto=CodigoProd;

    cout<<endl<<"Cantidad: ";
    cin>>Cantidad;
    while(Cantidad<=0){
        cout<<endl<<"Cantidad Invalida";
        cout<<endl<<"Cantidad: ";
        cin>>Cantidad;
    }
    if(GuardaPedido()==0){
        return false;
    }
    cout<<endl<<"Desea agregar mas productos al pedido?";
    cin>>respuesta;
    if(respuesta=='s'||respuesta=='S'){
        while(respuesta== 's'|| respuesta=='S'){
            ID=NumPedido;
            cout<<endl<<"Pedido Numero "<<ID<<endl;
            cout<<"Codigo de Producto: ";
            cin>>CodigoProd;
            while(prod.Buscar_Producto_ID(CodigoProd)==-1){
                cout<<endl<<"Codigo de Producto invalido.....";
                cout<<endl<<"Codigo de Producto: ";
                cin>>CodigoProd;
            }
            Codigo_Producto=CodigoProd;

            cout<<endl<<"Cantidad: ";
            cin>>Cantidad;
            while(Cantidad<=0){
                cout<<endl<<"Cantidad Invalida";
                cout<<endl<<"Cantidad: ";
                cin>>Cantidad;
            }
            if(GuardaPedido()==0){
                return false;
            }
            cout<<endl<<"Desea agregar mas productos al pedido?";
            cin>>respuesta;
        }
    }
    system("pause");
    system("cls");
    return true;
}

bool Pedido::GuardaPedido(){
    bool grabo;
    FILE *p=fopen("archivos/Pedidos.dat","ab");
    if(p==NULL){
        cout<<"Error";
        system("pause");
        return 0;
    }

    grabo=fwrite(this,sizeof(Pedido),1,p);
    fclose(p);
    return grabo;
}
void Pedido::Mostrar_Pedido(){
    FILE *p=fopen("archivos/Pedidos.dat","rb");
    if(p==NULL){
        cout<<"Error";
        system("pause");
        return ;
    }
    while(fread(this,sizeof(Pedido),1,p)){
        cout<<endl<<ID;
        cout<<endl<<Codigo_Producto;
        cout<<endl<<Cantidad;
    }
    fclose(p);
}
void Pedido::setCodigo_Producto(int _Codigo_Producto){
    Codigo_Producto=_Codigo_Producto;
}
void Pedido::setCantidad(int _Cantidad){
    Cantidad=_Cantidad;
}
void Pedido::setEstado(bool _Estado){
    Estado=_Estado;
}
int Pedido::getCodigo_Producto(){
    return Codigo_Producto;
}

int Pedido::getCantidad(){
    return Cantidad;
}
bool Pedido::getEstado(){
    return Estado;
}
void Pedido::setID(int _ID){
    ID=_ID;
}
int Pedido::getID(){
    return ID;
}

int Pedido::NumeroPedido(){

    int NumPedido;
    FILE *p=fopen("archivos/Pedidos.dat","rb");
    if(p==NULL){
        return 0;
    }
    fseek(p,sizeof(Pedido)*-1,2);
    fread(this,sizeof(Pedido),1,p);
    NumPedido=ID;
    fclose(p);
    return NumPedido;

}
