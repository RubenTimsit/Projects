#include <asm/desc.h>

void my_store_idt(struct desc_ptr *idtr) {
    asm volatile ("SIDT %0":: "m" (*idtr));
}

void my_load_idt(struct desc_ptr *idtr) {
    asm volatile ("LIDT %0":: "m" (*idtr));
}

void my_set_gate_offset(gate_desc *gate, unsigned long addr) {
    gate->offset_low = (u16)((addr) & 0xffff);
    gate->offset_middle = (u16)((addr >> 16) & 0xffff);
    gate->offset_high = (u32)(addr >> 32);
}

unsigned long my_get_gate_offset(gate_desc *gate) {
    unsigned long addr = 0;

    addr = gate->offset_low | (unsigned long)gate->offset_middle << 16
             | (unsigned long)gate->offset_high << 32;

    return addr;
}