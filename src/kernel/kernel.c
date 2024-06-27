void kmain(void){
  const char *boot_str = "basicOS";
  char *vidptr = (char*)0xb8000;      // video begins here
  unsigned int i = 0;
  unsigned int j = 0;

  // Cleaning the screen 
  // 25 rows, 80 columns, 2 bytes each
  
  while (j < 80 * 25 * 2){
    vidptr[j] = ' ';                  // blank character
    vidptr[j+1] = 0x07;               // attribute-byte - light grey on black screen
    j = j + 2;

  }
  
  j = 0;
  
  while(boot_str[j] != '\0'){
    vidptr[i] = boot_str[j];
    vidptr[i+1] = 0x07;
    ++j;
    i = i + 2;
  
  }
  
  return;

}
