#include <iostream>
using namespace std;
#include<cstdlib>
#include <cstring>
#include <cstdio>
#include "../Menu_Pedidos.h"


proveedore::proveedore(){
    Estado=true;
}

void proveedore::Cargar_Proveedore(){

    ID=CantidadProvedores()+1;

    cout<<"ID= "<<ID<<endl;
    cout<<"Nombre del proveedor: ";
    cin.ignore();
    cin.getline(Nombre, 50, '\n');
        while(Nombre[0]==' '){///validando el nombre que el primer caracter no sea un espacio
            cout<<endl<<"Nombre incorrecta, reingrese el Nombre"<<endl<<endl;
            cout<<">> Ingrese el Nombre: ";
            cin.getline(Nombre, 50, '\n');
        }
        cout<<"Numero de telefono: ";
    cin>>Telefono;
        while(Telefono<1000000000){ ///validando telefono que no sea menor a 10 0000 0000
            cout<<endl<<"telefono incorrecta, reingrese el telefono"<<endl<<endl;
            cout<<">> Ingrese el telefono: ";
            cin>>Telefono;
        }
    cout<<"Descripcion del Proveedor: ";
    cin.ignore();
    cin.getline(Nota, 200, '\n');
        while(Nota[0]==' '){///validando la nota que el primer caracter no sea un espacio
            cout<<endl<<"Nota incorrecta, reingrese el Nota"<<endl<<endl;
            cout<<">> Ingrese el Nota: ";
            cin.getline(Nota, 200, '\n');
        }

}

bool proveedore::Guardar_Proveedore(){
    bool grabo;
    FILE *p=fopen("archivos/Proveedores.dat","ab");
    if(p==NULL){
        return false;
    }
    grabo=fwrite(this, sizeof(proveedore),1,p);
    fclose(p);
return grabo;
}


bool proveedore::Guardar_Cambios(int Posicion){
    bool grabo;
    FILE *p=fopen("archivos/Proveedores.dat","rb+");
    if(p==NULL){
        cout<<"Error";
        system("pause");
        return 0;
    }

       cout<<"ID: "<<ID<<endl;
       cout<<"Nombre del proveedor: "<<Nombre<<endl;
       cout<<"Telefono: "<<Telefono<<endl;
       cout<<"Nota: "<<Nota<<endl;
       cout<<"Estado: "<<Estado<<endl;
       cout<<endl<<endl;
    fseek(p,Posicion*sizeof(proveedore),SEEK_SET);
    grabo=fwrite(this,sizeof(proveedore),1,p);
    fclose(p);
    return grabo;
}

int proveedore::posicionProveedor(int _ID){
    int contador=0;
    FILE *p=fopen("archivos/Proveedores.dat","rb");
    if(p==NULL){
        cout<<"Error";
        system("pause");
        return -1;
    }
    while(fread(this,sizeof(proveedore),1,p)){
        if(_ID==ID){
            fclose(p);
            return contador;
        }
        contador++;
    }
    fclose(p);
    cout<<endl<<"Nose encontro el proveedor";
    system("pause");
    return -1;
}

int proveedore::CantidadProvedores(){

    int contador=0;
    FILE *p=fopen("archivos/Proveedores.dat","rb");
    if(p==NULL){
        return contador;
    }
    while(fread(this,sizeof(proveedore),1,p)){
        contador++;
    }
    fclose(p);
    return contador;
}

void proveedore::Listar_Proveedores(){
   cout<<"ID: "<<ID<<endl;
   cout<<"Nombre del proveedor: "<<Nombre<<endl;
   cout<<"Telefono: "<<Telefono<<endl;
   cout<<"Nota: "<<Nota<<endl;
   cout<<"Estado: "<<Estado<<endl;
   cout<<endl<<endl;

}

int proveedore::getID(){
    return ID;
}
void proveedore::setEstado(bool estado){
    Estado=estado;
}
bool proveedore::getEstado(){
    return Estado;
}

void proveedore::setTelefono(int numero){
    Telefono=numero;}

int proveedore::getTelefono(){
return Telefono;}

void proveedore::setNombre(char *nuevoNombre){
    strcpy(Nombre,nuevoNombre);
}
char *proveedore::getNombre(){
    return Nombre;
}
void proveedore::setNota(char *nuevaNota){
    strcpy(Nota,nuevaNota);
}
char *proveedore::getNota(){
    return Nota;
}

