//Name : Ahmad Qaimari
//Student ID : 1210190
//Section : 4
#include <stdio.h> // define the header file
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_SIZE 1000
// Declaring the struct
struct node
{
    int Data;
    struct node *Next;

    struct node *Prev;
};

// function to delete lists
void DeleteList(struct node *L)
{
    if (L->Next != NULL)
    {
        struct node *P, *temp;
        P = L->Next;
        L->Next = NULL;

        while (P != NULL)
        {
            temp = P->Next;
            free(P);
            P = temp;
        }
    }
}
// Function to create an empty doubly linked list linked list
struct node *MakeEmpty(struct node *L)
{
    L = (struct node *)malloc(sizeof(struct node));
    if (L == NULL)
        printf("Out of memory\n");

    L->Next = NULL;
    L->Prev = NULL;

    return L;
}
// Function to check if the linked list is Empty
int IsEmpty(struct node *L)
{
    return L->Next == NULL;
}
// Function to check if a node is the last in its linked list
int IsLast(struct node *P, struct node *L)
{
    return P->Next == NULL;
}
// Function to get the last node of a linked list
struct node *GetLast(struct node *L)
{
    struct node *P;
    P = L;
    while (P->Next != NULL)
        P = P->Next;
    return P;
}
// Function to find a certain node using based on the element stored
struct node *Find(int x, struct node *L)
{
    struct node *P;
    P = L->Next;
    while (P != NULL && P->Data != x)
        P = P->Next;

    return P;
}
// Function to delete a specific element
void Delete(int x, struct node *L)
{
    struct node *P;
    P = Find(x, L);

    if (P->Prev == NULL)
    {
        L->Next = P->Next;
        P->Next->Prev = NULL;
        free(P);
    }

    else if (!IsLast(P, L))
    {
        P->Prev->Next = P->Next;
        P->Next->Prev = P->Prev;
        free(P);
    }
}

// Function to insert an element at the end of a doubly linked list
void InsertAtEnd(int x, struct node *L)
{
    struct node *new_node;
    new_node = (struct node *)malloc(sizeof(struct node));
    new_node->Data = x;
    new_node->Next = NULL;
    if (IsEmpty(L))
    { // Checking if the it's the first node to be inserted
        L->Next = new_node;
        new_node->Prev = NULL; // Connecting the first node inserted at the end to null,since a backwards connection from the first node to the head isn't needed
    }

    else
    { // checking if the element to be inserted isn't going to be the first element in the linked list
        struct node *P = L;
        while (P->Next != NULL)
            P = P->Next;

        P->Next = new_node;
        new_node->Prev = P;
    }
}
// Function to Insert at the front of the linked list(directly after head)
void InsertAtFront(int x, struct node *L)
{
    struct node *new_node;
    new_node = (struct node *)malloc(sizeof(struct node));
    new_node->Data = x;
    new_node->Prev = NULL;
    if (IsEmpty(L))
    { // Checking if the it's the first node to be inserted
        L->Next = new_node;
        new_node->Next = NULL; // connecting the node to null since it's going to be the last node
        new_node->Prev = NULL; // Connecting the first node inserted at the front to null,since a backwards connection from the first node to the head isn't needed
    }
    else
    {                             // checking if the element to be inserted isn't going to be the first element in the linked list
        L->Next->Prev = new_node; // connecting the first node after the head to the inserted node using a backward connection
        new_node->Next = L->Next; // connecting the inserted node to the first node after the head from the front
        L->Next = new_node;
    }
}
// Function to print the linked list
void PrintList(struct node *L)
{
    struct node *P = L;
    if (IsEmpty(L))
        printf("Empty List");
    else
        do
        {
            P = P->Next;
            printf("%d", P->Data);
        } while (!IsLast(P, L));
    printf("\n");
}

