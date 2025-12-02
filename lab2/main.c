#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{
    char alphabet[26] = "abcdefghijklmnopqrstuvwxyz";
    char message[1001] = "Khoor Zruog ! Frqjudwxodwlrqv, brx kdyh vxffhvvixoob ghfubswhg ph ! Kdyh ixq zlwk wklv sxccoh";
    
    double english_freq[26] = 
    {
        0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015,
        0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749,
        0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758,
        0.00978, 0.02360, 0.00150, 0.01974, 0.00074
    };
    
    // scanf("%[^\n]", message);

    int num[26] = {0};

    for (int i = 0; i < strlen(message); i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if ((message[i] == alphabet[j]) || (message[i] == (alphabet[j] - 32)))
            {
                num[j]++;
            }
        }
    }

    int best_shift = 0;
    double max_score = 0.0;

    for (int shift = 0; shift < 26; shift++) 
    {
        double current_score = 0.0;
        
        for (int k = 0; k < 26; k++) 
        {
            current_score += english_freq[k] * num[(k + shift) % 26];
        }

        if (current_score > max_score) 
        {
            max_score = current_score;
            best_shift = shift;
        }
    }

    for (int i = 0; i < strlen(message); i++) 
    {
        char c = message[i];
        
        if (c >= 'a' && c <= 'z') 
        {
            char decoded = 'a' + (c - 'a' - best_shift + 26) % 26;
            printf("%c", decoded);
        } 
        else if (c >= 'A' && c <= 'Z') 
        {
            char decoded = 'A' + (c - 'A' - best_shift + 26) % 26;
            printf("%c", decoded);
        } 
        else 
        {
            printf("%c", c);
        }
    }
    printf("\n");

    return 0;
}