#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <fstream>

#include "logsF.h" // Aseg�rate de que este archivo est� correctamente ubicado y contiene las definiciones necesarias

// Macros para facilitar el uso de sleep y definir el tama�o m�ximo del inventario
#define sleep(x) std::this_thread::sleep_for(std::chrono::seconds(x))
#define MAX_INVENTORY_LENGTH 100

using std::to_string;

// Estructura para representar los elementos del inventario
struct InventoryItems
{
    std::string id;
    std::string name;
    std::string provider;
    int quantity_left;
    float price;
};

// Declaraciones de funciones
std::string GenerateID();
bool inventoryLoad(InventoryItems inventario[], int &inventory_size);
void inventorySave(InventoryItems inventario[], int &inventory_size);
void addToInventory(InventoryItems inventario[], int &inventory_size);
void removeFromInventory(InventoryItems inventario[], int &inventory_size);
void editOnInventory(InventoryItems inventario[], int inventory_size);
void showInventory(InventoryItems inventario[], int inventory_size);
void exportToCSV(InventoryItems inventario[], int inventory_size, const std::string &filename);
void showInventoryTitle();
std::string generateCSVName();

// Funci�n principal del inventario que muestra el men� principal y gestiona las opciones del usuario
void mainInventory(InventoryItems inventario[], int &inventory_items)
{
    while (true)
    {
        system("cls");
        showInventoryTitle();

        int input;
        textColored("- Men� principal de Inventario -\n", GREEN);
        textColored("\n- Elija una opci�n -\n", CYAN);

        // Opciones del men� principal
        std::cout << "\n  1. ";
        textColored("A�adir objeto a inventario", ORANGE);
        std::cout << "\n  2. ";
        textColored("Remover objeto del inventario", ORANGE);
        std::cout << "\n  3. ";
        textColored("Editar objeto del inventario", ORANGE);
        std::cout << "\n  4. ";
        textColored("Mostrar inventario actual", ORANGE);
        std::cout << "\n  5. ";
        textColored("Exportar inventario a CSV", ORANGE);
        std::cout << "\n  6. ";
        textColored("<- Salir al men� principal", RED);
        std::cout << "\n\n#: ";

        fetchInput(input);

        // Manejo de las opciones del men�
        switch (input)
        {
        case 1:
            addToInventory(inventario, inventory_items);
            break;
        case 2:
            removeFromInventory(inventario, inventory_items);
            break;
        case 3:
            editOnInventory(inventario, inventory_items);
            break;
        case 4:
            system("cls");
            showInventoryTitle();
            showInventory(inventario, inventory_items);
            system("pause");
            break;
        case 5:
            exportToCSV(inventario, inventory_items, generateCSVName());
            break;
        case 6:
            return;
        default:
            std::cout << "�Opci�n invalida!";
            sleep(2);
            break;
        }
    }
}

// Genera un nombre �nico para el archivo CSV basado en la fecha actual
std::string generateCSVName()
{
    std::string date_f = to_string(get_current_year()) + "_" + to_string(get_current_month()) + "_" + to_string(get_current_day());
    std::string csv_filename = "INVENTARIO_ESTADO - " + date_f + "_";
    bool valid_file = false;
    int i = 1;

    do
    {
        std::ifstream check_file(APPDATA_PATH + "exports\\" + csv_filename + to_string(i) + ".csv");
        if (!check_file.is_open())
        {
            valid_file = true;
            csv_filename += to_string(i);
        }
        else
        {
            i++;
            check_file.close();
        }
    } while (!valid_file);

    return csv_filename + ".csv";
}

// Genera un ID �nico para un producto
std::string GenerateID()
{
    srand(time(0));
    char allowed_characters[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'Y', 'X', 'Z'};
    int charset_size = sizeof(allowed_characters) / sizeof(char);
    std::string ID;
    int ID_SIZE = 8;

    for (int i = 0; i < ID_SIZE; i++)
    {
        ID += allowed_characters[rand() % charset_size];
    }
    return ID;
}

// Exporta los datos del inventario a un archivo CSV
void exportToCSV(InventoryItems inventario[], int inventory_size, const std::string &filename)
{
    std::ofstream file;
    file.open(APPDATA_PATH + "exports\\" + filename);

    // Escribe la cabecera del CSV
    file << "ID,Nombre,Proveedor,Unidades,Precio\n";

    // Escribe los datos de cada item del inventario
    for (int i = 0; i < inventory_size; i++)
    {
        file << (i+1) << ",";
        file << inventario[i].name << ",";
        file << inventario[i].provider << ",";
        file << inventario[i].quantity_left << ",";
        file << inventario[i].price << "\n";
    }

    file.close();

    textColored("\n�Datos exportados a ", CYAN);
    textColored(filename, GREEN);
    textColored(" exitosamente!\n", CYAN);

    sleep(2);
}

