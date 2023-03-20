#include <stdio.h>
#include <string.h>

int nfind(char* string, char* pat) {
    int i, j;
    int start = 0;
    int lasts = strlen(string) - 1;
    int lastp = strlen(pat) - 1;
    int endmatch = lastp;
    for (i=0; endmatch<=lasts; endmatch++, start++) {
        if (string[endmatch] == pat[lastp]) {
            for (j=0, i=start; j<lastp && string[i]==pat[j]; i++, j++);
            if (j == lastp) return start;
        }
    }

}
 
int main() {
    char* string = "hello world!";
    char* pat = "wora";
  
    int n = nfind(string, pat);

    printf("%d\n", n);
}