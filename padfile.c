#include <stdio.h>
#include <stdint.h>
//#include <errno.h> //https://www.tutorialspoint.com/cprogramming/c_error_handling.htm

union msgblock { //all members of union occupy the chunk of memory
  uint8_t   e[64]; //unassigned 64  8 bit ints
  uint32_t  t[16]; //unassigned 16  32 bit ints
  uint64_t  s[8];  //unassigned 8   64 bit ints
};

enum status {READ, PAD0, PAD1, FINISH}; //use for flags for the status of where the code has run when padding the message

int nextMessageBlock (int argc, char *argv[]){

  union msgblock M;
  uint64_t numBits = 0;
  uint64_t numBytes; //number of bytes that f read returns back
  enum status S = READ; //variable that is an enum type set to read
  FILE* f;

  f = fopen(argv[1],"r");

  int i;

  if (f == NULL) {
        
    printf("Error opening file");

  }else{

    while (S == READ){ //while the flag is set to READ keep looping
     numBytes =  fread(M.e, 1, 64, f); //try to read 64 bits from the file and put them in message block M.e
     //numBytes will keep increasing everytime there is a read from the file, will keep track of all the bytes read. 
    
     printf("Read %2llu bytes\n", numBytes);


     numBits = numBytes + (numBytes + 8);  //Keep track of the num of bits read so far.  numBits will be a number between 0 and 64,
     if (numBytes < 56){ //if there is enough room in the message block to do all of the padding
        printf("I've found a block with less than 55 bytes.\n");
        //M.e[numBytes] = 0x01; //in first position. How this int is stored?
        //Warn look out for little and big endian
        M.e[numBytes] = 0x80;

        while(numBytes < 56){
          numBytes = numBytes +1;
          M.e[numBytes]=0x00;
        }//end while

        M.s[7] = numBits; //set the last element to numBits //TODO make sure this is big enden 
        S = FINISH; //change flag to finish to break loop
     }else if (numBytes < 64){
        //if you can add some info to the current message block but not all of the padding, append the 1 and fill it with 0s
        S = PAD0; 
        M.e[numBytes] = 0x80;
        while (numBytes < 64){
          numBytes = numBytes + 1;
          M.e[numBytes] = 0x00;
        }//end while
      }else if (feof(f)){ //finished reading everything in the file and it is a multiple of 512 in length
        S = PAD1;
      }


     //printf("%llu\n", numBytes);
    }//end while S == READ
  }//end else

  if(S == PAD0 || S == PAD1){
    for(i = 0; i < 56; i++){
      M.e[i] = 0x00;
    }
    M.s[7] = numBits;
  }
  if(S == PAD1){ //first bit of the last message block has to be 0 for PAD0 and 1 for PAD1
    M.e[0] = 0x80;
  }//end if

  fclose(f);

  for (int i = 0; i < 64; i++)
          printf("%x ", M.e[i]);// print all the elements of M as 64 individual bytes in Hex
  printf("\n");


  return 0;
}
