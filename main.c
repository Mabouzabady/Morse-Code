#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct Node
{
    char data;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct
{

    char letter;
    char morse[6];
} Convert;
//Array of struct used to find the mosre using the latin letters and to insert the binary tree
Convert arry[27] = {{' ', "/ "}, {'a', ".- "}, {'b', "-... "},{'c', "-.-. "}, {'d',"-.. "}, {'e', ". "}, {'f',"..-. "}, {'g', "--. "}, {'h',".... "},{'i', ".. "},
    {'j',".--- "},{'k', "-.- "}, {'l',".-.. "}, {'m', "-- "}, {'n',"-. "},{'o', "--- "}, {'p',".--. "}, {'q', "--.- "}, {'r',".-. "},{'s', "... "},
    {'t',"- "},{'u', "..- "}, {'v',"...- "}, {'w', ".-- "}, {'x',"-..- "}, {'y',"-.-- "}, {'z',"--.. "}
};
int stat[26] = {0};
//convert from text to morse
void textMorse()
{
    int dot=0;
    int dash=0;
    char text[99];
    printf("Enter the Text you want to convert\n");
    scanf(" %[^\n]", text);

    for (int i=0; text[i]!='\0' ; i++) //to access all the letters
    {
        for (int j=0; j<27; j++) // to compare accessed letters with the array of struct
        {
            if(tolower(text[i])==arry[j].letter)  // to check that all the capital letters are small
            {
                printf("%s", arry[j].morse);

                for(int i=0; arry[j].morse[i]!='\0'; i++)
                {
                    if (arry[j].morse[i]=='.')
                        dot++; // count dots
                    if (arry[j].morse[i]=='-')
                        dash++;
                } // count dashes
                break;
            }
        }
    }
    /*print number of dots and dashes in that simple way*/
    printf("\n The code has %d Dot(s)", dot);
    printf("\n The code has %d Dash(es)", dash);
}
// convert from Morse code to latin letters
void MorseText(Node *tree)
{
    char morse[99];
    printf("Enter The Morse you want to convert\n");
    scanf(" %[^\n]", morse);
    Node *temp = tree; // To make the tree balanced and not to affect its values
    int x = strlen(morse);
    for (int i=0; i< x; i++)
    {

        if(morse[i]=='.') //According to morse code diagram
            //dots are on the left
        {
            temp = temp->left;
        }

        if(morse[i]=='-')
        {
            // dashes are on the right
            temp = temp->right;
        }

        if (morse[i] =='/') //it means starting a new word, print space
        {
            printf(" ");
        }
// in case the string contain a space it means that is the end of the letter
//so it prints the data that the temp refers to
        if (morse[i] ==' ')
        {
            printf("%c", temp->data);
// change the value of the intialized zero array if a letter found
                  if(islower(temp->data))
                stat[temp->data-'a']++;

// we make temp refers to the head of the tree again to start searching for a new value
            temp = tree;
        }
    }
}

void FILE_MorseText(Node *tree)
{

   Node *temp = tree;
   FILE *fl;
   FILE *fl2;
   fl=fopen("Morse.txt", "r");
   char morse[150];
   fl2=fopen("Text.txt", "w");
   while (!feof(fl)){
   fgets(morse, 150, fl);
   int x = strlen(morse);
       for (int i=0; i< x; i++)
    {

        if(morse[i]=='.') //According to morse code diagram
            //dots are on the left
        {
            temp = temp->left;
        }

        if(morse[i]=='-')
        {
            // dashes are on the right
            temp = temp->right;
        }

        if (morse[i] =='/') //it means starting a new word, print space
        {
            fprintf(fl2, " ");
        }
// in case the string contain a space it means that is the end of the letter
//so it prints the data that the temp refers to
        if (morse[i] ==' ')
        {
            fprintf(fl2, "%c", temp->data);
// change the value of the intialized zero array if a letter found
                if(islower(temp->data))
                stat[temp->data-'a']++;

// we make temp refers to the head of the tree again to start searching for a new value
            temp = tree;
        }
    }
   }
   fclose(fl);
   fclose(fl2);

}
void FILE_textMorse()
{
  int dot=0;
  int dash=0;


   FILE *fl;
   FILE *fl2;
   fl=fopen("Text.txt", "r");
   char text[150];
   fl2=fopen("Morse.txt", "w");
   while (!feof(fl)){
   fgets(text, 150, fl);

       for (int i=0; text[i]!='\0' ; i++) //to access all the letters
    {
        for (int j=0; j<27; j++) // to compare accessed letters with the array of struct
        {
            if(tolower(text[i])==arry[j].letter)  // to check that all the capital letters are small
            {
                fprintf(fl2, "%s", arry[j].morse);

                for(int i=0; arry[j].morse[i]!='\0'; i++)
                {
                    if (arry[j].morse[i]=='.')
                        dot++; // count dots
                    if (arry[j].morse[i]=='-')
                        dash++;
                } // count dashes
                break;
            }
        }
    }
   }
   fclose(fl);
   fclose(fl2);
    printf("\n The code has %d Dot(s)", dot);
    printf("\n The code has %d Dash(es)", dash);
}
//Function creats an empty node with 2 NULL pointers
Node* create()
{

    Node* node = malloc(sizeof(Node));

    node->left= NULL;
    node->right= NULL;
    node->data = '\0';
    return node;
}
// Insert letters in tree using the array of structs
Node* Insert(Node *tree, char letter, char *morse)
{
// insertion is based on the morse code of letters and a key -latin letter-
    if(tree==NULL)
    {
        tree = create();
    }
// if the pointer refers to nothing, it creates an empty node with 2 NULL pointers
    if(*morse==' ')
    {
        tree->data = letter;
    }
// we insert the letter in case a space found
    if(*morse == '.')
    {
        tree->left = Insert((tree->left), letter, morse+1);
    }
// follow the same strategy of the diagra
// . go left
    if(*morse == '-')
    {
        tree->right = Insert((tree->right), letter, morse+1);
    }

// - go right
    return tree;
}


void delete_Tree(Node *tree)
{
    if (tree == NULL)  //Empty Tree Nothing to delete
      return;
    delete_Tree(tree->left);
    delete_Tree(tree->right);
    free(tree);
}
int main()
{
    int input;
    printf("                                    Welcome To Morse Code System\n");
    printf("                               This System coded by Abouzabady Mohamed\n");
    printf("                          Student at Budapest University of Technology and Economics\n\n\n\n\n");
    while(1)  // infinite loop to repeat the same lines till the user stops the program
    {
        printf("\n\nChoose an Option to Continue\n");
        printf("1. Convert From Text To Morse\n");
        printf("2. Convert From Morse To Text\n");
        printf("3. Convert From Morse To Text Using Files\n");
        printf("4. Convert From Text To Morse Using Files\n");
        printf("5. Exit From The System\n");
        scanf("%d", &input);
        switch(input)
        {

        case 1:
        {
            textMorse();
            break;
        }

        case 2:
        {
            Node* tree = create(); // Intialize the first node that will be empty
            // to get e as a left child, and t as a right child
            for (int i=1; i<27; i++ )
            {
                // loop to insert the letters in the tree using the array of structs
                tree = Insert(tree, arry[i].letter, arry[i].morse);
            }
            MorseText(tree);
            printf("\nLetter      Times\n");
            for(int i=0; i<26; i++)
            {
                printf("  %c           %d\n", i+97, stat[i]); // printing the letters with Ascii code and the number of repeted times

            }
            for(int i=0; i<26; i++)
            {
                stat[i]=0;
            }
            delete_Tree(tree);  //free the tree and delete all the elements of the tree

            break;
        }

        case 3:

            {
            Node* tree = create(); // Intialize the first node that will be empty
            // to get e as a left child, and t as a right child
            for (int i=1; i<27; i++ )
            {
                // loop to insert the letters in the tree using the array of structs
                tree = Insert(tree, arry[i].letter, arry[i].morse);
            }
            FILE_MorseText(tree);
            printf("\nLetter      Times\n");
            for(int i=0; i<26; i++)
            {
                printf("  %c           %d\n", i+97, stat[i]); // printing the letters with Ascii code and the number of repeted times
            }
            for(int i=0; i<26; i++)
            {
                stat[i]=0;
            }
            delete_Tree(tree);  //free the tree and delete all the elements of the tree

            break;
        }

        case 4:
            {
                FILE_textMorse();
                break;
            }


        case 5:
        {
            exit(0); // Stop the while loop and end the program
        }
        default:
        {
            printf("Invalid Input"); // and other input rather than 1, 2 or 3
            break;
        }
        }
    }

    return 0;
}

