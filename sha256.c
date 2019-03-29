// Thomas Duffy, 2019
// The secure hash alorithm 256 bit verion
// 

#include <stdio.h> // input/output header file
#include <stdint.h> // fixed bit length integers

#define SWAP_UINT32(x) (((x) >> 24) | (((x) & 0x00FF0000) >> 8) | (((x) & 0x0000FF00) << 8) | ((x) << 24));

#define Ch(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
#define Maj(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x) (rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22))
#define EP1(x) (rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25))
#define SIG_0(x) (rotr(x, 7) ^ rotr(x, 18) ^ ((x) >> 3))
#define SIG_1(x) (rotr(x, 17) ^ rotr(x, 19) ^ ((x) >> 10))
#define SWAP_UINT32(x) (((x) >> 24) | (((x) & 0x00FF0000) >> 8) | (((x) & 0x0000FF00) << 8) | ((x) << 24))

//Represents a message block
union msgblock { //all members of union occupy the same chunk of memory
  uint8_t   e[64]; //unassigned 64  8 bit ints
  uint32_t  t[16]; //unassigned 16  32 bit ints
  uint64_t  s[8];  //unassigned 8   64 bit ints
};

//use for flags for the status of where the code has run when padding the message
enum status {READ, PAD0, PAD1, FINISH}; // see sections 4.1.2 for definitions

//uint32_t sig0(uint32_t x);
//uint32_t sig1(uint32_t x);

//uint32_t SIG0(uint32_t x);
//uint32_t SIG1(uint32_t x);

//uint32_t Ch(uint32_t x, uint32_t y, uint32_t z);
//uint32_t Maj(uint32_t x, uint32_t y, uint32_t z);

// see section 3.2 for defintions
// uint32_t rotr(uint32_t n, uint32_t x);
// uint32_t shr(uint32_t n, uint32_t x);

//calculate the SHA256 hash of a given file
void sha256(FILE *f);

int nextMessageBlock(FILE *msgf, union msgblock *M, enum status *S, uint64_t *numBits);

//main run of the program. program starts here
int main (int argc, char *argv[]){

  FILE* msgf;
  msgf = fopen(argv[1],"r");

  if (msgf == NULL) {     
    printf("Error opening file");
  }else{
    sha256(msgf); //call function to run secure hash algorithm on the file
  }//end else
  fclose(msgf); //close the file when finished with it
  return 0;
}//end main

void sha256(FILE *msgf){
  
  union msgblock M; //the current message block
  uint64_t numBits = 0; //the number of bits read from the file
  enum status S = READ; //variable that is an enum type set to read. Used to tell the status

 //the K constants, defined in section 4.2.2
 uint32_t K[] = {
  0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
  0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
  0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
  0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
  0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
  0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
  0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
  0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
  0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
  0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
  0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
  0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
  0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
  0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
  0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
  0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
 };       

 uint32_t W[64]; //message schedule (section 6.2)
 uint32_t a, b, c , d, e, f, g, h; //working variables (section 6.2)
 uint32_t T1, T2; // two temporary variables (section 6.2)

 uint32_t H[8]= { //the hash value (section 6.2), the values come from section (5.3.3).   
    0x6a09e667
  , 0xbb67ae85
  , 0x3c6ef372
  , 0xa54ff53a
  , 0x510e527f
  , 0x9b05688c
  , 0x1f83d9ab
  , 0x5be0cd19 
 };

 //for looping
 int t, i;

 //for (i = 0; i < 1; i++){ //message blocks loop. See page 22.

 while (nextMessageBlock(msgf, &M, &S, &numBits)){
    //from page22, W[t] = M[t] for 0<= t >= 15
    for (t = 0; t < 16;t++){
      //W[t] = M.t[t];
      W[t] = SWAP_UINT32(M.th[t]);
    }

    //from page22, W[t] = ... equation in 6.2.2 part 1
    for (t = 16; t < 64; t++)
      W[t] =  SIG_1(W[t-2]) + W[t-7] + SIG_0(W[t-15]) + W[t-16];

    //initialise a, b, c ... h as per step 2, page 22
    a = H[0]; b = H[1]; c = H[2]; d = H[3]; 
    e = H[4]; f = H[5]; g = H[6]; h = H[7];

    //step 3
    for (t = 0; t < 64; t++){
      //see section 4.1.2 for Ch and Maj
      T1 = h + EP1(e) + Ch(e, f, g) + K[t] + W[t];
      T2 = EP0(a) + Maj(a,b,c);
      h = g;
      g = f;
      f = e;
      e = d + T1;
      d = c;
      c = b;
      b = a;
      a = T1 + T2;
    }//end for

   //step 4
    H[0] = a + H[0]; H[1] = b + H[1];
    H[2] = c + H[2]; H[3] = d + H[3];
    H[4] = e + H[4]; H[5] = f + H[5];
    H[6] = g + H[6]; H[7] = h + H[7];

 }//end message blocks while loop

  printf ("%08x %08x %08x %08x %08x %08x %08x %08x\n ", H[0], H[1], H[2], H[3], H[4], H[5], H[6], H[7]);

}//end sha256()

