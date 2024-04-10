#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define FRAME_SIZE 256
#define FRAME_ENTRIES 128
#define PAGE_SIZE 256
#define PAGE_ENTRIES 256

typedef struct PageTableEntry {
    uint16_t present : 1;
    uint16_t frame : 15;
} PageTableEntry;

PageTableEntry page_table[PAGE_ENTRIES];
uint8_t *physical_memory;

uint16_t translate_address(uint16_t logical_address) {
    uint8_t frame_number;
    uint8_t page_number = logical_address >> 8;

    if (page_table[page_number].present == 0) {
        // Page not present, allocate a frame for it.
        // For simplicity, just random a frame. Must fix this later.
        frame_number = rand() % FRAME_ENTRIES;

        page_table[page_number].present = 1;
        page_table[page_number].frame = frame_number;
    }

    uint16_t physical_address = (page_table[page_number].frame << 8) + (logical_address & 0xFF);

    printf("Translate logical address 0x%X (page number 0x%x, offset 0x%02x) to physical address 0x%X \n",
        logical_address, page_number, logical_address & 0xFF, physical_address);

    return physical_address;
}

void read_from_memory(uint16_t logical_address, uint8_t *value) {
    uint16_t physical_address = translate_address(logical_address);
    *value = physical_memory[physical_address];
}

void write_to_memory(uint16_t logical_address, uint8_t value) {
    uint16_t physical_address = translate_address(logical_address);
    physical_memory[physical_address] = value;
}

int main() {
    // Allocate physical memory
    physical_memory = calloc(PAGE_ENTRIES, PAGE_SIZE);

    // Read and write to memory
    uint8_t value;
    write_to_memory(0x123, 0xA);
    read_from_memory(0x123, &value);
    printf("Value read from memory: 0x%02X\n", value);
    write_to_memory(0x1234, 0xAB);
    read_from_memory(0x1234, &value);
    printf("Value read from memory: 0x%02X\n", value);

    // Calculate page table size
    size_t page_table_size = PAGE_ENTRIES * sizeof(PageTableEntry);
    printf("Page table size: %lu bytes\n", page_table_size);

    return 0;
}
