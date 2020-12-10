#include <iostream>
#include<cstdio>
using namespace std;
#include "Medio_Pago.h"
#include "../clases/Medios_Pago.h"

void Cargar_Medio_pago(){
    Medio_Pago uno;
    if(uno.Cargar_Mpago()==false){
        cout<<"Error de carga de Medio pago"<<endl;
        return;
    }
    if(uno.Guardar_Mpago()==false){
        cout<<"Error al guardar el Medio pago"<<endl;
        return;
    }
    cout<<"Medio pago cargado"<<endl;
}

void Mostar_TodosMpago(){
    Medio_Pago uno;
    FILE*p=fopen("archivos/MediosPago.dat","rb");
        if(p==NULL){
            fclose(p);
            cout<<"Error de archivo"<<endl;
            return;
        }
    while(fread(&uno, sizeof(Medio_Pago),1,p)){
        if(uno.getEstado()==true){
            uno.Listar_Mpago();
            cout<<endl;
        }
    }
    fclose(p);
return;
}

void Mostrar_X_Mpago(){
    int ID;
    cout<<"ID del producto: ";
    cin>>ID;
    Medio_Pago uno;
    if(uno.Buscar_ID_Mpago(ID)==-1){
        cout<<"Producto inexistente"<<endl;
        return;
    }
    if(uno.getEstado()==false){
        cout<<"Producto inexistente"<<endl;
        return;
    }
    uno.Listar_Mpago();
}

void Modificar_Mpago(){
    int ID;
    cout<<"ID del producto: ";
    cin>>ID;
    Medio_Pago uno;
    int pos=uno.Buscar_ID_Mpago(ID);
    if(pos==-1){
        cout<<"Producto inexistente"<<endl;
        return;
    }
    uno.Listar_Mpago();
    float porcentaje;
    cout<<"Ingrese el porcentaje de descuento: %";
    cin>>porcentaje;
        while(porcentaje<0){ ///validando descuento que no sea negativo
            cout<<endl<<"Porcentaje incorrecta, reingrese el Porcentaje"<<endl<<endl;
            cout<<">> Ingrese el porcentaje: %";
            cin>>porcentaje;
        }
    uno.setDescuento(porcentaje);
    if(uno.Modificar_Mpago(pos)==false){
        cout<<"Producto no guardado";
        return;
    }
    cout<<"Producto guardado"<<endl;
}

void Eliminar_Mpago(){
    int ID;
    cout<<"ID del producto: ";
    cin>>ID;
    Medio_Pago uno;
    int pos=uno.Buscar_ID_Mpago(ID);
    if(pos==-1){
        cout<<"Producto inexistente"<<endl;
        return;
    }
    uno.Listar_Mpago();
    uno.setEstado(false);
    if(uno.Modificar_Mpago(pos)==false){
        cout<<"Producto no guardado";
        return;
    }
    cout<<"Producto guardado"<<endl;
}












