#ifndef KERNEL_H
#define KERNEL_H
 
#define VIDEO_ADDRESS 0xb8000   

void kmain(void);
void kclear(void);
void kprint(const char *str);
void kprint_nl(void);

#endif