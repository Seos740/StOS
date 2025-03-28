### **StOS Alpha 1.0.2**  
#### **ChangeLog:**  
- **Added Memory Management Utilities**, supporting up to **_4GB_** of memory.  



#### **Supported SysCalls:**

File System (FileSystem.cpp)

- FindFile

- ReadClusters

- WriteClusters

- FindFreeCluster

- UpdateFATTable

- RegisterFile

- UnregisterFile

- CheckRingAccess

- GetCurrentRing

- ReadFile

- WriteFile

- ModifyFilePermissions

- DeleteFile

Memory Management (Memory.cpp)

- syscall_write_to_file

- malloc

- expandHeap

- free

- debug_log

Keyboard Input (KeyboardRead.cpp)

- read_scan_code

- kernel_keyp

