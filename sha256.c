// Thomas Duffy, 2019
// The secure hash alorithm 256 bit verion
// 

#include <stdio.h> // input/output header file
#include <stdint.h> // fixed bit length integers

void sha256();


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

}//end sha256()
