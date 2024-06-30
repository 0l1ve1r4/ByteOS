#include "kstdio.h"

int8_t *vidptr;
uint32_t current_loc;                       // current location on the screen
uint32_t buffer_index;                      // index for the input buffer
char input_buffer[BUFFER_SIZE];             // buffer to store input characters

void stdio_init(void){
    vidptr = (int8_t*) VIDEO_ADDRESS;
    current_loc = 0;
    buffer_index = 0;
}

void kclear(void) {
    uint32_t j = 0;
    current_loc = 0;
    while (j < COLUMNS_IN_LINE * LINES * BYTES_EACH_ELEMENT){
        vidptr[j] = ' '; 
        vidptr[j+1] = LIGHT_GREY;
        j = j + 2;
    }
    return;
}

void kprint(const char *str) {
    if (str == NULL || sizeof(str) == 0){
        return;
    }
    
    uint32_t i = 0;
    while (str[i] != '\0') {
        if (str[i] == '\n') {
            kprint_nl();
            i++;
            continue;
        }
        vidptr[current_loc++] = str[i++];
        vidptr[current_loc++] = LIGHT_GREY;
    }

    // delete the first line 
    if (current_loc >= SCREENSIZE) {
        i = 0;
        while (i < SCREENSIZE - LINE_SIZE ){
            vidptr[i] = vidptr[i + LINE_SIZE];
            i += BYTES_EACH_ELEMENT;
        }
        current_loc = SCREENSIZE - LINE_SIZE;
    }


}

void kprint_nl(void) {
    uint32_t line_size = BYTES_EACH_ELEMENT * COLUMNS_IN_LINE;
    current_loc = current_loc + (line_size - current_loc % (line_size));
}


void show_info(void) {
    char* heap_size = uint_to_str(get_heap_size());
    char* str = "Heap size: ";
    strcat(str, heap_size);

    uint8_t i = 0;
    int8_t* last_line_ptr = vidptr + (LINES - 1) * LINE_SIZE;
    while (str[i] != '\0') {
        last_line_ptr[i * BYTES_EACH_ELEMENT] = str[i];
        last_line_ptr[i * BYTES_EACH_ELEMENT + 1] = LIGHT_GREY;
        i++;
    }
}

// this functions needs to be here because uses vidptr
void keyboard_handler_main(void) {
    uint8_t status;
    char keycode;

    write_port(0x20, 0x20); // Write EOI

    status = read_port(KEYBOARD_STATUS_PORT);
    if (status & 0x01) {
        keycode = read_port(KEYBOARD_DATA_PORT);
        if (keycode < 0)
            return;

        switch (keycode) {
            case ENTER_KEY_CODE:
                input_buffer[buffer_index] = '\0';            
                kshell(input_buffer); 

                // Clear the input buffer
                buffer_index = 0;
                input_buffer[0] = '\0';
                break;

            case BACKSPACE_KEY_CODE:
                if (buffer_index > 0) {
                    buffer_index--;
                    input_buffer[buffer_index] = '\0';

                    if (current_loc > 0) {
                        current_loc -= BYTES_EACH_ELEMENT;
                        vidptr[current_loc] = ' ';
                        vidptr[current_loc + 1] = LIGHT_GREEN;
                    }
                }
                break;

            default:
                if (buffer_index < BUFFER_SIZE - 1) {
                    uint8_t character = keyboard_map[(uint8_t)keycode];
                    input_buffer[buffer_index++] = character;

                    vidptr[current_loc++] = character;
                    vidptr[current_loc++] = 0x07;
                }
                break;
        }
    }
}