#include <iostream>     // Biblioteca para operaciones de entrada y salida
#include <vector>       // Biblioteca para utilizar el contenedor vector
#include <string>       // Biblioteca para utilizar la clase string
#include <fstream>      // Biblioteca para manejar operaciones con archivos
#include <ctime>        // Biblioteca para manejar el tiempo

#include "inventoryFunctions.h"  // Incluye las funciones relacionadas al inventario

// Estructura que representa un producto
struct Producto
{
    std::string nombre;        // Nombre del producto
    float precio;              // Precio del producto
    int unidades_compradas;    // Cantidad de unidades compradas
    int id;                    // ID del producto
};

// Declaración de funciones
void showFacturacionTitle();
void mostrarMenu();

// Muestra el menú principal de facturación
void mostrarMenu()
{
    system("cls");  // Limpia la pantalla
    showFacturacionTitle();  // Muestra el título de facturación
    textColored("- Menú principal de Facturación -\n", GREEN);
    textColored("\n- Elija una opcion -\n\n", CYAN);

    // Opciones del menú
    std::cout << "1. ";
    textColored("Facturar\n", ORANGE);
    std::cout << "2. ";
    textColored("<- Salir de facturación\n\n", RED);
}

// Definición de la función de exportación a CSV
void exportarFacturaCSV(Producto productos_facturados[], int productos_cant, const std::string &factura_nombre, float total)
{
    std::string filename = factura_nombre + ".csv";  // Nombre del archivo CSV
    std::ofstream file(APPDATA_PATH + "facturas\\" + filename);  // Abre el archivo CSV para escribir

    // Escribe los encabezados del archivo CSV
    file << "Producto, Precio Unidad, Unidades Compradas, Subtotal\n";

    // Escribe los datos de cada producto facturado
    for (int i = 0; i < productos_cant; i++)
    {
        file << productos_facturados[i].nombre << ",";
        file << productos_facturados[i].precio << ",";
        file << productos_facturados[i].unidades_compradas << ",";
        file << productos_facturados[i].precio * productos_facturados[i].unidades_compradas << "\n";
    }

    // Escribe el total de la factura
    file << "Total,,," << total << "\n";

    file.close();  // Cierra el archivo
    std::cout << "¡Factura exportada a " << filename << " exitosamente!\n";  // Mensaje de éxito
}

