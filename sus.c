#include <stdio.h>
#include <string.h>

void sort_strings(char **strings, int count) {
    int i, j;
    char *temp;

    for (i = 1; i < count; i++) {
        temp = strings[i];
        j = i - 1;

        while (j >= 0 && strcmp(temp[0] == '_' ? temp+1 : temp, strings[j][0] == '_' ? strings[j]+1 : strings[j]) < 0) {
            strings[j+1] = strings[j];
            j--;
        }

        strings[j+1] = temp;
    }
}
