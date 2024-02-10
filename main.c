#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_STR_LEN 400
#define M 20

// 1 - разделитель из divs присутствует в в str

int isDiv(char sym, char *divs) {
    for (int i = 0; i < strlen(divs); i++) if (sym == divs[i]) return 1;
    return 0;
}

int isInArr(char *str, char arr[M][50]) {
    for (int i = 0; i < M; i++) if (arr[i] != NULL && !strcmp(str, arr[i]))  return 1;
    return 0;
}

// ready go, to go.
int main() {
    char *divs = " .,|";
    char tmp[MAX_STR_LEN] = {};
    char s_tmp[MAX_STR_LEN] = {};
    char str_divs[MAX_STR_LEN][10] = {};
    char *words[M] = {};

    fgets(tmp, MAX_STR_LEN - 1, stdin);
    tmp[strlen(tmp) - 1] = '\0';

    strcpy(s_tmp, tmp);

    // собираем все разделители (нужно собирать от слова до слова, а не посимвольно)
    int n = 0;
    int k = 0;
    int lastDiv = 0;
    for (int i = 0; i < strlen(tmp); i++) {
       if (isDiv(tmp[i], divs)) {
           str_divs[n][k++] = tmp[i];
           lastDiv = 1;
       } else if (lastDiv && !isDiv(tmp[i], divs)) {
           k = 0;
           n++;
           lastDiv = 0;
       }
    }

    // выделим слова
    int m = 0;
    char *ptr = strtok(tmp, divs);
    if (ptr != NULL) words[m++] = ptr;

    while (ptr != NULL) {
        ptr = strtok(NULL, divs);
        if (ptr != NULL) words[m++] = ptr;
    }

    // отберем лишние, копируя уникальные
    char uniqWords[M][50] = {};
    char forUniqWordsDivs[M][10] = {};

    int z = 0;
    for (int i = 0; i < M; i++) {
        if (words[i] != NULL && str_divs[i] != NULL) {
            if (!isInArr(words[i], uniqWords)) {
                strcpy(uniqWords[z], words[i]);
                strcpy(forUniqWordsDivs[z++], str_divs[i]);
            }
        }
    }

    // выведем разделители и слова
    for (int i = 0; i < M; i++) { // слово
        if (uniqWords[i] == NULL) break;
        printf("%s%s", uniqWords[i], forUniqWordsDivs[i]);
    }


    return 0;
}
