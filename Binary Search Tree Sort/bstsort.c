/*
    Student Name: Christian Agosto
    Panther ID: 5768463
    Describtion: This program recieves input (wether regular or a file
    from the command line input), and implements a binary search tree
    sorting algorithm. usage: bstsort [-c] [-o output_file_name] [input_file_name]
    if -c, the input will be test with Case Sensitive comparison, else it would
    be Insensitive. If -o is added, the input will be outputed to that file.
    If an input file is provided then the program will read the content and
    outputed to the screen or the output file. If there is no command line
    input then everything will be done on screen.

    I affirm that I wrote this program myself without any help
    form any other people or source from the internet.
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

/* Node struct that contain data as: string from the file or input,
count for ocurrence of each string and,
left and right child of the root/parent */
typedef struct Node
{
  char* data; //information given from input or file
  int count;  //count the number of ocurrence of data
  struct Node *left; //left child (smaller)
  struct Node *right; //right child (bigger)
} Node;

/*Case sensitive insertion method: Upper case letter would go first*/
Node* insertSensitive(Node *node, char* info)
{
  if (node == NULL)
  {
    Node *tmp;
    tmp = (Node*)malloc(sizeof(Node));
    tmp->data = strdup(info);
    tmp->count = 1;
    tmp->left = tmp->right = NULL;
    return tmp;
  }

  if (sensitiveComparison(node->data, info) < 0)
  {
    node->right = insertSensitive(node->right, info);
  }

  else if (sensitiveComparison(node->data, info) > 0)
  {
    node->left = insertSensitive(node->left, info);
  }

  return node;
}

/*Insensitive insertion method: only if the case was taken to run the
  program if no c flag was provided*/
Node* insertInsensitive(Node *node, char* info)
{
  if (node == NULL)
  {
    Node *tmp;
    tmp = (Node*)malloc(sizeof(Node));
    tmp->data = strdup(info);
    tmp->count = 1;
    tmp->left = tmp->right = NULL;
    return tmp;
  }

  if (insesitveComparison(node->data, info) < 0)
  {
    node->right = insertInsensitive(node->right, info);
  }

  else if (insesitveComparison(node->data, info) > 0)
  {
    node->left = insertInsensitive(node->left, info);
  }

  return node;
}

/*Sensitive method to search: for sentitive cases, so upper case letters
  have a higher priority*/
Node* searchSensitive(Node *node, char* info)
{
  if (node == NULL)
  {
    return NULL;
  }

  if (sensitiveComparison(node->data, info) < 0)
  {
    return searchSensitive(node->right, info);
  }

  else if (sensitiveComparison(node->data, info) > 0)
  {
    return searchSensitive(node->left, info);
  }

  else
  {
    return node;
  }
}

/* Insensitive method to search: for line with no sentitive cases*/
Node* searchInsensitive(Node *node, char* info)
{
  if (node == NULL)
  {
    return NULL;
  }

  if (insesitveComparison(node->data, info) < 0)
  {
    return searchInsensitive(node->right, info);
  }

  else if (insesitveComparison(node->data, info) > 0)
  {
    return searchInsensitive(node->left, info);
  }

  else
  {
    return node;
  }
}

/* Insensitive method to compare string: will check if two line have
   the same character no matter if one is uppercase and the other lower.*/
int insesitveComparison(char *line1, char *line2)
{
  int index = 0; //for strings index
  int check = 0; //to check if equal(0) or if one is larger(1 or -1)
  bool flag = true; //true if they are equal

  while (flag)
  {
    if (isupper(line1[index]) || isupper(line2[index]))
    {
      if (isupper(line1[index]))
      {
        char temp = line1[index] + 32;

        if(temp < line2[index])
        {
          check = -1;
          flag = false;
        }

        else if (temp == line2[index])
        {
          check = 0;
          flag = true;
          index++;
        }

        else if (temp > line2[index])
        {
          check = 1;
          flag = false;
        }
      }

      if (isupper(line2[index]))
      {
        char temp = line2[index] + 32;

        if(line1[index] < temp)
        {
          check = -1;
          flag = false;
        }

        else if (line1[index] == temp)
        {
          check = 0;
          flag = true;
          index++;
        }

        else if (line1[index] > temp)
        {
          check = 1;
          flag = false;
        }
      }

      if (isupper(line1[index]) && isupper(line2[index]))
      {
        char temp = line1[index] + 32;
        char temp1 = line2[index] + 32;

        if (temp < temp1)
        {
          check = -1;
          flag = false;
        }

        else if (temp == temp1)
        {
          check = 0;
          flag = true;
          index++;
        }

        else if (temp > temp1)
        {
          check = 1;
          flag = false;
        }
      }
    }

    else
    {
      if (line1[index] < line2[index])
      {
        check = -1;
        flag = false;
      }

      else if (line1[index] == line2[index])
      {
        check = 0;
        flag = true;
        index++;
      }

      else if (line1[index] > line2[index])
      {
        check = 1;
        flag = false;
      }
    }

    if (flag == true && check == 0 && index == strlen(line1)-1)
    {
      flag = false;
    }
  }

  return check;
}

/* Sensitive method to compare strings: will check if every character is
   the same. Meaning that if c and C are being compared, it would be false.*/
