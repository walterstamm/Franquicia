#include <iostream>
using namespace std;
#include <string.h>
#include "SINO.h"

bool Continuar(){
    char opcion[3]={};
    cout<<" Desea continuar (SI/NO): ";
    cin.ignore();
    cin.getline(opcion, 4, '\n');
    if((strcmp(opcion, "si") && strcmp(opcion, "SI") && strcmp(opcion, "Si") && strcmp(opcion, "sI")) ==0){
        return true;
    }
    else{
        if((strcmp(opcion, "no") && strcmp(opcion, "NO") && strcmp(opcion, "No") && strcmp(opcion, "nO"))==0){
            return false;
        }
    }
    do{
        cout<<endl<<"-Error de ingreso de datos-"<<endl;
        cout<<"Desea continuar (SI/NO): ";
        cin.getline(opcion, 4, '\n');
        if((strcmp(opcion, "si") && strcmp(opcion, "SI") && strcmp(opcion, "Si") && strcmp(opcion, "sI"))==0){
            return true;
        }
        else{
            if((strcmp(opcion, "no") && strcmp(opcion, "NO") && strcmp(opcion, "No") && strcmp(opcion, "nO"))==0){
                return false;
            }
        }
    }while(1!=0);
return true;
}

bool Continuar_SinCindIgnore(){
    char opcion[3]={};
    cout<<" Desea continuar (SI/NO): ";
    cin.getline(opcion, 4, '\n');
    if((strcmp(opcion, "si") && strcmp(opcion, "SI") && strcmp(opcion, "Si") && strcmp(opcion, "sI")) ==0){
        return true;
    }
    else{
        if((strcmp(opcion, "no") && strcmp(opcion, "NO") && strcmp(opcion, "No") && strcmp(opcion, "nO"))==0){
            return false;
        }
    }
    do{
        cout<<endl<<"-Error de ingreso de datos-"<<endl;
        cout<<"Desea continuar (SI/NO): ";
        cin.getline(opcion, 4, '\n');
        if((strcmp(opcion, "si") && strcmp(opcion, "SI") && strcmp(opcion, "Si") && strcmp(opcion, "sI"))==0){
            return true;
        }
        else{
            if((strcmp(opcion, "no") && strcmp(opcion, "NO") && strcmp(opcion, "No") && strcmp(opcion, "nO"))==0){
                return false;
            }
        }
    }while(1!=0);
return true;
}

bool SINO(){
    char opcion[3]={};
    cout<<"(SI/NO): ";
    cin.ignore();
    cin.getline(opcion, 4, '\n');
    if((strcmp(opcion, "si") && strcmp(opcion, "SI") && strcmp(opcion, "Si") && strcmp(opcion, "sI")) ==0){
        return true;
    }
    else{
        if((strcmp(opcion, "no") && strcmp(opcion, "NO") && strcmp(opcion, "No") && strcmp(opcion, "nO"))==0){
            return false;
        }
    }
    do{
        cout<<endl<<"-Error de ingreso de datos-"<<endl;
        cout<<"Desea continuar (SI/NO): ";
        cin.getline(opcion, 4, '\n');
        if((strcmp(opcion, "si") && strcmp(opcion, "SI") && strcmp(opcion, "Si") && strcmp(opcion, "sI"))==0){
            return true;
        }
        else{
            if((strcmp(opcion, "no") && strcmp(opcion, "NO") && strcmp(opcion, "No") && strcmp(opcion, "nO"))==0){
                return false;
            }
        }
    }while(1!=0);
return true;
}

bool SINO_SinCinIgnore(){
    char opcion[3]={};
    cout<<"(SI/NO): ";
    cin.getline(opcion, 4, '\n');
    if((strcmp(opcion, "si") && strcmp(opcion, "SI") && strcmp(opcion, "Si") && strcmp(opcion, "sI")) ==0){
        return true;
    }
    else{
        if((strcmp(opcion, "no") && strcmp(opcion, "NO") && strcmp(opcion, "No") && strcmp(opcion, "nO"))==0){
            return false;
        }
    }
    do{
        cout<<endl<<"-Error de ingreso de datos-"<<endl;
        cout<<"Desea continuar (SI/NO): ";
        cin.getline(opcion, 4, '\n');
        if((strcmp(opcion, "si") && strcmp(opcion, "SI") && strcmp(opcion, "Si") && strcmp(opcion, "sI"))==0){
            return true;
        }
        else{
            if((strcmp(opcion, "no") && strcmp(opcion, "NO") && strcmp(opcion, "No") && strcmp(opcion, "nO"))==0){
                return false;
            }
        }
    }while(1!=0);
return true;
}
