# Write three simple and small module programs.

1. hello1.c: Use module_init() and module_exit() macros. The /var/log/message file will show 
   "My Name: Loading Hello1 module - Hello World 1" 
   "My Name: Exiting Hello1 module - Goodbye World 1"
   
2. hello2.c: Use module_init(), module_exit(), __init, __exit macros, and __initdata. The /var/log/message file will show 
   "My Name: Loading Hello2 module - Hello World 2" 
   "My Name: Exiting Hello2 module - Goodbye World 2"
   Print the number "2" using "__initdata."
   
3. hello3.c: passing command line arguments using MODULE_PARM() macro.
   Try to print some numbers and strings such as
   [/var/log/messages]
   ...
   #kernel: Loading Hello 3: Hello World 3
   #kernel: ==============================
   #kernel: Name : My Name
   #kernel: Street : 123 My Way 
   #kernel: City : North Newark
   #kernel: ZIP code : 98765
   ...

Insert a module using "/sbin/insmod hello{1..3}.ko." Note that the dot after ko is not meant to be a part of the command (it's part of the sentence).
Each time you insert it will print whatever you included in the module will be printed to console or /var/log/messages.

for example:
    $ sudo insmod hello{1..3}.ko
    $ sudo tail -f /var/log/messages or sudo dmesg
    $ sudo rmmod hello{1..3}
    $ sudo tail -f /var/log/messages or sudo dmesg	
