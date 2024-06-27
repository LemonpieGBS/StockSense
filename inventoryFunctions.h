#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <fstream>

#include "logsF.h"  // AsegÃºrate de que este archivo estÃ¡ correctamente ubicado y contiene las definiciones necesarias

#define sleep(x) std::this_thread::sleep_for(std::chrono::seconds(x))
#define MAX_INVENTORY_LENGTH 100

using std::to_string;

struct InventoryItems {
    std::string id;
    std::string name;
    std::string provider;
    int quantity_left;
    float price;
};

std::string GenerateID();
bool inventoryLoad(InventoryItems inventario[], int &inventory_size);
void inventorySave(InventoryItems inventario[], int &inventory_size);
void addToInventory(InventoryItems inventario[], int &inventory_size);
void removeFromInventory(InventoryItems inventario[], int &inventory_size);
void editOnInventory(InventoryItems inventario[], int inventory_size);
void showInventory(InventoryItems inventario[], int inventory_size);
void exportToCSV(InventoryItems inventario[], int inventory_size, const std::string& filename);
void showInventoryTitle();
std::string generateCSVName();

void mainInventory(InventoryItems inventario[], int &inventory_items) {

    while(true) {
        system("cls");
        showInventoryTitle();

        int input;
        textColored("- Menú principal de Inventario -\n",GREEN);
        textColored("\n- Elija una opción -\n", CYAN);

        cout<<"\n  1. "; textColored("Añadir objeto a inventario",ORANGE);
        cout<<"\n  2. "; textColored("Remover objeto del inventario",ORANGE);
        cout<<"\n  3. "; textColored("Editar objeto del inventario",ORANGE);
        cout<<"\n  4. "; textColored("Mostrar inventario actual",ORANGE);
        cout<<"\n  5. "; textColored("Exportar inventario a CSV",ORANGE);
        cout<<"\n  6. "; textColored("<- Salir al menú principal",RED);
        std::cout << "\n\n#: ";

        

        std::cin >> input;

        switch(input) {
            case 1: addToInventory(inventario, inventory_items); break;
            case 2: removeFromInventory(inventario, inventory_items); break;
            case 3: editOnInventory(inventario, inventory_items); break;
            case 4: system("cls"); showInventoryTitle(); showInventory(inventario, inventory_items); system("pause"); break;
            case 5: exportToCSV(inventario, inventory_items, generateCSVName()); break;
            case 6: return; break;
            default: std::cout << "¡Opción invalida!"; sleep(2); break;
        }
    }
}

std::string generateCSVName() {

    std::string date_f = to_string(get_current_year()) + "_" + to_string(get_current_month()) + "_" + to_string(get_current_day());
    std::string csv_filename = "INVENTARIO_ESTADO - " + date_f + "_";
    bool valid_file = false;
    int i = 1;

    do {
        std::ifstream check_file (APPDATA_PATH + "exports\\" + csv_filename + to_string(i) + ".csv");

        if(!check_file.is_open()) { valid_file = true; csv_filename += to_string(i); }
        else { i++; check_file.close(); }

    } while(!valid_file);

    return csv_filename + ".csv";
}

