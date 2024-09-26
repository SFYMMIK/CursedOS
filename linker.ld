/* linker.ld */

ENTRY(kernel_main)  /* The entry point for the kernel */

SECTIONS
{
    /* Place the text (code) section at 0x100000 (1 MB) */
    . = 0x100000;
    
    .text :
    {
        *(.text)  /* All text (code) sections go here */
    }

    /* The data section follows the text section */
    .data :
    {
        *(.data)  /* All initialized data sections go here */
    }

    /* The bss section follows the data section */
    .bss :
    {
        *(.bss)   /* All uninitialized data sections go here */
        *(COMMON)
    }
}
