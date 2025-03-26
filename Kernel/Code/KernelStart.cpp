#include "KeyboardRead.h"

extern "C" void clear_screen() {
    char* video_memory = (char*)0xB8000;
    for (int i = 0; i < 80 * 25 * 2; i += 2) {
        video_memory[i] = ' ';      
        video_memory[i + 1] = 0x07; 
    }
}

extern "C" void kernel_main() {
    char* video_memory = (char*)0xB8000;
    const char* message = "StanleyOS Kernel is running in 32-Bit Mode. put your own code for once";
    
    for (int i = 0; message[i] != '\0'; i++) {
        video_memory[i * 2] = message[i];   
        video_memory[i * 2 + 1] = 0x07;     
    }

    while (1);
}