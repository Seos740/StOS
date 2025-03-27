#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

typedef unsigned char uint8_t;

typedef unsigned short uint16_t;

typedef unsigned int uint32_t;

uint8_t read_scan_code() {
    uint8_t scan_code;
    asm volatile ("inb %1, %0" : "=a" (scan_code) : "Nd" (KEYBOARD_DATA_PORT));
    return scan_code;
}

extern "C" void kernel_keyp() {
    char* video_memory = (char*)0xB8000;
    video_memory[0] = 'P';
    video_memory[1] = 0x07;

    while (1) {
        uint8_t scan_code = read_scan_code();
        video_memory[2] = scan_code;
        video_memory[3] = 0x07;
    }
}