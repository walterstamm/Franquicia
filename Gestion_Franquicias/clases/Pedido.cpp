#include <iostream>
using namespace std;
#include <cstring>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include "Pedido.h"
#include "Fecha.h"
#include "Producto.h"

Pedido::Pedido(){
    Estado=false;
    EstadoFinal=false;
}
Pedido::~Pedido(){
}

bool Pedido::Cargar_Pedido(){
    char respuesta;
    int CodigoProd,NumPedido;
    Producto prod;
    Fecha_Generado.setFechaHoy();
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
    EstadoFinal=false;
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
            EstadoFinal=0;
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
        cout<<endl<<"ID:"<<ID;
        cout<<endl<<"CODIGO DE PRODUCTO: "<<Codigo_Producto;
        cout<<endl<<"CANTIDAD PEDIDA: "<<Cantidad;
        Fecha_Generado.Mostrar_Fecha();
        if(EstadoFinal==1&&Estado==0){
            cout<<endl<<"PEDIDO RECHAZO O ANULADO";
        }
        else{
            if(EstadoFinal==1&&Estado==1){
                cout<<endl<<"PEDIDO RECIBIDO, POR MAS INFOMACION RECURRA A LA SECCION LOTES";
            }
            else{
                cout<<endl<<"PEDIDO PENDIENTE DE RECEPCION";
            }
        }
        cout<<endl<<"==============================================";
    }
    fclose(p);
}
void Pedido::setCodigo_Producto(int _Codigo_Producto){
    Codigo_Producto=_Codigo_Producto;
}
void Pedido::setFecha(Fecha f){
Fecha_Generado=f;
}
Fecha Pedido::getFecha(){
return Fecha_Generado;
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
bool Pedido::getEstadoFinal(){
    return EstadoFinal;
}

void Pedido::setEstadoFinal(bool state){
    EstadoFinal=state;
}
void Pedido::setID(int _ID){
    ID=_ID;
}
int Pedido::getID(){
    return ID;
}

int Pedido::NumeroPedido(){

    int NumPedido;
    FILE *t=fopen("archivos/Pedidos.dat","rb");
    if(t==NULL){
        return 0;
    }
    fseek(t,sizeof(Pedido)*-1,2);
    fread(this,sizeof(Pedido),1,t);
    NumPedido=ID;
    fclose(t);
    return NumPedido;

}

bool Pedido::Mostrar_Pedidos_sinConfirmacion(){
    Pedido aux;
    int i=0,Anterior,bandera=0;
    vector<Pedido> VecPedidos;
    FILE *p=fopen("archivos/Pedidos.dat","rb");
    if(p==NULL){
        cout<<"Error";
        system("pause");
        return false;
    }
   /// EstadoFinal=0;
    while(fread(&aux,sizeof(Pedido),1,p)){

        VecPedidos.push_back(aux);
    }
    fclose(p);
    if(VecPedidos.size()==0){
        return false;
    }

    for(i=0;i<VecPedidos.size();i++){

        if(VecPedidos[i].getEstado()==0){
            if(VecPedidos[i].getEstadoFinal()==0){
                if(bandera==0||Anterior!=VecPedidos[i].ID){
                    cout<<endl<<"-----------------------------------------------------";
                    VecPedidos[i].Fecha_Generado.Mostrar_Fecha();
                    cout<<endl<<"Numero de Pedido: "<<VecPedidos[i].ID;
                    cout<<endl<<"Codigo de Producto: "<<VecPedidos[i].Codigo_Producto;
                    cout<<endl<<"Cantidad: "<<VecPedidos[i].Cantidad<<endl;
                    bandera=1;
                    Anterior=VecPedidos[i].ID;
                }else{
                    cout<<endl<<endl<<"Codigo de Producto: "<<VecPedidos[i].Codigo_Producto;
                    cout<<endl<<"Cantidad: "<<VecPedidos[i].Cantidad<<endl<<endl;
                }
            }
        }
    }
    if(bandera==0){
        cout<<"NO HAY PEDIDOS PENDIENTES";
    }
    return true;
}
