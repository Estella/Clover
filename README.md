# Clover
![Clover Cipher](/clover_cipher.png)

## Clover Metamorphic Block Cipher
Clover is a lightweight metamorphic cipher based off the alleged "Red Pike" cipher from [GCHQ](https://en.wikipedia.org/wiki/Red_Pike_(cipher)), modified the cipher to be 128bit block and 128bit key to reduce the chances of birthday attacks via the [Sweet32](https://sweet32.info) method. The metamorphic crypto logic unit (CLU) is based off Magdy M. Saeb's work in the field of metamorphic encryption: [Stone Cipher](https://www.researchgate.net/publication/49588683_The_Stone_Cipher-192_SC-192_A_Metamorphic_Cipher), however the metamorphism are units of uint32_t WORD's vs uint8_t BYTE's or bit level. Metamorphic engines can easily be adapted to fit into feedback chains and be introduced to handle data at different levels to achieve a wide array of mixing.

## Compiling
```
[estella@mystagic.ca(~/projects/clover)]> gcc -O2 clover.c -o clover

[estella@mystagic.ca(~/projects/clover)]> file clover
clover: ELF 64-bit LSB shared object, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=a00cec8affa67af1fb1206f0277b9918edb95c50, not stripped

[estella@mystagic.ca(~/projects/clover)]> ./clover 
CLOVER Cipher, R: 17 (rounds)
K : 00000000 00000000 00000000 00000000
P1: 00000000 00000000 00000000 00000000
C : 4B190469 CEA634DC C9DB1A66 47ABF759
P2: 00000000 00000000 00000000 00000000
```