// Function to find the size of the linked lists that contain the digits(to decide the number of digits)
int DigitListSize(struct node *L)
{
    int count = 0;
    struct node *P = L;

    while (P != NULL)
    {
        count++;
        P = P->Next;
    }
    return count;
}
// Function to print the digits stored in the linked list
//** note: the linked lists that store the actual number are of different format in the sense that the first digit stored acts as a head(there's no seperate head node)
void PrintDigitList(struct node *L)
{
    struct node *P = L->Prev;
    do
    {
        printf("%d", P->Data);
        P = P->Next;
    } while (P != NULL);
    printf("\n");
}
// Function to compare two numbers that are stored in linked lists
int CMP(struct node *N1, struct node *N2)
{
    if (DigitListSize(N1) != DigitListSize(N2))
    {
        if (DigitListSize(N1) > DigitListSize(N2))
            return 1;
        else
            return 0;
    }

    else
    {
        while (N1 != NULL && N2 != NULL)
        {
            if (N1->Data > N2->Data)
                return 1;
            else if (N1->Data < N2->Data)
                return 0;

            else
            {
                N1 = N1->Next;
                N2 = N2->Next;
            }
        }
    }
    return 2;
}
// Function to read data from the file and store the digits and their indicies in linked list,returns a linked list
struct node *ReadData()
{
    FILE *in_file;
    char n1[MAX_SIZE];
    in_file = fopen("input.txt", "r");
    struct node *digits;
    digits = MakeEmpty(digits); // Creating an empty linked list to store the digits
    struct node *all_numbers;
    all_numbers = MakeEmpty(all_numbers); // Creating an empty linked list to store the indicies of the numbers
    struct node *temp = all_numbers;
    int count = 0; // keeps track of the indicies
    int neg_flag;  // flag to check if the number read from the input file is negative
    while (fgets(n1, MAX_SIZE, in_file))
    {
        neg_flag = 0;
        for (int i = 0; i < strlen(n1); i++)
        {
            if (n1[i] == '-')
                neg_flag = 1;

            else if (isdigit(n1[i]))
            {
                InsertAtEnd(n1[i] - '0', digits); // converting each character to an int and storing in the digits linked list
            }
            else
                continue;
            
        }
        count++;
        InsertAtEnd(count, all_numbers); // storing the indicies in a linked list
        temp = GetLast(all_numbers);     // used as a pointer to the newest added index
        temp->Prev = digits->Next;       // In the indicies linked list,the "Prev" pointer is used to point to the first digit in the corresponding index.The indicies' nodes acts as heads to the corresponding digit in the digit linked list.
        if (neg_flag)
            temp->Prev->Data *= -1; // Multiplying the head of the negative numbers by -1
        digits->Next->Prev = NULL;  // connecting the first digit of the number to null from the back
        digits->Next = NULL;        // resetting the pointer for the next iteration
    }
    // loop for printing the numbers alongside their indicies
    for (int i = 1; i <= count; i++)
    {
        printf("%d: ", i);
        PrintDigitList(Find(i, all_numbers));
    }

    fclose(in_file);

    return all_numbers;
}

// Implementing Addition,returns the result as a linked list
struct node *Add(struct node *N1, struct node *N2)
{
    struct node *Result = MakeEmpty(Result);
    // initializing the carry and the current sum variables
    int c = 0;
    int s;
    // inititalizing the integers that hold the current values
    int N1_digit, N2_digit;
    // Setting the pointer to the start reading the digits from right to left
    N1 = GetLast(N1);
    N2 = GetLast(N2);
    // A for loop for iterating through the numbers
    while (N1 != NULL || N2 != NULL)
    {
        if (N1 != NULL)
            N1_digit = N1->Data;
        else
            N1_digit = 0;

        if (N2 != NULL)
            N2_digit = N2->Data;
        else
            N2_digit = 0;

        s = N1_digit + N2_digit + c;
        c = s / 10;
        int r_digit = s % 10;
        // Inserting the digits to the front of the linked list
        InsertAtFront(r_digit, Result);

        if (N1 != NULL)
            N1 = N1->Prev;
        if (N2 != NULL)
            N2 = N2->Prev;
    }
    // if there's no carry,insert the digit as it is
    if (c > 0)
    {
        InsertAtFront(c, Result);
    }

