#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    char message1[1001];
    char message2[1001];
    char message3[1001];

    scanf("%s", message1);
    scanf("%s", message2);
    scanf("%s", message3);

    int len = strlen(message1);

    for (int i = 0; i < len; i += 2)
    {
        int val1, val2, val3;

        sscanf(&message1[i], "%2x", &val1);
        sscanf(&message2[i], "%2x", &val2);
        sscanf(&message3[i], "%2x", &val3);

        int original_char = val1 ^ val2 ^ val3;

        printf("%c", (char)original_char);
    }

    printf("\n");

    return 0;
}