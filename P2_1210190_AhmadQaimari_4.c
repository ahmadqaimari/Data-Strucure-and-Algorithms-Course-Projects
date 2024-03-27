//Name : Ahmad Qaimari
//Student ID : 1210190
//Section : 4
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_LINES 100
#define MAX_LEN 500

// Linked List Implementation:
struct list
{
    char Data;
    struct list *Next;
};
void DeleteList(struct list *L)
{
    struct list *P, *temp;
    P = L->Next;
    L->Next = NULL;

    while (P != NULL)
    {
        temp = P->Next;
        free(P);
        P = temp;
    }
}

struct list *MakeEmptylist(struct list *L)
{

    L = (struct list *)malloc(sizeof(struct list));
    if (L == NULL)
        printf("Out of memory\n");
    L->Next = NULL;

    return L;
}

int IsEmpty(struct list *L)
{
    return L->Next == NULL;
}

int IsLast(struct list *P, struct list *L)
{
    return P->Next == NULL;
}

struct list *Find(char x, struct list *L)
{
    struct list *P;
    P = L->Next;
    while (P != NULL && P->Data != x)
        P = P->Next;

    return P;
}

struct list *FindPrevious(char x, struct list *L)
{
    struct list *P;
    P = L->Next;
    while (P->Next != NULL && P->Next->Data != x)
        P = P->Next;

    return P;
}

void Delete(char x, struct list *L)
{
    struct list *P, *temp;
    P = FindPrevious(x, L);

    if (!IsLast(P, L))
    {
        temp = P->Next;
        P->Next = temp->Next;
        free(temp);
    }
}

int listSize(struct list *L)
{
    int count = 0;
    struct list *P = L->Next;

    while (P != NULL)
    {
        count++;
        P = P->Next;
    }
    return count;
}

void InsertAtEnd(char x, struct list *L)
{
    struct list *new_node;
    new_node = (struct list *)malloc(sizeof(struct list));
    new_node->Data = x;
    new_node->Next = NULL;
    if (IsEmpty(L))
    { // Checking if the it's the first node to be inserted
        L->Next = new_node;
    }
    else
    {
        struct list *P = L;
        while (P->Next != NULL)
            P = P->Next;
        P->Next = new_node;
    }
}

void PrintList(struct list *L)
{
    struct list *P = L;
    if (IsEmpty(L))
        printf("Empty List");
    else
        do
        {
            P = P->Next;
            printf("%c", P->Data);
        } while (!IsLast(P, L));
}

// Stack Implementation
typedef struct node *PtrToNode;
typedef PtrToNode Stack;
// stack struct for storing characters
struct node
{
    char Element;
    PtrToNode Next;
};
// stack struct for storing integers
struct iStack
{
    int Element;
    struct iStack *Next;
};
// Function to check if stack is empty
int isEmptyI(struct iStack *S)
{
    return S->Next == NULL;
}
// function to pop element from the stack
void iPop(struct iStack *S)
{
    struct iStack *firstCell;
    if (isEmptyI(S))
        printf("Empty Stack");
    else
    {
        firstCell = S->Next;
        S->Next = S->Next->Next;
        free(firstCell);
    }
}
// Function to initialize a stack
struct iStack *CreateiStack()
{

    struct iStack *S;
    S = (struct iStack *)malloc(sizeof(struct iStack));

    if (S == NULL)
        printf("Out of Space");

    S->Next = NULL;
    return S;
}
// Function to return the top of the stack
int iTop(struct iStack *S)
{
    if (!isEmptyI(S))
        return S->Next->Element;
    printf("Empty Stack");
}
// Function to push elements to the stack
void iPush(int x, struct iStack *S)
{
    struct iStack *temp;

    temp = (struct iStack *)malloc(sizeof(struct iStack));
    if (temp == NULL)
        printf("out of space");
    else
    {
        temp->Element = x;
        temp->Next = S->Next;
        S->Next = temp;
    }
}
// The following stack functions are exactly the same as the previous ones,except tha the data type here is char
int isEmpty(Stack S)
{
    return S->Next == NULL;
}

