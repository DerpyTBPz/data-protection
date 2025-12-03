#include <stdio.h>
#include <string.h>

const char *scanner(int qrcode[21][21])
{
    static char output[256]; 

    int val = (qrcode[8][2] << 2) | (qrcode[8][3] << 1) | qrcode[8][4];
    int mask_id = val ^ 5; 

    int bits[1024]; 
    int bit_count = 0;

    int c = 20;     
    int dir = -1; 

    while (c > 0)
    {
        if (c == 6) c--; 

        for (int k = 0; k < 21; k++)
        {
            int r = (dir < 0) ? (20 - k) : k; 

            for (int col_offset = 0; col_offset < 2; col_offset++)
            {
                int curr_c = c - col_offset;
                
                if (r == 6) continue; 
                if (r < 9 && curr_c < 9) continue;
                if (r < 9 && curr_c > 12) continue; 
                if (r > 12 && curr_c < 9) continue; 

                int pixel_val = qrcode[r][curr_c];
                int invert = 0;
                
                switch (mask_id) {
                    case 0: invert = (r + curr_c) % 2 == 0; break;
                    case 1: invert = r % 2 == 0; break;
                    case 2: invert = curr_c % 3 == 0; break;
                    case 3: invert = (r + curr_c) % 3 == 0; break;
                    case 4: invert = ((r / 2) + (curr_c / 3)) % 2 == 0; break;
                    case 5: invert = ((r * curr_c) % 2 + (r * curr_c) % 3) == 0; break;
                    case 6: invert = (((r * curr_c) % 2 + (r * curr_c) % 3) % 2) == 0; break;
                    case 7: invert = (((r + curr_c) % 2 + (r * curr_c) % 3) % 2) == 0; break;
                }
                
                bits[bit_count++] = pixel_val ^ invert;
            }
        }
        dir = -dir; 
        c -= 2;     
    }

    int len = 0;
    for (int i = 0; i < 8; i++) {
        len = (len << 1) | bits[4 + i];
    }

    int idx = 12;
    for (int i = 0; i < len; i++) {
        char char_val = 0;
        for (int b = 0; b < 8; b++) {
            char_val = (char_val << 1) | bits[idx++];
        }
        output[i] = char_val;
    }
    output[len] = '\0';

    return output;
}

int main()
{
    int value[21][21]= {{ 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1 },
                        { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1 },
                        { 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1 },
                        { 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1 },
                        { 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1 },
                        { 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1 },
                        { 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1 },
                        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
                        { 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1 },
                        { 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1 },
                        { 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1 },
                        { 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0 },
                        { 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0 },
                        { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0 },
                        { 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1 },
                        { 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1 },
                        { 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1 },
                        { 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0 },
                        { 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1 },
                        { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0 },
                        { 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1 }};
  
    const char *result = scanner(value); 

    printf("Decoded message: %s\n", result);
}