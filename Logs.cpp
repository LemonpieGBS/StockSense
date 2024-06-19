#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define LOG_FILE_NAME "logins.txt"

int login_user(char* username) {
    char password[MAX_PASSWORD_LENGTH];

    printf("Por favor, ingrese su nombre de usuario: ");
    scanf("%49s", username); // 
    printf("Por favor, ingrese su contrasena: ");
    scanf("%49s", password); 

    

    printf("Login exitoso.\n");
    return 1; 
}

void log_action_with_timestamp(const char* username) {
    time_t now = time(NULL);
    struct tm *tm_now = localtime(&now);
    char dt[64];
    strftime(dt, sizeof(dt), "%c", tm_now); 

    printf("Logueo realizado el: %s\n", dt);

    FILE *logFile = fopen(LOG_FILE_NAME, "a"); 
    if (logFile != NULL) {
        fprintf(logFile, "Usuario %s logueado el: %s\n", username, dt);
        fclose(logFile);
    } else {
        perror("No se pudo abrir el archivo de log");
    }
}

int main() {
    char username[MAX_USERNAME_LENGTH];

    if (login_user(username)) {
        log_action_with_timestamp(username);
    }

    return 0;
}