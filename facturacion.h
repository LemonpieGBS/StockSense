#include <iostream>
#include <vector>
#include <string>

#include "inventoryFunctions.h"

struct Producto {
    std::string nombre;
    float precio;
    int unidades_compradas;
    int id;
};

void mostrarMenu() {
    system("cls");
    std::cout << "=== Menu ===" << std::endl;
    //std::cout << "1. Agregar producto" << std::endl;
    std::cout << "1. Facturar" << std::endl;
    std::cout << "2. Salir" << std::endl;
    std::cout << "=============" << std::endl;
}

/* FUNCION DE PRUEBA DE ANTES DE INTEGRAR INVENTORYITEMS
void agregarProducto(InventoryItems arr[], int inv_cant) {
    std::string nombre;
    float precio;

    std::cout << "Ingrese el nombre del producto: ";
    std::cin >> nombre;
    std::cout << "Ingrese el precio del producto: ";
    std::cin >> precio;

    Producto nuevoProducto;
    nuevoProducto.nombre = nombre;
    nuevoProducto.precio = precio;

    productos.push_back(nuevoProducto);

    std::cout << "Producto agregado correctamente." << std::endl;
}
*/

void facturar(InventoryItems arr[], int inv_cant) {
    system("cls");
    std::cout << "=== Facturacion ===" << std::endl;

    std::string factura_nombre;
    std::cout<<"Ingrese el nombre de la factura: ";
    std::cin.ignore();
    std::getline(std::cin,factura_nombre);

    if (inv_cant == 0) {
        std::cout << "No hay productos para facturar." << std::endl;
        sleep(2);
        return;
    }

    float total = 0.0;

    std::cout<<"Elija un producto para facturar: ";
    int i = 0;
    for (int i = 0; i < inv_cant; i++) {
        std::cout << "\n"<< (i + 1) << ". ";
        std::cout << arr[i].name << " - $" << arr[i].price << ", Restantes: "<<arr[i].quantity_left<< std::endl;
        //total += producto.precio;
    }

    bool facturar_loop = true;
    int objeto_opcion, productos_cant = 0;
    Producto *productos_facturados = new Producto[inv_cant];

    do {
        std::string SN;

        std::cout<<"Ingrese el numero del producto a facturar: ";
        std::cin>>objeto_opcion;

        if(objeto_opcion > inv_cant || objeto_opcion < 0) std::cout<<"Objeto invalido!"<< std::endl;
        else {
            int unidades_deseadas;

            std::cout<<"Cuantas unidades desea del producto \""<<arr[objeto_opcion - 1].name<<"\"?: ";
            std::cin>>unidades_deseadas;

            if(unidades_deseadas > arr[objeto_opcion - 1].quantity_left) {

                std::cout<<"No hay suficientes unidades en inventario!"<< std::endl;
            } else {
                
                bool objeto_ya_facturado = false;
                for(i = 0; i < productos_cant; i++) {

                    if(productos_facturados[i].id == objeto_opcion - 1) {

                        objeto_ya_facturado = true;
                        productos_facturados[i].unidades_compradas += unidades_deseadas;
                        arr[productos_facturados[i].id].quantity_left -= unidades_deseadas;
                        break;
                    }

                }

                if(!objeto_ya_facturado) {

                    productos_facturados[productos_cant].nombre = arr[objeto_opcion - 1].name;
                    productos_facturados[productos_cant].precio = arr[objeto_opcion - 1].price;
                    productos_facturados[productos_cant].unidades_compradas = unidades_deseadas;
                    productos_facturados[productos_cant].id = objeto_opcion - 1;

                    arr[objeto_opcion - 1].quantity_left -= unidades_deseadas;
                    productos_cant++;

                }

            }
        }

        std::cout<<"Desea agregar otro producto? (S/N): ";
        std::cin>>SN;

        if(SN == "N" || SN == "n") facturar_loop = false;

    } while(facturar_loop == true);

    if(productos_cant == 0) return;

    std::cout << "============================================" << std::endl;
    std::cout << "NOMBRE DE FACTURA: "<<factura_nombre<< std::endl;
    std::cout << "FECHA: "<<get_current_day()<<"/"<<get_current_month()<<"/"<<get_current_year()<< std::endl;
    std::cout << "HORA: "<<get_current_hour()<<":"<<get_current_minute() << std::endl;
    std::cout << std::endl;

    for(int i = 0; i < productos_cant; i++) {
        std::cout << productos_facturados[i].nombre << " - $"<<productos_facturados[i].precio<<std::endl;
        if(productos_facturados[i].unidades_compradas > 1) {
            std::cout<<"- (x"<<productos_facturados[i].unidades_compradas<<") - $"<<(productos_facturados[i].precio * productos_facturados[i].unidades_compradas)<<std::endl;
        }
        total += (productos_facturados[i].precio * productos_facturados[i].unidades_compradas);
    }
    std::cout << "============================================" << std::endl;
    std::cout << "Total a pagar: $" << total << std::endl;
    //std::cout << "Cantidad de productos: " << cantidadProductos << std::endl;

    system("pause");
}

void facturarMain(InventoryItems arr[], int inv_cant) {

    int opcion;

    do {
        mostrarMenu();
        std::cout << "Ingrese una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                facturar(arr,inv_cant);
                break;
            case 2:
                std::cout << "Saliendo del programa..." << std::endl;
                return;
                break;
            default:
                std::cout << "Opcion invalida. Intente nuevamente." << std::endl;
                break;
        }

        std::cout << std::endl;
    } while (opcion != 3);

}