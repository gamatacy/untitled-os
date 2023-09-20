volatile char *video = (volatile char*)0xB8000;
int line = 0;
int pos = 0;

void write_string( int color, const char *string )
{
    while( *string != 0 )
    {
        if (*string == '\n') {
            line++;
            pos = 0;
        } else {
            *(video + line * 160 + pos * 2) = *string;
            *(video + line * 160 + pos * 2 + 1) = color;
            pos += 1;
            line += pos / 160;
            pos = pos % 160;
        }
        string++;
    }
}

void clear() {
    for (int i = 0; i < 80 * 25 * 2; i++) {
        *(video + i) = 0;
    }
    line = 0;
    pos = 0;
}

void kmain() {
    while (1) {
        for (int i = 0; i < 25; i++) {
            write_string(0x1F, "ITMO.FURS\n");
        }
        // fucked up sleep
        for (unsigned int i = 0; i < 1<<28-1; i++);
        clear();
        write_string(0x1F, "clear");
        // fucked up sleep
        for (unsigned int i = 0; i < 1<<28-1; i++);
        clear();
    }
}