void Pop(Stack S)
{
    PtrToNode firstCell;
    if (!isEmpty(S))
    // printf("Empty Stack");

    {
        firstCell = S->Next;
        S->Next = S->Next->Next;
        free(firstCell);
    }
}

void MakeEmpty(Stack S)
{
    if (S == NULL)
        printf("out of space");
    else
    {
        while (!isEmpty(S))
            Pop(S);
    }
}

Stack CreateStack()
{
    Stack S;
    S = (struct node *)malloc(sizeof(struct node));

    if (S == NULL)
        printf("Out of Space");

    S->Next = NULL;
    // MakeEmpty(S);
    return S;
}

char Top(Stack S)
{
    if (!isEmpty(S))
        return S->Next->Element;
    // printf("Empty Stack");
}

void Push(char x, Stack S)
{
    PtrToNode temp;

    temp = (Stack)malloc(sizeof(struct node));
    if (temp == NULL)
        printf("out of space");
    else
    {
        temp->Element = x;
        temp->Next = S->Next;
        S->Next = temp;
    }
}

void DisposeStack(Stack S)
{
    MakeEmpty(S);
    free(S);
}

void PrintStack(Stack S)
{
    if (!isEmpty(S))
    // printf("Empty Stack");

    {
        Stack TempStack = CreateStack();
        while (!isEmpty(S))
        {
            printf("%c\n", Top(S));
            Push(Top(S), TempStack);
            Pop(S);
        }

        while (!isEmpty(TempStack))
        {
            Push(Top(TempStack), S);
            Pop(TempStack);
        }
    }
}
// Functions to get Stack size
int Size(Stack S)
{
    int size = 0;
    Stack TempStack = CreateStack(); // Used to save elements that are popped before printing them
    while (!isEmpty(S))
    {
        size++;
        Push(Top(S), TempStack);
        Pop(S);
    }
    while (!isEmpty(TempStack))
    {
        Push(Top(TempStack), S);
        Pop(TempStack);
    }
    return size;
}

int iSize(struct iStack *S)
{
    int size = 0;
    struct iStack *TempStack = CreateiStack();
    while (!isEmptyI(S))
    {
        size++;
        iPush(iTop(S), TempStack);
        iPop(S);
    }
    while (!isEmptyI(TempStack))
    {
        iPush(iTop(TempStack), S);
        iPop(TempStack);
    }
    return size;
}

//*****Start of the program*******

