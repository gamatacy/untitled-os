ENTRY(start)

SECTIONS{
    . = 1M;

    .boot :
    {
        *(.header_start)
    }

    .text :
    {
        *(.text)
    }

    PROVIDE(end = .);
}