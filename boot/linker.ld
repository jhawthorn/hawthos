ENTRY(_start)
OUTPUT_FORMAT(binary)

SECTIONS {
   . = 0x08000000;

   .text : ALIGN(0x1000) {
      *(.text)
      *(.rodata*)
   }
   etext = .;

   .data : ALIGN (0x1000) {
      *(.data)
   }
   edata = .;

   .bss : ALIGN(0x1000) {
      *(COMMON)
      *(.bss)
   }
   end = .;
}
