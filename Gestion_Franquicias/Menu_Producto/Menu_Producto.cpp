#include <iostream>
#include <cstdio>
#include <iomanip> ///PARA TRABAJAR CON SETW


#include<cstdlib>   ///PARA USAR SYSTEM("PAUSE")
using namespace std;
#include "Menu_Producto.h"
#include "../clases/Producto.h"
#include "../Validaciones/SINO.h"
#include "../clases/Descuento.h"


void Cargar_Producto(){
    Producto uno;
    if(uno.Cargar_Producto()==false){
        cout<<"Error de carga de producto"<<endl;
        uno.~Producto();
        return;
    }
    if(uno.GuardarProducto()==false){
        cout<<"Error al guardar el producto"<<endl;
        uno.~Producto();
        return;
    }
    cout<<"Producto cargado"<<endl;
    uno.~Producto();
}

bool Mostrar_Todos_Producto(){
    Producto uno;
    bool mostro=false;
    FILE*p=fopen("archivos/producto.dat","rb");
        if(p==NULL){
            fclose(p);
            cout<<"Error de archivo"<<endl;
            system("pause");
            return false;
        }
    cout<<"==============================================================================="<<endl;
    cout << left;
    cout << setw(4) << "ID";
    cout << setw(18) << "Descripcion " << setw(9) << "Precio   " << setw(9) << "Cantidad" << setw(12) << "Cant_Min" << setw(16) << "Fecha Vto" << endl;
    cout<<"==============================================================================="<<endl;
    while(fread(&uno, sizeof(Producto),1,p)){
        if(uno.getEstado() == true){
            uno.Mostrar_Producto();
            mostro=true;
        }
    }
    fclose(p);
return mostro;
}

void Mostrar_X_Producto(){
    int ID;
    cout<<"ID del producto: ";
    cin>>ID;
    Producto uno;
    if(uno.Buscar_Producto_ID(ID)==-1){
        cout<<"Producto inexistente"<<endl;
        return;
    }
    cout<<"==============================================================================="<<endl;
    cout << left;
    cout << setw(4) << "ID";
    cout << setw(18) << "Descripcion " << setw(9) << "Precio   " << setw(9) << "Cantidad" << setw(12) << "Cant_Min" << setw(16) << "Fecha Vto" << endl;
    cout<<"==============================================================================="<<endl;
    uno.Mostrar_Producto();
}

void Modificar_Cantidad(){
    int ID;
    cout<<"ID del producto: ";
    cin>>ID;
    Producto uno;
    int pos=uno.Buscar_Producto_ID(ID);
    if(pos==-1){
        cout<<"Producto inexistente"<<endl;
        return;
    }
    uno.Mostrar_Producto();
    cout<<"Ingrese la cantidad: ";
    cin>>ID;
    while(ID<0){ ///validando Cantidad que no sea negativo
       cout<<endl<<"Cantidad incorrecta, reingrese el Cantidad"<<endl<<endl;
        cout<<">> Ingrese el Cantidad: ";
        cin>>ID;
    }
    uno.setCantidad(ID);
    if(uno.ModificarProducto(pos)==false){
        cout<<"Producto no guardado";
        return;
    }
    cout<<"Producto guardado"<<endl;
}

void Modificar_La_Cantidad_minima(){
    int ID;
    cout<<"ID del producto: ";
    cin>>ID;
    Producto uno;
    int pos=uno.Buscar_Producto_ID(ID);
    if(pos==-1){
        cout<<"Producto inexistente"<<endl;
        return;
    }
    uno.Mostrar_Producto();
    cout<<"Ingrese la cantidad minima: ";
    cin>>ID;
    while(ID<0){ ///validando Cantidad que no sea negativo
       cout<<endl<<"Cantidad minima incorrecta, reingrese el Cantidad minima"<<endl<<endl;
        cout<<">> Ingrese el Cantidad minima: ";
        cin>>ID;
    }
    uno.setCantidadMinima(ID);
    if(uno.ModificarProducto(pos)==false){
        cout<<"Producto no guardado"<<endl;
        return;
    }
    cout<<"Producto guardado"<<endl;
}

void Eliminar_Producto(){
    int ID;
    cout<<"ID del producto: ";
    cin>>ID;
    Producto uno;
    int pos=uno.Buscar_Producto_ID(ID);
    if(pos==-1){
        cout<<"Producto inexistente"<<endl;
        return;
    }
    uno.Mostrar_Producto();
    uno.setEstado(false);
    if(uno.ModificarProducto(pos)==false){
        cout<<"Producto no guardado";
        return;
    }
    cout<<"Producto guardado"<<endl;
}

void ventas(){
    int ID, cantidad;
    float total=0;
    do{
        cout<<"ID del producto: ";
        cin>>ID;
        Producto uno;
        int pos=uno.Buscar_Producto_ID(ID);
        if(pos==-1){
            cout<<"Producto inexistente"<<endl; ///no permite realizar la carga
        } else{///producto existente -- puede realizar la carga
                cout<<"Nombre: "<<uno.getNombre()<<endl;
                cout<<"Precio: "<<uno.getPrecio()<<endl;
                cout<<"cantidad: "<<uno.getCantidad()<<endl;
                Fecha dos; ///verificamos la fecha de vencimiento
                if(dos.RetornarFechaVencimiento()==true){/// esto es para comentar fecha de VENCIMIENTO
                cout<<"Ingrese la cantidad vendida: ";
                cin>>cantidad;
                while(cantidad<0 || uno.ValidarCantidadProducto(cantidad)!=true){ ///validando Cantidad que no sea negativo
                   cout<<endl<<"Cantidad minima incorrecta, reingrese el Cantidad minima"<<endl<<endl;
                    cout<<">> Ingrese el Cantidad minima: ";
                    cin>>cantidad;
                }
                total+=uno.getPrecio()*cantidad;
                uno.setCantidad(uno.getCantidad()-cantidad);
                uno.ModificarProducto(pos);
            }
            else{
                cout<<"Producto vencido";
            }
            ///generar objeto venta
        }
    }while(Continuar()==true);
    total=GenerarDescuento(total);
    cout<<"total $"<<total<<endl;
    ///boleta
}

void Modificar_Precio(){
    int ID;
    cout<<"ID del producto: ";
    cin>>ID;
    Producto uno;
    int pos=uno.Buscar_Producto_ID(ID);
    if(pos==-1){
        cout<<"Producto inexistente"<<endl;
        return;
    }
    uno.Mostrar_Producto();
    float precio;
    cout<<"Ingrese el precio: $";
    cin>>ID;
    while(precio<0){ ///validando Cantidad que no sea negativo
       cout<<endl<<"precio incorrecta, reingrese el precio"<<endl<<endl;
        cout<<">> Ingrese el precio: $";
        cin>>precio;
    }
    uno.setPrecio(precio);
    if(uno.ModificarProducto(pos)==false){
        cout<<"Producto no guardado"<<endl;
        return;
    }
    cout<<"Producto guardado"<<endl;
}
