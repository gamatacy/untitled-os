#include "paging.h"

page_entry_raw encode_page_entry(struct page_entry entry) {

    page_entry_raw raw = 0;

    raw |= (entry.p & 0x1);
    raw |= (entry.rw & 0x1) << 1;
    raw |= (entry.us & 0x1) << 2;
    raw |= (entry.pwt & 0x1) << 3;
    raw |= (entry.pcd & 0x1) << 4;
    raw |= (entry.a & 0x1) << 5;
    raw |= (entry.d & 0x1) << 6;
    raw |= (entry.rsvd & 0x1) << 7;
    raw |= (entry.ign1 & 0xF) << 8;
    raw |= (entry.address & 0xFFFFFFFFF) << 12;
    raw |= (entry.ign2 & 0x7FFF) << 48;
    raw |= (entry.xd & 0x1) << 63;

    return raw;

}

struct page_entry decode_page_entry(page_entry_raw raw) {

    struct page_entry entry;

    entry.p = raw & 0x1;
    entry.rw = (raw >> 1) & 0x1;
    entry.us = (raw >> 2) & 0x1;
    entry.pwt = (raw >> 3) & 0x1;
    entry.pcd = (raw >> 4) & 0x1;
    entry.a = (raw >> 5) & 0x1;
    entry.d = (raw >> 6) & 0x1;
    entry.rsvd = (raw >> 7) & 0x1;
    entry.ign1 = (raw >> 8) & 0xF;
    entry.address = (raw >> 12) & 0xFFFFFFFFF;
    entry.ign2 = (raw >> 48) & 0x7FFF;
    entry.xd = (raw >> 63) & 0x1;

    return entry;
}

void init_entry(struct page_entry *entry, uint64_t addr) {

    entry->p = 1;
    entry->rw = 1;
    entry->us = 0;
    entry->pwt = 1;
    entry->pcd = 0;
    entry->a = 0;
    entry->d = 0;
    entry->rsvd = 0;
    entry->ign1 = 0;
    entry->address = addr;
    entry->ign2 = 0;
    entry->xd = 0;

}

void init_paging() {

    struct page_entry_t p4, p3, p2, p1;
    struct page_entry_t physical_memory;
    struct page_entry p4_s, p3_s, p2_s, p1_s;

    p4_s = decode_page_entry(p4.table[0]);
    p3_s = decode_page_entry(p3.table[0]);
    p2_s = decode_page_entry(p2.table[0]);

    init_entry(&p4_s, &p3.table[0]);
    init_entry(&p3_s, &p2.table[0]);
    init_entry(&p2_s, &p1.table[0]);

    for (int i = 0; i < ENTRIES_COUNT; ++i) {
        p1_s = decode_page_entry(&p1.table[i]);

        init_entry(&p1_s, 0x1000);//&physical_memory.table[i]);

        p1.table[i] = encode_page_entry(p1_s);
    }

    p4.table[0] = encode_page_entry(p4_s);
    p3.table[0] = encode_page_entry(p4_s);
    p2.table[0] = encode_page_entry(p4_s);

    struct page_entry p;
    init_entry(&p, 0);
    physical_memory.table[0] = encode_page_entry(p);

    void *p4_table_p = &p4.table[0];

    asm volatile ("movq %0, %%rax; movq %%rax, %%cr3;"::"r"((uint64_t) p4_table_p));

}