// A�ade un nuevo item al inventario
void addToInventory(InventoryItems inventario[], int &inventory_size)
{
    system("cls");
    showInventoryTitle();
    InventoryItems new_item;

    textColored("- Men� de adici�n al inventario -", GREEN);
    textColored("\n\n# - Inserte el nombre del producto: ", CYAN);
    fetchInput(new_item.name);

    textColored("\n# - Inserte el proveedor del producto: ", CYAN);
    fetchInput(new_item.provider);

    textColored("\n# - Inserte la cantidad de unidades: ", CYAN);
    fetchInput(new_item.quantity_left);

    while(new_item.quantity_left < 0) {
        textColored("\n# - Inserte una cantidad valida: ", RED);
        fetchInput(new_item.quantity_left);
    }

    textColored("\n# - Inserte el precio del producto: ", CYAN);
    fetchInput(new_item.price);

    while(new_item.price <= 0) {
        textColored("\n# - Inserte una cantidad valida: ", RED);
        fetchInput(new_item.price);
    }

    new_item.id = GenerateID();

    inventario[inventory_size] = new_item;
    inventory_size++;

    textColored("\n�Objeto agregado con �xito!", GREEN);

    inventorySave(inventario, inventory_size);
    registrarLog("Producto '" + new_item.name + "' agregado al inventario");
    sleep(2);
}

// Remueve un item del inventario basado en su ID
void removeFromInventory(InventoryItems inventario[], int &inventory_size)
{
    system("cls");
    showInventoryTitle();
    textColored("- Men� de eliminaci�n de inventario -\n", RED);

    showInventory(inventario, inventory_size);
    if (inventory_size <= 0)
    {
        sleep(2);
        return;
    }

    int ID_input;
    textColored("\n# - Inserte el ID del producto a eliminar: ", CYAN);
    fetchInput(ID_input);

    int itemFound = ID_input - 1;
    if (itemFound < 0 || itemFound >= inventory_size)
    {
        textColored("\nEl ID que ingres� no es v�lido, volviendo al men�...", RED);
        sleep(2);
        return;
    }

    if (itemFound == -1)
    {
        textColored("\nNo se pudo encontrar el producto, volviendo al men�...", RED);
        sleep(2);
        return;
    }

    std::string SN;
    textColored("\n#- ESTA SEGURO DE BORRAR EL OBJETO DEL INVENTARIO? (S/N): ", RED);
    fetchInputSN(SN);

    if (SN == "N" || SN == "n") return;

    registrarLog("Producto '" + inventario[itemFound].name + "' fue borrado del inventario");

    textColored("\nObjeto encontrado: " + inventario[itemFound].name, YELLOW);
    for (int i = itemFound; i < inventory_size - 1; i++)
    {
        inventario[i] = inventario[i + 1];
    }

    inventory_size--;
    inventorySave(inventario, inventory_size);
    textColored("\nObjeto eliminado con �xito!", GREEN);
    sleep(2);
}

// Edita un item del inventario basado en su ID
void editOnInventory(InventoryItems inventario[], int inventory_size)
{
    system("cls");
    showInventoryTitle();
    textColored("- Men� de edici�n de inventario -\n", RED);

    showInventory(inventario, inventory_size);
    if (inventory_size <= 0)
    {
        sleep(2);
        return;
    }

    int ID_input;
    textColored("\n# - Inserte el ID del producto a editar: ", CYAN);
    fetchInput(ID_input);

    int itemFound = ID_input - 1;
    if (itemFound < 0 || itemFound >= inventory_size)
    {
        textColored("\nEl ID que ingres� no es v�lido, volviendo al men�...", RED);
        sleep(2);
        return;
    }

    int attribute_input;
    textColored("\nObjeto encontrado: " + inventario[itemFound].name, YELLOW);
    textColored("\n�Que atributo desea editar? (1. NOMBRE / 2. PROVEEDOR / 3. UNIDADES / 4. PRECIO)", CYAN);
    std::cout << "\n#: ";
    fetchInput(attribute_input);
    std::string old_att;

    // Edita el atributo seleccionado del item encontrado
    switch (attribute_input)
    {
    case (1):
        textColored("\nValor viejo: ", GREEN);
        std::cout << inventario[itemFound].name;
        old_att = inventario[itemFound].name;

        textColored("\n\nValor nuevo: ", GREEN);
        fetchInput(inventario[itemFound].name);

        registrarLog("El nombre del producto '" + inventario[itemFound].name + "' fue cambiado de: '" + old_att + "' a '" + inventario[itemFound].name + "'");

        textColored("\n�Objeto editado exitosamente!", GREEN);
        break;

    case (2):
        textColored("\nValor viejo: ", GREEN);
        std::cout << inventario[itemFound].provider;
        old_att = inventario[itemFound].provider;

        textColored("\n\nValor nuevo: ", GREEN);
        fetchInput(inventario[itemFound].provider);

        registrarLog("El proveedor del producto '" + inventario[itemFound].provider + "' fue cambiado de: '" + old_att + "' a '" + inventario[itemFound].provider + "'");

        textColored("\n�Objeto editado exitosamente!", GREEN);
        break;

    case (3):
        textColored("\nValor viejo: ", GREEN);
        std::cout << inventario[itemFound].quantity_left;
        old_att = inventario[itemFound].quantity_left;

        textColored("\n\nValor nuevo: ", GREEN);
        fetchInput(inventario[itemFound].quantity_left);

        while(inventario[itemFound].quantity_left < 0) {
            textColored("\n# - Inserte una cantidad valida: ", RED);
            fetchInput(inventario[itemFound].quantity_left);
        }

        registrarLog("La cantidad de unidades del producto '" + std::to_string(inventario[itemFound].quantity_left) + "' fueron cambiadas de: '" + old_att + "' a '" + std::to_string(inventario[itemFound].quantity_left) + "'");

        textColored("\n�Objeto editado exitosamente!", GREEN);
        break;

    case (4):
        textColored("\nValor viejo: ", GREEN);
        std::cout << inventario[itemFound].price;
        old_att = inventario[itemFound].price;

        textColored("\n\nValor nuevo: ", GREEN);
        fetchInput(inventario[itemFound].price);

        while(inventario[itemFound].price <= 0) {
            textColored("\n# - Inserte una cantidad valida: ", RED);
            fetchInput(inventario[itemFound].price);
        }

        registrarLog("El precio del producto '" + std::to_string(inventario[itemFound].price) + "' fue cambiado de: '" + old_att + "' a '" + std::to_string(inventario[itemFound].price) + "'");

        textColored("\n�Objeto editado exitosamente!", GREEN);
        break;

    default:
        textColored("ATRIBUTO INVALIDO! Volviendo al men�...", RED);
        break;
    }

    inventorySave(inventario, inventory_size);
    sleep(2);
}

