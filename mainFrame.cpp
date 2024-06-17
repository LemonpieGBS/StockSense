#include <iostream>

using std::cout;
using std::cin;
using std::string;

int main() {

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

        cin>>input;

        switch(input) {
            case(1): break;
            case(2): break;
            case(3): break;
            case(4): break;
            case(5): return 0; break;
            default: break;
        }
    }

    return 0;
}