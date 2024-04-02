#include <stdio.h>
#include <string.h>


// Function prototypes
int E(), E_prime(), T(), T_prime(), F();
const char *P;
char string[64];

int main() {
    puts("Enter the string");
    scanf("%s", string); // Read input from the user
    P = string;
    puts("");
    puts("Input Action");

    // Call the starting non-terminal E
    if (E() && *P == '\0') { // If parsing is successful and the cursor has reached the end

        puts("String is successfully parsed");
        return 0;
    } else {

        puts("Error in parsing String");
        return 1;
    }
}

// Grammar rule: E -> T E'
int E() {
    printf("%-16s E -> T E'\n", P);
    if (T()) { // Call non-terminal T
        if (E_prime()) // Call non-terminal E'
            return 1;
        else
            return 0;
    } else
        return 0;
}

// Grammar rule: E' -> + T E' | $
int E_prime() {
    if (*P == '+') {
        printf("%-16s E' -> + T E'\n", P);
        P++;
        if (T()) { // Call non-terminal T
            if (E_prime()) // Call non-terminal E'
                return 1;
            else
                return 0;
        } else
            return 0;
    } else {
        printf("%-16s E' -> $\n", P);
        return 1;
    }
}

// Grammar rule: T -> F T'
int T() {
    printf("%-16s T -> F T'\n", P);
    if (F()) { // Call non-terminal F
        if (T_prime()) // Call non-terminal T'
            return 1;
        else
            return 0;
    } else
        return 0;
}

// Grammar rule: T' -> * F T' | $
int T_prime() {
    if (*P == '*') {
        printf("%-16s T' -> * F T'\n", P);
        P++;
        if (F()) { // Call non-terminal F
            if (T_prime()) // Call non-terminal T'
                return 1;
            else
                return 0;
        } else
            return 0;
    } else {
        printf("%-16s T' -> $\n", P);
        return 1;
    }
}

// Grammar rule: F -> ( E ) | i
int F() {
    if (*P == '(') {
        printf("%-16s F -> ( E )\n", P);
        P++;
        if (E()) { // Call non-terminal E
            if (*P == ')') {
                P++;
                return 1;
            } else
                return 0;
        } else
            return 0;
    } else if (*P == 'i') {
        printf("%-16s F -> i\n", P);
        P++;
        return 1;
    } else
        return 0;
}