/*
uint32_t rotr(uint32_t n, uint32_t x){
  return (x >> n) | (x << (32 - n));

}//end rotr
uint32_t shr(uint32_t n, uint32_t x){
 return (x >> n);

}//end shr


//can use macros???

uint32_t sig0(uint32_t x){
 //see section 3.2 and 4.1.2  for definitions
 return (rotr(7, x) ^ rotr (18, x) ^ shr (3, x));
}//end sig0
uint32_t sig1(uint32_t x){
 //see section 3.2 and 4.1.2  for definitions
 return (rotr(17, x) ^ rotr (19, x) ^ shr (10, x));
}//end sig1

uint32_t SIG0(uint32_t x){
 return (rotr(2, x) ^ rotr (13, x) ^ rotr (22, x));
}
uint32_t SIG1(uint32_t x){
 return (rotr(6, x) ^ rotr (11, x) ^ rotr (25, x));
}

uint32_t Ch(uint32_t x, uint32_t y, uint32_t z){
 return ((x & y) ^ ((!x) & z));
}
uint32_t Maj(uint32_t x, uint32_t y, uint32_t z){
 return ((x & y) ^ (x & z) ^ (y & z));
}
*/

int nextMessageBlock(FILE *msgf, union msgblock *M, enum status *S, uint64_t *numBits){

  uint64_t numBytes; //number of bytes that f read returns back
  
  int i; //for looping

  //if we have finished all the message blocks, then S should be Finish
  if(*S == FINISH){
    return 0;
  }//end if Finish

  //otherwise, check if we need another block full of padding
  if(*S == PAD0 || *S == PAD1){
    for(i = 0; i < 56; i++){ //set the first 56bytes to all zero bits
      M->e[i] = 0x00;
    }//end for
    M->s[7] = *numBits; //set the last 64 bits to the number of bits in the file //TODO (should be big endian)
    *S = FINISH; //set flag to finish 

    if(*S == PAD1){ //first bit of the last message block has to be 0 for PAD0 and 1 for PAD1
      M->e[0] = 0x80;
    }//end if
    return 1; //keep the loop in sha256 going for one more iteration
  }//end if pad 0 or 1

  //If we get down here we haven't finished reading the file. So (S == READ)
  numBytes =  fread(M->e, 1, 64, msgf); //try to read 64 bits from the file and put them in message block M.e
  //numBytes will keep increasing everytime there is a read from the file, will keep track of all the bytes read. 
    
  *numBits = *numBits + (numBytes * 8);  //Keep track of the num of bits read so far.  numBits will be a number between 0 and 64,
  if (numBytes < 56){ //if there is enough room in the message block to do all of the padding
      printf("I've found a block with less than 55 bytes.\n");
      //Warn look out for little and big endian
      //add the one bit as per the standard
      M->e[numBytes] = 0x80;
      //add zero bits until the last 64 bits
      while(numBytes < 56){
        numBytes = numBytes +1;
        M->e[numBytes]=0x00;
      }//end while
      
      M->s[7] = *numBits; //append the file size in bits as a (//TODO should be big endian) unsigned 64 bit int 
      *S = FINISH; //change flag to finish to break loop
  //otherwise check if we can add some padding into this message block
  }else if (numBytes < 64){
    //tell S we need another message block with padding but no one bit.
    *S = PAD0; 
    //put the one bit into the current block
    M->e[numBytes] = 0x80;
    //pad the rest of the block with zero bits 
    while (numBytes < 64){
      numBytes = numBytes + 1;
      M->e[numBytes] = 0x00;
    }//end while
  }else if (feof(msgf)){ //finished reading everything in the file and it is a multiple of 512 in length
    *S = PAD1; //tell S we need a message block with all the padding
  }
  return 1;// return 1 so this function is called again
}//end while S == READ
