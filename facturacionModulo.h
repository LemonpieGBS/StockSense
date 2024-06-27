#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>

#include "inventoryFunctions.h"

struct Producto
{
    std::string nombre;
    float precio;
    int unidades_compradas;
    int id;
};

void showFacturacionTitle();

void mostrarMenu()
{

    system("cls");
    showFacturacionTitle();
    textColored("- Men� principal de Facturaci�n -\n", GREEN);
    textColored("\n- Elija una opcion -\n\n", CYAN);

    std::cout << "1. ";
    textColored("Facturar\n", ORANGE);
    std::cout << "2. ";
    textColored("<- Salir de facturaci�n\n\n", RED);
}

// Definición de la función de exportación a CSV
void exportarFacturaCSV(Producto productos_facturados[], int productos_cant, const std::string &factura_nombre, float total)
{
    std::string filename = factura_nombre + ".csv";
    std::ofstream file(APPDATA_PATH + "facturas\\" + filename);

    // Encabezados del archivo CSV
    file << "Producto, Precio Unidad, Unidades Compradas, Subtotal\n";

    // Escribe los datos de cada producto facturado
    for (int i = 0; i < productos_cant; i++)
    {
        file << productos_facturados[i].nombre << ",";
        file << productos_facturados[i].precio << ",";
        file << productos_facturados[i].unidades_compradas << ",";
        file << productos_facturados[i].precio * productos_facturados[i].unidades_compradas << "\n";
    }

    // Escribe el total
    file << "Total,,," << total << "\n";

    file.close();
    std::cout << "�Factura exportada a " << filename << " exitosamente!\n";
}

void facturar(InventoryItems arr[], int inv_cant)
{
    system("cls");
    showFacturacionTitle();

    textColored("- M�dulo de Facturaci�n -\n", GREEN);

    std::string factura_nombre;
    textColored("\n#: Ingrese el nombre de la factura: ", CYAN);
    std::cin.ignore();
    std::getline(std::cin, factura_nombre);

    if (inv_cant == 0)
    {
        textColored("\nNo hay productos para facturar.\n", RED);
        sleep(2);
        return;
    }

    float total = 0.0;

    textColored("\n#: Elija un producto para facturar: \n", CYAN);
    int i = 0;
    for (int i = 0; i < inv_cant; i++)
    {
        std::cout << "\n"
                  << (i + 1) << ". ";
        textColored(arr[i].name, GREEN);
        std::cout << " - $";
        sColor(GREEN);
        printf("%.2f", arr[i].price);
        resetColor();
        std::cout << ", Restantes: ";
        textColored(std::to_string(arr[i].quantity_left) + "\n", GREEN);
    }

    bool facturar_loop = true;
    int objeto_opcion, productos_cant = 0;
    Producto *productos_facturados = new Producto[inv_cant];

    do
    {
        std::string SN;

        textColored("\n#: Ingrese el numero del producto a facturar: ", CYAN);
        std::cin >> objeto_opcion;

        if (objeto_opcion > inv_cant || objeto_opcion < 0)
            textColored("�Objeto invalido!\n", RED);
        else
        {
            int unidades_deseadas;

            textColored("\n#: �Cuantas unidades desea del producto \"", CYAN);
            textColored(arr[objeto_opcion - 1].name, PURPLE);
            textColored("\"?: ", CYAN);

            std::cin >> unidades_deseadas;

            if (unidades_deseadas > arr[objeto_opcion - 1].quantity_left)
            {
                textColored("\n�No hay suficientes unidades en inventario!\n", RED);
            }
            else
            {
                bool objeto_ya_facturado = false;
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

        textColored("\n#: �Desea agregar otro producto? (S/N): ", CYAN);
        std::cin >> SN;

        if (SN == "N" || SN == "n")
            facturar_loop = false;

    } while (facturar_loop == true);

    if (productos_cant == 0)
        return;

    textColored("================================================================================================\n\n", GRAY);
    std::cout << "NOMBRE DE FACTURA: " << factura_nombre << std::endl;
    textColored("================================================================================================\n\n", GRAY);
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
    textColored("================================================================================================\n\n", GRAY);
    std::cout << "Total a pagar: $" << total << std::endl
              << std::endl;
    system("pause");

    std::string date_f = to_string(get_current_year()) + "_" + to_string(get_current_month()) + "_" + to_string(get_current_day());
    std::string NombreCSV = date_f + "_" + factura_nombre + "_" + GenerateID();

    exportarFacturaCSV(productos_facturados, productos_cant, NombreCSV, total);
    delete[] productos_facturados; // Don't forget to free the dynamically allocated memory
}

void facturarMain(InventoryItems arr[], int inv_cant)
{
    int opcion;

    do
    {
        mostrarMenu();
        std::cout << "#: ";
        std::cin >> opcion;

        switch (opcion)
        {
        case 1:
            facturar(arr, inv_cant);
            break;
        case 2:
            std::cout << "Saliendo del programa..." << std::endl;
            return;
        default:
            std::cout << "Opcion inv�lida. Intente nuevamente." << std::endl;
            break;
        }
    } while (opcion != 2);
}

void showFacturacionTitle()
{
    sColor(GREEN);
    std::cout << "  _____ _    ____ _____ _   _ ____      _    ____ ___ ___  _   _ \n";
    std::cout << " |  ___/ \\  / ___|_   _| | | |  _ \\    / \\  / ___|_ _/ _ \\| \\ | |\n";
    std::cout << " | |_ / _ \\| |     | | | | | | |_) |  / _ \\| |    | | | | |  \\| |\n";
    std::cout << " |  _/ ___ \\ |___  | | | |_| |  _ <  / ___ \\ |___ | | |_| | |\\  |\n";
    std::cout << " |_|/_/   \\_\\____| |_|  \\___/|_| \\_\\/_/   \\_\\____|___\\___/|_| \\_|\n";
    std::cout << "\n";
    resetColor();
}