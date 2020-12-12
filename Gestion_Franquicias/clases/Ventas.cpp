#include <iostream>
#include <string.h>
#include <cstdio>
#include <iomanip>
#include <cstdlib>
#include <vector>
using namespace std;
#include "Ventas.h"
#include "Producto.h"

Ventas::Ventas(){
    Cod_Producto = 0;
    strcpy(Descripcion, "nada");
    Cant_Producto = 0;
    Precio = 0;
    Importe = 0;
}

void Ventas::Cargar_Venta(int NroFactura, int CodProducto, char *Descrip, int CantProducto, float Precios, float Importes){
        V_Nro_Fact = NroFactura;
        Cod_Producto = CodProducto;
        strcpy(Descripcion, Descrip);
        Cant_Producto = CantProducto;
        Precio = Precios;
        Importe = Importes;
}

int Ventas::Leo_Ventas(){
    int Cant_Ventas=-1;
    FILE *Ven=fopen("archivos/Ventas.dat", "rb");
    if(Ven == NULL){
        cout<<"No se abrio el Archivo Ventas.dat";
        return Cant_Ventas=0;
    }
    while(fread(this, sizeof(Ventas), 1, Ven)){
        Cant_Ventas ++;
    }
    getNro_Fact();
    return Cant_Ventas;
}

int Ventas::BuscarPosicion(int Numero){
    int Pos=-1;
    FILE *Ven=fopen("archivos/Ventas.dat", "rb");
    if(Ven == NULL){
        cout<<"No se abrio el Archivo Ventas.dat";
        return Pos;
    }
    while(fread(this, sizeof(Ventas), 1, Ven)){
        if(Numero == V_Nro_Fact){
            return Pos;
        }


    }
    return Pos;
}

///este get no retorna nada da otro error

void Ventas::getVentas(){
    cout<<"\nNro_Factura: "<<V_Nro_Fact;
    cout<<"\nCod_Produto: "<<Cod_Producto;
    cout<<"\nDescripción: "<<Descripcion;
    cout<<"\nCant_Producto:"<<Cant_Producto;
    cout<<"\nPrecio: "<<Precio;
    cout<<"\nSubtotal: "<<Importe;
}

void Ventas::MostrarVenta(){
    cout << right;
    cout << setw(4);
    cout << getNro_Fact();
    cout << setw(6);
    cout << getCod_Producto();
    cout << setw(3);
    cout << " ";
    cout << left;
    cout << setw(16);
    cout << getDescripcion();
    cout << right;
    cout << setw(5);
    cout << getCant_Producto();
    cout << setw(10);
    cout << getPrecio();
    cout << setw(13);
    cout << getImporte()<<endl;
}

Ventas Preventa( int CodProducto, int NroFactura, int CantProducto){
    char Descrip[20];
    Producto prod;
    Ventas ven;
    FILE *Pr = fopen("archivos/producto.dat", "rb");
    if(Pr == NULL){ cout<<"Error"; system("pause");
            return ven; }

    while(fread(&prod, sizeof(Producto), 1, Pr)){
        if(CodProducto == prod.getID()){
            strcpy(Descrip, prod.getNombre());
            cout<<"Producto: "<<Descrip;                ///     COPIO EL NOMBRE
            float Precios=(prod.getPrecio());           ///     COPIO EL PRECIO
            cout<<"Precio: "<<Precios;
            float Importe = Precios * CantProducto;     ///     ASIGNO SUBTOTAL A IMPORTE EL VALOR POR EL REGISTRO
            cout<<"\nProducto: "<<Descrip<<" Precio: "<<Precios<<" Subtotal: "<<Importe<<endl;
            ///     CARGO EL CONTENIDO DE LAS VARIABLES EN VENTAS
            ven.Cargar_Venta(NroFactura, CodProducto, Descrip, CantProducto, Precios, Importe);
            fclose(Pr);
            return ven;
        }
    }
    fclose(Pr);
    return ven;
}

void Ventas::GuardaVentas(){
    FILE *Ven = fopen("archivos/Ventas.dat", "ab");
    if(Ven == NULL) {
        cout<<"ERROR = Ventas.dat";
        return;}
    int caso = fwrite(this, sizeof(Ventas), 1, Ven);
    if(caso == 0){
        cout<<"NO SE GRABO"<<endl;
    } else{
        if(caso == 1){ }
    }
}
