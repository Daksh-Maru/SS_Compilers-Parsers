
#include<stdio.h> 
#include<string.h>
void main() 
{ 
    char stack[20],ip[20],opt[10][10][1],ter[10]; 

    int i,j,k,n,col,row;

    for(i=0;i<10;i++){
        stack[i]='\0'; ip[i]='\0'; 
        for(j=0;j<10;j++){
            opt[i][j][1]='\0';
        }
    }
    
    /*
        stack of characters
        string of terminals
        input string.
        operation table.
    */

    printf("Enter the no.of terminals:"); 
    scanf("%d",&n); 
    printf("\nEnter the terminals:"); 
    scanf("%s",ter); 


    printf("\nEnter the table values:\n"); 
    for(i=0;i<n;i++) { 
        for(j=0;j<n;j++) { 
            printf("Enter the value for %c %c:",ter[i],ter[j]); 
            scanf("%s",&opt[i][j][0]); 
        } 
    }


    printf("\nOPERATOR PRECEDENCE TABLE:\n"); 
    for(i=0;i<n;i++){
        printf("\t%c",ter[i]);
    } 
    printf("\n"); 
    for(i=0;i<n;i++) {
        printf("\n%c",ter[i]); 
        for(j=0;j<n;j++){
            printf("\t%c",opt[i][j][0]);
        }
    }

    int top=0;
    stack[top]='$'; 
    printf("\nEnter the input string:"); 
    scanf("%s",ip); 
    printf("\nSTACK\t\t\tINPUT STRING\t\t\tACTION\n"); 
    printf("\n%s\t\t\t%s\t\t\t",stack,ip); 

    int idx=0; 
    while(idx<=strlen(ip)) { 
        for(k=0;k<n;k++) { 
            if(stack[top]==ter[k]) 
            col=k; 
            if(ip[idx]==ter[k]) 
            row=k; 
        } 
        if((stack[top]=='$')&&(ip[idx]=='$')){ 
            printf("String is accepted"); 
            break;
        } 
        else if((opt[col][row][0]=='<') ||(opt[col][row][0]=='=')) { 
            stack[++top]=opt[col][row][0]; 
            stack[++top]=ip[idx]; 
            printf("Shift %c",ip[idx]); 
            idx++; 
        } 
        else { 
            if(opt[col][row][0]=='>') { 
                while(stack[top]!='<'){--top;} 
                top=top-1; 
                printf("Reduce"); 
            } 
            else { 
                printf("\nString is not accepted"); 
                break; 
            } 
        } 
        printf("\n"); 
        for(k=0;k<=top;k++) { 
            printf("%c",stack[k]); 
        } 
        printf("\t\t\t"); 
        for(k=idx;k<strlen(ip);k++){ 
            printf("%c",ip[k]); 
        } 
        printf("\t\t\t"); 
    } 
}   