// Function to print out the menu
void displaymenu()
{
    printf("Choose one of the following options:\n1-Read from input file\n2-Check Validity\n3-Convert infix to prefix\n4-Evaluate the prefix \n5-Print Invalid Equations\n6-Print All Equations to Output File\n7-Exit");
}
// Function to check if the brackets are balanced in the equation,returns 1(true) or 0(false)
int isBalanced(char EQ[])
{
    Stack S = CreateStack();             // Initializing an empty stack
    for (int i = 0; i < strlen(EQ); i++) // for loop to iterate through the equation
    {
        // if it's an opening bracket,simply push to the stack
        if (EQ[i] == '[' || EQ[i] == '(')
        {
            Push(EQ[i], S);
        }
        // if it's a closing bracket,we have multiple scenarios
        else if (EQ[i] == ']' || EQ[i] == ')')
        {
            if (isEmpty(S)) // if the stack is empty then this closing bracket has no opening,so return false
            {
                return 0;
            }
            else if (EQ[i] == ']' && Top(S) == '[') // if the closing bracket matches the one on top of the stack we pop it
                Pop(S);
            else if (EQ[i] == ')' && Top(S) == '(') // if the closing bracket matches the one on top of the stack we pop it
                Pop(S);
            else // if there's no match
                return 0;
        }
    }
    if (!isEmpty(S)) // if the stack isn't empty then false(no matching brackets)
        return 0;

    return 1; // if all statements are passed then the equation is balanced
}
// Function to check for extra signs in an equation,returns 1(true) or 0(false)
int op_check(char EQ[])
{
    // Initializing an empty linked list to save equation
    struct list *EQ_list = MakeEmptylist(EQ_list);

    for (int i = 0; i < strlen(EQ); i++) // for loop for iterating through the equation and inserting its characters to a linked list
        InsertAtEnd(EQ[i], EQ_list);
    struct list *temp = EQ_list->Next; // used to iterate through the linked list
    while (temp != NULL)               // while loop to iterate through linked list to trim the equatins in some mathematical scenarios
    {
        // if statements to check for double signs and deal with them depending on their mathematical behavior
        if ((temp->Data == '+' && temp->Next->Data == '-') || (temp->Data == '-' && temp->Next->Data == '+'))
        {
            struct list *P = temp->Next;
            temp->Next = P->Next;
            temp->Data = '-';
            free(P);
            temp = EQ_list->Next;
            continue;
        }
        else if (temp->Data == '-' && temp->Next->Data == '-')
        {
            struct list *P = temp->Next;
            temp->Next = P->Next;
            temp->Data = '+';
            free(P);
            temp = EQ_list->Next;
            continue;
        }
        temp = temp->Next;
    }
    // Turning the trimmed linked list back to a string
    char final[50] = "";
    char cToStr[2]; // Used to concatenate a character with a string
    cToStr[1] = '\0';
    struct list *strtemp = EQ_list->Next;

    while (strtemp != NULL) // while loop to iterate through the linked list
    {
        cToStr[0] = strtemp->Data;
        strcat(final, cToStr); // Inserting each character to the empty string
        strtemp = strtemp->Next;
    }
    //****Checking the validity of the operators
    // Initializing a stack to save operands
    struct iStack *nums = CreateiStack();
    // Initializing a stack to save operators
    Stack op = CreateStack();
    char current_digit;
    int i = 0;
    // if the string starts with an operation then it's invalid
    if (final[0] == '/' || final[0] == '*' || final[0] == '+')
        return 0;
    // if the string ends with an operation then it's invalid
    else if (final[strlen(final) - 1] == '/' || final[strlen(final) - 1] == '*' || final[strlen(final) - 1] == '+' || final[strlen(final) - 1] == '-' || final[strlen(final) - 1] == '-')
        return 0;
    // if it's a sign then skip(differentiating between negative sign and subtraction operation)
    else if (final[0] == '-')
    {
        i++;
    }

    while (i < strlen(final)) // while loop to iterate through string
    {
        // Checking for operations
        if (final[i] == '+' || final[i] == '-' || final[i] == '*' || final[i] == '/')
        {
            // Checking for multiple mathematical Scenarios for negative numbers
            if (final[i + 1] == ')')
                return 0;
            else if (final[i] == '-' && final[i - 1] == '(')
            {
                i++;
                continue;
            }
            else if (final[i] == '/' && final[i + 1] == '-')
            {
                i++;
                continue;
            }
            else if (final[i] == '*' && final[i + 1] == '-')
            {
                i++;
                continue;
            }
            // if all if statements are passed,then it's an operation so push to stack
            Push(final[i], op);
            // if there are multiple operations in the stack then it's an invalid equation
            if (Size(op) > 1)
                return 0;
            i++;
        }
        // checking for numbers in the equation
        else if (isdigit(final[i]))
        {
            char current_num[50] = "";
            int count = 0;
            while (isdigit(final[i + count])) // While loop to turn a number of multiple digits in the equation string into an integer
            {

                current_digit = final[i + count];
                cToStr[0] = current_digit;
                cToStr[1] = '\0';
                strcat(current_num, cToStr);
                count++;
            }
            int x = atoi(current_num); // turning the substring into an integer
            iPush(x, nums);            // push the number to the stack
            if (iSize(nums) == 2)      // As soon as there are multiple numbers in the stack,we pop one of them
            {
                iPop(nums);
                if (isEmpty(op)) // if the are operations then the equation is wrong
                    return 0;
                else
                    Pop(op);
            }
            i += count;
        }
        else
            i++;
    }
    return 1; // if all the statements are passed,then the equation is valid
}
// Function to sort the operations based on their presedence,returns an integer
int precedence(char ch)
{
    switch (ch)
    {
    case '+':
    case '-':
        return 1;

    case '*':
    case '/':
        return 2;

    case '^':
        return 3;
    }
    return -1;
}

