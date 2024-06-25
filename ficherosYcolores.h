#include <windows.h>
#include <iostream>
#include <string>

std::string APPDATA_PATH = std::string(getenv("appdata")) + "\\StockSense-II\\";

enum COLORS {BLACK = 0, DARK_BLUE = 1, DARK_GREEN = 2, DARK_CYAN = 3, DARK_RED = 4, DARK_PURPLE = 5, DARK_YELLOW = 6, 
LIGHT_GRAY = 7, GRAY = 8, BLUE = 9, GREEN = 10, CYAN = 11, RED = 12, PURPLE = 13, YELLOW = 14, WHITE = 15};

void sColor(int col) {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,col);

}

void resetColor() {
    sColor(LIGHT_GRAY);
}

void textColored(std::string output, int col) {
    sColor(col);
    std::cout << output;
    resetColor();
}