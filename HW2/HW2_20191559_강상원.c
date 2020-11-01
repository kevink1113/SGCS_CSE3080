#include <stdio.h>
#include <string.h>

#define max_string_size 101
#define max_pattern_size 101

int pmatch();

void fail();

int failure[max_pattern_size];
char string[max_string_size];
char pat[max_pattern_size];
int cnt1 = 0;
int cnt2 = 0;

int naiveSearch(char *string, char *pattern) {
    int i, j;
    int res;
    for (i = 0; i < strlen(string) - strlen(pattern) + 1; i++) {
        cnt1++;
        res = 1;
        for (j = i; j < i + strlen(pattern); j++) {
            cnt1++;
            if (string[j] != pattern[j - i]) res = 0;
        }
        cnt1--;
        if (res == 1) return i;
    }
    return -1;
}

int pmatch(char *string, char *pat) {
/* Knuth, Morris, Pratt string matching algorithm */
    int i = 0, j = 0;
    int lens = strlen(string);
    int lenp = strlen(pat);
    //
    //printf("%d %d\n", lens, lenp);
    //
    while (i < lens && j < lenp) {
        cnt2++;
        if (string[i] == pat[j]) {
            i++;
            j++;
        } else if (j == 0) i++;
        else j = failure[j - 1] + 1;
    }
    return ((j == lenp) ? (i - lenp) : -1);
}

void fail(char *pat) {
/* compute the pattern’s failure function */
    int i, j, n = strlen(pat);
    failure[0] = -1;
    for (j = 1; j < n; j++) {
        i = failure[j - 1];
        while ((pat[j] != pat[i + 1]) && (i >= 0))
            i = failure[i];
        if (pat[j] == pat[i + 1])
            failure[j] = i + 1;
        else failure[j] = -1;
    }
}

int main() {
    scanf("%s %s", string, pat);

    int res1 = naiveSearch(string, pat);
    if (res1 == -1) printf("NO\n");
    else printf("YES %d\n", cnt1);

    fail(pat);
    int res2 = pmatch(string, pat);
    if (res2 == -1) printf("NO\n");
    else printf("YES %d\n", cnt2);

    return 0;
}
