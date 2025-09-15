# FoxyBoot
Foxy boot is a minimal bootloader for the stm32f4

- The Flash size is 1Mb : 0x0800 0000 - 0x080F FFFF
- The SRAM is 194 - 64 = 128Kb 0x2000 0000 - 0x2001 FFFF
- The CCM (core coupled memory) 64 Kb 
## bootloader 
- The bootloader size will be 32Kb, so it will be from  0x0800 0000 - 0x0800 8000
- the new flash layou will be from  0x0800 8000 - 0x080F FFFF

in the bootloader can jump to the main functionm by taking the address the address of Vector table, the vector table contains the address for the reset handler 
the reset handler will then launch our main

for the main app we include the bootloader section by adding section called `bootloader_section` in the linker scritp and we create an assembly file that includes the `bootloader.bin` into that section 

in the app we need to offset the the vector table with the bootloade size unless our app will point to the vector table of the bootloader.

# tools 
after the bootlader genraration we pad the extra space with 0xff 
to analyse the .bin file we use `bewitched Boolloader.bin` 
can be installed from [link](https://github.com/francisrstokes/bewitched)