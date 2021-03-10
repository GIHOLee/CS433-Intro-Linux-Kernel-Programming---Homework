# Writing Your Own Exception/Interrupt Handler

* Write an "Assembly handler" and a correspodning "C handler."
* Try to follow the steps below and also the ones discussed in class yesterday:
    - Obtain the IDT table address using inline assembly. See store_idt()/load_idt() for loading and storing the IDT base address.
    - Replace the high and low address of IDT entry n with the new high/low address, where n is an exception number.
    - The new high and low address that would go into the IDT entry will be defined by your own assembly handler.
    - Write your own assembly handler. Use this handler address as the new high & low in IDT.
    - Your assembly handler will call your own C handler.
    - Your C handler will print or do something to indicate that your C handler is activated.
    - Your C handler will terminate normally and return to your assembly handler.
    - Upon returning from your C handler, your assembly handler will jump to the original asm handler.
    - Find the original C handler address from System.map.
* The following statments in your application will generate a "divide error" exception with the message "Floating point exception."

``` c
    int i=1, j=0;
    printf("%d",i/j);

```
  
Make sure to include some print statements to indicate that the handler is activated.
Include your name and the nature of the exception/interrupt along with the condition(s) that triggered the event if possible.
The above example is one of many possibilities. Check the web for more references and try several different techniques if your time allows.

1. KERNEL_SRC/arch/x86/include/asm/traps.h: declare 'my_divide_error' function.

``` c
asmlinkage void my_divide_error(void); // ++
```

2. KERNEL_SRC/arch/x86/kernel/traps.c: define 'do_my_divide_error' function and modify 'X86_TRAP_DE' to 'my_divide_error'.

``` c
DO_ERROR(X86_TRAP_DE,     SIGFPE,  FPE_INTDIV,   IP, "my divide error",     my_divide_error) // ++
```

``` c
void __init trap_init(void)
{
	/* Init cpu_entry_area before IST entries are set up */
	setup_cpu_entry_areas();

	idt_setup_traps();

	idt_setup_trap_my_divide_error(); // ++
	...
}

```

3. KERNEL_SRC/arch/x86/include/asm/desc.h: declare 'idt_setup_trap_my_divide_error' function.

``` c
extern void idt_setup_trap_my_divide_error(void); // ++
```

4. KERNEL_SRC/arch/x86/kernel/idt.c: define 'idt_setup_trap_my_divide_error' function.

``` c
// ++
void __init idt_setup_trap_my_divide_error()
{
	gate_desc desc;
	struct idt_data t = INTG(X86_TRAP_DE, my_divide_error);
	idt_init_desc(&desc, &t);
	write_idt_entry(idt_table, t.vector, &desc);
	set_bit(t.vector, system_vectors);
}
// ++

```

5. KERNEL_SRC/arch/x86/entry/entry_64.S: add idtenty.

``` c
idtentry my_divide_error		do_my_divide_error		has_error_code=0 // ++
```

6. application test:

``` c
#include <stdio.h>

int main(int argc, char **argv)
{
  int i = 1, j = 0;
  printf("%d\n", i/j);
  return 0;
}

```

