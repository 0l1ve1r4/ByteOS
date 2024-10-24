/* This file is part of ByteOS.
    Copyright (C) 2024 Guilherme Oliveira Santos
    This is free software: you can redistribute it and/or modify it 
    under the terms of the GNU GPL3 or (at your option) any later version. 
	
	* File: shell.c 
	* Description: kernel builtin shell
*/


#include <limits.h>
#include <fs/ramfs.h>
#include <kernel/shell.h>
#include <gui/gameEngine.h>

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <types.h>

size_t num_builtins(void);

/* Shell command handler */
void shell(char* command);

/* defined at kernel/tty for clear built-in*/
extern void terminalClearAll(void);

/* Commands */
void shell_exit(char** args);
void shell_echo(char** args);
void shell_clear(char** args);
void shell_help(char** args);
void shell_status(char** args);
void shell_color(char** args);
void shell_date(char** args);
void shell_ls(char** args);
void shell_touch(char** args);
void shell_cat(char** args);
void shell_pong(char** args);

char* builtin_str[] = {
    "poweroff",
    "echo",
    "clear",
    "help",
    "status",
    "color",
    "date",
    "ls",
    "touch",
    "cat",
    "pong",
};

char* builtin_desc[] = {
    "Shutdown the kernel",
    "Echo the input",
    "Clear the screen",
    "Show this help message",
    "Show the status of the system",
    "Change the color of the shell",
    "Show the current date",
    "List files",
    "Create a new file",
    "Show file content",
    "A Simple \"tennis like\" game"
};

void (*builtin_func[]) (char**) = {
    &shell_exit,
    &shell_echo,
    &shell_clear,
    &shell_help,
    &shell_status,
    &shell_color,
    &shell_date,
    &shell_ls,
    &shell_touch,
    &shell_cat,
    &shell_pong,

};

char * getTime(void){
    static tm time;
    gmtime(&time);
    
    return time.time_str;
    
}

static char history[1][U8_MAX];

void add_to_history(const char* command) {
    strncpy(history[0], command, U8_MAX - 1);
}

// Clear the screen and show the OS prompt
void shell_initialize(void) {
    
    printf("\n============= Welcome to Byte%sOS%s | "
            "Developed By Guilherme %s0l1ve1r4%s =============\n",
            "\033[92m", "\033[37m",
            "\033[92m", "\033[37m");
    printf("\n");
    while (1) {
        char buffer[U8_MAX];

        printf("[%s] root@%skernel%s:$/ ", getTime(), 
                             "\033[92m", "\033[37m");

        if (scanf("%i", &buffer) == -1){
                strncpy(buffer, history[0], U8_MAX - 1);
                buffer[U8_MAX - 1] = '\0'; // Ensure null termination
                printf("%s\n", buffer);
                shell(buffer);
            }

            else {
            add_to_history(buffer);
            shell(buffer);
            }
    }
} 

size_t num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

void shell(char* command) {
    char** args = split_str(command, ' ');
    command = args[0];
    char** arguments = args + 1;    

    size_t i = 0, status = 0;
    for (i = 0; i < num_builtins(); i++) {
        if (strcmp(command, builtin_str[i]) == 0) {
            (*builtin_func[i])(arguments);;
            status = 1;
        }
    }

    if (status == 0){
        printf("Command [%s%s%s] not found.\n", "\033[91m", command, "\033[37m");
    }

}

// There are some unused parameters in the functions below
// This is because the functions are pointers to functions
// and they need to have the same signature

#pragma GCC diagnostic ignored "-Wunused-parameter"

void shell_exit(char** args) {
    printf("Shutting down the kernel...\n");
}


void shell_echo(char** args) {
    if (args[0] == NULL) {
        return; // No arguments
    }
    
    if (strcmp(args[0], ">>") == 0) {
        char str[MAX_FILE_SIZE] = {0};
        size_t current_length = 0;

        u8 i = 1; // Start from the second argument
        while (args[i] != NULL) {
            size_t arg_length = strlen(args[i]);
            
            if (current_length + arg_length + 1 >= MAX_FILE_SIZE) {
                printf("String too long\n");
                return;
            }

            strncpy(str + current_length, args[i], arg_length);
            current_length += arg_length;

            if (args[i + 1] != NULL) {
                str[current_length] = ' ';
                current_length++;
            }

            i++;
        }

        str[current_length] = '\0'; // Null-terminate the final string

        File* file = ramfs_find_file(args[1]);
        if (file == NULL) {
            printf("File not found: %s\n", args[1]);
            return;
        }

        ramfs_write_file(file, (const u8*)str, strlen(str));

        return;
    }

    // Print all arguments if not using the redirection operator
    while (*args) {
        printf("%s ", *args);
        args++;
    }
    printf("\n"); // Add a newline at the end
}



void shell_clear(char** args) {
    terminalClearAll();
}

void shell_help(char** args){
    u8 description = strcmp(args[0], "--verbose");
    description == 0 ? printf("Available commands:\n") : printf("There is no help in the void. " 
    "Joking, use --verbose to show.\n");    

    if (description) {
        return;
    }

    for (u8 i = 0; i < num_builtins(); i++) {
        printf("%s", builtin_str[i]);
        
        if (!description) {
            printf(":\t%s", builtin_desc[i]);
        }
        printf("\n");
    }
}

void shell_status(char** args){
    printf("%s\n", "Not implemented");
}

void shell_color(char** args){
    printf("Color command\n");
    return;
}

void shell_date(char** args){
    static tm time;
    static char date_buffer[20];
    static char time_buffer[20];
    time.date_str = date_buffer;
    time.time_str = time_buffer;
    gmtime(&time);
    
    if (args[0] == NULL){
        
    }
    printf("Date: %s | Time UTC: %s\n", time.date_str, time.time_str);
    
}

void shell_ls(char** args){
    ramfs_ls();
}

void shell_touch(char** args){
    ramfs_create_file(args[0], U8_MAX);
}

void shell_cat(char** args){
    ramfs_cat(args[0]);
}

void shell_pong(char** args){
    if (pong()){
        terminalClearAll();
        printf("YOU WIN!\n");
    }

    else {
        terminalClearAll();
        printf("YOU LOSE!\n");
    }
}

#pragma GCC diagnostic pop


