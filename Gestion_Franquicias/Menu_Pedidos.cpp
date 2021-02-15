#include<iostream>
#include<cstdlib>
#include<cstdio>
#include <vector>
#include "Menu_Pedidos.h"
#include "clases/Pedido.h"
#include "clases/Producto.h"
#include "clases/Lotes_Productos.h"

using namespace std;

void Menu_Pedidos(){
    int opcion;
    while(true){
        cout<<endl<<"=========================================================";
        cout<<endl<<"                MENÚ PROVEEDORES                         ";
        cout<<endl<<"=========================================================";
        cout<<endl<<"1) CARGA DE PROVEEDORES..................................";
        cout<<endl<<"2) GENERAR PEDIDOS.......................................";
        cout<<endl<<"3) CONFIRMAR/DAR DE BAJA PEDIDOS.........................";
        cout<<endl<<"4) MODIFICAR PROVEEDORES(DAR DE BAJA PROVEEDOR)..........";
        cout<<endl<<"5) LISTAR PROVEEDORES....................................";
        cout<<endl<<"6) HISTORIAL DE PEDIDOS REALIZADOS.......................";
        cout<<endl<<"0) VOLVER AL MENU PRINCIPAL..............................";
        cout<<endl<<"=========================================================";
        cout<<endl<<"\t Opción:  ";
        cin>>opcion;
        system ("cls");
        switch(opcion){
        case 1:
            Carga_Provedores();
            break;
        case 2:
            GeneraPedido();
        break;
        case 3:
            ConfirmarPedido();
        break;
        case 4:
            DarBajaProveedor();

            break;
        case 5:
            Mostrar_Proveedores();
            break;
        case 0:
            return;
        default:
            cout<<endl<<"\t Opcion incorrecta"<<endl<<endl;

            system ("pause");

        break;
        }
        system ("cls");
    }
}

void Carga_Provedores(){
    proveedore provedor;
    bool Valido;
    provedor.Cargar_Proveedore();
    Valido=provedor.Guardar_Proveedore();
    if(Valido){
        cout<<endl<<"Se ha guardado exitosamente el nuevo Proveedor";
        system("pause");
        system("cls");
        return;
    }
    cout<<endl<<"No se ha podido guardar....";
    system("pause");
}


void Mostrar_Proveedores(){
    proveedore reg;
    FILE *Registros=fopen("archivos/Proveedores.dat","rb");
    if(Registros==NULL){
        cout<<"Error al abrir registro";
        system("pause");
        return;
    }
    while(fread(&reg,sizeof(proveedore),1,Registros)){
    reg.Listar_Proveedores();
    }
    system("pause");
    system("cls");
}


bool ValidarIDProveedores(int _ID){
    proveedore reg;
    FILE *p=fopen("archivos/Proveedores.dat","rb");
    if(p==NULL){
        cout<<"Error";
        system("pause");
        return false;
    }
    while(fread(&reg,sizeof(proveedore),1,p)){
        if(_ID==reg.getID()){
            fclose(p);
            return false;
        }
    }
    fclose(p);
    return true;
}


void DarBajaProveedor(){
    int ID,Telefono,Posicion;
    bool validacion;
    char respuesta,Nombres[50],Nota[200];
    proveedore reg;
    system("cls");
    cout<<"Ingrese el ID a modificar: "<<endl;
    cin>>ID;
    BuscarID(&reg,ID);
    if(reg.getID()!=ID){
        return;
    }
    Posicion=reg.posicionProveedor(reg.getID());
    cout<<"Desea dar de baja a este Proveedor?(S/N)"<<endl;
    cin>>respuesta;
    if(respuesta=='s'||respuesta=='S'){
        reg.setEstado(false); ///puse este set estado que faltaba
        if(reg.Guardar_Cambios(Posicion)){
        cout<<"Se dio de baja con exito!";
        system("pause");
        return;
    }
    cout<<endl<<"No se puedo guardar los cambios";
    system("pause");
    system("cls");
    return;
    }

    reg.Listar_Proveedores();
    cout<<endl<<"Modificar el Nombre?(S/N)";
    cin>>respuesta;
    if(respuesta=='s'||respuesta=='S'){
        cout<<"Nombre del proveedor: ";
    cin.ignore();
    cin.getline(Nombres, 50, '\n');
        while(Nombres[0]==' '){///validando el nombre que el primer caracter no sea un espacio
            cout<<endl<<"Nombre incorrecta, reingrese el Nombre"<<endl<<endl;
            cout<<">> Ingrese el Nombre: ";
            cin.getline(Nombres, 50, '\n');
        }
        reg.setNombre(Nombres);
    }
    cout<<endl<<"Modificar numero de telefono?(S/N)";
    cin>>respuesta;
    if(respuesta=='s'||respuesta=='S'){
        cin>>Telefono;
        reg.setTelefono(Telefono);
    }

    cout<<endl<<"Modificar la descripcion? S/N ";
    cin>>respuesta;
    if(respuesta=='s'||respuesta=='S'){
        cout<<"Descripcion del Proveedor: ";
        cin.ignore();
        cin.getline(Nota, 200, '\n');
        while(Nota[0]==' '){///validando la nota que el primer caracter no sea un espacio
            cout<<endl<<"Nota incorrecta, reingrese el Nota"<<endl<<endl;
            cout<<">> Ingrese el Nota: ";
            cin.getline(Nota, 200, '\n');
        }
        reg.setNota(Nota);
    }
    cout<<endl<<endl;
    reg.Listar_Proveedores();
    cout<<endl<<endl;
    validacion=reg.Guardar_Cambios(Posicion);
    if(validacion){
        cout<<"Se guardaron los cambion con exito!";
        system("pause");
        return;
    }
    cout<<endl<<"No se puedo guardar los cambios";
    system("pause");
    system("cls");
}



