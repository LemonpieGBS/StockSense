#include <fstream>
#include <string>
#include <iostream>
using namespace std;

void registrarLog(const std::string& accion) {
    ofstream archivo("logs.txt", std::ios::app); 
    if (archivo.is_open()) {
      
        int year = get_current_year();
        int month = get_current_month();
        int day = get_current_day();
        int hour = get_current_hour();
        int minute = get_current_minute();
        int second = get_current_second();

    
        char buffer[80];
        std::sprintf(buffer, "%04d-%02d-%02d %02d:%02d:%02d", year, month, day, hour, minute, second);

        archivo << buffer << " - " << accion << std::endl;

        archivo.close();
    } else {
        std::cerr << "No se pudo abrir el archivo de logs." << std::endl;
    }
}
void addToInventory(InventoryItems inventario[], int &inventory_size) {

    cout << "Producto agregado al inventario." << std::endl;
    inventory_size++; 

    registrarLog("Producto agregado al inventario");
}
void removeFromInventory(InventoryItems inventario[], int &inventory_size) {
    cout << "Producto eliminado del inventario." << endl;
    inventory_size--; 


    registrarLog("Producto eliminado del inventario");
}
void mostrarLogs() {
    ifstream archivo("logs.txt");
    if (archivo.is_open()) {
        string linea;
        while (std::getline(archivo, linea)) {
            std::cout << linea << std::endl;
        }
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo de logs." << endl;
    }
}
switch (opcion) {
    case 1:
        addToInventory(inventario, inventory_size);
        break;
    case 2:
        removeFromInventory(inventario, inventory_size);
        break;
    case 3:
        editOnInventory(inventario, inventory_size);
        break;
    case 4:
        mostrarLogs();
        break;
}