std::string GenerateID() {

    srand(time(0));

    char allowed_characters[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','Y','X','Z'};
    int charset_size = sizeof(allowed_characters) / sizeof(char);
    std::string ID;
    int ID_SIZE = 8;

    for(int i = 0; i < ID_SIZE; i++) {
        ID += allowed_characters[rand() % charset_size];
    }
    return ID;
}

void exportToCSV(InventoryItems inventario[], int inventory_size, const std::string& filename) {
    std::ofstream file;
    file.open(APPDATA_PATH + "exports\\" + filename);

    // Escribe la cabecera del CSV
    file << "ID,Nombre,Proveedor,Unidades,Precio\n";

    // Escribe los datos de cada item del inventario
    for (int i = 0; i < inventory_size; i++) {
        file << inventario[i].id << ",";
        file << inventario[i].name << ",";
        file << inventario[i].provider << ",";
        file << inventario[i].quantity_left << ",";
        file << inventario[i].price << "\n";
    }

    file.close();

    textColored("\n¡Datos exportados a ",CYAN);
    textColored(filename,GREEN);
    textColored(" exitosamente!\n",CYAN);

    sleep(2);
}


void addToInventory(InventoryItems inventario[], int &inventory_size) {

    system("cls");
    showInventoryTitle();
    InventoryItems new_item;

    std::cin.ignore();
    
    textColored("- Menú de adición al inventario -",GREEN);
    textColored("\n\n# - Inserte el nombre del producto: ",CYAN);
    getline(std::cin,new_item.name);

    textColored("\n# - Inserte el proveedor del producto: ",CYAN);
    getline(std::cin,new_item.provider);

    textColored("\n# - Inserte la cantidad de unidades: ",CYAN);
    std::cin>>new_item.quantity_left;

    textColored("\n# - Inserte el precio del producto: ", CYAN);
    std::cin>>new_item.price;

    new_item.id = GenerateID();

    inventario[inventory_size] = new_item;
    inventory_size++;

    textColored("\n¡Objeto agregado con éxito!", GREEN);

    inventorySave(inventario,inventory_size);
    registrarLog("Producto '" + new_item.name + "' agregado al inventario");
    sleep(2);
}

void removeFromInventory(InventoryItems inventario[], int &inventory_size) {

    system("cls");
    showInventoryTitle();
    textColored("- Menú de eliminación de inventario -\n",RED);

    showInventory(inventario,inventory_size);
    if(inventory_size <= 0) { sleep(2); return; }

    std::string ID_input;
    textColored("\n# - Inserte el ID del producto a eliminar: ",CYAN);
    std::cin>>ID_input;

    int itemFound = -1;
    for(int i = 0; i < inventory_size; i++) {
        if(ID_input == inventario[i].id) { itemFound = i; break; }
    }

    if(itemFound == -1) {
        textColored("\nNo se pudo encontrar el producto, volviendo al menú...",RED);
        sleep(2);
        return;
    }

    registrarLog("Producto '" + inventario[itemFound].name + "' fue borrado del inventario");

    textColored("\nObjeto encontrado: " + inventario[itemFound].name,YELLOW);
    for(int i = itemFound; i < inventory_size - 1; i++) {
        inventario[i] = inventario[i+1];
    }

    inventory_size--;
    inventorySave(inventario,inventory_size);
    textColored("\nObjeto eliminado con éxito!",GREEN);
    sleep(2);
}

void editOnInventory(InventoryItems inventario[], int inventory_size) {

    system("cls");
    showInventoryTitle();
    textColored("- Menú de edición de inventario -\n",RED);

    showInventory(inventario, inventory_size);
    if(inventory_size <= 0) { sleep(2); return; }

    std::string ID_input;
    textColored("\n# - Inserte el ID del producto a editar: ",CYAN);
    std::cin>>ID_input;

    int itemFound = -1;
    for(int i = 0; i < inventory_size; i++) {
        if(ID_input == inventario[i].id) { itemFound = i; break; }
    }

    if(itemFound == -1) {
        textColored("\nNo se pudo encontrar el producto, volviendo al menú...",RED);
        sleep(2);
        return;
    }

    int attribute_input;
    textColored("\nObjeto encontrado: " + inventario[itemFound].name,YELLOW);
    textColored("\n¿Que atributo desea editar? (1. NOMBRE / 2. PROVEEDOR / 3. UNIDADES / 4. PRECIO)",CYAN);
    std::cout<<"\n#: ";
    std::cin>>attribute_input;
    std::string old_att;

    switch(attribute_input) {
        case(1):
        textColored("\nValor viejo: ",GREEN);
        std::cout<<inventario[itemFound].name;
        old_att = inventario[itemFound].name;

        textColored("\n\nValor nuevo: ",GREEN);
        std::cin>>inventario[itemFound].name;

        registrarLog("El nombre del producto '" + inventario[itemFound].name + "' fue cambiado de: '" + old_att + "' a '" + inventario[itemFound].name + "'");

        textColored("\n¡Objeto editado exitosamente!",GREEN);
        break;

        case(2):
        textColored("\nValor viejo: ",GREEN);
        std::cout<<inventario[itemFound].provider;
        old_att = inventario[itemFound].provider;

        textColored("\n\nValor nuevo: ",GREEN);
        std::cin>>inventario[itemFound].provider;

        registrarLog("El proveedor del producto '" + inventario[itemFound].name + "' fue cambiado de: '" + old_att + "' a '" + inventario[itemFound].provider + "'");

        textColored("\n¡Objeto editado exitosamente!",GREEN);
        break;

        case(3):
        textColored("\nValor viejo: ",GREEN);
        std::cout<<inventario[itemFound].quantity_left;
        old_att = inventario[itemFound].quantity_left;

        textColored("\n\nValor nuevo: ",GREEN);
        std::cin>>inventario[itemFound].quantity_left;

        registrarLog("La cantidad de unidades del producto '" + inventario[itemFound].name + "' fueron cambiadas de: '" + old_att + "' a '" + std::to_string(inventario[itemFound].quantity_left) + "'");

        textColored("\n¡Objeto editado exitosamente!",GREEN);
        break;

        case(4):
        textColored("\nValor viejo: ",GREEN);
        std::cout<<inventario[itemFound].price;
        old_att = inventario[itemFound].price;

        textColored("\n\nValor nuevo: ",GREEN);
        std::cin>>inventario[itemFound].price;

        registrarLog("El precio del producto '" + inventario[itemFound].name + "' fue cambiado de: '" + old_att + "' a '" + std::to_string(inventario[itemFound].price) + "'");

        textColored("\n¡Objeto editado exitosamente!",GREEN);
        break;

        default:
        textColored("ATRIBUTO INVALIDO! Volviendo al menú...",RED);
        break;
    }

    inventorySave(inventario,inventory_size);
    sleep(2);
}

void showInventory(InventoryItems inventario[], int inventory_size) {

    textColored("- Inventario Actual -\n\n",GREEN);

    if(inventory_size == 0) { std::cout<<"¡No hay objetos en el inventario!"; return; }

    for(int i = 0; i < inventory_size; i++) {

        textColored("\n- ID: ", GREEN); std::cout<<inventario[i].id<<", ";
        textColored("Nombre: ",GREEN); std::cout<<inventario[i].name;

        textColored("\n  Proveedor: ",GREEN); std::cout<<inventario[i].provider<<", ";
        textColored("Unidades: ",GREEN); std::cout<<inventario[i].quantity_left;
        
        textColored("\n  Precio: ",GREEN); std::cout<<inventario[i].price<<"\n\n";
        textColored("================================================================================================\n",GRAY);
    }

}

void showInventoryTitle() {
    sColor(GREEN);
    std::cout<<"  ___ _   ___     _______ _   _ _____  _    ____  ___ ___  \n";
    std::cout<<" |_ _| \\ | \\ \\   / / ____| \\ | |_   _|/ \\  |  _ \\|_ _/ _ \\ \n";
    std::cout<<"  | ||  \\| |\\ \\ / /|  _| |  \\| | | | / _ \\ | |_) || | | | |\n";
    std::cout<<"  | || |\\  | \\ V / | |___| |\\  | | |/ ___ \\|  _ < | | |_| |\n";
    std::cout<<" |___|_| \\_|  \\_/  |_____|_| \\_| |_/_/   \\_\\_| \\_\\___\\___/ \n";
    std::cout<<"\n";
    resetColor();
}

bool inventoryLoad(InventoryItems inventario[], int &inventory_size) {

    std::ifstream FILE (APPDATA_PATH + "inventario.dat");
    if(FILE.is_open()) {
        std::string curr_line;

        while(std::getline(FILE,curr_line)) {

            int wrd_cnt = 0;
            std::string current_word = "";

            for(char ch : curr_line) {

                if(ch != ';') current_word += ch;
                else {
                    wrd_cnt++;
                    switch(wrd_cnt) {
                        case 1: inventario[inventory_size].id = current_word; break;
                        case 2: inventario[inventory_size].name = current_word; break;
                        case 3: inventario[inventory_size].provider = current_word; break;
                        case 4: inventario[inventory_size].quantity_left = std::stoi(current_word); break;
                        case 5: inventario[inventory_size].price = std::stof(current_word); break;
                        default: break;
                    }
                    current_word = "";
                }
            }

            inventory_size++;

        }
        return true;
    } else {
        return false;
    }
}

void inventorySave(InventoryItems inventario[], int &inventory_size)  {

    std::ofstream FILE (APPDATA_PATH + "inventario.dat");
    for(int i = 0; i < inventory_size; i++) {
        FILE << inventario[i].id << ";";
        FILE << inventario[i].name << ";";
        FILE << inventario[i].provider << ";";
        FILE << inventario[i].quantity_left << ";";
        FILE << inventario[i].price << ";\n";
    }
    FILE.close();
}