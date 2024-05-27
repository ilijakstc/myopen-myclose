#include "mypopen_mypclose.h"

int main() { 
    // // we create processes for both `ls` and `wc` // `popen` returns a FILE* that represents // the process' stdout (`r`) or stdin (`w`) 
    FILE *ls = mypopen("ls", "r"); 
    FILE *wc = mypopen("wc", "w"); 
    // we consume the output of `ls` and feed it to `wc` 
    char buf[1024]; 
    while (fgets(buf, sizeof(buf), ls) != NULL){
        fputs(buf, wc); 
    }
    // once we're done, we close the streams 
    mypclose(ls); 
    mypclose(wc);

    return 0;
    }