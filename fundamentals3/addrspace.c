/*
why should we not use C?
- dangerous
- easy to make serious mistakes
- undefined behavior: compiler advances regularly break old code
- plays a major role in our ongoing computer security nightmare

so why do we use C?
- close to the machine
     - struct layout rules let us define a language objet whose memory layout is exactly what a piece of hardware expects (Eg. screen, a disk driver)
- long and rich history of people getting serious work done

C compiler doesn’t move the portions of a struct around in order
a C programmer can chose to design a structure so that the hardware expects it better

why does const char* s = “foo”
imply strchr(s, ‘o’) == &s[1]

c standards exist

undefined behavior
some incorrect programs have undefined behavior!
in a way, these programs are not c programs
once a program executes undefined behavior, (nasal demons) anything can happen
if a compiler can prove that a condition would cause undefined behavior, it can assume that a behavior will never happen

eg of undefined behavior:
int f(int index) {
let a[10] == …; (initialized)
//if (index < 0 || index >= 10)
 //    abort();
x = a[index];
// if (index >= 10)
     abort();
return x
}
without comments, would be undefined behavior

if we changed second occurrence of “10” to 11, the compiler would assume that index will never be 10, so the compiler will not handle a 10 and we don’t know what it would do

shorthand: “nasal demons"
eg. INT_MIN - 1
eg. double free
eg. dereference a null pointer
integer overflow is undefined
unsigned integer overflow is defined
arithmetic on all operations with unsigned integers, except division by 0, is defined

storage duration:
the way we reason about how long an object lasts
static: object lives as long as the program
automatic: like java scope
dynamic: object is explicitly allocated by malloc, and explicitly deallcoated by free

why dynamic storage duration?
- objects can outlive the functions that created them
- object size determined by input

global lasts

if we visualize memory, the long rectangle has the following occupying space: 
constants, statics, heaps, empty space, automatics 
automatics are laid out in lower addresses, and fill in right to left, extending into empty space
as we allocate dynamic variables, heap grows to the right
automatic memory and heap memory grow closer to each other

if we try to reference anything in the empty space, **undefined behavior**

I'm so glad i reviewed malloc and free last night lol
malloc and free are general-purpose allocators, meant to work for any sized object and for many usage patterns
but these are really hard: 

exercise for today: membench.c. library files called mb
chunks are structs with a size
n times, frees a randomly chosen chunk, then allocates another chunk
finally, frees all of the chunks
library that supports allocation and freeing of these chunk objects. 

membench-malloc creates 496 chunks, and does 50 million alloc and free cycles 
you can do time ./membench-malloc 
nice!
timer
time function
speed
effiiciency


the cheat version of malloc does nothing
LOL
faster than google's and jason evans' malloc
twice as fast as google's malloc
LOL


*/


#include <stdio.h>
#include <stdlib.h>

// why are global variables always in the same space?
// randomizing everything increases startup time by a lot



// static storage duration
char global_ch = 'B';
// adding the keyword static to the above line, 
// means that you can't name the variable elsewhere
// memory statistics variable in assignment 1 LOL, thanks yo 


// static storage duration
const char const_global_ch = 'C';

int main(int argc, char* argv[]) {
    // static storage duration
    (void) argc, (void) argv;

    // automatic storage duration
    char local_ch = 'A';
    const char const_local_ch = 'E';

    // ask how the below ones work 
    // what happens if i have a pointer to an automatic variable? 
    // pointer has an address to storage that doensm't exist anymore
    // dereferencing that variable means that you'll have undefined behavior
    
    // pointer is automatic, 'D' is dynamic
    char *heap_ch = (char*) malloc(1);
    *heap_ch = 'D';

    printf("Address of a global variable\t\t%p\n", &global_ch);
    printf("Address of a const global variable\t%p\n", &const_global_ch);
    
    // the below two have much higher address indexes. 
    // these addresses are roughly 2 ^ 47, halfway up to FFFFFFFF 
    printf("Address of a local variable\t\t%p\n", &local_ch);
    printf("Address of a const local variable\t%p\n", &const_local_ch);


    // when you run the program again, the statics and globals don't change their addresses, 
    // but the dynamic and automatic do change
    // program changes the dynamic and automatic addresses for secuirty 
    // turns out, if you know the addresses of dynamically allocated and automatic variables, 
    // it makes it much easier to break into a C program that has undefined behavior
    // programs become much more vulnerable


    printf("Address of a heap variable\t\t%p\n", heap_ch);
    printf("Address of main\t\t\t\t%p\n", main);
    return 0;
}
