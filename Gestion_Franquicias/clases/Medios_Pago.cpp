#include <iostream>
#include <cstdlib>
using namespace std;
#include <cstring>
#include <cstdio>
#include "Medios_Pago.h"
#include "../Validaciones/SINO.h"

Medio_Pago::Medio_Pago(){
    strcpy(Medio, "sin medio");
    Descuento=0;
    Estado=true;
}

bool Medio_Pago::Cargar_Mpago(){
    cout<<"Ingrese el ID ";
    cin>>ID;
        while(ID<0 || ValidarID_Mpago(ID)!=false){ ///validando id que no sea negativo y no se repita
            cout<<"Error ID";
                if(Continuar()==false){
                    system ("cls");
                    return false;
                }
            cout<<">> Ingrese el ID: ";
            cin>>ID;
        }
    cout<<"Cargar el medio de pago que obtendra el descuento: ";
    cin.ignore();
    cin.getline(Medio, 10, '\n');
        while(Medio[0]==' '){
            cout<<endl<<"Medio incorrecta, reingrese el Medio"<<endl<<endl;
            cout<<">> Ingrese el medio: ";
            cin.getline(Medio, 10, '\n');
        }
    cout<<"Ingrese el monto que obtendra el desucento: $";
    cin>>Monto;
        while(Monto<0){ ///validando monto que no sea negativo
            cout<<endl<<"Monto incorrecta, reingrese el Monto"<<endl<<endl;
            cout<<">> Ingrese el monto: $";
            cin>>Monto;
        }
    cout<<"Ingrese el porcentaje de descuento: %";
    cin>>Descuento;
        while(Descuento<0){ ///validando descuento que no sea negativo
            cout<<endl<<"Porcentaje incorrecta, reingrese el Porcentaje"<<endl<<endl;
            cout<<">> Ingrese el porcentaje: %";
            cin>>Descuento;
        }
return true;
}

void Medio_Pago::Listar_Mpago(){
    cout<<"ID "<<ID<<endl;
    cout<<"Medio Pago "<<Medio<<endl;
    cout<<"Monto $"<<Monto<<endl;
    cout<<"Descuento %"<<Descuento<<endl;
}

bool Medio_Pago::Guardar_Mpago(){
    bool grabo;
    FILE *p=fopen("archivos/MediosPago.dat","ab");
    if(p==NULL){
        return false;
    }
    grabo=fwrite(this, sizeof(Medio_Pago),1,p);
    fclose(p);
return grabo;
}

bool Medio_Pago::Modificar_Mpago(int pos){
    bool correcto;
    FILE *p=fopen("archivos/MediosPago.dat","rb+");
        if(p==NULL){
            fclose(p);
            return false;
        }
    fseek(p, pos*sizeof(Medio_Pago), SEEK_SET);
    correcto= fwrite(this, sizeof(Medio_Pago), 1, p);
    fclose(p);
return correcto;
}

int Medio_Pago::Buscar_ID_Mpago(int _ID){
    int pos=0;
    FILE *p=fopen("archivos/MediosPago.dat","rb");
        if(p==NULL){
            fclose(p);
            return -1;///retorna -1 si no encontro el ID
        }
    while(fread(this, sizeof(Medio_Pago),1,p)){
        if(ID==_ID){
            fclose(p);
            return pos; ///retorna la posicion del archivo
        }
        pos++;
    }
    fclose(p);
return -1; ///retorna -1 si no encontro el ID
}

bool ValidarID_Mpago(int _ID){
    Medio_Pago uno;
    FILE *p=fopen("archivos/MediosPago.dat","rb");
        if(p==NULL){
            fclose(p);
            return false;
        }
    while(fread(&uno, sizeof(Medio_Pago),1,p)){
        if(uno.getID()==_ID){
            fclose(p);
            return true; ///retorna la posicion del archivo
        }
    }
    fclose(p);
return false; ///retorna -1 si no encontro el ID
}

float Medio_Pago::Generar_MPago(float total){
    if(total<Monto){///validamos que el total supere al monto minimo de descuento
        cout<<"No supera el monto de descuento"<<endl;
        return total;///si no supera se retorna el total sin operaciones matematicas
    }
return ((Descuento*total)/100);///generamos el descuento
}

float Generar_MPago(float total){
    cout<<"Desea generar medio pago ";
    if(SINO_SinCinIgnore()==false){/// utilizo la funcion de SINO sin cin.ignore
        return total;
    }
    int ID;
    cout<<"ID del medio pago: ";
    cin>>ID;
    Medio_Pago uno;
    while(uno.Buscar_ID_Mpago(ID)==-1){///valido el ID y abro la memoria
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
    cout<<"Porcentaje de descuento %"<<uno.getDescuento()<<endl; ///muestra el porcentaje
return uno.Generar_MPago(total); ///retorna el descuento generado por el metodo "Generar_MPago"
}












