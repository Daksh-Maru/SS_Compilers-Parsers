#include <stdio.h> 
#include <stdlib.h> 
#include <stdbool.h> 
#include <string.h> 
#include <ctype.h> 
#define MAX_OPERATORS 10 
#define MAX_INPUT_LENGTH 100 
typedef struct { 
char stack[MAX_INPUT_LENGTH]; 
int top; 
} OperatorStack; 
typedef struct { 
int stack[MAX_INPUT_LENGTH]; 
int top; 
} OperandStack; 
int precedence[MAX_OPERATORS][MAX_OPERATORS]; 
void initPrecedenceTable() { 
for (int i = 0; i < MAX_OPERATORS; i++) { 
for (int j = 0; j < MAX_OPERATORS; j++) { 
precedence[i][j] = -1; 
} 
} 
precedence['+']['+'] = precedence['+']['-'] = precedence['-']['+'] = precedence['-']['-'] = 0; precedence['*']['*'] = precedence['*']['/'] = precedence['/']['*'] = precedence['/']['/'] = 1; 
precedence['+']['*'] = precedence['+']['/'] = precedence['-']['*'] = precedence['-']['/'] = 1; 
precedence['*']['+'] = precedence['*']['-'] = precedence['/']['+'] = precedence['/']['-'] = 0; 
} 
void pushOperator(OperatorStack *stack, char op) { 
stack->stack[++stack->top] = op; 
} 
char popOperator(OperatorStack *stack) { 
return stack->stack[stack->top--]; 
} 
void pushOperand(OperandStack *stack, int val) { 
stack->stack[++stack->top] = val; 
}
int popOperand(OperandStack *stack) { 
return stack->stack[stack->top--]; 
} 
int getPrecedence(char op) { 
return precedence[op][op]; 
} 
int performOperation(int operand1, char operator, int operand2) { switch (operator) { 
case '+': 
return operand1 + operand2; 
case '-': 
return operand1 - operand2; 
case '*': 
return operand1 * operand2; 
case '/': 
return operand1 / operand2; 
default: 
return 0; 
} 
} 
int evaluateExpression(char *expression, int start, int end) { OperatorStack operatorStack; 
OperandStack operandStack; 
operatorStack.top = -1; 
operandStack.top = -1; 
int i = start; 
while (i <= end) { 
if (expression[i] == '(') { 
int j = i + 1; 
int parenCount = 1; 
while (j <= end) { 
if (expression[j] == '(') 
parenCount++; 
else if (expression[j] == ')') { 
parenCount--; 
if (parenCount == 0) 
break; 
} 
j++; 
} 
int subResult = evaluateExpression(expression, i + 1, j - 1); pushOperand(&operandStack, subResult); 
i = j; 
} else if (isdigit(expression[i])) { 
int num = 0;
while (isdigit(expression[i])) { 
num = num * 10 + (expression[i] - '0'); 
i++; 
} 
pushOperand(&operandStack, num); 
continue; 
} else if (expression[i] == ')') { 
i++; 
continue; 
} else { 
while (operatorStack.top != -1 && getPrecedence(operatorStack.stack[operatorStack.top]) >= precedence[operatorStack.stack[operatorStack.top]][expression[i]]) { 
char op = popOperator(&operatorStack); 
int op2 = popOperand(&operandStack); 
int op1 = popOperand(&operandStack); 
pushOperand(&operandStack, performOperation(op1, op, op2)); 
} 
pushOperator(&operatorStack, expression[i]); 
} 
i++; 
} 
while (operatorStack.top != -1) { 
char op = popOperator(&operatorStack); 
int op2 = popOperand(&operandStack); 
int op1 = popOperand(&operandStack); 
pushOperand(&operandStack, performOperation(op1, op, op2)); 
} 
return operandStack.stack[operandStack.top]; 
} 
void printPrecedenceTable() { 
printf("Operator Precedence Table:\n"); 
printf(" + - * / ( )\n"); 
for (int i = 0; i < MAX_OPERATORS; i++) { 
printf("%c ", i < 4 ? ('+' + i) : (i == 4 ? '(' : ')')); 
for (int j = 0; j < MAX_OPERATORS; j++) { 
printf("%d ", precedence[i][j]); 
} 
printf("\n"); 
} 
} 
int main() { 
initPrecedenceTable(); 
printPrecedenceTable(); 
char inputExpression[MAX_INPUT_LENGTH]; 
do { 
printf("Enter the expression: "); 
scanf("%s", inputExpression);
inputExpression[strlen(inputExpression)] = '\0'; 
int result = evaluateExpression(inputExpression, 0, strlen(inputExpression) - 1); 
printf("Result: %d\n", result); 
printf("Do you want to solve another problem? (yes/no): "); 
char answer[4]; 
scanf("%s", answer); 
if (strcmp(answer, "no") == 0) 
break; 
} while (1); 
return 0; 
} 

