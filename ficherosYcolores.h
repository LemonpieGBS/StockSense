#include <windows.h>
#include <iostream>
#include <string>

std::string APPDATA_PATH = std::string(getenv("appdata")) + "\\StockSense-II\\";

/*
enum COLORS {BLACK = 0, DARK_BLUE = 1, DARK_GREEN = 2, DARK_CYAN = 3, DARK_RED = 4, DARK_PURPLE = 5, DARK_YELLOW = 6, 
LIGHT_GRAY = 7, GRAY = 8, BLUE = 9, GREEN = 10, CYAN = 11, RED = 12, PURPLE = 13, YELLOW = 14, WHITE = 15};
*/

enum COLORS {

    BLACK = 0,
    DARK_RED = 124,
    RED = 196,
    BLUE = 21,
    PURPLE = 201,
    CYAN = 51,
    DEF_WHITE = 7,
    GRAY = 8,
    YELLOW = 226,
    ORANGE = 214,
    GREEN = 82

};

void sColor(int col) { printf("\e[38;5;%dm",col); }

/*
void sColor(int col) {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,col);

}
*/

void resetColor() {
    std::cout<<"\033[39m";
}

void textColored(std::string output, int col) {
    sColor(col);
    std::cout << output;
    resetColor();
}