int sensitiveComparison(char *line1, char *line2)
{
    int index = 0; //for strings index
    int check = 0; //to check if equal(0) or if one is larger(1 or -1)
    bool flag = true; //true if they are equal

  while (flag)
  {
    if (isupper(line1[index]) || isupper(line2[index]))
    {
      if (isupper(line1[index]) && islower(line2[index]))
      {
        check = -1;
        flag = false;
      }

      else if (islower(line1[index]) && isupper(line2[index]))
      {
        check = 1;
        flag = false;
      }

      else
      {
        if (line1[index] < line2[index])
        {
          check = -1;
          flag = false;
        }

        if (line1[index] == line2[index])
        {
          index++;
          flag = true;
        }

        if (line1[index] > line2[index])
        {
          check = 1;
          flag = false;
        }
      }
    }

    else if ((isupper(line1[index]) && isupper(line2[index]))
     || (islower(line1[index]) && islower(line2[index])))
    {
      if (line1[index] < line2[index])
      {
        check = -1;
        flag = false;
      }

      if (line1[index] == line2[index])
      {
        index++;
        flag = true;
      }

      if (line1[index] > line2[index])
      {
        check = 1;
        flag = false;
      }
    }

    if (flag == true && check == 0 && index == strlen(line1)-1)
    {
      flag = false;
    }
  }

  return check;
}

/* In Order method to output: 1. left child, 2.parent, 3. right*/
void inOrder(Node* node)
{
  if (node == NULL)
  {
    return;
  }

  inOrder(node->left);
  printf("%d %s\n", node->count, node->data);
  inOrder(node->right);
}

/*In Order Method to output results to output file:
  1. left child, 2.parent, 3. right */
void inOrderOutput(Node* node, FILE *output)
{
  if (node != NULL)
  {
    inOrderOutput(node->left, output);
    fprintf(output, "%d %s\n", node->count, node->data);
    inOrderOutput(node->right, output);
  }
}

/*Post order method: 1. left, 2. right, 3. parent*/
void postOrder(Node* node)
{
  if (node == NULL)
  {
    return;
  }

  postOrder(node->left);
  postOrder(node->right);
  free(node->data);
  free(node);
}


int main(int argc, char **argv)
{
  const int LENGHT = 100;
  extern char *optarg;
  extern int optind;
  int c = 0;
  int err = 0;
  FILE * output_file, *input_file = NULL;
  char* line = (char*)malloc(LENGHT * sizeof(char)); //Memory allocation
  Node *root = NULL;
  int cflag = 0;
  int oflag = 0;
  size_t lenght;
  ssize_t read;
  static char usage[] =
    "usage: bstsort [-c] [-o output_file_name] [input_file_name]\n";

	while ((c = getopt(argc, argv, "co:")) != -1)
		switch (c)
		{
            case 'c':
            cflag = 1;
            break;

            case 'o':
            oflag = 1;
            output_file = fopen(optarg, "w");
            break;

            case '?':
            err = 1;
            break;
		}

  //Case if there is an error which would print out the usage
  if (err == 1)
  {
    fprintf(stderr, usage, argv[0]);
    exit(1);
  }

  //Verifies if any input file was provided
  if (optind < argc)
  {
    input_file = fopen(argv[optind], "r");
  }

  //True if cflag was provided
  if (cflag == 1)
  {
    if (input_file)
    {
      while ((read = getline(&line, &lenght, input_file)) > 1)
      {
        if (line[strlen(line)-1] == '\n')
        {
          line[strlen(line)-1] = 0;
        }

        Node *searchSen = searchSensitive(root, line); //search for sentitive.

        if (strlen(line) != 1 && searchSen == NULL)
        {
          root = insertSensitive(root, line);
        }

        else if (strlen(line) != 1 && searchSen != NULL)
        {
          Node *n = searchSensitive(root, line);
          n->count += 1;
        }
      }
    }

    //else if there is no inputfile
    else
    {
      printf("Enter a line: \n");
      while ((read = getline(&line, &lenght, stdin)) > 1)
      {
        if (line[strlen(line)-1] == '\n')
        {
          line[strlen(line)-1] = 0;
        }
        Node *searchSen = searchSensitive(root, line); //search for sentitive.
        if (strlen(line) != 1 && searchSen == NULL)
        {
          root = insertSensitive(root, line);
        }
        else if (strlen(line) != 1 && searchSen != NULL)
        {
          Node *n = searchSensitive(root, line);
          n->count += 1;
        }
      }
    }
  }

  // If input file is found
  else if (input_file != NULL)
  {
    while ((read = getline(&line, &lenght, input_file)) > 1)
    {
      if (line[strlen(line)-1] == '\n')
      {
        line[strlen(line)-1] = 0;
      }

      Node *searchIns = searchInsensitive(root, line); //search insensitive

      if (strlen(line) != 1 && searchIns == NULL)
      {
      root = insertInsensitive(root, line);
      }
      else if (strlen(line) != 1 && searchIns != NULL)
      {
        Node *n = searchInsensitive(root, line);
        n->count += 1;
      }
    }
  }

  /* else, if no inputfile, get from standard input*/
  else
  {
    printf("Enter a line: \n");
    while ((read = getline(&line, &lenght, stdin)) > 1)
    {
      if (line[strlen(line)-1] == '\n')
      {
        line[strlen(line)-1] = 0;
      }

      Node *searchIns = searchInsensitive(root, line); //search insensitive

      if (strlen(line) != 1 && searchIns == NULL)
      {
        root = insertInsensitive(root, line);
      }
      else if (strlen(line) != 1 && searchIns != NULL)
      {
        Node *n = searchInsensitive(root, line);
        n->count += 1;
      }
    }
  }

  if (oflag == 1)
  {
    inOrderOutput(root, output_file);
  }

  else
  {
    inOrder(root);
  }

  postOrder(root);

  exit(0);
}
