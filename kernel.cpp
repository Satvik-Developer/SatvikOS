/*
        Kernel.cpp 
        This is the main kernel the
*/

#include "types.h" // Refenrence TO TYPES
#include "gdt.h"  // Reference To the Global Descriptor Table







// PrintF fucntion 
// Its very basic one because making a real one would take a lot of time
void printf(char* str)
{
    static uint16_t* VideoMemory = (uint16_t*)0xb8000;
    for(int i = 0; str[i] != '\0'; ++i)
    {
        VideoMemory[i] = (VideoMemory[i] & 0xFF00) | str[i]; // Video memory is manipulated so that the color is defined as the default one 
    }
}
typedef void (*constructor)();
extern "C" constructor  start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
    (*i)();
}

// The main kernel 

/* Its is made as an c function because when g++ compiles  a programm it changes the name of a 
function a little bit so by making it a  function it name would not be changes and the loader.s
would be able to actually call it */

extern "C" void kernelMain(const void* multiboot_strcture, uint32_t /* magicnumber*/)
{
    printf("Hello World ------------------ My Own Operating System ------------ Made By Satvik");
    GlobalDescriptorTable gdt;
    while(1); // Infinite loop so that the os does not crash immediate 
}