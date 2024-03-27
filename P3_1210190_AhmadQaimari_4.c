//Name : Ahmad Qaimari
//Student ID : 1210190
//Section : 4
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

//Declaring the struct of the BST
typedef struct Node *TNode;
struct Node
{
    int ID;
    char name[20];
    char city[20];
    int class_id;
    char date[20];
    TNode left;
    TNode right;
};
//Function to print the BST contents by tracing it inorderly
void Printinorder(TNode T)
{
    if (T != NULL)
    {
        Printinorder(T->left);
        printf("%s\t%d\t%s\t%d\t%s\n", T->name, T->ID, T->city, T->class_id, T->date);
        Printinorder(T->right);
    }
}
//Function to search for a student given the ID
TNode find(int x, TNode root)
{
    if (root == NULL)
        return NULL;
    if (root->ID == x)
    {
        return root;
    }
    else if (x < root->ID)
    {
        return find(x, root->left);
    }
    else
    {
        return find(x, root->right);
    }
}
//Function to find the leftmost node in the BST
TNode findMin(TNode root)
{
    if (root == NULL)
        return NULL;
    else if (root->left == NULL)
        return root;
    else
        return findMin(root->left);
}
//Function to find the rightmost node int he BST
TNode findMax(TNode root)
{
    if (root == NULL)
        return NULL;
    else if (root->right == NULL)
        return root;
    else
        return findMax(root->right);
}
//Function to Delete a student from the BST given its ID
TNode Delete(int x, TNode T)
{
    TNode temp;
    if (T == NULL){
        printf("Empty tree");
    }
        
    else if (x < T->ID)
        T->left = Delete(x, T->left);
    else if (x > T->ID)
        T->right = Delete(x, T->right);
    else if (T->left && T->right)
    {
        temp = findMin(T->right);
        T->ID = temp->ID;
        strcpy(T->name, temp->name);
        strcpy(T->date, temp->date);
        T->class_id = temp->class_id;
        strcpy(T->city, temp->city);
        T->right = Delete(T->ID, T->right);
    }
    else
    {
        temp = T;
        if (T->left == NULL)
            T = T->right;
        else if (T->right == NULL)
            T = T->left;

        free(temp);
    }
    return T;
}
//Function to initialize a BST with a given ID
struct Node *CreateTNode(int ID)
{
    struct Node *newNode = malloc(sizeof(struct Node));

    newNode->ID = ID;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}
//Function to insert a student ID in accordance with the BST rules given its ID
struct Node *Insert(int ID, TNode root)
{
    if (root == NULL)
    { // the tree is empty
        root = CreateTNode(ID);
        return root;
    }

    else if (ID < root->ID)
    {
        root->left = Insert(ID, root->left);
    }
    else
    {
        root->right = Insert(ID, root->right);
    }
    return root;
}

//Function to insert a student's information as given by the user
struct Node *InsertStudent(TNode T)
{
    int entered_id;
    printf("Enter the student ID or enter -1 to exit");
    scanf("%d", &entered_id);
while(entered_id!=-1){
     if (find(entered_id, T) == NULL)
    {
        T = Insert(entered_id, T);
        TNode new_student = find(entered_id, T);
        char entered_info[100];
        printf("Enter the student's name,city,class id and the date of enrollment in that order\n");
        scanf("%s", entered_info);
        int i = 0;
        char *p = strtok(entered_info, ",");//Using strtok to divide the info from the string 
        char *array[4];

        while (p != NULL)//iterating through the tokens
        {
            array[i++] = p;
            p = strtok(NULL, ",");//storing each piece of information in an array
        }
        //Assigning the information from the user to the inserted node
        strcpy(new_student->name, array[0]);
        strcpy(new_student->city, array[1]);
        strcpy(new_student->date, array[3]);
        int cid;
        sscanf(array[2], "%d", &cid);
        new_student->class_id = cid;
        break;
    }
     else{
            printf("ID already exists,Please choose another ID or enter -1 to exit\n");
            scanf("%d",&entered_id);
     }
        
    
}
   

