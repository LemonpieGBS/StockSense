#include <iostream>

int main() {

    while(true) {

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
            case(1): break;
            case(2): break;
            case(3): break;
            case(4): break;
            case(5): return 0; break;
        }
    }
}