ENTRY(start)

SECTIONS{
    . = 1M;

    .boot :
    {
        *(.header)
    }

    .text :
    {
        *(.text)
    }

}