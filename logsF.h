#include <fstream>
#include <string>
#include <iostream>

#include "ficherosYcolores.h"
#include "time_functions.h"
using namespace std;

void showLogsTitle();

void registrarLog(const std::string& accion) {

    ofstream archivo(APPDATA_PATH + "logs.txt", std::ios::app); 
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
        textColored("#ERROR: No se pudo abrir el archivo de logs.",RED);
    }

}
/* PROTOTIPO DE LOGS #1
void addToInventory(InventoryItems inventario[], int &inventory_size) {

    cout << "Producto agregado al inventario." << std::endl;
    inventory_size++; 

    registrarLog("Producto agregado al inventario");
}
*/

/* PROTOTIPO DE LOGS #2
void removeFromInventory(InventoryItems inventario[], int &inventory_size) {
    cout << "Producto eliminado del inventario." << endl;
    inventory_size--; 


    registrarLog("Producto eliminado del inventario");
}
*/

void mostrarLogs() {

    system("cls");
    showLogsTitle();
    ifstream archivo(APPDATA_PATH + "logs.txt");
    if (archivo.is_open()) {
        textColored("================================================================================================\n",GRAY);
        string linea;
        while (std::getline(archivo, linea)) {
            textColored(linea + "\n",YELLOW);
        }
        textColored("================================================================================================\n",GRAY);
        archivo.close();
    } else {
        textColored("- No se pudo abrir el archivo de logs.",RED);
    }
}

/* Opción de Prueba
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
*/

void showLogsTitle() {
    sColor(GREEN);
    std::cout<<"  _____ ____      _    _   _ ____    _    ____ ____ ___ ___  _   _ _____ ____  \n";
    std::cout<<" |_   _|  _ \\    / \\  | \\ | / ___|  / \\  / ___/ ___|_ _/ _ \\| \\ | | ____/ ___| \n";
    std::cout<<"   | | | |_) |  / _ \\ |  \\| \\___ \\ / _ \\| |  | |    | | | | |  \\| |  _| \\___ \\ \n";
    std::cout<<"   | | |  _ <  / ___ \\| |\\  |___) / ___ \\ |__| |___ | | |_| | |\\  | |___ ___) |\n";
    std::cout<<"   |_| |_| \\_\\/_/   \\_\\_| \\_|____/_/   \\_\\____\\____|___\\___/|_| \\_|_____|____/ \n";
    std::cout<<"\n";
    resetColor();
}