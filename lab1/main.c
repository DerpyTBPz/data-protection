#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

int main()
{
    // DEBUG VALUES
    char operation[257] = "ENCODE";
    int pseudo_random_number = 4;
    char rotor1[28] = "BDFHJLCPRTXVZNYEIWGAKMUSQO";
    char rotor2[28] = "AJDKSIRUXBLHWTMCQZGNPEYFVO";
    char rotor3[28] = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
    char message[1025] = "AAA";


    scanf("%[^\n]", operation);
    scanf("%d", &pseudo_random_number); fgetc(stdin);
    scanf("%[^\n]", rotor1); fgetc(stdin);
    scanf("%[^\n]", rotor2); fgetc(stdin);
    scanf("%[^\n]", rotor3); fgetc(stdin);
    scanf("%[^\n]", message);

    if (strcmp(operation, "ENCODE") == 0)
    {
        int count = 0;
        for(int i = 0; i < sizeof(message); i++)
        {
            if (message[i] == '\0')
            {
                count = 0;
                break;
            }
            else
            {
                for (int j = 0; j < sizeof(ALPHABET); j++)
                {
                    if (message[i] == ALPHABET[j])
                    {
                        int new_index = (j + count + pseudo_random_number) % 26;
                        message[i] = ALPHABET[new_index];
                        break;
                    }
                }
                for (int j = 0; j < sizeof(rotor1); j++)
                {
                    if (message[i] == ALPHABET[j])
                    {
                        message[i] = rotor1[j];
                        break;
                    }
                }
                for (int j = 0; j < sizeof(rotor2); j++)
                {
                    if (message[i] == ALPHABET[j])
                    {
                        message[i] = rotor2[j];
                        break;
                    }
                }
                for (int j = 0; j < sizeof(rotor3); j++)
                {
                    if (message[i] == ALPHABET[j])
                    {
                        message[i] = rotor3[j];
                        break;
                    }
                }
                count++;
            }
        }
    }
    else if (strcmp(operation, "DECODE") == 0)
    {
        int count = 0;
        for(int i = 0; i < strlen(message); i++)
        {
            for (int j = 0; j < 26; j++)
            {
                if (message[i] == rotor3[j])
                {
                    message[i] = ALPHABET[j];
                    break;
                }
            }
            for (int j = 0; j < 26; j++)
            {
                if (message[i] == rotor2[j])
                {
                    message[i] = ALPHABET[j];
                    break;
                }
            }
            for (int j = 0; j < 26; j++)
            {
                if (message[i] == rotor1[j])
                {
                    message[i] = ALPHABET[j];
                    break;
                }
            }
            for (int j = 0; j < 26; j++)
            {
                if (message[i] == ALPHABET[j])
                {
                    int new_index = (j - (count + pseudo_random_number) + 26*10) % 26;
                    message[i] = ALPHABET[new_index];
                    break;
                }
            }
            count++;
        }
    }

    printf("%s\n", message);

    return 0;
}