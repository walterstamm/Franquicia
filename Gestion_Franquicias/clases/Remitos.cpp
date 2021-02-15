#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
#include "Remitos.h"




Remito::Remito(){
Estado=true;
}
Remito::~Remito(){
cout<<"Se ha eliminado este remito";
}

void Remito::setFecha_Remito(){
    Fecha _Fecha;
    cout<<"Cargue la Fecha del Remito"<<endl;
   bool valido= _Fecha.Cargar_Fecha();
   Fecha_Remito=_Fecha;
}
void Remito::setVto_Producto(Fecha _Vto_Prod){
    Vto_Producto=_Vto_Prod;
}
void Remito::Cargar_Remito(){
    cout<<"Ingrese el ID del provedor: "<<endl;
    cin>>ID_Provedor;
    cout<<"Codigo Producto: "<<endl;
    cin>>Codigo_Producto;
    cout<<"Cantidad: "<<endl;
    cin>>Cantidad;
    cout<<"Precio: "<<endl;
    cin>>Precio;
    ///Generar numero de remito automatico por sistema
    ///Desarrollar todo el trabajo de fechas, para poder validad los vtos
    cout<<"Presione ENTER para Finalizar"<<endl;
    system("pause");
    Estado=true;

}
void Mostrar_Remito();

void Remito::setID_Provedor(int _ID_Provedor){
    ID_Provedor=_ID_Provedor;
}
void Remito::setCodigo_Producto(int _Codigo_Producto){
    Codigo_Producto=_Codigo_Producto;
}
void Remito::setCantidad(int _Cantidad){
    Cantidad=_Cantidad;
}
void Remito::setPrecio(float _Precio){
    Precio=_Precio;
}
void Remito::setNro_Remito(int _Nro_Remito){
    Nro_Remito=_Nro_Remito;
}
void Remito::setEstado(bool _Estado){
    Estado=_Estado;
}

int Remito::setID_Provedor(){
    return ID_Provedor;
}
int Remito::setCodigo_Producto(){
    return Codigo_Producto;
}
int Remito::setCantidad(){
    return Cantidad;
}

float Remito::setPrecio(){
    return Precio;
}
int Remito::setNro_Remito(){
    return Nro_Remito;
}
bool Remito::setEstado(){
    return Estado;
}
