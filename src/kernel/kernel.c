#include "types.h"
#include "colors.h"
#include "kernel.h"

static int8_t *vidptr = (int8_t*) VIDEO_ADDRESS;
void kmain(void){
const char *boot_str = " _Welcome to the _       ___  ____  \n"
                       "| |__   __ _ ___(_) ___ / _ \\/ ___| \n"
                       "| '_ \\ / _` / __| |/ __| | | \\___ \\ \n"
                       "| |_) | (_| \\__ \\ | (__| |_| |___) |\n"
                       "|_.__/ \\__,_|___/_|\\___|\\___/|____/ \n"
                       "A simple x86 kernel written from scratch!\n";
  kclear();
  kprint(boot_str);

  return;

}

void kclear(void){
  uint32_t i = 0;
  uint32_t j = 0;
  while (j < COLUMNS_IN_LINE * LINES * BYTES_EACH_ELEMENT){
    vidptr[j] = ' ';                  // blank character
    vidptr[j+1] = LIGHT_GREY;
    j = j + 2;
  }
  return;
}

void kprint(const char *str) {
    uint32_t i = 0, j = 0, row = 0, col = 0;
    
    while (str[j] != '\0') {
        if (str[j] == '\n') {
            row++;
            col = 0;
            if (row >= LINES) {
                row = 0; // Optionally, implement scrolling or screen clearing
            }
            i = row * COLUMNS_IN_LINE * 2;
        } else {
            if (col >= COLUMNS_IN_LINE) {
                col = 0;
                row++;
                if (row >= LINES) {
                    row = 0; // Optionally, implement scrolling or screen clearing
                }
                i = row * COLUMNS_IN_LINE * BYTES_EACH_ELEMENT;
            }
            vidptr[i] = str[j];
            vidptr[i+1] = WHITE;
            i += 2;
            col++;
        }
        j++;
    }
}