// Función principal para el proceso de facturación
void facturar(InventoryItems arr[], int inv_cant)
{
    system("cls");  // Limpia la pantalla
    showFacturacionTitle();  // Muestra el título de facturación

    textColored("- Módulo de Facturación -\n", GREEN);

    std::string factura_nombre;
    textColored("\n#: Ingrese el nombre de la factura: ", CYAN);
    std::cin.ignore();
    std::getline(std::cin, factura_nombre);  // Lee el nombre de la factura

    if (inv_cant == 0)
    {
        textColored("\nNo hay productos para facturar.\n", RED);
        sleep(2);  // Pausa para que el usuario pueda ver el mensaje
        return;
    }

    float total = 0.0;  // Variable para almacenar el total de la factura

    textColored("\n#: Elija un producto para facturar: \n", CYAN);
    int i = 0;
    for (int i = 0; i < inv_cant; i++)
    {
        // Muestra cada producto disponible para facturar
        std::cout << "\n" << (i + 1) << ". ";
        textColored(arr[i].name, GREEN);
        std::cout << " - $";
        sColor(GREEN);
        printf("%.2f", arr[i].price);
        resetColor();
        std::cout << ", Restantes: ";
        textColored(std::to_string(arr[i].quantity_left) + "\n", GREEN);
    }

    bool facturar_loop = true;  // Variable de control para el bucle de facturación
    int objeto_opcion, productos_cant = 0;
    Producto *productos_facturados = new Producto[inv_cant];  // Array dinámico para almacenar los productos facturados

    do
    {
        std::string SN;

        textColored("\n#: Ingrese el numero del producto a facturar: ", CYAN);
        std::cin >> objeto_opcion;

        // Verifica si la opción es válida
        if (objeto_opcion > inv_cant || objeto_opcion < 0)
            textColored("¡Objeto invalido!\n", RED);
        else
        {
            int unidades_deseadas;

            // Solicita la cantidad de unidades deseadas del producto seleccionado
            textColored("\n#: ¿Cuantas unidades desea del producto \"", CYAN);
            textColored(arr[objeto_opcion - 1].name, PURPLE);
            textColored("\"?: ", CYAN);

            std::cin >> unidades_deseadas;

            // Verifica si hay suficientes unidades en inventario
            if (unidades_deseadas > arr[objeto_opcion - 1].quantity_left)
            {
                textColored("\n¡No hay suficientes unidades en inventario!\n", RED);
            }
            else
            {
                bool objeto_ya_facturado = false;
                // Verifica si el producto ya ha sido facturado
                for (i = 0; i < productos_cant; i++)
                {
                    if (productos_facturados[i].id == objeto_opcion - 1)
                    {
                        objeto_ya_facturado = true;
                        productos_facturados[i].unidades_compradas += unidades_deseadas;
                        arr[productos_facturados[i].id].quantity_left -= unidades_deseadas;
                        break;
                    }
                }

                // Si el producto no ha sido facturado, lo añade a la lista de productos facturados
                if (!objeto_ya_facturado)
                {
                    productos_facturados[productos_cant].nombre = arr[objeto_opcion - 1].name;
                    productos_facturados[productos_cant].precio = arr[objeto_opcion - 1].price;
                    productos_facturados[productos_cant].unidades_compradas = unidades_deseadas;
                    productos_facturados[productos_cant].id = objeto_opcion - 1;

                    arr[objeto_opcion - 1].quantity_left -= unidades_deseadas;
                    productos_cant++;
                }
            }
        }

        // Pregunta al usuario si desea agregar otro producto a la factura
        textColored("\n#: ¿Desea agregar otro producto? (S/N): ", CYAN);
        std::cin >> SN;

        if (SN == "N" || SN == "n")
            facturar_loop = false;

    } while (facturar_loop == true);

    if (productos_cant == 0)
        return;

    // Muestra el resumen de la factura
    textColored("\n================================================================================================\n\n", GRAY);
    std::cout << "NOMBRE DE FACTURA: " << factura_nombre << std::endl;
    textColored("\n================================================================================================\n\n", GRAY);
    for (int i = 0; i < productos_cant; i++)
    {
        std::cout << productos_facturados[i].nombre << " - $" << productos_facturados[i].precio;
        if (productos_facturados[i].unidades_compradas > 1)
        {
            std::cout << " - (x" << productos_facturados[i].unidades_compradas << ") - $" << (productos_facturados[i].precio * productos_facturados[i].unidades_compradas) << std::endl;
        }
        else
            std::cout << std::endl;
        total += (productos_facturados[i].precio * productos_facturados[i].unidades_compradas);
    }
    textColored("\n================================================================================================\n\n", GRAY);
    std::cout << "Total a pagar: $" << total << std::endl << std::endl;
    system("pause");

    // Genera el nombre del archivo CSV con la fecha y un ID único
    std::string date_f = to_string(get_current_year()) + "_" + to_string(get_current_month()) + "_" + to_string(get_current_day());
    std::string NombreCSV = date_f + "_" + factura_nombre + "_" + GenerateID();

    // Exporta la factura a un archivo CSV
    exportarFacturaCSV(productos_facturados, productos_cant, NombreCSV, total);
    delete[] productos_facturados; // Libera la memoria asignada dinámicamente
}

// Función principal del módulo de facturación
void facturarMain(InventoryItems arr[], int inv_cant)
{
    int opcion;

    do
    {
        mostrarMenu();  // Muestra el menú de facturación
        std::cout << "#: ";
        std::cin >> opcion;

        // Ejecuta la acción correspondiente según la opción seleccionada
        switch (opcion)
        {
        case 1:
            facturar(arr, inv_cant);  // Llama a la función de facturación
            break;
        case 2:
            std::cout << "Saliendo del programa..." << std::endl;
            return;  // Sale del programa
        default:
            std::cout << "Opcion inválida. Intente nuevamente." << std::endl;
            break;
        }
    } while (opcion != 2);
}

// Función que muestra el título de facturación
void showFacturacionTitle()
{
    sColor(GREEN);  // Cambia el color del texto a verde
    std::cout << "  _____ _    ____ _____ _   _ ____      _    ____ ___ ___  _   _ \n";
    std::cout << " |  ___/ \\  / ___|_   _| | | |  _ \\    / \\  / ___|_ _/ _ \\| \\ | |\n";
    std::cout << " | |_ / _ \\| |     | | | | | | |_) |  / _ \\| |    | | | | |  \\| |\n";
    std::cout << " |  _/ ___ \\ |___  | | | |_| |  _ <  / ___ \\ |___ | | |_| | |\\  |\n";
    std::cout << " |_|/_/   \\_\\____| |_|  \\___/|_| \\_\\/_/   \\_\\____|___\\___/|_| \\_|\n";
    std::cout << "\n";
    resetColor();  // Restablece el color del texto
}