    return Result;
}
// Implementing Addition,returns the result as a linked list
struct node *Sub(struct node *N1, struct node *N2)
{
    struct node *Result = MakeEmpty(Result);
    // checking if the numbers are equal to output zero immediately
    if (CMP(N1, N2) == 2)
        InsertAtEnd(0, Result);
    // Entering the function
    else
    {
        // Initializing the borrow and the current subtraction result variables
        int b = 0;
        int s;
        // Setting the pointer to the start reading the digits from right to left
        N1 = GetLast(N1);
        N2 = GetLast(N2);
        // A for loop for iterating through the numbers
        while (N1 != NULL || N2 != NULL)
        {
            if (N1 != NULL && N2 != NULL)
            {
                if (((N1->Data) + b) >= (N2->Data))
                {
                    s = (((N1->Data) + b) - (N2->Data));
                    b = 0;
                }
                else
                {
                    s = ((N1->Data) + b + 10 - (N2->Data));
                    b = -1;
                }
                N1 = N1->Prev;
                N2 = N2->Prev;
            }
            else if (N1 != NULL && N2 == NULL)
            {
                if (N1->Data >= 1)
                {                         // Checking if the remaining digit is larger than 1
                    s = ((N1->Data) + b); // storing the remaining digit after subtracting the borrowed value
                    b = 0;                // resetting borrow
                }
                else
                {
                    if (b != 0)
                    {
                        s = ((N1->Data) + 10 + b);
                        b = -1;
                    }
                    else
                        s = N1->Data;
                }
                N1 = N1->Prev;
            }
            InsertAtFront(s, Result);
        }
        // while loop to remove extra zeores on the left
        while (Result->Next->Data == 0)
        {
            Delete(0, Result);
        }
    }

    return Result;
}
// Implementing Multiplication,returns result as a linked list
struct node *Mul(struct node *N1, struct node *N2)
{
    // Initializing a linked list to keep the value of the current total
    struct node *total = MakeEmpty(total);
    // checking if either number is zero to output 0 immediately
    if (N1->Data == 0 || N2->Data == 0)
        InsertAtEnd(0, total);

    else
    {
        // initializng the "total" linked list to zero
        InsertAtEnd(0, total);
        // intializing a variable to keep track of the added zeroes to the current total
        int k = 0;
        // Setting the pointer to the start reading the digits from right to left
        N1 = GetLast(N1);
        N2 = GetLast(N2);
        // A for loop for iterating through the numbers
        while (N2 != NULL)
        {
            // Carry and current Multiplication result variables
            int c = 0;
            int s = 0;
            // initializing a temp node to iterate through the first number
            struct node *temp = N1;
            // Creating a linked list to hold current subtraction total
            struct node *X = MakeEmpty(X);

            while (temp != NULL)
            {
                s = ((temp->Data) * (N2->Data) + c) % 10;
                c = ((temp->Data) * (N2->Data) + c) / 10;
                InsertAtFront(s, X);
                temp = temp->Prev;
            }
            // If there's remaining carry Insert as it is
            if (c != 0)
                InsertAtFront(c, X);
            // Insert zeroes At front of current result
            for (int i = 0; i < k; i++)
                InsertAtEnd(0, X);
            // Adding current multiplication result to the total
            total = Add(X->Next, total->Next);
            k++;
            N2 = N2->Prev;
            X->Next = NULL;
        }
        // while loop to remove extra zeores on the left
        while (total->Next->Data == 0)
        {
            Delete(0, total);
        }
    }

    return total;
}

// Implementing Division,returns result as a linked list
struct node *Div(struct node *N1, struct node *N2)
{
    // Initializing temp nodes for iteration
    struct node *N1_temp = N1;
    struct node *N2_temp = N2;
    // initializng empty linked lists for holding values used in the division operation
    struct node *rem = MakeEmpty(rem);
    struct node *mp = MakeEmpty(mp);
    struct node *r_mul = MakeEmpty(r_mul);
    struct node *quo = MakeEmpty(quo);
    int i;
    // Initializing a linked list that holds zero that is used for testing purposes
    struct node *z = MakeEmpty(z);
    InsertAtEnd(0, z);

