#include <stdio.h>
#include <stdint.h>
//#include <errno.h> //https://www.tutorialspoint.com/cprogramming/c_error_handling.htm

union msgblock {
  uint8_t   e[64];
  uint32_t  t[16];
  uint64_t  s[8]; 
};

int main (int argc, char *argv[]){

  union msgblock M;
  uint64_t numBytes;
  FILE* f;

  f = fopen(argv[1],"r");

  if (f == NULL) {
        
    printf("Error opening file");

  }else{

    while (!feof(f)){
     numBytes =  fread(M.e, 1, 64, f);
     printf("%llu\n", numBytes);
    }
  }
  fclose(f);

  return 0;
}