    return T;
}
//Function to print the menu of the update function
void DisplayInfoMenu()
{
    printf("Which info would you like to update:\n1-ID\n2-Name\n3-City\n4-class id\n5-Date of Enrollment\n6-Exit\n");
}
//Function to find a student given its ID and updating its info
TNode findandupdate(TNode T)
{
    int entered_id;
    printf("Enter the ID of the student that you wish to update his/her info");
    scanf("%d", &entered_id);
    TNode current_student = find(entered_id, T);//getting the student from its ID
    if (current_student != NULL)
    {
        printf("Student's Info :\n");
        printf("%s\t%d\t%s\t%d\t%s\n", current_student->name, current_student->ID, current_student->city, current_student->class_id, current_student->date);
        DisplayInfoMenu();
        int op;
        scanf("%d", &op);
        //Letting the user choose which info to update
        while (op != 6)
        {
            if (op == 1)
            {
                printf("Choose a new ID or press -1 to exit\n");
                int new_id;
                scanf("%d", &new_id);
                while (new_id != -1)
                {
                    if (find(new_id, T) != NULL)//CHecking if the ID already exists to prevent having multiple sudents with the same ID
                    {
                        printf("There already exists a student with the entered ID,Please choose another ID or press -1 to exit");
                        scanf("%d", &new_id);
                    }
                    else
                    {
                        current_student->ID = new_id;
                        printf("ID Updated\n");
                        break;
                    }
                }
            }
            else if (op == 2)
            {
                printf("Choose a new name or press -1 to exit\n");
                char new_name[20];
                scanf("%s", new_name);
                if (strcmp(new_name, "-1"))
                {
                    strcpy(current_student->name, new_name);
                    printf("Name Updated\n");
                }
            }

            else if (op == 3)
            {
                printf("Choose a new city or press -1 to exit\n");
                char new_city[20];
                scanf("%s", new_city);
                if (strcmp(new_city, "-1"))
                {
                    strcpy(current_student->city, new_city);
                    printf("City Updated\n");
                }
            }
            else if (op == 4)
            {
                printf("Choose a new class ID or press -1 to exit\n");
                int new_class_id;
                scanf("%d", &new_class_id);
                if (new_class_id != -1)
                {
                    current_student->class_id = new_class_id;
                    printf("Class ID Updated\n");
                }
            }
            else if (op == 5)
            {
                printf("Choose a new date of enrollment or press -1 to exit");
                char new_date[20];
                scanf("%s", new_date);
                if (strcmp(new_date, "-1"))
                {
                    strcpy(current_student->date, new_date);
                    printf("Date of enrollment Updated\n");
                }
            }
            printf("\nStudent Info After Updating:\n");
            printf("\n%s\t%d\t%s\t%d\t%s\n\n", current_student->name, current_student->ID, current_student->city, current_student->class_id, current_student->date);

            DisplayInfoMenu();
            scanf("%d", &op);
        }
        printf("\nUpdate Info Menu Quitted\n");
    }

    else
        printf("\nStudent with entered ID doesn't exist\n\n");

    return T;
}

