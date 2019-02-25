// Thomas Duffy, 2019
// The secure hash alorithm 256 bit verion
// 

#include <stdio.h> // input/output header file
#include <stdint.h> // fixed bit length integers

void sha256();

// see sections 4.1.2 for definitions
uint32_t sig0(uint32_t x);
uint32_t sig1(uint32_t x);

// see section 3.2 for defintions
uint32_t rotr(uint32_t n, uint32_t x);
uint32_t shr(uint32_t n, uint32_t x);

int main {int argc, char *argv[]){

 sha256(); //call function

 return 0;
}//end main

void sha256(){

 uint32_t W[64]; //message schedule (section 6.2)
 uint32_t a, b, c , d, e, f, g, h; //working variables (section 6.2)
 uint32_t T1, T2; // two temporary variables (section 6.2)

 uint32_t H[8]= { //the hash value (section 6.2), the values come from section (5.3.3) 
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
 uint32_t M [16];

 //for looping
 int t;

 //from page22, W[t] = M[t] for 0<= t >= 15
 for (t=0; t<16;t++)
    W[t] = M[t];

 //from page22, W[t] = ... equation in 6.2.2 part 1
 for (t=16; t<64; t++)
    sig1(W[t-2] + W[t-7] + sig0(W[t-15]) + W[t-16];

  //initialise a, b, c ... h as per step 2, page 22
  a = H[0]; b = H[1]; c = H[2]; d = H[3]; e = H[4]; f = H[5]; g = H[6]; h = H[7];

  //step 3
  for (t=0; t<64; t++){
    //see section 4.1.2 for Ch and Maj
    T1 = h + SIG_1(e) + Ch(e, f, g) + K[t] + W[t];
    T2 = SIG_0(a) + Maj(a,b,c);
    h = g;
    g = f;
    f = e;
    e = d + T1;
    d = c;
    c = b;
    b = a;
    a = T1 + T2;


   //step 4
    H[0] = a + H[0];
    H[1] = b + H[1];
    H[2] = c + H[2];
    H[3] = d + H[3];
    H[4] = e + H[4];
    H[5] = f + H[5];
    H[6] = g + H[6];
    H[7] = h + H[7];

  }//end for

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


