#include <conio.h>      // Librería para getch() y funciones de consola
#include <iostream>     // Entrada y salida estándar
#include <string>       // Manipulación de cadenas de texto

#define MAX_STRING_LENGTH 60    // Longitud máxima permitida para cadenas de texto
#define MAX_INTEGER_LENGTH 8    // Longitud máxima permitida para números enteros

// Función para capturar entrada de texto
void fetchInput(std::string &input) {

    char backspace = '\b';      // Carácter de retroceso
    char cReturn = '\r';        // Carácter de retorno de carro (Enter)
    char tab = '\t';            // Carácter de tabulación

    char ch = getch();          // Obtener el primer carácter ingresado
    std::string return_string;  // Cadena para almacenar la entrada

    // Loop para capturar entrada hasta presionar Enter
    while(ch != cReturn || return_string.length() <= 0) {

        // Procesar retroceso
        if(ch == backspace) {
            if(return_string.length() > 0) {
                return_string.resize(return_string.length() - 1);  // Eliminar último carácter
                std::cout << "\b \b";   // Borrar carácter en la consola
            }
        } else if(ch == cReturn || ch == 0 || ch == tab || ch == ';') {
            ch = getch();   // Leer el siguiente carácter
        } else {
            // Validar longitud máxima de entrada
            if(return_string.length() >= MAX_STRING_LENGTH) { ch=getch(); continue; }

            return_string += ch;    // Agregar carácter a la cadena de entrada
            std::cout << ch;        // Mostrar carácter en la consola
        }

        ch = getch();   // Leer el siguiente carácter
    }

    std::cout << "\n";  // Nueva línea después de la entrada
    input = return_string;  // Asignar el valor de entrada a la variable de referencia
}

// Función para capturar entrada de números enteros
void fetchInput(int &input) {

    char allowed_characters[] = {'-', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int char_amount = 11;

    char backspace = '\b';
    char cReturn = '\r';
    char tab = '\t';

    char ch = getch();
    std::string return_string;

    while(ch != cReturn || return_string.length() <= 0) {

        if(ch == backspace) {

            if(return_string.length() > 0) {
                return_string.resize(return_string.length() - 1);
                std::cout << "\b \b";   // Borrar carácter en la consola
            }
        }  else if(ch == cReturn || ch == 0 || ch == tab) {
            ch = getch();   // Leer el siguiente carácter
        } else {

            if(return_string.length() >= MAX_INTEGER_LENGTH) { ch=getch(); continue;}
            
            bool is_allowed = false;
            
            // Verificar si el carácter actual es permitido
            for(int i = 0; i < char_amount; i++) {
                if(ch == allowed_characters[i]) {
                    is_allowed = true;
                    break;
                }
            }

            if(ch == '-' && return_string.length() != 0) is_allowed = false;

            if(is_allowed) {
                return_string += ch;
                std::cout << ch;    // Mostrar carácter en la consola
            }
        }
        ch = getch();   // Leer el siguiente carácter
    }

    std::cout << "\n";  // Nueva línea después de la entrada
    input = std::stoi(return_string);
}

// Función para capturar entrada de números flotantes
void fetchInput(float &input) {

    char allowed_characters[] = {'-', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'};
    int char_amount = 12;

    char backspace = '\b';
    char cReturn = '\r';
    char tab = '\t';

    bool placed_dot = false;    // Bandera para controlar la posición del punto decimal

    char ch = getch();
    std::string return_string;

    while(ch != cReturn || return_string.length() <= 0) {

        if(ch == backspace) {

            if(return_string.length() > 0) {

                // Si se borra un punto, restablecer la bandera
                if(return_string[return_string.length() - 1] == '.') placed_dot = false;

                return_string.resize(return_string.length() - 1);
                std::cout << "\b \b";   // Borrar carácter en la consola
            }
        }  else if(ch == cReturn || ch == 0 || ch == tab) {
            ch = getch();   // Leer el siguiente carácter
        } else {

            if(return_string.length() >= MAX_INTEGER_LENGTH) { ch=getch(); continue;}
            
            bool is_allowed = false;
            
            // Verificar si el carácter actual es permitido
            for(int i = 0; i < char_amount; i++) {
                if(ch == allowed_characters[i]) {
                    is_allowed = true;
                    break;
                }
            }

            if(ch == '-' && return_string.length() != 0) is_allowed = false;
            if(ch == '.' && placed_dot) is_allowed = false;

            if(is_allowed) {
                if(ch == '.') placed_dot = true;   // Establecer la bandera si se ingresa un punto

                return_string += ch;
                std::cout << ch;    // Mostrar carácter en la consola
            }
        }
        ch = getch();   // Leer el siguiente carácter
    }

    std::cout << "\n";  // Nueva línea después de la entrada

    std::locale::global(std::locale("C"));
    input = std::stof(return_string); // Convertir cadena a flotante y asignar a la variable de referencia
    setlocale(LC_ALL, "spanish");
}

void fetchInputSN(std::string &input) {

    char allowed_characters[] = {'S', 's', 'N', 'n'};
    int char_amount = 11;

    char backspace = '\b';
    char cReturn = '\r';
    char tab = '\t';

    char ch = getch();
    std::string return_string;

    while(ch != cReturn || return_string.length() <= 0) {

        if(ch == backspace) {

            if(return_string.length() > 0) {
                return_string.resize(return_string.length() - 1);
                std::cout << "\b \b";   // Borrar carácter en la consola
            }
        }  else if(ch == cReturn || ch == 0 || ch == tab) {
            ch = getch();   // Leer el siguiente carácter
        } else {

            if(return_string.length() >= 1) { ch=getch(); continue;}
            
            bool is_allowed = false;
            
            // Verificar si el carácter actual es permitido
            for(int i = 0; i < char_amount; i++) {
                if(ch == allowed_characters[i]) {
                    is_allowed = true;
                    break;
                }
            }

            if(ch == '-' && return_string.length() != 0) is_allowed = false;

            if(is_allowed) {
                return_string += ch;
                std::cout << ch;    // Mostrar carácter en la consola
            }
        }
        ch = getch();   // Leer el siguiente carácter
    }

    std::cout << "\n";  // Nueva línea después de la entrada
    input = return_string;  // Convertir cadena a entero y asignar a la variable de referencia
}