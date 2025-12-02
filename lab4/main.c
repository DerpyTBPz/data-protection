#include <openssl/evp.h> // FOR CODEWARS, CHANGE TO <openssl/md5.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void crack(const char *md5_hash, char pin[5 + 1]) 
{
    unsigned char target_digest[16]; 
    unsigned char current_digest[16];
    char candidate[6]; 

    for (int i = 0; i < 16; i++) 
    {
        int temp;
        sscanf(&md5_hash[i * 2], "%2x", &temp);
        target_digest[i] = (unsigned char)temp;
    }

    for (int i = 0; i < 100000; i++) 
    {
        sprintf(candidate, "%05d", i);
        // FOR CODEWARS, CHANGE TO MD5((unsigned char*)candidate, 5, current_digest);
        EVP_Digest((unsigned char*)candidate, 5, current_digest, NULL, EVP_md5(), NULL); 
        if (memcmp(target_digest, current_digest, 16) == 0) 
        {
            strcpy(pin, candidate);
            return;
        }
    }
}

int main()
{
    char PIN[] = "12345";
    char md5_hash[] = "827ccb0eea8a706c4c34a16891f84e7b";
    char cracked_pin[6];
    crack(md5_hash, cracked_pin);
    printf("Cracked PIN: %s\n", cracked_pin);
}