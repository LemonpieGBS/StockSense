#include <iostream> // Biblioteca para operaciones de entrada y salida
#include <direct.h> // Biblioteca para operaciones de directorios (como crear directorios)
#include <wchar.h>  // Biblioteca para manejar caracteres anchos
#include <locale.h> // Biblioteca para configurar la localización
#include <sstream>

#include "facturacionModulo.h" // Incluye el módulo de facturación, se asume que este archivo contiene funciones relacionadas a la facturación

using std::cout;
using std::string;

string version = "1.0.0"; // Define la versión del programa

// Declaración de funciones que serán definidas más adelante
void showMenuTitle();
void mostrarCreditos();

int main()
{
    // Establece la configuración regional a español
    setlocale(LC_ALL, "spanish");

    // Porque los floats no funcionan
    std::cout.precision(2);
    std::cout.setf(std::ios::fixed);

    // Crea los directorios necesarios si no existen
    _mkdir(APPDATA_PATH.c_str());
    _mkdir((APPDATA_PATH + "exports").c_str());
    _mkdir((APPDATA_PATH + "facturas").c_str());

    // Inicializa el inventario
    InventoryItems inventario[MAX_INVENTORY_LENGTH];
    int inventory_items = 0;

    // Carga el inventario desde un archivo o base de datos
    inventoryLoad(inventario, inventory_items);

    // Comando para abrir el explorador de archivos en la ruta especificada
    string OpenExplorer = "explorer " + APPDATA_PATH;

    // Bucle principal del programa
    while (true)
    {
        system("cls"); // Limpia la pantalla
        int input;
        sColor(GREEN);   // Cambia el color del texto a verde
        showMenuTitle(); // Muestra el título del menú
        resetColor();    // Restablece el color del texto
        cout << "Creado para: ";
        textColored("UAM - Nicaragua", CYAN); // Muestra el texto en color cian

        // Muestra las opciones del menú
        textColored("\n- Elija una opción -\n", CYAN);
        cout << "\n  1. ";
        textColored("Inventario", ORANGE);
        cout << "\n  2. ";
        textColored("Facturación", ORANGE);
        cout << "\n  3. ";
        textColored("Reporte de Transacciones", ORANGE);
        cout << "\n  4. ";
        textColored("Abrir Carpeta de Datos", ORANGE);
        cout << "\n  5. ";
        textColored("Mostrar Creditos", ORANGE);
        cout << "\n  6. ";
        textColored("<- Salir del Programa", RED);
        cout << "\n\n#: ";

        fetchInput(input); // Lee la opción del usuario

        // Ejecuta la acción correspondiente según la opción seleccionada
        switch (input)
        {
        case (1):
            mainInventory(inventario, inventory_items); // Gestiona el inventario
            break;
        case (2):
            facturarMain(inventario, inventory_items); // Gestiona la facturación
            break;
        case (3):
            mostrarLogs();   // Muestra los logs de transacciones
            system("pause"); // Pausa para que el usuario pueda ver los logs
            break;
        case (4):
            system(OpenExplorer.c_str()); // Abre la carpeta de datos en el explorador de archivos
            break;
        case (5):
            mostrarCreditos(); // Muestra los créditos del programa
            break;
        case (6):
            return 0; // Sale del programa
            break;
        default:
            break; // No hace nada si la opción no es válida
        }
    }

    return 0; // Fin del programa
}

// Función que muestra el título del menú
void showMenuTitle()
{
    std::cout << " :::::::: ::::::::::: ::::::::   ::::::::  :::    ::: ::::::::  :::::::::: ::::    :::  ::::::::  :::::::::: \n";
    std::cout << ":+:    :+:    :+:    :+:    :+: :+:    :+: :+:   :+: :+:    :+: :+:        :+:+:   :+: :+:    :+: :+:        \n";
    std::cout << "+:+           +:+    +:+    +:+ +:+        +:+  +:+  +:+        +:+        :+:+:+  +:+ +:+        +:+        \n";
    std::cout << "+#++:++#++    +#+    +#+    +:+ +#+        +#++:++   +#++:++#++ +#++:++#   +#+ +:+ +#+ +#++:++#++ +#++:++#   \n";
    std::cout << "       +#+    +#+    +#+    +#+ +#+        +#+  +#+         +#+ +#+        +#+  +#+#+#        +#+ +#+        \n";
    std::cout << "#+#    #+#    #+#    #+#    #+# #+#    #+# #+#   #+# #+#    #+# #+#        #+#   #+#+# #+#    #+# #+#        \n";
    std::cout << " ########     ###     ########   ########  ###    ### ########  ########## ###    ####  ########  ########## \n";
}

// Función que muestra los créditos del programa
void mostrarCreditos()
{
    system("cls");   // Limpia la pantalla
    sColor(GREEN);   // Cambia el color del texto a verde
    showMenuTitle(); // Muestra el título del menú
    resetColor();    // Restablece el color del texto
    cout << "Creado para: ";
    textColored("UAM - Nicaragua", CYAN); // Muestra el texto en color cian

    // Muestra los créditos del grupo de trabajo
    textColored("\n\n================================================================================================\n", GRAY);
    textColored("\nGrupo de trabajo\n", GREEN);
    cout << "\n- Coordinador de Grupo y responsable del sistema de inventario: ";
    textColored("Emilio Fernando Meza Ortiz", CYAN);
    cout << "\n- Miembro de trabajo y responsable del sistema de facturación: ";
    textColored("Emmanuel Leonardo Aguilar Novoa", CYAN);
    cout << "\n- Miembro de trabajo y responsable del sistema de reporte de transacciones: ";
    textColored("Diego Armando Urbina Aviles", CYAN);
    cout << "\n- Miembro de trabajo y responsable del sistema de exportación de datos: ";
    textColored("Oscar Enrique Arnuero Ramos\n", CYAN);
    textColored("\n================================================================================================\n", GRAY);

    // Muestra el crédito al docente responsable
    cout << "\n- Docente responsable: ";
    textColored("Silvia Gigdalia Ticay López", GREEN);
    textColored("\n\nPara la facultad de Ingenieria y Arquitectura de la Universidad Americana (UAM) Nicaragua", YELLOW);
    textColored("\nVersion " + version + "\n", YELLOW);

    sColor(GRAY);    // Cambia el color del texto a gris
    system("pause"); // Pausa para que el usuario pueda leer los créditos
}