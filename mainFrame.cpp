#include <iostream> // Biblioteca para operaciones de entrada y salida
#include <direct.h> // Biblioteca para operaciones de directorios (como crear directorios)
#include <wchar.h>  // Biblioteca para manejar caracteres anchos
#include <locale.h> // Biblioteca para configurar la localizaci�n
#include <sstream>

#include "facturacionModulo.h" // Incluye el m�dulo de facturaci�n, se asume que este archivo contiene funciones relacionadas a la facturaci�n

using std::cout;
using std::string;

string version = "1.0.0"; // Define la versi�n del programa

// Declaraci�n de funciones que ser�n definidas m�s adelante
void showMenuTitle();
void mostrarCreditos();

int main()
{
    // Establece la configuraci�n regional a espa�ol
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
        showMenuTitle(); // Muestra el t�tulo del men�
        resetColor();    // Restablece el color del texto
        cout << "Creado para: ";
        textColored("UAM - Nicaragua", CYAN); // Muestra el texto en color cian

        // Muestra las opciones del men�
        textColored("\n- Elija una opci�n -\n", CYAN);
        cout << "\n  1. ";
        textColored("Inventario", ORANGE);
        cout << "\n  2. ";
        textColored("Facturaci�n", ORANGE);
        cout << "\n  3. ";
        textColored("Reporte de Transacciones", ORANGE);
        cout << "\n  4. ";
        textColored("Abrir Carpeta de Datos", ORANGE);
        cout << "\n  5. ";
        textColored("Mostrar Creditos", ORANGE);
        cout << "\n  6. ";
        textColored("<- Salir del Programa", RED);
        cout << "\n\n#: ";

        fetchInput(input); // Lee la opci�n del usuario

        // Ejecuta la acci�n correspondiente seg�n la opci�n seleccionada
        switch (input)
        {
        case (1):
            mainInventory(inventario, inventory_items); // Gestiona el inventario
            break;
        case (2):
            facturarMain(inventario, inventory_items); // Gestiona la facturaci�n
            break;
        case (3):
            mostrarLogs();   // Muestra los logs de transacciones
            system("pause"); // Pausa para que el usuario pueda ver los logs
            break;
        case (4):
            system(OpenExplorer.c_str()); // Abre la carpeta de datos en el explorador de archivos
            break;
        case (5):
            mostrarCreditos(); // Muestra los cr�ditos del programa
            break;
        case (6):
            return 0; // Sale del programa
            break;
        default:
            break; // No hace nada si la opci�n no es v�lida
        }
    }

    return 0; // Fin del programa
}

// Funci�n que muestra el t�tulo del men�
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

// Funci�n que muestra los cr�ditos del programa
void mostrarCreditos()
{
    system("cls");   // Limpia la pantalla
    sColor(GREEN);   // Cambia el color del texto a verde
    showMenuTitle(); // Muestra el t�tulo del men�
    resetColor();    // Restablece el color del texto
    cout << "Creado para: ";
    textColored("UAM - Nicaragua", CYAN); // Muestra el texto en color cian

    // Muestra los cr�ditos del grupo de trabajo
    textColored("\n\n================================================================================================\n", GRAY);
    textColored("\nGrupo de trabajo\n", GREEN);
    cout << "\n- Coordinador de Grupo y responsable del sistema de inventario: ";
    textColored("Emilio Fernando Meza Ortiz", CYAN);
    cout << "\n- Miembro de trabajo y responsable del sistema de facturaci�n: ";
    textColored("Emmanuel Leonardo Aguilar Novoa", CYAN);
    cout << "\n- Miembro de trabajo y responsable del sistema de reporte de transacciones: ";
    textColored("Diego Armando Urbina Aviles", CYAN);
    cout << "\n- Miembro de trabajo y responsable del sistema de exportaci�n de datos: ";
    textColored("Oscar Enrique Arnuero Ramos\n", CYAN);
    textColored("\n================================================================================================\n", GRAY);

    // Muestra el cr�dito al docente responsable
    cout << "\n- Docente responsable: ";
    textColored("Silvia Gigdalia Ticay L�pez", GREEN);
    textColored("\n\nPara la facultad de Ingenieria y Arquitectura de la Universidad Americana (UAM) Nicaragua", YELLOW);
    textColored("\nVersion " + version + "\n", YELLOW);

    sColor(GRAY);    // Cambia el color del texto a gris
    system("pause"); // Pausa para que el usuario pueda leer los cr�ditos
}