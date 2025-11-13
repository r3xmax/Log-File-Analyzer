#include <stdio.h>
#include <string.h>

#define MAX_LOG_WORD_LENGTH 8

typedef enum _LogType {INFO, WARNING, ERROR} LogType;

int parser(char* line, LogType* log_type, FILE* log_file) {

    char log_type_word[MAX_LOG_WORD_LENGTH];

    // Put the line content into the buffer.
    fgets(line, 256, log_file);

    // Parsing the line ignoring the first number and retrieving the second word.
    sscanf(line, "%*d %s", log_type_word);

    // Figure out the log type.
    if(strcmp(log_type_word, "INFO") == 0) {
        *log_type = INFO;        
    } else if (strcmp(log_type_word, "WARNING") == 0) {
        *log_type = WARNING;
    } else if (strcmp(log_type_word, "ERROR") == 0) {
        *log_type = ERROR;
    } else {
        printf("[ERROR] Log type not recognized.\n");
        return 0;
    }

    return 1;
}

int clasifier(char* line, LogType* log_type, FILE* info_file, FILE* warning_file, FILE* error_file) {
    switch (*log_type)    {
    case INFO:
        fprintf(info_file, "%s", line);
        break;


    case WARNING:
        fprintf(warning_file, "%s", line);
        break;

    case ERROR:
        fprintf(error_file, "%s", line);
        break;

    default:
        printf("[WARNING] Log type not recognized");
        return 0;
    }

    return 1;
}

void getFileSize(int* file_size, char* line, FILE* log_file) {
    int character = 0;

    while((character = fgetc(log_file)) != EOF) {
        if(character == '\n') (*file_size)++;
    }

    // Reset file pointer to 0.
    rewind(log_file);
}

void closeFile(FILE* log_file, FILE* info_file, FILE* warning_file, FILE* error_file) {
    fclose(log_file);
    fclose(info_file);
    fclose(warning_file);
    fclose(error_file);
}

int main() {

    /* ==============================================================
    *  |                          Dataset                           |
    *  ==============================================================
    */

    // Log File
    FILE* log_file = fopen("../resources/logs.txt", "r");

    // Generated Files
    FILE* info_file = fopen("../resources/info.txt", "a");
    FILE* warning_file = fopen("../resources/warning.txt", "a");
    FILE* error_file = fopen("../resources/error.txt", "a");

    char line[256];
    LogType log_type;
    int file_size = 0;

    /* ==============================================================
    *  |                       Program's Logic                      |
    *  ==============================================================
    */

    // Initial check
    if(!log_file || !info_file || !warning_file || !error_file) {
        printf("[!] Couldn't open all necesary files. Exiting...");
        return -1;
    }

    // Get logs.txt size
    getFileSize(&file_size, line, log_file);

    // For each log line, clasify and put it into respective file.
    for(int i = 0; i < file_size; i++) {
        parser(line, &log_type, log_file);
        clasifier(line, &log_type, info_file, warning_file, error_file);
    }

    // Close all the file handles
    closeFile(log_file, info_file, warning_file, error_file);

    return 0;
}