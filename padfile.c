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
  uint64_t numBits = 0;
  uint64_t numBytes;
  FILE* f;

  f = fopen(argv[1],"r");

  if (f == NULL) {
        
    printf("Error opening file");

  }else{

    while (!feof(f)){
     numBytes =  fread(M.e, 1, 64, f);
     //numBytes will keep increasing everytime there is a read from the file, will keep track of all the bytes read. 
     //numBits will be a number between 0 and 64,
     numBits = numBytes + (numBytes + 8);
     if (numBytes < 56){ //if there is enough room in the message block to do all of the padding
        printf("I've found a block with less than 55 bytes.\n");
        //M.e[numBytes] = 0x01; //in first position. How this int is stored?
        //Warn look out for little and big endian
        M.e[numBytes] = 0x80;

        while(numBytes < 56){
          numBytes = numBytes +1;
          M.e[numBytes]=0x00;
        }//end while

        M.s[7] = numBits; //set the last element to numBits 
        
     }//end inner if
     //printf("%llu\n", numBytes);
    }
  }//end else
  fclose(f);

  for (int i = 0; i < 64; i++)
          printf("%x ", M.e[i]);// print all the elements of M as 64 individual bytes in Hex
  printf("\n");


  return 0;
}
