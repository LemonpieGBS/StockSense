#include <fstream>
#include <string>
#include <iostream>

#include "ficherosYcolores.h"
#include "time_functions.h"
#include "fetchInput.h"

using namespace std;

// Declaración de funciones
void showLogsTitle();
void registrarLog(const std::string &accion);
void mostrarLogs();

// Registra una acción en el archivo de logs con la fecha y hora actual
void registrarLog(const std::string &accion)
{
    ofstream archivo(APPDATA_PATH + "logs.txt", std::ios::app);
    if (archivo.is_open())
    {
        int year = get_current_year();
        int month = get_current_month();
        int day = get_current_day();
        int hour = get_current_hour();
        int minute = get_current_minute();
        int second = get_current_second();

        // Formatea la fecha y hora
        char buffer[80];
        std::sprintf(buffer, "%04d-%02d-%02d %02d:%02d:%02d", year, month, day, hour, minute, second);

        // Escribe la fecha, hora y la acción en el archivo de logs
        archivo << buffer << " - " << accion << std::endl;
        archivo.close();
    }
    else
    {
        textColored("#ERROR: No se pudo abrir el archivo de logs.", RED);
    }
}

// Muestra los logs en la consola
void mostrarLogs()
{
    system("cls");
    showLogsTitle();
    ifstream archivo(APPDATA_PATH + "logs.txt");
    if (archivo.is_open())
    {
        textColored("================================================================================================\n", GRAY);
        string linea;
        while (std::getline(archivo, linea))
        {
            textColored(linea + "\n", YELLOW);
        }
        textColored("================================================================================================\n", GRAY);
        archivo.close();
    }
    else
    {
        textColored("- No se pudo abrir el archivo de logs.", RED);
    }
}

// Muestra el título de los logs en la consola
void showLogsTitle()
{
    sColor(GREEN);
    std::cout << "  _____ ____      _    _   _ ____    _    ____ ____ ___ ___  _   _ _____ ____  \n";
    std::cout << " |_   _|  _ \\    / \\  | \\ | / ___|  / \\  / ___/ ___|_ _/ _ \\| \\ | | ____/ ___| \n";
    std::cout << "   | | | |_) |  / _ \\ |  \\| \\___ \\ / _ \\| |  | |    | | | | |  \\| |  _| \\___ \\ \n";
    std::cout << "   | | |  _ <  / ___ \\| |\\  |___) / ___ \\ |__| |___ | | |_| | |\\  | |___ ___) |\n";
    std::cout << "   |_| |_| \\_\\/_/   \\_\\_| \\_|____/_/   \\_\\____\\____|___\\___/|_| \\_|_____|____/ \n";
    std::cout << "\n";
    resetColor();
}

// stof porque se muere
float stringToFloat(std::string w) {
    std::locale::global(std::locale("C"));
    float returner = std::stof(w);
    setlocale(LC_ALL, "spanish");
    return returner;
}