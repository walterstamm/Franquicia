#ifndef MENU_PEDIDOS_H_INCLUDED
#define MENU_PEDIDOS_H_INCLUDED
#include <vector>
#include <string>
#include "clases/proveedores.h"
#include "clases/Pedido.h"

void Menu_Pedidos();
void Carga_Provedores();///Carga nuevos Provedores
void Mostrar_Proveedores();
bool ValidarIDProveedores(int);//valida si el ID existe
void DarBajaProveedor();/// da de baja logica al proveedor,(vamos es intuitivo el nombre de la funcion, no pidan mas)xD
void BuscarID(proveedore *,int);
void GeneraPedido();///genera pedido
void ConfirmarPedido();///Confirma pedido realizado o da de baja pedido
bool BajaPedido(int);/// da de baja al pedido


#endif // MENU_PEDIDOS_H_INCLUDED
