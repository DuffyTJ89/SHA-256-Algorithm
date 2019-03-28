// Thomas Duffy, 2019
// The secure hash alorithm 256 bit verion
// 

#include <stdio.h> // input/output header file
#include <stdint.h> // fixed bit length integers

void sha256();

union msgblock { //all members of union occupy the chunk of memory
  uint8_t   e[64]; //unassigned 64  8 bit ints
  uint32_t  t[16]; //unassigned 16  32 bit ints
  uint64_t  s[8];  //unassigned 8   64 bit ints
};

enum status {READ, PAD0, PAD1, FINISH}; //use for flags for the status of where the code has run when padding the message// see sections 4.1.2 for definitions

uint32_t sig0(uint32_t x);
uint32_t sig1(uint32_t x);

uint32_t SIG0(uint32_t x);
uint32_t SIG1(uint32_t x);

uint32_t Ch(uint32_t x, uint32_t y, uint32_t z);
uint32_t Maj(uint32_t x, uint32_t y, uint32_t z);

// see section 3.2 for defintions
uint32_t rotr(uint32_t n, uint32_t x);
uint32_t shr(uint32_t n, uint32_t x);

int main (int argc, char *argv[]){

 sha256(); //call function

 return 0;
}//end main

void sha256(){

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

 //the current message block
 uint32_t M [16] = {0, 0, 0, 0, 0, 0, 0, 0};

 //for looping
 int t, i;

 for (i=0; i<1; i++){ //message blocks loop. See page 22.

 //from page22, W[t] = M[t] for 0<= t >= 15
 for (t=0; t<16;t++)
    W[t] = M[t];

 //from page22, W[t] = ... equation in 6.2.2 part 1
 for (t=16; t<64; t++)
   W[t] =  sig1(W[t-2]) + W[t-7] + sig0(W[t-15]) + W[t-16];

  //initialise a, b, c ... h as per step 2, page 22
  a = H[0]; b = H[1]; c = H[2]; d = H[3]; e = H[4]; f = H[5]; g = H[6]; h = H[7];

  //step 3
  for (t=0; t<64; t++){
    //see section 4.1.2 for Ch and Maj
    T1 = h + SIG1(e) + Ch(e, f, g) + K[t] + W[t];
    T2 = SIG0(a) + Maj(a,b,c);
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
    H[0] = a + H[0];
    H[1] = b + H[1];
    H[2] = c + H[2];
    H[3] = d + H[3];
    H[4] = e + H[4];
    H[5] = f + H[5];
    H[6] = g + H[6];
    H[7] = h + H[7];

 }//end message blocks loop

  printf ("%x %x %x %x %x %x %x %x\n ", H[0], H[1], H[2], H[3], H[4], H[5], H[6], H[7]);

}//end sha256()

uint32_t rotr(uint32_t n, uint32_t x){
 return (x >> n) | (x << (32 - n));

}//end rotr
uint32_t shr(uint32_t n, uint32_t x){
 return (x >> n);

}//end shr



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
