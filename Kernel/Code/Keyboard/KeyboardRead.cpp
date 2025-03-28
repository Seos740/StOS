#define KEYBOARD_DATA_PORT  0x60
#define KEYBOARD_STATUS_PORT 0x64

#include "KeyboardRead.h"

typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;

// QWERTY US keyboard layout (simplified, no special keys)
const char scan_code_to_ascii[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', // Backspace
    '\t', // Tab
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', // Enter
    0, // Control
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0, // Left Shift
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, // Right Shift
    '*',
    0, // Alt
    ' ', // Space
    0, // Caps Lock
};

// Read keyboard scan code
uint8_t read_scan_code() {
    uint8_t scan_code;
    asm volatile ("inb %1, %0" : "=a" (scan_code) : "Nd" (KEYBOARD_DATA_PORT));
    return scan_code;
}

// Handle the keyboard interrupt (IRQ1)
extern "C" void kernel_keyp() {
    static uint32_t position = 0; // Position in video memory
    char* video_memory = (char*)0xB8000;

    // Acknowledge the interrupt (PIC)
    asm volatile("outb %0, %1" : : "a"(0x20), "Nd"(0x20));  // Send EOI to PIC master

    uint8_t scan_code = read_scan_code();

    if (scan_code < 128) { // Ignore key releases
        char key = scan_code_to_ascii[scan_code];

        if (key) {
            // Display the key at the current position
            video_memory[position] = key;
            video_memory[position + 1] = 0x07; // White text
            position += 2; // Move to the next position in video memory

            // Wrap to next line if we reach the end of the screen (80x25)
            if (position >= 80 * 25 * 2) {
                position = 0; // Reset to the top of the screen
            }
        }
    }
}
