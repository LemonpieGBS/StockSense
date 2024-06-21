#include <iostream>
#include <vector>
#include <string>

struct Producto {
    std::string nombre;
    float precio;
};

void mostrarMenu() {
    std::cout << "=== Menu ===" << std::endl;
    std::cout << "1. Agregar producto" << std::endl;
    std::cout << "2. Facturar" << std::endl;
    std::cout << "3. Salir" << std::endl;
    std::cout << "=============" << std::endl;
}

void agregarProducto(std::vector<Producto>& productos) {
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

void facturar(const std::vector<Producto>& productos) {
    std::cout << "=== Facturacion ===" << std::endl;

    if (productos.empty()) {
        std::cout << "No hay productos para facturar." << std::endl;
        return;
    }

    float total = 0.0;
    int cantidadProductos = productos.size();

    for (const auto& producto : productos) {
        std::cout << producto.nombre << " - $" << producto.precio << std::endl;
        total += producto.precio;
    }

    std::cout << "===================" << std::endl;
    std::cout << "Total a pagar: $" << total << std::endl;
    std::cout << "Cantidad de productos: " << cantidadProductos << std::endl;
}

int main() {
    std::vector<Producto> productos;

    int opcion;

    do {
        mostrarMenu();
        std::cout << "Ingrese una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                agregarProducto(productos);
                break;
            case 2:
                facturar(productos);
                break;
            case 3:
                std::cout << "Saliendo del programa..." << std::endl;
                break;
            default:
                std::cout << "Opcion invalida. Intente nuevamente." << std::endl;
                break;
        }

        std::cout << std::endl;
    } while (opcion != 3);

    return 0;
}