// Function to do the prefix conversion,returns a linked list
struct list *convert(char EQ[])
{
    // Converting to linked list
    struct list *EQ_list = MakeEmptylist(EQ_list);
    for (int i = 0; i < strlen(EQ); i++)
        InsertAtEnd(EQ[i], EQ_list);
    struct list *temp = EQ_list->Next;
    while (temp != NULL) // for loop to iterate through the linked list to trim it
    {
        if ((temp->Data == '+' && temp->Next->Data == '-') || (temp->Data == '-' && temp->Next->Data == '+'))
        {
            struct list *P = temp->Next;
            temp->Next = P->Next;
            temp->Data = '-';
            free(P);
            temp = EQ_list->Next;
            continue;
        }
        else if (temp->Data == '-' && temp->Next->Data == '-')
        {
            struct list *P = temp->Next;
            temp->Next = P->Next;
            temp->Data = '+';
            free(P);
            temp = EQ_list->Next;
            continue;
        }
        temp = temp->Next;
    }
    // Turning the linked list into a string
    char final[50] = "";
    char cToStr[2];
    cToStr[1] = '\0';
    struct list *strtemp = EQ_list->Next;

    while (strtemp != NULL)
    {
        cToStr[0] = strtemp->Data;
        strcat(final, cToStr);
        strtemp = strtemp->Next;
    }

    //******Start of conversion
    Stack S = CreateStack();
    struct list *prefix = MakeEmptylist(prefix); // Used to save the output
    strrev(final);                               // Reversing the string to start iterating from the end
    int i = 0;

    while (i < strlen(final)) // While loop to iterate through the reversed string
    {
        // Chechking for multiple mathematical scenarios
        if (isdigit(final[i]))
        {
            InsertAtEnd(' ', prefix);
            int count = 0;
            while (isdigit(final[i + count]))
            {
                InsertAtEnd(final[i + count], prefix);
                count++;
            }
            i += count;
            continue;
        }

        else if (final[i] == '-' && (final[i + 1] == '(' || final[i + 1] == '['))
        {
            InsertAtEnd('-', prefix);
            i++;
            continue;
        }

        else if (final[i] == '-' && (final[i + 1] == '*' || final[i + 1] == '/'))
        {
            InsertAtEnd('-', prefix);
            i++;
            continue;
        }

        else if (i == strlen(final) - 1 && final[i] == '-')
        {
            InsertAtEnd('-', prefix);
            i++;
            continue;
        }
        // Dealing with operations based on their presedence
        else if (final[i] == '-' || final[i] == '*' || final[i] == '+' || final[i] == '/')
        {
            if (isEmpty(S))
                Push(final[i], S);
            else if (Top(S) == ')' || Top(S) == ']') // Here the closed brackets act as open ones and vice-versa,this is because the string is in reverse
                Push(final[i], S);
            else if ((!isEmpty(S)) && ((precedence(Top(S))) <= precedence(final[i])))
                Push(final[i], S);
            else if ((!isEmpty(S)) && ((precedence(Top(S))) > precedence(final[i])))
            {
                while (precedence(Top(S)) > precedence(final[i]))
                {
                    InsertAtEnd(Top(S), prefix);
                    Pop(S);
                }
                Push(final[i], S);
            }
            i++;
            continue;
        }
        else if (final[i] == ')' || final[i] == ']')
        {
            Push(final[i], S);
            i++;
            continue;
        }

        else if (final[i] == '(') // When reaching a closing bracket,pop elemnts till reaching the opening one(brackets are reversed)
        {
            while (Top(S) != ')' && !isEmpty(S))
            {
                InsertAtEnd(' ', prefix);
                InsertAtEnd(Top(S), prefix);
                Pop(S);
            }
            Pop(S);
            i++;
            continue;
        }
        else if (final[i] == '[')
        {
            while (Top(S) != ']')
            {
                InsertAtEnd(Top(S), prefix);
                InsertAtEnd(' ', prefix);
                Pop(S);
            }
            Pop(S);
            i++;
            continue;
        }
    }
    if (!isEmpty(S))
    {
        while (!isEmpty(S))
        {
            InsertAtEnd(' ', prefix);
            InsertAtEnd(Top(S), prefix);
            Pop(S);
        }
    }
    // Turning back to a string like how we have done before
    struct list *revtemp = prefix->Next;
    char prefixstr[50] = "";
    while (revtemp != NULL)
    {
        cToStr[0] = revtemp->Data;
        strcat(prefixstr, cToStr);
        revtemp = revtemp->Next;
    }

