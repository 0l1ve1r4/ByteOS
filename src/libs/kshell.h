#ifndef KSHELL_H
#define KSHELL_H

#define MAX_COMMAND_LENGTH 100

#define OS_PROMPT " _               _       ___  ____  \n"\
                  "| |__   __ _ ___(_) ___ / _ \\/ ___| \n"\
                  "| '_ \\ / _` / __| |/ __| | | \\___ \\ \n"\
                  "| |_) | (_| \\__ \\ | (__| |_| |___) |\n"\
                  "|_.__/ \\__,_|___/_|\\___|\\___/|____/ \n"\
                  "A simple x86 kernel written from scratch!\n\n"

#define SHELL_PROMPT "root@kernel:$/ "

void kshell_init(void);
void kshell(const char* command);

#endif // KSHELL_H