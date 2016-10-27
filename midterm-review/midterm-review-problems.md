1. Sizes and alignments
QUESTION 1A. True or false: For any non-array type X, the size of X (sizeof(X)) is greater than or equal to the alignment of type X.

QUESTION 1B. True or false: For any type X, the size of struct Y { X a; char newc; } is greater than the size of X.

QUESTION 1C. True or false: For any types A1...An (with n ≥ 1), the size of struct Y is greater than the size of struct X, given:

  struct X {     struct Y {
     A1 a1;         A1 a1;
     ...            ...
     An an;         An an;
  };                char newc;
                 };
QUESTION 1D. True or false: For any types A1...An (with n ≥ 1), the size of struct Y is greater than the size of union X, given:

  union X {      struct Y {
     A1 a1;         A1 a1;
     ...            ...
     An an;         An an;
  };             };
Let alignof(T) equal the alignment of type T.

QUESTION 1E. Assume that structure struct Y { ... } contains K char members and M int members, with K≤M, and nothing else. Write an expression defining the maximum sizeof(struct Y).

QUESTION 1F. You are given a structure struct Z { T1 a; T2 b; T3 c; } that contains no padding. What does (sizeof(T1) + sizeof(T2) + sizeof(T3)) % alignof(struct Z) equal?

QUESTION 1G. Arrange the following types in increasing order by size. Sample answer: “1 < 2 = 4 < 3” (choose this if #1 has smaller size than #2, which has equal size to #4, which has smaller size than #3).

char
struct minipoint { uint8_t x; uint8_t y; uint8_t z; }
int
unsigned short[1]
char**
double[0]
2. Expressions
QUESTION 2A. Here are eight expressions. Group the expressions into four pairs so that the two expressions in each pair have the same value, and each pair has a different value from every other pair. There is one unique answer that meets these constraints. m has the same type and value everywhere it appears (there’s one unique value for m that meets the problem’s constraints). Assume an x86 machine.

sizeof(&m)
-1
m & -m
m + ~m + 1
16 >> 2
m & ~m
m
1
3. Hello binary
This problem locates 8-bit numbers horizontally and vertically in the following 16x16 image. Black pixels represent 1 bits and white pixels represent 0 bits. For horizontal arrangements, the most significant bit is on the left as usual. For vertical arrangements, the most significant bit is on top.

Hellodecor.gif

Examples: The 8-bit number 15 (hexadecimal 0x0F, binary 0b00001111) is located horizontally at 3,4, which means X=3, Y=4.

The pixel at 3,4 is white, which has bit value 0.
4,4 is white, also 0.
5,4 is white, also 0.
6,4 is white, also 0.
7,4 is black, which has bit value 1.
8,4, 9,4, and 10,4 are black, giving three more 1s.
Reading them all off, this is 0b00001111, or 15.
15 is also located horizontally at 7,6.

The 8-bit number 0 is located vertically at 0,0. It is also located horizontally at 0,0 and 1,0.

The 8-bit number 134 (hexadecimal 0x86, binary 0b10000110) is located vertically at 8,4.

QUESTION 3A. Where is 3 located vertically? (All questions refer to 8-bit numbers.)

QUESTION 3B. Where is 12 located horizontally?

QUESTION 3C. Where is 255 located vertically?

4. Hello memory
Shintaro Tsuji wants to represent the image of Part 3 in computer memory. He stores it in an array of 16-bit unsigned integers:

uint16_t cute[16];
Row Y of the image is stored in integer cute[Y].

QUESTION 4A. What is sizeof(cute), 2, 16, 32, or 64?

QUESTION 4B. printf("%d\n", cute[0]); prints 16384. Is Shintaro’s machine big-endian or little-endian?

5. Hello program
Now that Shintaro has represented the image in memory as an array of uint16_t objects, he can manipulate the image using C. For example, here’s a function.

void swap(void) {
   for (int i = 0; i < 16; ++i)
      cute[i] = (cute[i] << 8) | (cute[i] >> 8);
}
Running swap produces the following image:

Hello-swap.gif

Shintaro has written several other functions. Here are some images (A is the original):

Hello-f0.gif	 	Hello-f7.gif	 	Hello-f2.gif	 	Hello-f3.gif	 	Hello-f4.gif
A		B		C		D		E
 
Hello-f5.gif	 	Hello-f6.gif	 	Hello-f1.gif	 	Hello-f8.gif	 	Hello-f9.gif
F		G		H		I		J
For each function, what image does that function create?

QUESTION 5A.

void f0() {
   for (int i = 0; i < 16; ++i)
      cute[i] = ~cute[i];
}
QUESTION 5B.

void f1() {
   for (int i = 0; i < 16; ++i) {
      cute[i] = ((cute[i] >> 1) & 0x5555) | ((cute[i] << 1) & 0xAAAA);
      cute[i] = ((cute[i] >> 2) & 0x3333) | ((cute[i] << 2) & 0xCCCC);
      cute[i] = ((cute[i] >> 4) & 0x0F0F) | ((cute[i] << 4) & 0xF0F0);
      cute[i] =  (cute[i] >> 8)           |  (cute[i] << 8);
   }
}
QUESTION 5C.

void f2() {
   char *x = (char *) cute;
   for (int i = 0; i < 16; ++i)
      x[2*i] = i;
}
For “fun”
The following programs generated the other images. Can you match them with their images?

void f3() {
   for (int i = 0; i < 16; ++i)
      cute[i] &= ~(7 << i);
}
void f4() {
   swap();
   for (int i = 0; i < 16; ++i)
      cute[i] <<= i/4;
   swap();
}
void f5() {
   for (int i = 0; i < 16; ++i)
      cute[i] = -1 * !!(cute[i] & 64);
}
void f6() {
   for (int i = 0; i < 16; ++i) {
      int tmp = cute[15-i];
      cute[15-i] = cute[i];
      cute[i] = tmp;
   }
}
void f7() {
   for (int i = 0; i < 16; ++i)
      cute[i] = cute[i] & -cute[i];
}
void f8() {
   for (int i = 0; i < 16; ++i)
      cute[i] ^= cute[i] ^ cute[i];
}
void f9() {
   for (int i = 0; i < 16; ++i)
      cute[i] = cute[i] ^ 4080;
}
6. Memory regions
Consider the following program:

struct ptrs {
    int** x;
    int* y;
};

struct ptrs global;

void setup(struct ptrs* p) {
    int* a = malloc(sizeof(int));
    int* b = malloc(sizeof(int));
    int* c = malloc(sizeof(int));
    int* d = malloc(sizeof(int));
    int* e = malloc(sizeof(int) * 2);
    int** f = malloc(4 * sizeof(int*));
    int** g = malloc(sizeof(int*));

    *a = 0;
    *b = 0;
    *c = (int) a;
    *d = *b;
    e[0] = 29;
    e[1] = (int) &d[100000];

    f[0] = b;
    f[1] = c;
    f[2] = 0;
    f[3] = 0;

    *g = c;

    global.x = f;
    global.y = e;

    p->x = g;
    p->y = &e[1];
}

int main(int argc, char** argv) {
    stack_bottom = (char*) &argc;
    struct ptrs p;
    setup(&p);
    m61_collect();
    do_stuff(&p);
}
This program allocates objects a through g on the heap and then stores those pointers in some stack and global variables. (It then calls our conservative garbage collector from class, but that won’t matter until the next problem.) We recommend you draw a picture of the state setup creates.

QUESTION 6A. Assume that (uintptr_t) a == 0x8300000, and that malloc returns increasing addresses. Match each address to the most likely expression with that address value. The expressions are evaluated within the context of main. You will not reuse an expression.

Value	 		Expression
1.  	0x8300040		A.  	&p
2.  	0x8049894		B.  	(int*) *p.x[0]
3.  	0x8361AF0		C.  	&global.y
4.  	0x8300000		D.  	global.y
5.  	0xBFAE0CD8		E.  	(int*) *p.y
7. Garbage collection
Here is the top-level function for the conservative garbage collector we wrote in class.

void m61_collect(void) {
    char* stack_top = (char*) &stack_top;

    // The entire contents of the heap start out unmarked
    for (size_t i = 0; i != nmr; ++i)
	mr[i].marked = 0;

    // Mark all reachable objects, starting with the roots (the stack)
    m61_markaccessible(stack_top, stack_bottom - stack_top);

    // Free everything that wasn't marked
    for (size_t i = 0; i != nmr; ++i)
	if (mr[i].marked == 0) {
	    m61_free(mr[i].ptr);
	    --i;		// m61_free moved different data into this
				// slot, so we must recheck the slot
	}
}
This garbage collector is not correct because it doesn’t capture all memory roots.

Consider the program from the previous section, and assume that an object is reachable if do_stuff can access an address within the object via variable references and memory dereferences without casts or pointer arithmetic. Then:

QUESTION 7A. Which reachable objects will m61_collect() free? Circle all that apply.

a 		 b 		 c 		 d 		 e 		 f 		 g 		 None of these
QUESTION 7B. Which unreachable objects will m61_collect() not free? Circle all that apply.

a 		 b 		 c 		 d 		 e 		 f 		 g 		 None of these
QUESTION 7C. Conservative garbage collection in C is often slower than precise garbage collection in languages such as Java. Why? Circle all that apply.

C is generally slower than other languages.
Conservative garbage collectors must search all reachable memory for pointers. Precise garbage collectors can ignore values that do not contain pointers, such as large character buffers.
C programs generally use the heap more than programs in other languages.
None of the above.

8. I/O caching
Mary Ruefle, a poet who lives in Vermont, is working on her caching I/O library for CS61’s problem set 2. She wants to implement a cache with N slots. Since searching those slots might slow down her library, she writes a function that maps addresses to slots. Here’s some of her code.

 #define SLOTSIZ 4096
 typedef struct io61_slot {
     char buf[SLOTSIZ];
     off_t pos; // = (off_t) -1 for empty slots
     ssize_t sz;
 } io61_slot;
 
 #define NSLOTS 64
 struct io61_file {
     int fd;
     off_t pos; // current file position
     io61_slot slots[NSLOTS];
 };
 
 static inline int find_slot(off_t off) {
     return off % NSLOTS;
 }
 
 int io61_readc(io61_file* f) {
     int slotindex = find_slot(f->pos);
     io61_slot* s = &f->slots[slotindex];
 
     if (f->pos < s->pos || f->pos >= s->pos + s->sz) {
         // slot contains wrong data, need to refill it
         off_t new_pos = lseek(f->fd, f->pos, SEEK_SET);
         assert(new_pos != (off_t) -1); // only handle seekable files for now
         ssize_t r = read(f->fd, s->buf, SLOTSIZ);
         if (r == -1 || r == 0)
             return EOF;
         s->pos = f->pos;
         s->sz = r;
     }
 
     int ch = (unsigned char) s->buf[f->pos - s->pos];
     ++f->pos;
     return ch;
 }
Before she can run and debug this code, Mary is led “to an emergency of feeling that ... results in a poem.” She’ll return to CS61 and fix her implementation soon, but in the meantime, let’s answer some questions about it.

QUESTION 8A. True or false: Mary’s cache is a direct-mapped cache.

QUESTION 8B. What changes to Mary’s code could change your answer to Question 8A? Circle all that apply.

New code for find_slot (keeping io61_readc the same)
New code in io61_readc (keeping find_slot the same)
New code in io61_readc and new code for find_slot
None of the above
QUESTION 8C. Which problems would occur when Mary’s code was used to sequentially read a seekable file of size 2MiB (2×220 = 2097152 bytes) one character at a time? Circle all that apply.

Excessive CPU usage (>10x stdio)
Many system calls to read data (>10x stdio)
Incorrect data (byte x read at a position where the file has byte y≠x)
Read too much data (more bytes read than file contains)
Read too little data (fewer bytes read than file contains)
Crash/undefined behavior
None of the above
QUESTION 8D. Which of these new implementations for find_slot would fix at least one of these problems with reading sequential files? Circle all that apply.

return (off * 2654435761) % NSLOTS; /* integer hash function from Stack Overflow */
return (off / SLOTSIZ) % NSLOTS;
return off & (NSLOTS - 1);
return 0;
return (off >> 12) & 0x3F;
None of the above
9. Memory errors
The following function constructs and returns a lower-triangular matrix of size N. The elements are random 2-dimensional points in the unit square. The matrix is represented as an array of pointers to arrays.

 typedef struct point2 {
     double d[2];
 } point2;
 typedef point2* point2_vector;
 
 point2_vector* make_random_lt_matrix(size_t N) {
     point2_vector* m = (point2_vector*) malloc(sizeof(point2_vector) * N);
     for (size_t i = 0; i < N; ++i) {
         m[i] = (point2*) malloc(sizeof(point2) * (i + 1));        /* LINE A */
         for (size_t j = 0; j <= i; ++j)
             for (int d = 0; d < 2; ++d)
                 m[i][j].d[d] = drand48();                          /* LINE B */
     }
     return m;
 }
This code is running on an x86 machine (size_t is 32 bits). You may assume that the machine has enough free physical memory and the process has enough available virtual address space to satisfy any malloc() call.

QUESTION 9A. Give a value of N so that, while make_random_lt_matrix(N) is running, no malloc() returns NULL, but a memory error (such as a null pointer dereference or an out-of-bounds dereference) happens on Line A. The memory error should happen specifically when i == 1.

(This problem is probably easier when you write your answer in hexadecimal.)

QUESTION 9B. Give a value of N so that no malloc() returns NULL, and no memory error happens on Line A, but a memory error does happen on Line B.

10. Caches and reference strings
QUESTION 10A. True or false: A direct-mapped cache with N or more slots can handle any reference string containing ≤N distinct addresses with no misses except for cold misses.

QUESTION 10B. True or false: A fully-associative cache with N or more slots can handle any reference string containing ≤N distinct addresses with no misses except for cold misses.


Consider the following 5 reference strings.

Name	String
α	1
β	1, 2
γ	1, 2, 3, 4, 5
δ	2, 4
ε	5, 2, 4, 2
QUESTION 10C. Which of the strings might indicate a sequential access pattern? Circle all that apply.

α	β	γ	δ	ε	None of these
QUESTION 10D. Which of the strings might indicate a strided access pattern with stride >1? Circle all that apply.

α	β	γ	δ	ε	None of these

The remaining questions concern concatenated permutations of these five strings. For example, the permutation αβγδε refers to this reference string:

1, 1, 2, 1, 2, 3, 4, 5, 2, 4, 5, 2, 4, 2.
We pass such permutations through an initially-empty, fully-associative cache with 3 slots, and observe the numbers of hits.

QUESTION 10E. How many cold misses might a permutation observe? Circle all that apply.

0	1	2	3	4	5	Some other number

Under LRU eviction, the permutation αβεγδ observes 5 hits as follows. (We annotate each access with “h” for hit or “m” for miss.)

1m; 1h, 2m; 5m, 2h, 4m, 2h; 1m, 2h, 3m, 4m, 5m; 2m, 4h.
QUESTION 10F. How many hits does this permutation observe under FIFO eviction?

QUESTION 10G. Give a permutation that will observe 8 hits under LRU eviction, which is the maximum for any permutation. There are several possible answers. (Write your answer as a permutation of αβγδε. For partial credit, find a permutation that has 7 hits, etc.)

QUESTION 10H. Give a permutation that will observe 2 hits under LRU eviction, which is the minimum for any permutation. There is one unique answer. (Write your answer as a permutation of αβγδε. For partial credit, find a permutation that has 3 hits, etc.)

11. Git
Edward Snowden is working on a CS61 problem set and he has some git questions.

QUESTION 11A. The CS61 staff has released some new code. Which commands will help Edward get the code from code.seas.harvard.edu into his repository? Circle all that apply.

git commit
git add
git push
git pull
QUESTION 11B. Edward has made some changes to his code. He hasn’t run git since making the changes. He wants to upload his latest version to code.seas.harvard.edu. Put the following git commands in an order that will accomplish this goal. You won’t necessarily use every command. You may add flags to a command (but you don’t have to). If you add flags, tell us what they are.

git commit
git add
git push
git pull
Edward Snowden’s partner, Edward Norton, has been working on the problem set also. They’ve been working independently.

At midnight on October 10, here’s how things stood. The git log for the partners’ shared code.seas.harvard.edu repository looked like this. The committer is listed in (parentheses).

 52d44ee Pset release. (kohler)
The git log for Snowden’s local repository:

 3246d07 Save Greenwald's phone number (snowden)
 8633fbd Start work on a direct-mapped cache (snowden)
 52d44ee Pset release. (kohler)
The git log for Norton’s local repository:

 81f952e try mmap (norton)
 52d44ee Pset release. (kohler)
At noon on October 11, their shared code.seas.harvard.edu repository has this log:

 d446e60 Increase cache size (snowden)
 b677e85 use mmap on mmappable files (norton)
 b46cfda Merge branch 'master' of code.seas.harvard.edu:~TheTrueHOOHA/cs61/TheTrueHOOHAs-cs61-psets.git \
         (norton)
 81f952e try mmap (norton)
 3246d07 Save Greenwald's phone number (snowden)
 8633fbd Start work on a direct-mapped cache (snowden)
 52d44ee Pset release. (kohler)
QUESTION 11C. Give an order for these commands that could have produced that log starting from the midnight October 10 state. You might not use every command, and you might use some commands more than once. Sample (incorrect) answer: “1 4 4 5 2.”

snowden: git commit -a
snowden: git push
snowden: git pull
norton: git commit -a
norton: git push
norton: git pull
QUESTION 11D. In your answer to Question 11C, circle the step(s) where there might have been a merge conflict.

12. Debugging
QUESTION 12A. Match each tool or technique with a debugging situation for which it is well suited. Produce the best overall match that uses each situation exactly once.

1. strace	A. Investigating segmentation faults
2. gdb	B. Finding memory leaks
3. valgrind --tool=memcheck	C. Checking your assumptions and verifying invariants
4. printf statements	D. Discovering I/O patterns
5. assert	E. Displaying program state
13. Processor cache
The git version control system is based on commit hashes, which are 160-bit (20-byte) hash values used to identify commits. In this problem you’ll consider the processor cache behavior of several versions of a “grading server” that maps commits to grades. Here’s the first version:

 typedef struct commit_info {
     char hash[20];
     int grade[11];
 } commit_info;
 
 commit_info* commits;
 size_t N;
 
 int get_grade1(const char* hash, int pset) {
     for (size_t i = 0; i != N; ++i)
         if (memcmp(commits[i].hash, hash, 20) == 0)
             return commits[i].grade[pset];
     return -1;
 }
We will ask questions about the average number of cache lines accessed by variants of get_grade(hash, pset). You should make the following assumptions:

The hash argument is uniformly drawn from the set of known commits. That is, the probability that hash equals the ith commit’s hash is 1/N.
Only count cache lines accessible via commits. Don’t worry about cache lines used for local variables, for parameters, for global variables, or for instructions. For instance, do not count the hash argument or the global-data cache line that stores the commits variable itself.
Every object is 64-byte aligned, and no two objects share the same cache line.
Commit hashes are mathematically indistinguishable from random numbers. Thus, the probability that two different hashes have the same initial k bits equals 1/2k.
Fully correct answers would involve ceiling functions, but you don’t need to include them.
QUESTION 13A. What is the expected number of cache lines accessed by get_grade1, in terms of N?

The second version:

 typedef struct commit_info {
     char hash[20];
     int grade[11];
 } commit_info;
 
 commit_info** commits;
 size_t N;
 
 int get_grade2(const char hash[20], int pset) {
     for (size_t i = 0; i != N; ++i)
         if (memcmp(commits[i]->hash, hash, 20) == 0)
             return commits[i]->grade[pset];
     return -1;
 }
QUESTION 13B. What is the expected number of cache lines accessed by get_grade2, in terms of N?

The third version:

 typedef struct commit_info {
     char hash[20];
     int grade[11];
 } commit_info;
 
 typedef struct commit_hint {
     char hint[4];
     commit_info* commit;
 } commit_hint;
 
 commit_hint* commits;
 size_t N;
 
 int get_grade3(const char* hash, int pset) {
     for (size_t i = 0; i != N; ++i)
         if (memcmp(commits[i].hint, hash, 4) == 0
             && memcmp(commits[i].commit->hash, hash, 20) == 0)
             return commits[i].commit->grade[pset];
     return -1;
 }
QUESTION 13C. What is the expected number of cache lines accessed by get_grade3, in terms of N? (You may assume that N≤2000.)

The fourth version is actually a hash table.

 typedef struct commit_info {
     char hash[20];
     int grade[11];
 } commit_info;
 
 commit_info** commits;
 size_t commits_hashsize;
 
 int get_grade4(const char* hash, int pset) {
     // choose initial bucket
     size_t bucket;
     memcpy(&bucket, hash, sizeof(bucket));
     bucket = bucket % commits_hashsize;
     // search for the commit starting from that bucket
     while (commits[bucket] != NULL) {
         if (memcmp(commits[bucket]->hash, hash, 20) == 0)
             return commits[bucket]->grade[pset];
         bucket = (bucket + 1) % commits_hashsize;
     }
     return -1;
 }
QUESTION 13D. Assume that a call to get_grade4 encounters C expected hash collisions (i.e., examines C buckets before finding the bucket that actually contains hash). What is the expected number of cache lines accessed by get_grade4, in terms of N and C?

14. Assembly
Here is some x86 assembly code.

 f:
         movl a, %eax
         movl b, %edx
         andl $255, %edx
         subl %edx, %eax
         movl %eax, a
         ret
QUESTION 14A. Write valid C code that could have compiled into this assembly (i.e., write a C definition of function f), given the global variable declarations “extern unsigned a, b;.” Your C code should compile without warnings. REMINDER: You are not permitted to run a C compiler, except for the C compiler that is your brain.

QUESTION 14B. Write different valid, warning-free C code that could have compiled into that assembly. This version should contain different operators than your first version. (For extra credit, use only one operator.)

QUESTION 14C. Again, write different valid, warning-free C code that could have compiled into that assembly. In this version, f should have a different type than in your first version.

15. Data representation (12 points)
Assume a 32-bit x86 architecture unless explicitly told otherwise.

Write your assumptions if a problem seems unclear, and write down your reasoning for partial credit.

QUESTION 15A. Arrange the following values in increasing numeric order. Assume that x is an int with value 8192.

EOF
x & ~x
(signed char) 0x47F
x | ~x
1000
(signed char) 65535
The size of the stdio cache
-0x80000000
A possible answer might be “a < b < c = d < e < f < g < h.”


For each of the remaining questions, write one or more arguments that, when passed to the provided function, will cause it to return the integer 61 (which is 0x3d hexadecimal). Write the expected number of arguments of the expected types.

QUESTION 15B.

int f1(int n) {
    return 0x11 ^ n;
}

QUESTION 15C.

int f2(const char* s) {
    return strtol(s, NULL, 0);
}
QUESTION 15D. Your answer should be different from the previous answer.

int f3(const char* s) {
    return strtol(s, NULL, 0);
}
QUESTION 15E. For this problem, you will also need to define a global variable. Give its type and value.

f4:
    movl 4(%esp), %eax    # 4(%esp) is the first argument to the function
    andl $5, %eax
    addl %eax, %eax
    addl 8(%esp), %eax    # 8(%esp) is the second argument to the function
    movzbl y, %edx
    subl %edx, %eax
    ret
16. Sizes and alignments (12 points)
Assume a 32-bit x86 architecture unless explicitly told otherwise.

Write your assumptions if a problem seems unclear, and write down your reasoning for partial credit.

QUESTION 16A. Use the following members to create a struct of size 16. You will use each member exactly once, and char a comes first.

char a; (we’ve written this for you)
unsigned char b;
short c;
int d;
struct size_16 {
    char a;



};

QUESTION 16B. Repeat Question 16A, but create a struct with size 12.

struct size_12 {
    char a;



};
QUESTION 16C. Repeat Question 16A, but create a struct with size 8.

struct size_8 {
    char a;



};
Question 6D. Consider the following structs:

struct x {
    T x1;
    U x2;
};
struct y {
    struct x y1;
    V y2;
};
Give definitions for T, U, and V so that there is one byte of padding in struct x after x2, and two bytes of padding in struct y after y1.

17. Dynamic memory allocation (16 points)
QUESTION 17A. True or false?

free(NULL) is an error.
malloc(0) can never return NULL.
QUESTION 17B. Give values for sz and nmemb so that calloc(sz, nmemb) will always return NULL (on a 32-bit x86 machine), but malloc(sz * nmemb) might or might not return null.

Consider the following 8 statements. (p and q have type char*.)

free(p);
free(q);
p = q;
q = NULL;
p = (char*) malloc(12);
q = (char*) malloc(8);
p[8] = 0;
q[4] = 0;
QUESTION 17C. Put the statements in an order that would execute without error or evoking undefined behavior. Memory leaks count as errors. Use each statement exactly once. Sample answer: “abcdefgh.”


QUESTION 17D. Put the statements in an order that would cause one double-free error, and no other error or undefined behavior (except possibly one memory leak). Use each statement exactly once.

QUESTION 17E. Put the statements in an order that would cause one memory leak (one allocated piece of memory is not freed), and no other error or undefined behavior. Use each statement exactly once.

QUESTION 17F. Put the statements in an order that would cause one boundary write error, and no other error or undefined behavior. Use each statement exactly once.

18. Pointers and debugging allocators (12 points)
You are debugging some students’ m61 code from Problem Set 1. The codes use the following metadata:

typedef struct meta { ...
    struct meta* next;
    struct meta* prev;
} meta;

meta* mhead;    // head of active allocations list
Their linked-list manipulations in m61_malloc are similar.

void* m61_malloc(size_t sz, const char* file, int line) {
    ...
    meta* m = (meta*) ptr;
    m->next = mhead;
    m->prev = NULL;
    if (mhead)
        mhead->prev = m;
    mhead = m;
    ...
}
But their linked-list manipulations in m61_free differ.

Alice’s code:

void m61_free(void* ptr, ...) { ...  
    meta* m = (meta*) ptr - 1;
    if (m->next != NULL)
        m->next->prev = m->prev;
    if (m->prev == NULL)
        mhead = NULL;
    else
        m->prev->next = m->next;
    ...
}
Bob’s code:

void m61_free(void* ptr, ...) { ...  
    meta* m = (meta*) ptr - 1;
    if (m->next)
        m->next->prev = m->prev;
    if (m->prev)
        m->prev->next = m->next;
    ...
}
Chris’s code:

void m61_free(void* ptr, ...) { ...  
    meta* m = (meta*) ptr - 1;
    m->next->prev = m->prev;
    m->prev->next = m->next;
    ...
}
Donna’s code:

void m61_free(void* ptr, ...) { ...  
    meta* m = (meta*) ptr - 1;
    if (m->next)
        m->next->prev = m->prev;
    if (m->prev)
        m->prev->next = m->next;
    else
        mhead = m->next;
    ...
}
You may assume that all code not shown is correct.

QUESTION 18A. Whose code will segmentation fault on this input? List all students that apply.

int main() {
    void* ptr = malloc(1);
    free(ptr);
}

QUESTION 18B. Whose code might report something like “invalid free of pointer [ptr1], not allocated” on this input? (Because a list traversal starting from mhead fails to find ptr1.) List all students that apply. Don’t include students whose code would segfault before the report.

int main() {
    void* ptr1 = malloc(1);
    void* ptr2 = malloc(1);
    free(ptr2);
    free(ptr1);   // <- message printed here
}

QUESTION 18C. Whose code would improperly report something like “LEAK CHECK: allocated object [ptr1] with size 1” on this input? (Because the mhead list appears not empty, although it should be.) List all students that apply. Don’t include students whose code would segfault before the report.

int main() {
    void* ptr1 = malloc(1);
    free(ptr1);
    m61_printleakreport();
}
QUESTION 18D. Whose linked-list code is correct for all inputs? List all that apply.

19. Arena allocation (15 points)
Chimamanda Ngozi Adichie is a writing a program that needs to allocate and free a lot of nodes, where a node is defined as follows:

typedef struct node {
    int key;
    void* value;
    struct node* left;
    struct node* right;      // also used in free list
} node;
She uses a variant of the arena allocator we saw in Lectures 5 and 6. Here’s part of the code.

typedef struct arena_group {
    struct arena_group* next_group;
    node nodes[1024];
} arena_group;

typedef struct arena {
    node* frees;
    arena_group* groups;
} arena;

node* node_alloc(arena* a) {
    if (!a->frees) {
        arena_group* g = (arena_group*) malloc(sizeof(arena_group));
        // ... link g to a->groups ...
        for (size_t i = 0; i != 1023; ++i)
            g->nodes[i].right = &g->nodes[i + 1];
        g->nodes[1023].right = NULL;
        a->frees = &g->nodes[0];
    }
    node* n = a->frees;
    a->frees = n->right;
    return n;
}

void node_free(arena* a, node* n) {
    n->right = a->frees;
    a->frees = n;
}
QUESTION 19A. True or false?

This allocator never has external fragmentation.
This allocator never has internal fragmentation.
QUESTION 19B. Chimamanda’s frenemy Paul Auster notices that if many nodes are allocated right in a row, every 1024th allocation seems much more expensive than the others. The reason is that every 1024th allocation initializes a new group, which in turn adds 1024 nodes to the free list. Chimamanda decides instead to allow a single element of the free list to represent many contiguous free nodes. The average allocation might get a tiny bit slower, but no allocation will be much slower than average. Here’s the start of her idea:

node* node_alloc(arena* a) {
    if (!a->frees) {
        arena_group* g = (arena_group*) malloc(sizeof(arena_group));
        // ... link g to a->groups ...
        g->nodes[0].key = 1024;   // g->nodes[0] is the 1st of 1024 contiguous free nodes
        g->nodes[0].right = NULL;
        a->frees = &g->nodes[0];
    }
    node* n = a->frees;
    // ???
    return n;
}
Complete this function by writing code to replace // ???.


QUESTION 19C. Write a node_free function that works with the node_alloc function from the previous question.

void node_free(arena* a, node* n) {
}
QUESTION 19D. Complete the following new function.

// Return the arena_group containing node n. n must be a node returned by
// a previous call to node_alloc(a).
arena_group* node_find_group(arena* a, node* n) {
    for (arena_group* g = a->groups; g; g = g->next_group) {
    }
    return NULL;
}
QUESTION 19E. Chimamanda doesn’t like that the node_find_group function from Question 5D takes O(G) time, where G is the number of allocated arena_groups. She remembers a library function that might help, posix_memalign:

int posix_memalign(void** memptr, size_t alignment, size_t size);

The function posix_memalign() allocates size bytes and places the address of the allocated memory in *memptr. The address of the allocated memory will be a multiple of alignment, which must be a power of two and a multiple of sizeof(void *). ...

“Cool,” she says, “I can use this to speed up node_find_group!” She now allocates a new group with the following code:

arena_group* g;
int r = posix_memalign(&g, 32768, sizeof(arena_group));
assert(r == 0); // posix_memalign succeeded
Given this allocation strategy, write a version of node_find_group that takes O(1) time.

arena_group* node_find_group(arena* a, node* n) {
}
20. IO caching and strace (18 points)
Elif Batuman is investigating several program executables left behind by her ex-roommate Fyodor. She runs each executable under strace in the following way:

strace -o strace.txt ./EXECUTABLE files/text1meg.txt > files/out.txt
Help her figure out properties of these programs based on their system call traces.

QUESTION 20A. Program ./mysterya:

open("files/text1meg.txt", O_RDONLY)    = 3
brk(0)                                  = 0x8193000
brk(0x81b5000)                          = 0x81b5000
read(3, "A", 1)                         = 1
write(1, "A", 1)                        = 1
read(3, "\n", 1)                        = 1
write(1, "\n", 1)                       = 1
read(3, "A", 1)                         = 1
write(1, "A", 1)                        = 1
read(3, "'", 1)                         = 1
write(1, "'", 1)                        = 1
read(3, "s", 1)                         = 1
write(1, "s", 1)                        = 1
...
Circle at least one option in each column.

Sequential IO
Reverse sequential IO
Strided IO
No read cache
Unaligned read cache
Aligned read cache
No write cache
Write cache
Cache size 4096
Cache size 2048
Cache size 1024
Other
QUESTION 20B. Program ./mysteryb:

open("files/text1meg.txt", O_RDONLY)    = 3
brk(0)                                  = 0x96c5000
brk(0x96e6000)                          = 0x96e6000
read(3, "A\nA's\nAA's\nAB's\nABM's\nAC's\nACTH'"..., 2048) = 2048
write(1, "A\nA's\nAA's\nAB's\nABM's\nAC's\nACTH'"..., 2048) = 2048
read(3, "kad\nAkron\nAkron's\nAl\nAl's\nAla\nAl"..., 2048) = 2048
write(1, "kad\nAkron\nAkron's\nAl\nAl's\nAla\nAl"..., 2048) = 2048
...
Circle at least one option in each column.

Sequential IO
Reverse sequential IO
Strided IO
No read cache
Unaligned read cache
Aligned read cache
No write cache
Write cache
Cache size 4096
Cache size 2048
Cache size 1024
Other
QUESTION 20C. Program ./mysteryc:

open("files/text1meg.txt", O_RDONLY)    = 3
brk(0)                                  = 0x9064000
brk(0x9085000)                          = 0x9085000
fstat64(3, {st_mode=S_IFREG|0664, st_size=1048576, ...}) = 0
lseek(3, 1046528, SEEK_SET)             = 1046528
read(3, "ingau\nRheingau's\nRhenish\nRhianno"..., 2048) = 2048
write(1, "oR\ntlevesooR\ns'yenooR\nyenooR\ns't"..., 2048) = 2048
lseek(3, 1044480, SEEK_SET)             = 1044480
read(3, "Quinton\nQuinton's\nQuirinal\nQuisl"..., 2048) = 2048
write(1, "ehR\neehR\naehR\ns'hR\nhR\nsdlonyeR\ns"..., 2048) = 2048
lseek(3, 1042432, SEEK_SET)             = 1042432
read(3, "emyslid's\nPrensa\nPrensa's\nPrenti"..., 2048) = 2048
write(1, "\ns'nailitniuQ\nnailitniuQ\nnniuQ\ns"..., 2048) = 2048
lseek(3, 1040384, SEEK_SET)             = 1040384
read(3, "Pindar's\nPinkerton\nPinocchio\nPin"..., 2048) = 2048
write(1, "rP\ndilsymerP\ns'regnimerP\nregnime"..., 2048) = 2048
...
Circle at least one option in each column.

Sequential IO
Reverse sequential IO
Strided IO
No read cache
Unaligned read cache
Aligned read cache
No write cache
Write cache
Cache size 4096
Cache size 2048
Cache size 1024
Other
QUESTION 20D. Program ./mysteryd:

open("files/text1meg.txt", O_RDONLY)    = 3
brk(0)                                  = 0x9a0e000
brk(0x9a2f000)                          = 0x9a2f000
fstat64(3, {st_mode=S_IFREG|0664, st_size=1048576, ...}) = 0
lseek(3, 1048575, SEEK_SET)             = 1048575
read(3, "o", 2048)                      = 1
lseek(3, 1048574, SEEK_SET)             = 1048574
read(3, "Ro", 2048)                     = 2
lseek(3, 1048573, SEEK_SET)             = 1048573
read(3, "\nRo", 2048)                   = 3
...
lseek(3, 1046528, SEEK_SET)             = 1046528
read(3, "ingau\nRheingau's\nRhenish\nRhianno"..., 2048) = 2048
write(1, "oR\ntlevesooR\ns'yenooR\nyenooR\ns't"..., 2048) = 2048
lseek(3, 1046527, SEEK_SET)             = 1046527
read(3, "eingau\nRheingau's\nRhenish\nRhiann"..., 2048) = 2048
lseek(3, 1046526, SEEK_SET)             = 1046526
read(3, "heingau\nRheingau's\nRhenish\nRhian"..., 2048) = 2048
...
Circle at least one option in each column.

Sequential IO
Reverse sequential IO
Strided IO
No read cache
Unaligned read cache
Aligned read cache
No write cache
Write cache
Cache size 4096
Cache size 2048
Cache size 1024
Other
QUESTION 20E. Program ./mysterye:

open("files/text1meg.txt", O_RDONLY)    = 3
brk(0)                                  = 0x93e5000
brk(0x9407000)                          = 0x9407000
read(3, "A", 1)                         = 1
read(3, "\n", 1)                        = 1
read(3, "A", 1)                         = 1
...
read(3, "A", 1)                         = 1
read(3, "l", 1)                         = 1
write(1, "A\nA's\nAA's\nAB's\nABM's\nAC's\nACTH'"..., 1024) = 1024
read(3, "t", 1)                         = 1
read(3, "o", 1)                         = 1
read(3, "n", 1)                         = 1
...
Circle at least one option in each column.

Sequential IO
Reverse sequential IO
Strided IO
No read cache
Unaligned read cache
Aligned read cache
No write cache
Write cache
Cache size 4096
Cache size 2048
Cache size 1024
Other

QUESTION 20F. Program ./mysteryf:

open("files/text1meg.txt", O_RDONLY)    = 3
brk(0)                                  = 0x9281000
brk(0x92a3000)                          = 0x92a3000
read(3, "A\nA's\nAA's\nAB's\nABM's\nAC's\nACTH'"..., 4096) = 4096
write(1, "A", 1)                        = 1
write(1, "\n", 1)                       = 1
write(1, "A", 1)                        = 1
...
write(1, "A", 1)                        = 1
write(1, "l", 1)                        = 1
read(3, "ton's\nAludra\nAludra's\nAlva\nAlvar"..., 4096) = 4096
write(1, "t", 1)                        = 1
write(1, "o", 1)                        = 1
write(1, "n", 1)                        = 1
...
Circle at least one option in each column.

Sequential IO
Reverse sequential IO
Strided IO
No read cache
Unaligned read cache
Aligned read cache
No write cache
Write cache
Cache size 4096
Cache size 2048
Cache size 1024
Other
21. Processor cache (15 points)
The following questions use the following C definition for an NxM matrix (the matrix has N rows and M columns).

typedef struct matrix {
    unsigned N;
    unsigned M;
    double elt[0];
} matrix;

matrix* matrix_create(unsigned N, unsigned M) {
    matrix* m = (matrix*) malloc(sizeof(matrix) + N * M * sizeof(double));
    m->N = N;
    m->M = M;
    for (size_t i = 0; i < N * M; ++i)
        m->elt[i] = 0.0;
    return m;
}
Typically, matrix data is stored in row-major order: element mij (at row i and column j) is stored in m->elt[i*m->M + j]. We might write this in C using an inline function:

inline double* melt1(matrix* m, unsigned i, unsigned j) {
    return &m->elt[i * m->M + j];
}
But that’s not the only possible method to store matrix data. Here are several more.

inline double* melt2(matrix* m, unsigned i, unsigned j) {
    return &m->elt[i + j * m->N];
}

inline double* melt3(matrix* m, unsigned i, unsigned j) {
    return &m->elt[i + ((m->N - i + j) % m->M) * m->N];
}

inline double* melt4(matrix* m, unsigned i, unsigned j) {
    return &m->elt[i + ((i + j) % m->M) * m->N];
}

inline double* melt5(matrix* m, unsigned i, unsigned j) {
    assert(m->M % 8 == 0);
    unsigned k = (i/8) * (m->M/8) + (j/8);
    return &m->elt[k*64 + (i % 8) * 8 + j % 8];
}
QUESTION 21A. Which method (of melt1–melt5) will have the best processor cache behavior if most matrix accesses use loops like this?

for (unsigned j = 0; j < 100; ++j)
    for (unsigned i = 0; i < 100; ++i)
        f(*melt(m, i, j));
QUESTION 21B. Which method will have the best processor cache behavior if most matrix accesses use loops like this?

for (unsigned i = 0; i < 100; ++i)
    f(*melt(m, i, i));
QUESTION 21C. Which method will have the best processor cache behavior if most matrix accesses use loops like this?

for (unsigned i = 0; i < 100; ++i)
    for (unsigned j = 0; j < 100; ++j)
        f(*melt(m, i, j));
QUESTION 21D. Which method will have the best processor cache behavior if most matrix accesses use loops like this?

for (int di = -3; di <= 3; ++di)
    for (int dj = -3; dj <= 3; ++dj)
        f(*melt(m, I + di, J + dj));
QUESTION 21E. Here is a matrix-multiply function in ikj order.

matrix* matrix_multiply(matrix* a, matrix* b) {
    assert(a->M == b->N);
    matrix* c = matrix_create(a->N, b->M);
    for (unsigned i = 0; i != a->N; ++i)
        for (unsigned k = 0; k != a->M; ++k)
            for (unsigned j = 0; j != b->M; ++j)
                *melt(c, i, j) += *melt(a, i, k) * *melt(b, k, j);
}
This loop order is cache-optimal when data is stored in melt1 order. What loop order is cache-optimal for melt2?

QUESTION 21F. You notice that accessing a matrix element using melt1 is very slow. After some debugging, it seems like the processor on which you are running code has a very slow multiply instruction. Briefly describe a change to struct matrix that would let you write a version of melt1 with no multiply instruction. You may add members, change sizes, or anything you like.

22. Data Representation (10 points)
Sort the following expressions in ascending order by value, using the operators <, =, >. For example, if we gave you:

A. int i = 6;
B. int j = 0x6;
C. int k = 3;
you would write k < i = j or k < j = i.

a. unsigned char u = 0x191; truncated to 0x91 = 9*16+1 = 145
b. char c = 0x293; truncated to 0x92, but signed, so -0x6D
c. unsigned long l = 0xFFFFFFFF; That's 2^32 - 1
d. int i = 0xFFFFFFFF; That's -1
e. int j = i + 3; That's 2
f. 4 GB That's 2^32
g. short *s; sizeof(*s); That's 2
h. long l = 256; That's 256
i. (binary) 100000000000000000000000000000000000 2^36
j. unsigned long Q = 0xACE - 0x101; 0x9CD=2509
23. Memory (10 points)
For the following questions, select the part(s) of memory from the list below that best describes where you will find the object.

1. heap

2. stack

3. between the heap and the stack

4. in a read-only data segment

5. in a text segment starting at address 0x08048000

6. in a read/write data segment

7. in a register

Assume the following code, compiled without optimization.

#include
#include
const long maxitems = 1000;
struct info {
     char name[20];
     unsigned int age;
     short height;
} s = { "sushi", 1, 9 };
int
main(int argc, char *argv[])
{
     static long L = 0xbadf00d;
     unsigned long u = 0x8badf00d;
     int i, num = maxitems + 1;
     struct info *sp;
     printf("What did you do? %lx?\n", u);
     while (num > maxitems || num < 10) {
         printf("How much of it did you eat? ");
         scanf (" %d", &num);
     }
     sp = (struct info *)malloc(num * sizeof(*sp));
     for (i = 0; i < num; i++)
     sp[i] = s;

     return (0xdeadbeef);
}
Question 23A: The value 0xdeadbeef, when we are returning from main.

Question 23B: The variable maxitems

Question 23C:. The structure s

Question 23D: The structure at sp[9]

Question 23E: The variable u

Question 23F: main

Question 23G: printf

Question 23H: argc

Question 23I: The number the user enters

Question 23J: The variable L


24. Pot Pourri (10 points)
Question 24A: What does the following instruction place in %eax? sarl $31, %eax

Question 24B: True/False: A direct-mapped cache with N slots can handle any reference string with < N distinct addresses with no misses except for compulsory misses.

Question 24C: What is 1 (binary) TB in hexadecimal?

Question 24D: Write the answer to the following in hexadecimal: 0xabcd + 12

Question 24E: True/False: The garbage collector we discussed is conservative, because it only runs when we tell it to.

Question 24F: True/False: Given the definition int array[10] the following two expressions mean the same thing: &array[4] and array + 4.

Question 24G: Using the matrix multiply from lecture 12, in what order should you iterate over the indices i, j, and k to achieve the best performance.

Question 24H: True/False: fopen, fread, fwrite, and fclose are system calls.

Question 24I: Which do you expect to be faster (on the CS50 appliance): insertion sorting into a linked list of 1000 elements or into an array of 1000 elements?

Question 24J: What does the hardware do differently when adding signed versus unsigned numbers?

25. Assembly and Data Structures (23 points)
For each code sample below, indicate the most likely type of the data being accessed. (If multiple types are equally likely, just pick one.)

Question 25A: movzbl %al, %eax

Question 25B: movl -28(%ebp), %edx

Question 25C: movsbl -32(%ebp), %eax

Question 25D: movzwl -30(%ebp), %eax

For each code sample below, indicate the most likely data structure being accessed (assume that g_var is a global variable). Be as specific as possible.

Question 25E: movzwl 6(%edx, %eax, 12), %eax

Question 25F: movl (%edx, %eax, 4), %eax

Question 24G:

movzbl 4(%eax), %eax
movsbl %al, %eax
For the remaining questions, indicate for what values of the register contents will the jump be taken. Question 25H: xorl %eax, %eax

jge LABEL
Question 25I: testb $1, %eax

jne
Question 25J: cmpl %edx, %eax

jlt LABEL
26. Caching - part I (5 points)
Assume that we have a cache that holds four pages. Assume that each letter below indicates an access to a page. Answer the following questions as they pertain to the following sequence of accesses.

E D C B A E D A A A B C D E 
Question 26A: What is the hit rate assuming an LRU replacement policy?

Question 26B: What pages will you have in the cache at the end of the run?

Question 26C: What is the best possible hit rate attainable if you could see into the future?

27. Caching - part II (12 points)
Intel and CrossPoint have announced a new persistent memory technology with performance approaching that of DRAM. Your job is to calculate some performance metrics to help system architectects decide how to best incorporate this new technology into their platform.

Let's say that it takes 64ns to access one (32-bit) word of main memory (DRAM) and 256ns to access one (32-bit) word of this new persistent memory, which we'll call NVM (non-volatile memory). The block size of the NVM is 256 bytes. The NVM designers are quite smart and although it takes a long time to access the first byte, when you are accessing NVM sequentially, the devices perform read ahead and stream data efficiently -- at 32 GB/second, which is identical to the bandwidth of DRAM.

Question 27A: Let's say that we are performing random accesses of 32 bits (on a 32-bit processor). What fraction of the accesses must be to main memory (as opposed to NVM) to achieve performance within 10% of DRAM?


Question 27B: Let's say that they write every byte of a 256 block in units of 32 bits. How much faster will write-back cache perform relative to a write-through cache? (An approximate order of magnitude will be sufficient; showing work can earn partial credit.)


Question 27C: Why might you not want to use a write-back cache?

28. Memory and Pointers (12 points)
If multiple processes are sharing data via mmap, they may have the file mapped at different virtual addresses. In this case, pointers to the same object will have different values in the different processes. One way to store pointers in mmapped memory so that multiple processes can access them consistently is using relative pointers. Rather than storing a regular pointer, you store the offset from the beginning of the mmapped region and add that to the address of the mapping to obtain a real pointer. An alternative representation is called selfrelative pointers. In this case, you store the difference in address between the current location (i.e., the location containing the pointer) and the location to which you want to point. Neither representation addresses pointers between the mmapped region and the rest of the address space; you may assume such pointers do not exist.

Question 28A: State one advantage that relative pointers have over self-relative pointers.


Question 28B: State one advantage that self-relative pointers have over relative pointers.


For the following questions, assume the following setup:

char *region; /* Address of the beginning of the region. */
/*
 * The following are sample structures you might find in
 * a linked list that you are storing in an mmaped region.
 */
struct ll1 {
     unsigned value;
     TYPE1 r_next; /* Relative Pointer. */
};
struct ll2 {
     unsigned value;
     TYPE2 sr_next; /* Self-Relative Pointer. */
};
struct ll1 node1;
struct ll2 node2;
Question 28C: Propose a type for TYPE1 and give 1 sentence why you chose that type.


Question 28D: Write a C expression to generate a (properly typed) pointer to the element referenced by the r_next field of ll1.


Question 28E: Propose a type for TYPE2 and give 1 sentence why you chose that type.


Question 28F: Write a C expression to generate a (properly typed) pointer to the element referenced by the sr_next field of ll2.

