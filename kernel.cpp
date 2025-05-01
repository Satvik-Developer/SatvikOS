/*
        Kernel.cpp 
        This is the main kernel Everything happens starts and ends their life here
*/

#include "types.h" // Refenrence TO TYPES
#include "gdt.h"  // Reference To the Global Descriptor Table
#include"interrupts.h"

// PrintF fucntion 
// Its very basic one because making a real one would take a lot of time
void printf(char* str)
{
    static uint16_t* VideoMemory = (uint16_t*)0xb8000;
    static uint8_t x = 0, y = 0;
    for(int i = 0; str[i] != '\0'; ++i)
    {
        switch (str[i])
        {
        case '\n':
            y++;
            x = 0;
            break;
        
        default:
            VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | str[i]; // Video memory is manipulated so that the color is defined as the default one 
            x++;
            break;
        }
        if (x>=80)
        {
            y++;
            x = 0;
        }
        if (y>=25)
        {
            for (y = 0;y < 25; y++)
                for (x = 0;x < 80;x++)
                    VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';
            x = 0;
            y = 0;        
        }
        
        
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
    printf("Initialising The OS \n");
    printf("Please Wait For a moment\n");
    printf("Hello World ------------------ My Own Operating System ------------ Made By Satvik"); // A little bit styling for fun funna fun
    GlobalDescriptorTable gdt;
    InterruptManager interrupts(0x20, &gdt);
    interrupts.Activate();
    while(1); // Infinite loop so that the os does not crash immediate 
}
