#include <iostream>
#include <iomanip>
using namespace std;
#include<cstdlib>
#include <cstring>
#include <cstdio>
#include "Producto.h"
#include "../Validaciones/SINO.h"
#include "Lotes_Productos.h"

Producto::Producto(){
    Precio=0;
    estado=false;
}

Producto::~Producto(){
}

bool Producto::Cargar_Producto(){
    ID=NumeroId()+1;
    cout<<endl<<"ID: "<<ID<<endl;
    cout<<"Ingrese el nombre: ";
    cin.ignore();
    cin.getline(Nombre, 50, '\n');
        while(Nombre[0]==' '){///validando el nombre que el primer caracter no sea un espacio
            cout<<endl<<"Nombre incorrecta, reingrese el Nombre"<<endl<<endl;
            cout<<">> Ingrese el Nombre: ";
            cin.getline(Nombre, 30, '\n');
        }
    cout<<"Ingrese el precio por unidad: $";
    cin>>Precio;
        while(Precio<=0){ ///validando Precio que no sea negativo
            cout<<endl<<"Precio incorrecta, reingrese el Precio"<<endl<<endl;
            cout<<">> Ingrese el Precio por unidad: $";
            cin>>Precio;
        }

    Cantidad=0;

    cout<<"Ingrese la cantidad minima: ";
    cin>>Cantidad_Minima;
        while(Cantidad_Minima<=0){ ///validando minima que no sea negativo
            cout<<endl<<"cantidad minima incorrecta, reingrese la cantidad m�nima"<<endl<<endl;
            cout<<">> Ingrese el cantidad m�nima: ";
            cin>>Cantidad_Minima;
        }
    ///bool verificacion=Vencimiento.Cargar_Fecha_Vencimiento();
    /**while(Vencimiento.Cargar_Fecha_Vencimiento()!=true){
        cout<<endl<<"Fecha de vencimiento incorrecta"<<endl<<endl;
        if(Continuar()==false){
            system ("cls");
            return false;
        }
    }*/
return true;
}

void Producto::Mostrar_Producto(){ ///Muestra la cabezera del producto
            Lotes_Prod Prod;
            int Cant = Prod.Cuento_CantProd_Lotes( ID);
            cout << left;
            cout << setw(4);
            cout << ID;
            cout << setw(18);
            cout << Nombre;
            cout << right;
            cout << setw(6);
            cout << Precio;
            /**cout << setw(9);
            cout << Cantidad;*/
            cout << setw(10);
            cout << Cantidad_Minima;
            /**cout << setw(10);
            cout << Fecha().getDia()<<"/"<<Fecha().getMes()<<"/"<<Fecha().getAnio();
            cout << setw(9);
            cout << estado*/
            cout << endl;


    /**cout<<"ID "<<ID<<endl;
    cout<<"Nombre "<<Nombre<<endl;
    cout<<"Precio $"<<Precio<<endl;
    cout<<"Cantidad "<<Cantidad<<endl;
    cout<<"Cantidad Minima "<<Cantidad_Minima<<endl;
    cout<<"Fecha de vencimiento "<<endl;
    Vencimiento.Mostrar_Fecha();
    cout<<endl<<"Fecha de ingreso "<<endl;
    Actual.Mostrar_Fecha();
    cout<<endl<<endl;*/
}

void Producto::Mostrar(){ ///Muestra la informacion de los archivos
    Producto pro;
    Lotes_Prod Lot;
    FILE * P= fopen("archivos/producto.dat","rb");
    if(P==NULL){ return;}
    cout<<"Nro    Cant     Producto"<<endl;
    while(fread(&pro, sizeof(Producto), 1, P)){
        cout<<pro.getID()<<"      "<<Lot.Cuento_CantProd_Lotes(pro.getID())<<"       "<<pro.getNombre()<<endl;
    }
    cout<<endl;
    fclose(P);
}

bool Producto::GuardarProducto(){
    bool grabo;
    FILE *p=fopen("archivos/producto.dat","ab");
    if(p==NULL){
        return false;
    }
    grabo=fwrite(this, sizeof(Producto),1,p);
    fclose(p);
return grabo;
}