    // Checking if the numbers are equal to output 1 immediately
    if (CMP(N1, N2) == 2)
    {
        if (N1 && N2 == 0)
        { // Division by zero check
            printf("Can't divide by zero");
        }
        else
        {
            InsertAtEnd(1, quo);
            InsertAtEnd(0, rem);
        }
    }
    else
    {
        // for loop to store needed digits for current division
        for (i = 0; i < DigitListSize(N2_temp); i++)
        {
            InsertAtEnd(N1_temp->Data, rem);
            N1_temp = N1_temp->Next;
        }

        // for loop to find the multiple of current dividend number
        for (i = 0; i < 10; i++)
        {

            InsertAtEnd(i, mp);
            r_mul = Mul(N2_temp, mp->Next);
            if (!CMP(rem->Next, r_mul->Next))
                break;
            DeleteList(mp);
            DeleteList(r_mul);
        }

        DeleteList(mp);
        DeleteList(r_mul);

        InsertAtEnd(i - 1, mp);

        r_mul = Mul(N2_temp, mp->Next);
        rem = Sub(rem->Next, r_mul->Next);

        InsertAtEnd(i - 1, quo);
        DeleteList(mp);
        DeleteList(r_mul);

        while (N1_temp != NULL)
        {
            InsertAtEnd(N1_temp->Data, rem);
            // Checking if the remaining digits of the divident are zeroes
            if (Add(rem->Next, z->Next)->Next->Data == 0)
            {
                InsertAtEnd(0, quo); // Insert a zero to the quotient each time
                N1_temp = N1_temp->Next;
                continue;
            }
            // While loop to skip zeroes on the left
            while (rem->Next->Data == 0)
            {
                rem = rem->Next;
            }

            for (i = 0; i < 10; i++)
            {
                InsertAtEnd(i, mp);
                r_mul = Mul(N2_temp, mp->Next);
                if (!CMP(rem->Next, r_mul->Next))
                    break;
                DeleteList(mp);
                DeleteList(r_mul);
            }
            DeleteList(mp);
            DeleteList(r_mul);

            InsertAtEnd(i - 1, mp);
            r_mul = Mul(N2_temp, mp->Next);
            rem = Sub(rem->Next, r_mul->Next);
            InsertAtEnd(i - 1, quo);
            DeleteList(mp);
            DeleteList(r_mul);
            N1_temp = N1_temp->Next;
        }
        // While loop for removing extra zeores on the left
        while (quo->Next->Data == 0)
        {
            Delete(0, quo);
        }
        if (Add(rem->Next, z->Next)->Next->Data == 0)
        {
            rem=z;
        }
        else
        {
            while(rem->Next->Data==0)
                Delete(0,rem);
        }
    }
    printf("\nRemainder is \t");
    PrintList(rem);
    printf("Quotient is \t");
    return quo;
}
// Function for displaying the menu options
void displaymenu()
{
    printf("Choose one of the following options:\n1-Addition\n2-Subtraction\n3-Multiplication\n4-Division\n5-Print last result to output file\n6-Quit\n");
}