//Function to students into another tree sorted by names
TNode InsertLex(char Name[], int ID, char city[], int class_id, char date[], TNode T)
{
    char entered_temp[20];
    strcpy(entered_temp, Name);
    if (T == NULL)//CHecking if the tree is empty
    {
        T = (TNode)malloc(sizeof(struct Node));

        T->ID = ID;
        strcpy(T->name, entered_temp);
        strcpy(T->city, city);
        T->class_id = class_id;
        strcpy(T->date, date);
        T->left = T->right = NULL;
    }
    else if (T != NULL)
    {
        char tree_temp[20];
        strcpy(tree_temp, T->name);
        if (strcmp(strlwr(Name), strlwr(tree_temp)) <= 0)//Using strlwr to make sure the names are ordered correctly
            T->left = InsertLex(entered_temp, ID, city, class_id, date, T->left);
        else
            T->right = InsertLex(entered_temp, ID, city, class_id, date, T->right);
    }

    return T;
}
//Function to copy the BST's contents into another tree and sorting it by name
TNode CloneTree(TNode names, TNode T)
{
    if (T->left != NULL)
        names = CloneTree(names, T->left);

    names = InsertLex(T->name, T->ID, T->city, T->class_id, T->date, names);

    if (T->right != NULL)
        names = CloneTree(names, T->right);

    return names;
}
//Function to search for students that live in a given city by tracing it inorderly
int SearchCitizens(char city[], TNode sorted, int flag)
{
    if (sorted != NULL)
    {
        strlwr(city);
        flag = SearchCitizens(city, sorted->left, flag);//flag is used to check if there aren't any students in the given city

        char temp[20];
        strcpy(temp, sorted->city);//Using strlwr to eliminate case-sensitivity
        strlwr(temp);

        if (strcmp(temp, city) == 0)
        {
            flag = 1;
            printf("%s\t%d\t%s\t%d\t%s\n", sorted->name, sorted->ID, sorted->city, sorted->class_id, sorted->date);
        }

        flag = SearchCitizens(city, sorted->right, flag);
    }

    return flag;
}
//Function to print the students that study in the same given class by tracing it inorderly
void SearchClasses(int class_id, TNode sorted)
{

    if (sorted != NULL)
    {
        SearchClasses(class_id, sorted->left);

        if (sorted->class_id == class_id)
            printf("%s\t%d\t%s\t%d\t%s\n", sorted->name, sorted->ID, sorted->city, sorted->class_id, sorted->date);
        SearchClasses(class_id, sorted->right);
    }
}

//Function to check if the given class is empty
int isEmptyClass(int class_id, TNode sorted, int flag)
{

    if (sorted->left != NULL)
        flag = isEmptyClass(class_id, sorted->left, flag);

    if (sorted->class_id == class_id)
        flag = 0;

    if (sorted->right != NULL)
        flag = isEmptyClass(class_id, sorted->right, flag);

    return flag;
}
//Function to print only the non-empty class
void PrintClasses(TNode sorted)
{
    int flag = 1;
    for (int i = 1; i < 13; i++)
    {
        if (!isEmptyClass(i, sorted, flag))
        {
            SearchClasses(i, sorted);
            printf("\n");
        }
    }
}
//Function to save all students from the tree to a file
void SaveToFile(TNode T, FILE *students_file)
{
    if (T != NULL)
    {
        SaveToFile(T->left, students_file);
        fprintf(students_file, "%s|%d|%s|%d|%s\n", T->name, T->ID, T->city, T->class_id, T->date);
        SaveToFile(T->right, students_file);
    }
}
//Function too read from a file that already has saved data into a tree
TNode ReadFromFile(TNode T, FILE *students_file)
{

    char n1[250];
    while (fgets(n1,250,students_file)!=NULL)
    {
        n1[strcspn(n1, "\n")] = 0;
        int i = 0;
        char *p = strtok(n1, "|");//using strtok to divide the lines in the file to pieces of information
        char *arr[5];
        while (p != NULL)//saving the pieces of information in an array
        {
            arr[i++] = p;
            p = strtok(NULL, "|");
        }
        //assigning information to a node and inserting it in a tree
        int id = atoi(arr[1]);
        T = Insert(id, T);
        TNode new_student = find(id, T);
        strcpy(new_student->name, arr[0]);
        strcpy(new_student->city, arr[2]);
        new_student->class_id = atoi(arr[3]);
        strcpy(new_student->date, arr[4]);
    }

    return T;
}
//Function to check if a file is empty
int isEmptyFile(FILE *students_file)
{
    if (NULL != students_file)
    {
        fseek(students_file, 0, SEEK_END);//fseek is used to go through the file until its end and check if it has any saved bytes
        int size = ftell(students_file);//ftell is used to return the current file position after going through its's bits,if 0 then the file is empty

        if (size != 0)
        {
            fseek(students_file, 0, SEEK_SET);
            return 0;
        }
    }
    rewind(students_file);
    return 1;
}
//Function to display the main menu of the program
void DisplayMainMenu()
{
    printf("Choose one of the following options:\n1-Insert a Student\n2-Find a Student and update Info\n3-List Students in Lexicographic Order of their Names\n4-List Students from a certain city\n5-List all students by their class in lexicographic order of their names\n6-Delete a Student\n7-Save all Students to a File\n8-Exit");
}