int Producto::Buscar_Producto_ID(int _ID){
    int pos=0;
    FILE *p=fopen("archivos/producto.dat","rb");
        if(p==NULL){
            fclose(p);
            return -1;///retorna -1 si no encontro el ID
        }
    while(fread(this, sizeof(Producto),1,p)){
        if(ID==_ID){
            fclose(p);
            return pos; ///retorna la posicion del archivo
        }
        pos++;
    }
    fclose(p);
return -1; ///retorna -1 si no encontro el ID
}

bool Producto::ModificarProducto(int pos){
    bool correcto;
    FILE *p=fopen("archivos/Producto.dat","rb+");
        if(p==NULL){
            fclose(p);
            return false;
        }
    fseek(p, pos*sizeof(Producto), SEEK_SET);
    correcto= fwrite(this, sizeof(Producto), 1, p);
    fclose(p);
return correcto;
}

bool ValidarIDProducto(int _ID){
    Producto uno;
    FILE *p=fopen("archivos/producto.dat","rb");
        if(p==NULL){
            fclose(p);
            return false;
        }
    while(fread(&uno, sizeof(Producto),1,p)){
        if(uno.getID()==_ID){
            fclose(p);
            return true; ///retorna la posicion del archivo
        }
    }
    fclose(p);
return false; ///retorna -1 si no encontro el ID
}

bool Producto::ValidarCantidadProducto(int _cantidad){
    if(_cantidad> Cantidad){
        cout<<"Cantidad excedida"<<endl;
        cout<<"usted cuenta con: "<<Cantidad<<endl;
        return false;
    }
return true;
}

int Producto::getCantidad_Cod(int cod){

    FILE *p=fopen("archivos/Producto.dat","rb");
        if(p==NULL){
            return -1;
        }
    int pos = Buscar_Producto_ID(cod);

    fseek(p, pos*sizeof(Producto), SEEK_SET);
    fwrite(this, sizeof(Producto), 1, p);
    int Cantidad = getCantidad();
    fclose(p);

    return Cantidad;
}

bool Cargar_Producto(int ID){
    char nombre[50];
    int precio, cantidad, cantidad_Minima;
    Producto pr;
    pr.setID(ID);
    cout<<"ID Nro:            "<<pr.getID()<<endl;
    cout<<"Ingrese el nombre: ";
    cin.ignore();
    cin.getline(nombre, 50, '\n');
        while(nombre[0] == ' '){///validando el nombre que el primer caracter no sea un espacio
            cout<<endl<<"Nombre incorrecto, reingrese el Nombre"<<endl<<endl;
            cout<<">> Ingrese el Nombre: ";
            cin.getline(nombre, 50, '\n');
        }
        pr.setNombre(nombre);
    cout<<"Ingrese el precio por unidad: $";
    cin>>precio;
        while(precio<0){ ///validando Precio que no sea negativo
            cout<<endl<<"Precio incorrecta, reingrese el Precio"<<endl<<endl;
            cout<<">> Ingrese el Precio por unidad: $";
            cin>>precio;
        }
        pr.setPrecio(precio);
    cout<<"Ingrese la cantidad: ";
    cin>>cantidad;
        while(cantidad<0){ ///validando Cantidad que no sea negativo
            cout<<endl<<"Cantidad incorrecta, reingrese el Cantidad"<<endl<<endl;
            cout<<">> Ingrese el Cantidad: ";
            cin>>cantidad;
        }
        pr.setCantidad(cantidad);
    cout<<"Ingrese la cantidad minima: ";
    cin>>cantidad_Minima;
        while(cantidad_Minima<0){ ///validando minima que no sea negativo
            cout<<endl<<"cantidad minima incorrecta, reingrese la cantidad m�nima"<<endl<<endl;
            cout<<">> Ingrese el cantidad m�nima: ";
            cin>>cantidad_Minima;
        }
        pr.setCantidadMinima(cantidad_Minima);
    ///bool verificacion=Vencimiento.Cargar_Fecha_Vencimiento();
    while(Fecha().Cargar_Fecha_Vencimiento()!=true){
        cout<<endl<<"Fecha de vencimiento incorrecta"<<endl<<endl;
        if(Continuar()==false){
            system ("cls");
            return false;
        }
    }
    return true;
}

int Producto::NumeroId(){
    int NumId;
    FILE *p=fopen("archivos/producto.dat","rb");
    if(p==NULL){
        return 0;
    }
    fseek(p,sizeof(Producto)*-1,2);
    fread(this,sizeof(Producto),1,p);
    NumId=ID;
    fclose(p);
    return NumId;
}

