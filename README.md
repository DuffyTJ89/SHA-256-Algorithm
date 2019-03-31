# SHA-256 Hashing Algorithm
This is a C program to perform the Secure Hash Algorithm (SHA) algorithm, specifically the 256-bit version known as SHA-256.
SHA-2 (Secure Hash Algorithm 2) is a set of cryptographic hash functions designed by the United States National Security Agency (NSA). The SHA-2 family consists of six hash functions that are 224, 256, 384 or 512 bits

This project is the SHA-256 version.

# Setup and Install to run this program

### Installation to run c files
- Windows - www.mingw.org
Linux run command
```sh
sudo apt-get install build-essential
```
### Run
To compile -
```sh
gcc SHA256.c -o SHA256
```
To run - 
```sh
./SHA256 testFile.txt
```

The algorithm works on an empty file. As such I have commented out the check for empty file.

Example : 
Using https://www.xorbin.com/tools/sha256-hash-calculator 

the empty file returns a hash of :

e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855

Seen here:

![alt text](https://raw.githubusercontent.com/DuffyTJ89/SHA-256-Algorithm/master/pics/emptyOnline.PNG)

and using this program we get the same hash result :

![alt text](https://raw.githubusercontent.com/DuffyTJ89/SHA-256-Algorithm/master/pics/emptyFileMyProgram.PNG)

## Single Character

#### The program doesn't work when using a text file with just a single character in it. It does return a hash but the value isn't correct.

Using https://www.xorbin.com/tools/sha256-hash-calculator


![alt text](https://raw.githubusercontent.com/DuffyTJ89/SHA-256-Algorithm/master/pics/singleCharOnline.PNG)


Using https://emn178.github.io/online-tools/sha256_checksum.html

![alt text](https://raw.githubusercontent.com/DuffyTJ89/SHA-256-Algorithm/master/pics/singleCharOnline2.PNG)

#### Both have the same output, but this program returns

![alt text](https://raw.githubusercontent.com/DuffyTJ89/SHA-256-Algorithm/master/pics/singleChar.PNG)

### Author
Thomas Duffy