int main()
{
    // TNode root = NULL;
    // TNode names=NULL;
    // root=Insert(2,root);
    // root=Insert(1,root);
    // root=Insert(3,root);
    // strcpy(root->name,"ahmad");
    // strcpy(root->left->name,"qussay");
    // strcpy(root->right->name,"sam");
    // strcpy(root->city,"ram");
    // strcpy(root->date,"20-5");
    // strcpy(root->left->city,"ram");
    // strcpy(root->left->date,"20-5");
    // strcpy(root->right->city,"ram");
    // strcpy(root->right->date,"20-5");
    // root->class_id=12;
    // root->left->class_id=12;
    // root->right->class_id=12;
    // int id = 3;
    // if(find(id,root)!=NULL)
    //     root=Delete(id,root);
    // Printinorder(root);
    
    FILE *students_file;
    students_file = fopen("students.dat", "r");
    
    //Initializing the main tree of the program
    TNode main_tree = NULL;
    if(!isEmptyFile(students_file))
        main_tree = ReadFromFile(main_tree, students_file);
    fclose(students_file);

    //Start of interactable part of the program
    DisplayMainMenu();
    int op;
    scanf("%d", &op);
    //Main loop for the program menu
    while (op != 8)
    {
        if (op == 1)
        {
            main_tree = InsertStudent(main_tree);
        }

        else if (op == 2)
        {
            if(main_tree==NULL)
                printf("No saved students \n");
            else{
                main_tree = findandupdate(main_tree);
            }

            
        }

        else if (op == 3)
        {
            if(main_tree==NULL)
                printf("No saved students \n");
            else{
            TNode sorted_lex = NULL;
            //saving the BST in a tree ordered by names
            sorted_lex = CloneTree(sorted_lex, main_tree);
            Printinorder(sorted_lex);
            }
            
        }

        else if (op == 4)
        {
            if(main_tree==NULL)
                printf("No saved students \n");
            else{
            TNode sorted_lex = NULL;
            sorted_lex = CloneTree(sorted_lex, main_tree);
            char entered_city[20];
            printf("Enter the city that you want to list its citizens\n");
            scanf("%s", entered_city);
            int flag = 0;
            flag = SearchCitizens(entered_city, sorted_lex, flag);
            //if-statement to check if there aren't any students from the given city
            if (!flag)
                printf("There are no students are from the entered city\n");
            }
            
        }

        else if (op == 5)
        {
            if(main_tree==NULL)
                printf("No saved students \n");
            else{
            TNode sorted_lex = NULL;
            //saving the BST in a tree ordered by names
            sorted_lex = CloneTree(sorted_lex, main_tree);
            PrintClasses(sorted_lex);
            }
            
        }

        else if (op == 6)
        {
        if(main_tree==NULL)
                printf("No Saved Sudents\n");
        else{
             int entered_id;
            printf("Enter the ID of the student you want to delete or enter -1 to exit\n");
            scanf("%d", &entered_id);
            while(entered_id!=-1){
                if(find(entered_id,main_tree)!=NULL){
                    main_tree = Delete(entered_id, main_tree);
                    break;
                    }
                else{
                   printf("Student with entered ID doesn't exist,enter a new ID or enter -1 to exit");
                   scanf("%d",&entered_id);
                }
                    
            }
        }
            
        }

        else if (op == 7)
        {
             if(main_tree==NULL)
                printf("No saved students \n");
            else{
            //Opening the file in append mode to write students in seperate lines
            students_file = fopen("students.dat", "a");
            SaveToFile(main_tree, students_file);
            fclose(students_file);
            printf("Students saved to file successfully\n");
            }
            
        }

        DisplayMainMenu();
        scanf("%d", &op);
    }

    printf("\nProgram Quitted");

    return 0;
 }