int main()
{
    printf("Welcome!Enter 1 to read the data from the file or enter -1 to exit the program");
    int op1;
    int op;
    scanf("%d", &op1);
    // Creating a pointer to the output file
    FILE *output = fopen("test.txt", "a");
    // Reading Data and displaying menu
    while (op1 != -1)
    {
        if (op1 == 1)
        {
            struct node *all_numbers;
            all_numbers = ReadData();
            printf("Choose the numbers to perform operations on or enter 0 to exit the program");
            int N1, N2;
            scanf("%d", &N1);
            if (N1 == 0)
                break;
            scanf("%d", &N2);
            if (N2 == 0)
                break;
            // Prev pointer used here to point to the fisrt digit of the stored number from the corresponding index node
            struct node *no1 = Find(N1, all_numbers)->Prev;
            struct node *no2 = Find(N2, all_numbers)->Prev;
            displaymenu();
            scanf("%d", &op);
            // Creating an empty linked list to store result of operations
            struct node *R = MakeEmpty(R);

            while (op != 6)
            {

                // Addition Option
                if (op == 1)
                {
                    // If statements to check different mathematical situations to deal with negative numbers
                    if (no1->Data < 0 && no2->Data < 0)
                    {
                        struct node *P1 = no1;
                        P1->Data *= -1;

                        struct node *P2 = no2;
                        P2->Data *= -1;

                        R = Add(P1, P2);
                        P1->Data *= -1;
                        P2->Data *= -1;
                    }

                    else if (no1->Data < 0 && no2->Data >= 0)
                    {
                        struct node *P1 = no1;
                        P1->Data *= -1;
                        if (CMP(P1, no2) == 1)
                        {
                            R = Sub(P1, no2);
                            R->Next->Data *= -1;
                        }
                        else if (CMP(no1, no2) == 0)
                        {
                            R = Sub(no2, no1);
                        }
                        P1->Data *= -1;
                    }

                    else if (no1->Data >= 0 && no2->Data < 0)
                    {
                        struct node *P2 = no2;
                        P2->Data *= -1;
                        if (CMP(P2, no1) == 1)
                        {
                            R = Sub(P2, no1);
                            R->Next->Data *= -1;
                        }
                        else if (CMP(P2, no1) == 0)
                        {
                            R = Sub(no1, P2);
                        }
                        P2->Data *= -1;
                    }
                    else if (no1->Data >= 0 && no2->Data >= 0)
                    {
                        R = Add(no1, no2);
                    }

                    PrintList(R);
                }

                // Subtration Option
                else if (op == 2)
                {
                    // If statements to check different mathematical situations to deal with negative numbers
                    if (no1->Data < 0 && no2->Data < 0)
                    {
                        no1->Data *= -1;
                        no2->Data *= -1;
                        if (CMP(no1, no2))
                            R = Sub(no1, no2);

                        else if (CMP(no1, no2) == 0)
                            R = Sub(no2, no1);
                    }

                    else if (no1->Data < 0 && no2->Data >= 0)
                    {
                        no1->Data *= -1;
                        R = Add(no1, no2);
                        R->Next->Data *= -1;
                        no1->Data *= -1;
                    }

                    else if (no1->Data >= 0 && no2->Data < 0)
                    {
                        no2->Data *= -1;
                        R = Add(no1, no2);
                        no2->Data *= -1;
                    }

                    else if (no1->Data >= 0 && no2->Data >= 0)
                    {
                        if (CMP(no1, no2))
                            R = Sub(no1, no2);
                        else
                        {
                            R = Sub(no2, no1);
                            R->Next->Data *= -1;
                        }
                    }

                    PrintList(R);
                }
                // Multiplication Option
                else if (op == 3)
                {
                    // If statements to check different mathematical situations to deal with negative numbers
                    if (no1->Data < 0 && no2->Data < 0)
                    {
                        no1->Data *= -1;
                        no2->Data *= -1;
                        R = Mul(no1, no2);
                        no1->Data *= -1;
                        no2->Data *= -1;
                    }

                    else if (no1->Data < 0 && no2->Data >= 0)
                    {
                        no1->Data *= -1;
                        R = Mul(no1, no2);
                        R->Next->Data *= -1;
                        no1->Data *= -1;
                    }

                    else if (no1->Data >= 0 && no2->Data < 0)
                    {
                        no2->Data *= -1;
                        R = Mul(no1, no2);
                        R->Next->Data *= -1;
                        no2->Data *= -1;
                    }

                    else if (no1->Data >= 0 && no2->Data >= 0)
                        R = Mul(no1, no2);

                    PrintList(R);
                }
                // Division Option
                else if (op == 4)
                {
                    // If statements to check different mathematical situations to deal with negative numbers
                    if (no1->Data < 0 && no2->Data < 0)
                    {
                        no1->Data *= -1;
                        no2->Data *= -1;
                        if (CMP(no1, no2))
                        {
                            R = Div(no1, no2);
                            PrintList(R);
                        }

                        else
                            printf("Dividend is smaller than divisor\n");
                        no1->Data *= -1;
                        no2->Data *= -1;
                    }

                    if (no1->Data < 0 && no2->Data > 0)
                    {
                        no1->Data *= -1;
                        if (CMP(no1, no2))
                        {
                            R = Div(no1, no2);
                            R->Next->Data *= -1;
                            PrintList(R);
                        }

                        else
                            printf("Dividend is smaller than divisor\n");
                        no1->Data *= -1;
                    }

                    else if (no1->Data >= 0 && no2->Data < 0)
                    {
                        no2->Data *= -1;
                        if (CMP(no1, no2))
                        {
                            R = Div(no1, no2);
                            R->Next->Data *= -1;
                            PrintList(R);
                        }

                        else
                            printf("Dividend is smaller than divisor\n");
                        no2->Data *= -1;
                    }

                    else if (no1->Data >= 0 && no2->Data > 0)
                    {
                        if (CMP(no1, no2))
                        {
                            R = Div(no1, no2);
                            PrintList(R);
                        }
                        else
                            printf("Dividend is smaller than divisor\n");
                    }

                    if (no2->Data == 0)
                        printf("Can't divide by zero\n");
                }
                // Print Result Option: Prints latest result
                else if (op == 5)
                {
                    struct node *P = R;
                    if (IsEmpty(R))
                        printf("No operation has been carried");
                    else
                        do
                        {
                            P = P->Next;
                            fprintf(output, "%d", P->Data);
                        } while (!IsLast(P, R));
                    fprintf(output, "\n");
                }

                displaymenu();
                scanf("%d", &op);
            }
        }
        printf("Welcome!Enter 1 to read the data from the file or enter -1 to exit the program");
        scanf("%d", &op1);
    }
    printf("Program Quitted");
    return 0;
}