    strrev(prefixstr); // reversing the string back
    struct list *R = MakeEmptylist(R);
    for (int i = 0; i < strlen(prefixstr); i++)
        InsertAtEnd(prefixstr[i], R);

    return R;
}

int reverseDigits(int num) // Function to return the reverse of an integer
{
    int rev_num = 0;
    while (num > 0)
    {
        rev_num = rev_num * 10 + num % 10;
        num = num / 10;
    }
    return rev_num;
}

int EvaluatePrefix(char EQ[]) // Function to evaluate the prefix,returns the result
{
    struct iStack *Y = CreateiStack();
    // Using the created "convert" function to turn to the prefix notation
    struct list *exp_list = convert(EQ);
    struct list *temp = exp_list->Next;
    char exp[50] = "";
    char cToStr[2];
    cToStr[1] = '\0';
    while (temp != NULL)
    {
        cToStr[0] = temp->Data;
        strcat(exp, cToStr);
        temp = temp->Next;
    }

    // The evaluation statts from the end of the prefix notation
    int i = strlen(exp) - 1;
    char current_digit;
    while (i >= 0)
    {
        if (isdigit(exp[i]))
        {
            // Turning the substring of a multi-digit number into an integer to save in the stack
            char current_num[50] = "";
            int count = 0;
            while (isdigit(exp[i - count]))
            {

                current_digit = exp[i - count];
                cToStr[0] = current_digit;
                cToStr[1] = '\0';
                strcat(current_num, cToStr);
                count++;
            }
            int x = atoi(current_num);
            // We use the created reverse digits to reverse the number we extracted from the equation.since we're reading from the end
            x = reverseDigits(x);
            // if the number has a minus sign right before it,then we multiply by -1
            if (exp[i - count] == '-')
                x *= -1;
            iPush(x, Y);
            i -= count;
        }
        // Checking for operations
        else if (exp[i] == '-' && isdigit(exp[i + 1]))
        {
            i--;
            continue;
        }

        else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/')
        {
            // If an operation is found,push the top 2 integers in the stack and carry the operation
            int op1 = iTop(Y);
            iPop(Y);
            int op2 = iTop(Y);
            iPop(Y);

            if (exp[i] == '+')
            {
                int r = op1 + op2;
                iPush(r, Y);
            }
            else if (exp[i] == '-')
            {
                int r = op1 - op2;
                iPush(r, Y);
            }
            else if (exp[i] == '*')
            {
                int r = op1 * op2;
                iPush(r, Y);
            }
            else if (exp[i] == '/')
            {
                int r = op1 / op2;
                iPush(r, Y);
            }
            i--;
        }
        else
            i--;
    }
    return iTop(Y);
}
//*****Main(Driver) function
int main()
{
    // The data from the file is saved into a 2d array
    int line = 0;
    char Data[MAX_LINES][MAX_LEN];

    int op;

    displaymenu();
    scanf("%d", &op);
    int flag = 0;
    while (op != 7)
    {
        // Reading the data from the file
        if (op == 1)
        {
            flag = 1; // Flag to check if the data has been read
            printf("Enter the name of the file or enter -1 to go back\n");
            char file_name[] = "";
            scanf("%s", &file_name);
            if (atoi(file_name) == -1)
                continue;

            FILE *file;

            file = fopen(strcat(file_name, ".txt"), "r");

            while (file == NULL) // while loop to check if a file with the entered name exists in the directory of the program
            {
                printf("Wrong file name.please enter a correct file name or enter -1 to go back\n");
                scanf("%s", &file_name);
                if (atoi(file_name) == -1)
                    break;
                else
                {
                    file = fopen(strcat(file_name, ".txt"), "r");
                }
            }
            if (atoi(file_name) == -1)
                continue;

            while (!feof(file) && !ferror(file))
                if (fgets(Data[line], MAX_LEN, file) != NULL)
                    line++;

            fclose(file);

            for (int i = 0; i < line; i++)
                printf("%s\n", Data[i]);
        }
        // Checking the validity of each equation
        else if (op == 2)
        {
            if (flag == 0)
            {
                printf("The data hasn't been read yet,please choose option 1 to read the data first\n");
            }

            for (int i = 0; i < line; i++) // For loop to iterate through the equations the 2d array
            {
                // Removing the new_line character at the end of each line
                if (Data[i][strlen(Data[i]) - 1] == '\n')
                    Data[i][strlen(Data[i]) - 1] = '\0';
                printf("%s->", Data[i]);
                if (op_check(Data[i]) && isBalanced(Data[i]))
                    printf("Valid\n");

                else
                    printf("Invalid\n");
            }
        }
        // Printing the prefix of valid equations
        else if (op == 3)
        {
            for (int i = 0; i < line; i++) // For loop to iterate through the equations the 2d array
            {
                if (Data[i][strlen(Data[i]) - 1] == '\n')
                    Data[i][strlen(Data[i]) - 1] = '\0';
                if (op_check(Data[i]) && isBalanced(Data[i]))
                {
                    struct list *converted = MakeEmptylist(converted);
                    converted = convert(Data[i]);
                    PrintList(converted);
                    printf("\n");
                }
            }
        }
        // Evaluating each equation in prefix notation and printing the results
        else if (op == 4)
        {
            for (int i = 0; i < line; i++) // For loop to iterate through the equations the 2d array
            {
                if (Data[i][strlen(Data[i]) - 1] == '\n')
                    Data[i][strlen(Data[i]) - 1] = '\0';
                if (op_check(Data[i]) && isBalanced(Data[i]))
                {
                    printf("Equation %d -> %d\n", i + 1, EvaluatePrefix(Data[i]));
                }
                else
                    printf("Equation %d -> Invalid\n", i + 1);
            }
        }
        // Printing invalid equations
        else if (op == 5)
        {
            int no_invalid = 1;
            for (int i = 0; i < line; i++) // For loop to iterate through the equations the 2d array
            {

                if (Data[i][strlen(Data[i]) - 1] == '\n')
                    Data[i][strlen(Data[i]) - 1] = '\0';
                if (!(op_check(Data[i]) && isBalanced(Data[i])))
                {
                    no_invalid = 0;
                    printf("%s\n", Data[i]);
                }
            }
            if (no_invalid)
                printf("There aren't any invalid equations\n");
        }
        // Printing the validity,prefix notation and prefix evaluation result for each equation to an output file
        else if (op == 6)
        {
            FILE *o_file = fopen("p2_output.txt", "a");
            for (int i = 0; i < line; i++) // For loop to iterate through the equations the 2d array
            {

                if (Data[i][strlen(Data[i]) - 1] == '\n')
                    Data[i][strlen(Data[i]) - 1] = '\0';

                if ((op_check(Data[i]) && isBalanced(Data[i])))
                {
                    fprintf(o_file, "%s ->Valid\t", Data[i]);

                    fprintf(o_file, "Result: %d\t", EvaluatePrefix(Data[i]));
                    struct list *converted = convert(Data[i]);
                    struct list *P = converted;
                    do // Do-While loop to print the prefix notation that's saved in the linked list
                    {
                        P = P->Next;
                        fprintf(o_file, "%c", P->Data);
                    } while (!IsLast(P, converted));
                    fprintf(o_file, "\n");
                }
                else
                    fprintf(o_file, "%s ->Invalid\n", Data[i]);
            }
            fclose(o_file);
        }
        displaymenu();
        scanf("%d", &op);
    }
    printf("Program Quitted");
    return 0;
}