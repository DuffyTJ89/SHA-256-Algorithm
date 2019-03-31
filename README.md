# SHA-256 Hashing Algorithm
C program to perform the Secure Hash Algorithm (SHA) algorithm, specifically the 256-bit version known as SHA-256.

SHA-2 (Secure Hash Algorithm 2) is a set of cryptographic hash functions designed by the United States National Security Agency (NSA). The SHA-2 family consists of six hash functions with digests (hash values) that are 224, 256, 384 or 512 bits

SHA-256 and SHA-512 are novel hash functions computed with 32-bit and 64-bit words, respectively. This project is the SHA-256 version.

The algorithm works on an empty file. As such I have commented out the check for empty file.

Example : 
Using https://www.xorbin.com/tools/sha256-hash-calculator 
the empty file returns a hash of :
e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855

***insert pic here***

![alt text](https://raw.githubusercontent.com/DuffyTJ89/SHA-256-Algorithm/master/pics/emptyOnline.PNG)

and using this program we get the same hash result :

![alt text](https://raw.githubusercontent.com/DuffyTJ89/SHA-256-Algorithm/master/pics/emptyFileMyProgram.PNG)