// Muestra el inventario actual
void showInventory(InventoryItems inventario[], int inventory_size)
{
    textColored("- Inventario Actual -\n\n", GREEN);

    if (inventory_size == 0)
    {
        std::cout << "�No hay objetos en el inventario!";
        return;
    }

    // Recorre e imprime cada item del inventario
    for (int i = 0; i < inventory_size; i++)
    {
        textColored("\n- #: ", GREEN);
        std::cout << (i+1) << ", ";
        textColored("Nombre: ", GREEN);
        std::cout << inventario[i].name;

        textColored("\n  Proveedor: ", GREEN);
        std::cout << inventario[i].provider << ", ";
        textColored("Unidades: ", GREEN);
        std::cout << inventario[i].quantity_left << ", ";
        textColored("Precio: ", GREEN);
        std::cout << inventario[i].price << "\n";
        textColored("================================================================================================\n", GRAY);
    }
}

// Muestra el t�tulo del inventario
void showInventoryTitle()
{
    sColor(GREEN);
    std::cout << "  ___ _   ___     _______ _   _ _____  _    ____  ___ ___  \n";
    std::cout << " |_ _| \\ | \\ \\   / / ____| \\ | |_   _|/ \\  |  _ \\|_ _/ _ \\ \n";
    std::cout << "  | ||  \\| |\\ \\ / /|  _| |  \\| | | | / _ \\ | |_) || | | | |\n";
    std::cout << "  | || |\\  | \\ V / | |___| |\\  | | |/ ___ \\|  _ < | | |_| |\n";
    std::cout << " |___|_| \\_|  \\_/  |_____|_| \\_| |_/_/   \\_\\_| \\_\\___\\___/ \n";
    std::cout << "\n";
    resetColor();
}

// Carga el inventario desde un archivo
bool inventoryLoad(InventoryItems inventario[], int &inventory_size)
{
    std::ifstream FILE(APPDATA_PATH + "inventario.dat");
    if (FILE.is_open())
    {
        std::string curr_line;

        while (std::getline(FILE, curr_line))
        {
            int wrd_cnt = 0;
            std::string current_word = "";

            for (char ch : curr_line)
            {
                if (ch != ';')
                    current_word += ch;
                else
                {
                    wrd_cnt++;
                    switch (wrd_cnt)
                    {
                    case 1:
                        inventario[inventory_size].id = current_word;
                        break;
                    case 2:
                        inventario[inventory_size].name = current_word;
                        break;
                    case 3:
                        inventario[inventory_size].provider = current_word;
                        break;
                    case 4:
                        inventario[inventory_size].quantity_left = std::stoi(current_word);
                        break;
                    case 5:
                        inventario[inventory_size].price = stringToFloat(current_word);
                        break;
                    default:
                        break;
                    }
                    current_word = "";
                }
            }
            inventory_size++;
        }
        return true;
    }
    else
    {
        return false;
    }
}

// Guarda el inventario en un archivo
void inventorySave(InventoryItems inventario[], int &inventory_size)
{
    std::ofstream FILE(APPDATA_PATH + "inventario.dat");
    for (int i = 0; i < inventory_size; i++)
    {
        FILE << inventario[i].id << ";";
        FILE << inventario[i].name << ";";
        FILE << inventario[i].provider << ";";
        FILE << inventario[i].quantity_left << ";";
        FILE << inventario[i].price << ";\n";
    }
    FILE.close();
}