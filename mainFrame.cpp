#include <iostream>
#include <direct.h>

#include "facturacionModulo.h"

using std::cout;
using std::cin;
using std::string;

string version = "1.0.0";

void showMenuTitle();
void mostrarCreditos();

int main() {

    _mkdir(APPDATA_PATH.c_str());
    _mkdir((APPDATA_PATH + "exports").c_str());
    _mkdir((APPDATA_PATH + "facturas").c_str());

    InventoryItems inventario[MAX_INVENTORY_LENGTH];
    int inventory_items = 0;

    inventoryLoad(inventario,inventory_items);
    string OpenExplorer = "explorer " + APPDATA_PATH;

    while(true) {

        system("cls");
        int input;
        sColor(GREEN); showMenuTitle(); resetColor();
        cout<<"Creado para: "; textColored("UAM - Nicaragua", CYAN);

        textColored("\n- Elija una opcion -\n", CYAN);
        cout<<"\n  1. "; textColored("Inventario",DARK_YELLOW);
        cout<<"\n  2. "; textColored("Facturacion",DARK_YELLOW);
        cout<<"\n  3. "; textColored("Reporte de Transacciones",DARK_YELLOW);
        cout<<"\n  4. "; textColored("Abrir Carpeta de Datos",DARK_YELLOW);
        cout<<"\n  5. "; textColored("Mostrar Creditos",DARK_YELLOW);
        cout<<"\n  6. "; textColored("<- Salir del Programa",RED);
        cout<<"\n\n#: ";

        cin>>input;

        switch(input) {
            case(1): mainInventory(inventario,inventory_items); break;
            case(2): facturarMain(inventario,inventory_items); break;
            case(3): mostrarLogs(); system("pause"); break;
            case(4): system(OpenExplorer.c_str()); break;
            case(5): mostrarCreditos(); break;
            case(6): return 0; break;
            default: break;
        }
    }

    return 0;
}

void showMenuTitle() {
    std::cout<<" :::::::: ::::::::::: ::::::::   ::::::::  :::    ::: ::::::::  :::::::::: ::::    :::  ::::::::  :::::::::: \n";
    std::cout<<":+:    :+:    :+:    :+:    :+: :+:    :+: :+:   :+: :+:    :+: :+:        :+:+:   :+: :+:    :+: :+:        \n";
    std::cout<<"+:+           +:+    +:+    +:+ +:+        +:+  +:+  +:+        +:+        :+:+:+  +:+ +:+        +:+        \n";
    std::cout<<"+#++:++#++    +#+    +#+    +:+ +#+        +#++:++   +#++:++#++ +#++:++#   +#+ +:+ +#+ +#++:++#++ +#++:++#   \n";
    std::cout<<"       +#+    +#+    +#+    +#+ +#+        +#+  +#+         +#+ +#+        +#+  +#+#+#        +#+ +#+        \n";
    std::cout<<"#+#    #+#    #+#    #+#    #+# #+#    #+# #+#   #+# #+#    #+# #+#        #+#   #+#+# #+#    #+# #+#        \n";
    std::cout<<" ########     ###     ########   ########  ###    ### ########  ########## ###    ####  ########  ########## \n";
}

void mostrarCreditos() {

    system("cls");
    sColor(GREEN); showMenuTitle(); resetColor();
    cout<<"Creado para: "; textColored("UAM - Nicaragua", CYAN);

    cout<<"\n\n================================================================================================\n";
    textColored("Grupo de trabajo\n",GREEN);
    cout<<"\n- Coordinador de Grupo y responsable del sistema de inventario: "; textColored("Emilio Fernando Meza Ortiz",CYAN);
    cout<<"\n- Miembro de trabajo y responsable del sistema de facturacion: "; textColored("Emmanuel Leonardo Aguilar Novoa",CYAN);
    cout<<"\n- Miembro de trabajo y responsable del sistema de reporte de transacciones: "; textColored("Diego Armando Urbina Aviles",CYAN);
    cout<<"\n- Miembro de trabajo y responsable del sistema de exportacion de datos: "; textColored("Oscar Enrique Arnuero Ramos",CYAN);
    cout<<"\n\n================================================================================================\n";

    cout<<"\n- Docente responsable: "; textColored("Silvia Gigdalia Ticay López",GREEN);
    textColored("\n\nPara la facultad de Ingenieria y Arquitectura de la Universidad Americana (UAM) Nicaragua",YELLOW);
    textColored("\nVersion " + version + "\n",YELLOW);

    sColor(GRAY); system("pause");

}