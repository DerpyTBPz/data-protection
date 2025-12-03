#include <stdlib.h>
#include <stdio.h>  
#include <string.h>

// for both functions, return null-terminated strings

char encoded_message[1024];
char encoded_message_triple[3072];

char *encode(const char *text) 
{
  for (int i = 0; text[i] != '\0'; i++) 
  {
    char ch = text[i];
    unsigned char byte = (unsigned char)ch;
    for (int j = 7; j >= 0; j--) 
    {
      encoded_message[i * 8 + (7 - j)] = (byte & (1 << j)) ? '1' : '0';
    }
    for (int j = 0; j < 8; j++) 
    {
      encoded_message_triple[i * 24 + j * 3 + 0] = encoded_message[i * 8 + j];
      encoded_message_triple[i * 24 + j * 3 + 1] = encoded_message[i * 8 + j];
      encoded_message_triple[i * 24 + j * 3 + 2] = encoded_message[i * 8 + j];
    }
  }
  encoded_message_triple[strlen(text) * 24] = '\0';
  return encoded_message_triple;
}

char *decode(const char *bits) 
{
    static char decoded_text[1024];
    int text_index = 0;
    int bit_len = strlen(bits);

    for (int i = 0; i + 23 < bit_len; i += 24) 
    {
        unsigned char byte = 0;
        for (int j = 0; j < 8; j++) 
        {
            int chunk_start = i + j * 3;

            int ones = 0;
            if (bits[chunk_start] == '1') ones++;
            if (bits[chunk_start + 1] == '1') ones++;
            if (bits[chunk_start + 2] == '1') ones++;

            if (ones >= 2) 
            {
                byte |= (1 << (7 - j));
            }
        }
        decoded_text[text_index++] = (char)byte;
    }

    decoded_text[text_index] = '\0';
    return decoded_text;
}

int main() 
{
  char text[] = "The Sensei told me that i can do this kata";
  
  char *encoded = encode(text);
  printf("Encoded: %s\n", encoded);

  printf("Encoded triple: %s\n", encoded_message_triple);
  
  char *decoded = decode(encoded_message_triple);
  printf("Decoded: %s\n", decoded);
  
  return 0;
}