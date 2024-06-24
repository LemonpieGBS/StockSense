#include <iostream>
#include "facturacion.h"

using std::cout;
using std::cin;
using std::string;

int main() {

    InventoryItems inventario[MAX_INVENTORY_LENGTH];
    int inventory_items = 0;

    while(true) {
        system("cls");
        int input;
        cout<<"StockSense-II\n";

        cout<<"\nElija una opción: ";
        cout<<"\n 1. Inventario";
        cout<<"\n 2. Facturación";
        cout<<"\n 3. Reporte de Acciones";
        cout<<"\n 4. Exportar datos";
        cout<<"\n 5. <- Salir";
        cout<<"\n\n#: ";

        cin>>input;

        switch(input) {
            case(1): mainInventory(inventario,inventory_items); break;
            case(2): facturarMain(inventario,inventory_items); break;
            case(3): mostrarLogs(); system("pause"); break;
            case(4): break;
            case(5): return 0; break;
            default: break;
        }
    }

    return 0;
}