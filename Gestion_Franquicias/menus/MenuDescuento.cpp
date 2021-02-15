#include <iostream>
#include<cstdio>
using namespace std;
#include "MenuDescuento.h"
#include "../clases/Descuento.h"

void CargarDescuento(){
    Descuento uno;
    if(uno.Cargar_Descuento()==false){
        cout<<"Error de carga de descuento"<<endl;
        return;
    }
    if(uno.Guardar_Descuento()==false){
        cout<<"Error al guardar el producto de descuento"<<endl;
        return;
    }
    cout<<"Descuento cargado"<<endl;
}

bool ListarTodosDescuento(){
    Descuento uno;
    bool mostro=false;
    FILE*p=fopen("archivos/descuento.dat","rb");
        if(p==NULL){
            fclose(p);
            return false;
        }
    while(fread(&uno, sizeof(Descuento),1,p)){
        if(uno.getEstado()==true){
            uno.ListarDescuento();
            mostro=true;
            cout<<endl<<endl;
        }
    }
    fclose(p);
return mostro;
}

void Mostrar_x_Descuento(){
    int ID;
    cout<<"ID del producto: ";
    cin>>ID;
    Descuento uno;
    if(uno.Buscar_Descuento_ID(ID)==-1){
        cout<<"Producto inexistente"<<endl;
        return;
    }
    if(uno.getEstado()==false){
        cout<<"Producto eliminado"<<endl;
        return;
    }
    uno.ListarDescuento();
    cout<<endl;
}

void ModificarDescuento(){
    int ID;
    cout<<"ID del descuento: ";
    cin>>ID;
    Descuento uno;
    int pos=uno.Buscar_Descuento_ID(ID);
    if(pos==-1){
        cout<<"Descuento inexistente"<<endl;
        return;
    }
    uno.ListarDescuento();
    cout<<endl<<endl;
    float monto, porcentaje;
    cout<<"Ingrese el monto minimo para acceder al descuento: $";
    cin>>monto;
    while(monto<0){ ///validando minima incorrecta que no sea negativo
        cout<<endl<<"Error monto, reingrese la monto"<<endl<<endl;
        cout<<">> Ingrese el monto: $";
        cin>>monto;
    }
    uno.setMonto(monto);
    cout<<"Ingrese el procentaje: %";
    cin>>porcentaje;
    while(porcentaje<0 || porcentaje>100){ ///validando minima incorrecta que no sea negativo
        cout<<endl<<"Error porcentaje, reingrese la porcentaje"<<endl<<endl;
        cout<<">> Ingrese el porcentaje: %";
        cin>>porcentaje;
    }
    uno.setPorcentaje(porcentaje);
    if(uno.ModificarDescuento(pos)==false){
        cout<<"Descuento no guardado";
        return;
    }
    cout<<"Descuento guardado"<<endl;
}

void ModificarEstadoDescuento(){
    int ID;
    cout<<"ID del descuento: ";
    cin>>ID;
    Descuento uno;
    int pos=uno.Buscar_Descuento_ID(ID);
    if(pos==-1){
        cout<<"Descuento inexistente"<<endl;
        return;
    }
    uno.ListarDescuento();
    cout<<endl<<endl;
    uno.setEstado(false);
    if(uno.ModificarDescuento(pos)==false){
        cout<<"Descuento no guardado";
        return;
    }
    cout<<"Descuento guardado"<<endl;
}
