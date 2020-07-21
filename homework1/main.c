
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline char * sub_string(char *dst, char *src, int s_indx, int e_indx)
{
  int len = e_indx - s_indx;
  int i = 0;
  if (len <= 0)
      return NULL;
  
  while (i < len && *(src + s_indx + i)) {
    *(dst + i) = *(src + s_indx + i);
    i++;
  }
  dst[i] = '\0';
  
  return dst;
}

static inline char * asm_sub_string(char *dst, char *src, int s_indx, int e_indx)
{
  int len = e_indx - s_indx;
  
  /*
   * cld: Clears the DF flag in the EFLAGS register. When the DF flag is set to 0, string operations increment the index registers (ESI and/or EDI).
   * rep: Repeat String Operation Prefix, CX/ECX/RCX register store count.
   * movsb: Move Data(one byte) from String(ES:DI) to String(DS:SI).
   * "S": SI register, "D": DI register, "c": CX/ECX/RCX register.
   */
  __asm__ __volatile__("cld \n\t" 
		       "rep \n\t"
		       "movsb \n\t"
		       :
		       :"S"(src + s_indx), "D"(dst), "c"(len)
		       :
		       );

  dst[len] = '\0';
  
  return dst;
}

int main(int argc, char **argv)
{
  char *src, *dst;  
  char *d1, *d2;
  int s_indx, e_indx;  
  int ret = 0;

  if (argc < 4) {
    printf ("Usage: %s \"src\" s_indx e_indx", argv[0]);
    return ret;
  }
  
  src = argv[1];
  s_indx = atoi(argv[2]);
  e_indx = atoi(argv[3]);

  if (NULL == (dst = (char *)malloc(strlen(src) + 1)))
    return ret;  
  
  d1 = sub_string(dst, src, s_indx, e_indx);  
  printf ("%s\n", d1);
  d2 = asm_sub_string(dst, src, s_indx, e_indx);
  printf ("%s\n", d2);
  
  free (dst);
  
  return d1 == d2;
}
  
