#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
using namespace std;
#include "Descuento.h"
#include "../Validaciones/SINO.h"

Descuento::Descuento(){
    Estado=true;
}

bool Descuento::Cargar_Descuento(){
    cout<<"Ingrese el ID de descuento: ";
    cin>>ID;
    while(ID<0 || Validar_ID_Descuento(ID)!=false){ ///validando minima incorrecta que no sea negativo
        cout<<endl<<"Error ID"<<endl<<endl;
            if(Continuar()==false){
                system ("cls");
                return false;
            }
        cout<<">> Ingrese el ID: ";
        cin>>ID;
    }
    cout<<"Ingrese el monto minimo para acceder al descuento: $";
    cin>>Monto;
    while(Monto<0){ ///validando minima incorrecta que no sea negativo
        cout<<endl<<"Error monto, reingrese la monto"<<endl<<endl;
        cout<<">> Ingrese el monto: $";
        cin>>Monto;
    }
    cout<<"Ingrese el porcentaje de descuento: %";
    cin>>Porcentaje;
    while(Porcentaje<0 || Porcentaje>100){ ///validando minima incorrecta que no sea negativo
        cout<<endl<<"Error porcentaje, reingrese la porcentaje"<<endl<<endl;
        cout<<">> Ingrese el porcentaje: %";
        cin>>Monto;
    }
return true;
}

void Descuento::ListarDescuento(){
    cout<<"ID: "<<ID<<endl;
    cout<<"Monto minimo: "<<Monto<<endl;
    cout<<"Porcentaje: "<<Porcentaje<<endl;
    cout<<"Estado: "<<Estado<<endl;
    cout<<"Fecha inicio"<<endl;
    Actual.Mostrar_Fecha();
    cout<<endl;
}

bool Descuento::Guardar_Descuento(){
    bool grabo;
    FILE *p=fopen("archivos/descuento.dat","ab");
    if(p==NULL){
        return false;
    }
    grabo=fwrite(this, sizeof(Descuento),1,p);
    fclose(p);
return grabo;
}

int Descuento::Buscar_Descuento_ID(int _ID){
    int pos=0;
    FILE *p=fopen("archivos/descuento.dat","rb");
        if(p==NULL){
            fclose(p);
            return -1;///retorna -1 si no encontro el ID
        }
    while(fread(this, sizeof(Descuento),1,p)){
        if(ID==_ID){
            fclose(p);
            return pos; ///retorna la posicion del archivo
        }
        pos++;
    }
    fclose(p);
return -1; ///retorna -1 si no encontro el ID
}

bool Descuento::ModificarDescuento(int pos){
    bool correcto;
    FILE *p=fopen("archivos/descuento.dat","rb+");
        if(p==NULL){
            fclose(p);
            return false;
        }
    fseek(p, pos*sizeof(Descuento), SEEK_SET);
    correcto= fwrite(this, sizeof(Descuento), 1, p);
    fclose(p);
return correcto;
}

bool Validar_ID_Descuento(int _ID){
    Descuento uno;
    FILE *p=fopen("archivos/descuento.dat","rb");
        if(p==NULL){
            fclose(p);
            return false;
        }
    while(fread(&uno, sizeof(Descuento),1,p)){
        if(uno.getID()==_ID){
            fclose(p);
            return true; ///retorna la posicion del archivo
        }
    }
    fclose(p);
return false; ///retorna -1 si no encontro el ID
}

float Descuento::GenerarDescuento(float total){
    if(total<Monto){///validamos que el total supere al monto minimo de descuento
        cout<<"No supera el monto de descuento"<<endl;
        return total;///si no supera se retorna el total sin operaciones matematicas
    }
return ((Porcentaje*total)/100);///generamos el descuento
}

float GenerarDescuento(float total){
    cout<<"Desea generar descuento ";
    if(SINO_SinCinIgnore()==false){/// utilizo la funcion de SINO sin cin.ignore
        return total;
    }
    int ID;
    cout<<"ID del descuento: ";
    cin>>ID;
    Descuento uno;
    while(uno.Buscar_Descuento_ID(ID)==-1){///valido el ID y abro la memoria
        cout<<endl<<"Error ID"<<endl;
            if(Continuar()==false){ ///incorrecto pregunto si continual
                system ("cls");
                return false;
            }
        cout<<">> Ingrese el ID: ";
        cin>>ID;
    }
    if(uno.getEstado()==false){ ///si el estado del descuento es false no existe tal descuento
        cout<<"Descuento eliminado"<<endl;
        return total;
    }
    cout<<"Porcentaje de descuento %"<<uno.getPorcentaje()<<endl; ///muestra el porcentaje
return uno.GenerarDescuento(total); ///retorna el descuento
}
