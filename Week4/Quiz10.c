#include <stdio.h>
#include <string.h>

int strnchar(char* s, char p) {
    int cnt = 0;
    for (int i=0; i<strlen(s); i++) {
        if (s[i] == p) cnt++;
    }

    return cnt;
}
 
int main() {
    char* string = "hello world!";
    char check_char = 'l';
  
    int n = strnchar(string, check_char);

    printf("%d\n", n);
}