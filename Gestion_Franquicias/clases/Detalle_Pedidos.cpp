#include<iostream>
#include "Detalle_Pedidos.h"
using namespace std;


Detalle_Pedido::Detalle_Pedido(){};

void Detalle_Pedido::setID_Pedido(int _ID_Pedido){
    ID_Pedido=_ID_Pedido;
}
void Detalle_Pedido::setID_Producto(int _ID_Producto){
    ID_Producto=_ID_Producto;
}
void Detalle_Pedido::setCantidad(int _Cantidad){
    cantidad=_Cantidad;
}
void Detalle_Pedido::setPrecio(float _Precio){
    precio=_Precio;
}

int Detalle_Pedido::getID_Pedido(){
    return ID_Pedido;
}
int Detalle_Pedido::getID_Producto(){
    return ID_Producto;
}
int Detalle_Pedido::getCantidad(){
    return cantidad;
}
float Detalle_Pedido::getPrecio(){
    return precio;
}