void BuscarID(proveedore *registro,int id){

    FILE *p=fopen("archivos/Proveedores.dat","rb");
    if(p==NULL){
        cout<<"Error";
        system("pause");
        return;
    }
    while(fread(registro,sizeof(proveedore),1,p)){
        if(id==registro->getID()){
            fclose(p);
            return;
        }
    }
    cout<<"No se encontro ese ID..."<<endl;
    fclose(p);
}


void GeneraPedido(){
    system("cls");
    Pedido reg;
    reg.Cargar_Pedido();
}


void ConfirmarPedido(){
    int numPedido,accion;
    Pedido reg;
    if(reg.Mostrar_Pedidos_sinConfirmacion()==0){
       return;
    }
    cout<<"========================================================";
    cout<<endl<<endl<<"Ingrese el Numero de pedido: ";
    cin>>numPedido;
    if(ValidaNumeroPedido(numPedido)){



    cout<<endl<<"1. DAR DE BAJA";
    cout<<endl<<"2.CONFIRMAR RECEPCION DE PEDIDO"<<endl;
    cin>>accion;
    switch(accion){
        case 1:
            if (BajaPedido(numPedido)){
                cout<<endl<<"Baja exitosa";
                system("pause");
                system("cls");
                return;
            }
            cout<<endl<<"No se puedo concretar la baja";
            return;
            break;

        case 2:
            if(PedidoRecibido(numPedido)){
                cout<<endl<<"Pedido Confirmado";
                system("pause");
                return;
            }
            cout<<endl<<"ERROR";
            return;
            break;

        default:
            cout<<"Opcion Incorrecta";
            return;
    }
    }
    else{
        cout<<endl<< "El numero de pedido no existe o ya ha sido recibido o rechazado";
        system("pause");
    }
    system("cls");

}

bool ValidaNumeroPedido(int numPedido){
    Pedido aux;
    int i=0,Anterior,bandera=0;
    vector<Pedido> VecPedidos;
    FILE *p=fopen("archivos/Pedidos.dat","rb");
    if(p==NULL){
        cout<<"Error";
        system("pause");
        return false;
    }
    while(fread(&aux,sizeof(Pedido),1,p)){

        VecPedidos.push_back(aux);
    }
    fclose(p);
    if(VecPedidos.size()==0){
        return false;
    }

    for(i=0;i<VecPedidos.size();i++){
        if(VecPedidos[i].getEstado()==0&&VecPedidos[i].getEstadoFinal()==0){
            if(VecPedidos[i].getID()==numPedido){
                bandera=1;
            }
        }
    }
    return bandera;

}


bool BajaPedido(int numPedido){
    Pedido aux;
    vector<Pedido> VecPedidos;
    int i;

    FILE *p=fopen("archivos/Pedidos.dat","rb");
    if(p==NULL){
        cout<<"Error";
        system("pause");
        return false;
    }

    while(fread(&aux,sizeof(Pedido),1,p)){
        VecPedidos.push_back(aux);

    }
    fclose(p);

    for(i=0;i<VecPedidos.size();i++){
        if(VecPedidos[i].getID()==numPedido){
            VecPedidos[i].setEstado(false);
            VecPedidos[i].setEstadoFinal(true);
        }
    }

    FILE *v=fopen("archivos/Pedidos.dat","wb");
    if(p==NULL){
        cout<<"Error";
        system("pause");
        return false;
    }
    for(i=0;i<VecPedidos.size();i++){
        fwrite(&VecPedidos[i],sizeof(Pedido),1,v);
    }

    fclose(v);
    return true;
}

bool AltaPedido(int numPedido){
    Pedido aux;
    vector<Pedido> VecPedidos;
    int i;

    FILE *p=fopen("archivos/Pedidos.dat","rb");
    if(p==NULL){
        cout<<"Error";
        system("pause");
        return false;
    }

    while(fread(&aux,sizeof(Pedido),1,p)){
        VecPedidos.push_back(aux);

    }
    fclose(p);

    for(i=0;i<VecPedidos.size();i++){
        if(VecPedidos[i].getID()==numPedido){
            VecPedidos[i].setEstado(true);
            VecPedidos[i].setEstadoFinal(true);
        }
    }

    FILE *v=fopen("archivos/Pedidos.dat","wb");
    if(p==NULL){
        cout<<"Error";
        system("pause");
        return false;
    }
    for(i=0;i<VecPedidos.size();i++){
        fwrite(&VecPedidos[i],sizeof(Pedido),1,v);
    }

    fclose(v);
    return true;
}

bool PedidoRecibido(int numPedido){
    bool respuesta;
    Lotes_Prod aux;
    respuesta=aux.AltaPedido(numPedido);
    AltaPedido(numPedido);
    return respuesta;
}
