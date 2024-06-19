#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#define sleep(x) std::this_thread::sleep_for(std::chrono::seconds(x))
#define MAX_INVENTORY_LENGTH 100

struct InventoryItems {

    std::string id;
    std::string name;
    std::string provider;
    int quantity_left;
    float price;

};

std::string GenerateID();
void addToInventory(InventoryItems inventario[], int &inventory_size);
void removeFromInventory(InventoryItems inventario[], int &inventory_size);
void editOnInventory(InventoryItems inventario[], int inventory_size);
void showInventory(InventoryItems inventario[], int inventory_size);

int main() {

    int inventory_items = 0;
    InventoryItems inventario[MAX_INVENTORY_LENGTH];

    while(true) {

        system("cls");

        int input;
        std::cout<<"Menu de Inventario";
        std::cout<<"\nEliga lo que quiera hacer:\n";

        std::cout<<"\n 1.Añadir objeto a inventario";
        std::cout<<"\n 2.Remover objeto de inventario";
        std::cout<<"\n 3.Editar objeto de inventario";
        std::cout<<"\n 4.Mostrar inventario";
        std::cout<<"\n 5.<- Salir";
        std::cout<<"\n\n#:";

        std::cin>>input;

        switch(input) {
            case(1): addToInventory(inventario,inventory_items); break;
            case(2): removeFromInventory(inventario,inventory_items); break;
            case(3): editOnInventory(inventario,inventory_items); break;
            case(4): showInventory(inventario,inventory_items); system("pause"); break;
            case(5): return 0; break;
        }
    }
}

std::string GenerateID() {
    char allowed_characters[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G'
    ,'H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','Y','X','Z'};

    int charset_size = sizeof(allowed_characters) / sizeof(allowed_characters[0]);

    std::string ID;
    int ID_SIZE = 8;

    for(int i = 0; i < ID_SIZE; i++) {
        ID += allowed_characters[rand() % charset_size];
    }

    return ID;
}

void addToInventory(InventoryItems inventario[], int &inventory_size) {

    system("cls");
    InventoryItems new_item;

    std::cin.ignore();
    
    std::cout<<"Menu de adición al inventario";
    std::cout<<"\n\nInserte el nombre del producto: ";
    getline(std::cin,new_item.name);

    std::cout<<"\nInserte el proveedor del producto: ";
    getline(std::cin,new_item.provider);

    std::cout<<"\nInserte la cantidad de unidades: ";
    std::cin>>new_item.quantity_left;

    std::cout<<"\nInserte el precio del producto: ";
    std::cin>>new_item.price;

    new_item.id = GenerateID();

    inventario[inventory_size] = new_item;
    inventory_size++;

    std::cout<<"\nObjeto añadido con exito!";
    sleep(2);
}

void removeFromInventory(InventoryItems inventario[], int &inventory_size) {

    showInventory(inventario,inventory_size);
    if(inventory_size <= 0) { sleep(2); return; }

    std::string ID_input;
    std::cout<<"\nInserte el ID del producto a eliminar: ";
    std::cin>>ID_input;

    int itemFound = -1;
    for(int i = 0; i < inventory_size; i++) {
        if(ID_input == inventario[i].id) { itemFound = i; break; }
    }

    if(itemFound == -1) {
        std::cout<<"\nNo se pudo encontrar el producto, volviendo al menu...";
        sleep(2);
        return;
    }

    std::cout<<"\nObjeto encontrado: "<<inventario[itemFound].name;
    for(int i = itemFound; i < inventory_size - 1; i++) {
        inventario[i] = inventario[i+1];
    }

    inventory_size++;
    std::cout<<"\nObjeto eliminado con éxito!";
}

void editOnInventory(InventoryItems inventario[], int inventory_size) {

    showInventory(inventario, inventory_size);
    if(inventory_size <= 0) { sleep(2); return; }

    std::string ID_input;
    std::cout<<"\nInserte el ID del producto a eliminar: ";
    std::cin>>ID_input;

    int itemFound = -1;
    for(int i = 0; i < inventory_size; i++) {
        if(ID_input == inventario[i].id) { itemFound = i; break; }
    }

    if(itemFound == -1) {
        std::cout<<"\nNo se pudo encontrar el producto, volviendo al menu...";
        sleep(2);
        return;
    }

    int attribute_input;
    std::cout<<"\nObjeto encontrado: "<<inventario[itemFound].name;
    std::cout<<"\nQue atributo desea editar? (1. NOMBRE / 2. PROVEEDOR / 3. UNIDADES / 4. PRECIO)";
    std::cin>>attribute_input;

    switch(attribute_input) {
        case(1):
        std::cout<<"\nValor viejo: "<<inventario[itemFound].name;
        std::cout<<"\n\nValor nuevo: ";
        std::cin>>inventario[itemFound].name;

        std::cout<<"\nObjeto editado exitosamente!";
        break;

        case(2):
        std::cout<<"\nValor viejo: "<<inventario[itemFound].provider;
        std::cout<<"\n\nValor nuevo: ";
        std::cin>>inventario[itemFound].provider;

        std::cout<<"\nObjeto editado exitosamente!";
        break;

        case(3):
        std::cout<<"\nValor viejo: "<<inventario[itemFound].quantity_left;
        std::cout<<"\n\nValor nuevo: ";
        std::cin>>inventario[itemFound].quantity_left;

        std::cout<<"\nObjeto editado exitosamente!";
        break;

        case(4):
        std::cout<<"\nValor viejo: "<<inventario[itemFound].price;
        std::cout<<"\n\nValor nuevo: ";
        std::cin>>inventario[itemFound].price;

        std::cout<<"\nObjeto editado exitosamente!";
        break;

        default:
        std::cout<<"ATRIBUTO INVALIDO! Volviendo al menú...";
        break;
    }
    sleep(2);
}

void showInventory(InventoryItems inventario[], int inventory_size) {

    system("cls");

    if(inventory_size == 0) { std::cout<<"No hay objetos en el inventario!"; return; }

    for(int i = 0; i < inventory_size; i++) {
        std::cout<<"- ID: "<<inventario[i].id<<", Nombre: "<<inventario[i].name;
        std::cout<<"\n  Proveedor: "<<inventario[i].provider<<", Unidades: "<<inventario[i].quantity_left;
        std::cout<<"\n  Precio: "<<inventario[i].price<<"\n";
    }

}