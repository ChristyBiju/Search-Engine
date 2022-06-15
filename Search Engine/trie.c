#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include "trie.h"

// for creating a new node in trie
node_trie *new_node()
{
    node_trie *t = NULL;
    t = (node_trie *)malloc(sizeof(node_trie));
    if (!t)
    {
        return NULL;
    }
    else
    {
        int i;
        t->end_of_quest = 0;
        for (i = 0; i < 26; i++)
        {
            t->child[i] = NULL;
        }
    }
    return t;
}

// to insert the entire database from the file into the trie
node_trie *insert_from_file()
{
    node_trie *root = NULL;

    // creating a new node at root
    if ((root = (malloc(sizeof(node_trie)))) == NULL)
    {
        printf("Out of Memory");
    }

    int i;
    for (i = 0; i < 26; i++)
    {
        root->child[i] = NULL;
    }

    // value of end_of_quest of new node is kept 0
    root->end_of_quest = 0;

    int index;

    node_trie *tmp = root;

    // opening the database file
    FILE *fp = fopen("database.txt", "r+");
    if (!fp)
    {
        printf("Error in opening the database.");
    }

    char quest[10000];
    char ans[200000];

    // inserting all the questions from the database in the trie
    while ((fscanf(fp, "%s", quest)) != EOF)
    {
        // stores the ans after question in the ans array (ignoring the whitespace)
        fgets(ans, 200000, fp);

        int quest_len = strlen(quest);
        for (i = 0; i < quest_len; i++)
        {
            
            // checking if the character of the quest is alphabet or not
            if (isalpha(quest[i]))
            {
                // converting all the characters in lower case
                index = (int)tolower(quest[i]) - 'a';
            }
            
            if (quest[i] == '1')
            {
                tmp->space = 1;
                continue;
            }
            
            // for handling characters which are not alphabets
            if (index > 25 || index < 0)
            {
                continue;
            }
            // creating a new node for a character
            if (tmp->child[index] == NULL)
            {
                if ((tmp->child[index] = malloc(sizeof(node_trie))) == NULL)
                {
                    printf("Out of memory");
                }

                tmp = tmp->child[index];
                tmp->space = 0;
                int j;
                for (j = 0; j < 26; j++)
                {
                    tmp->child[j] = NULL;
                }
                tmp->end_of_quest = 0;
            }
            // if the node for that particular character is already present the move to the next node
            else
            {
                tmp = tmp->child[index];
            }
            // after reaching the end node (i.e. last character) make the value of end_of_quest as 1 and store the ans from the file in the ans of the last node
            if (i == quest_len - 1)
            {
                tmp->end_of_quest = 1;
                strcpy(tmp->ans, ans);
            }
        }

        tmp = root;
    }
    fclose(fp);
    return root;
}

char *search(node_trie *root, char *key)
{
    // char pref[100];
    node_trie *tmp = root;

    int i;
    for (i = 0; key[i] != '\0'; i++)
    {
        // pref[i] = key[i];
        int index = (int)tolower(key[i]) - 'a';
        // when a character of the question is not present then return null as that question is not present
        if (tmp->child[index] == NULL)
        {
            return NULL;
        }
        // pref[i] = key[i];
        tmp = tmp->child[index];
    }

    // after reaching the end of the question(i.e. last node) return the ans which is stored
    if (tmp->end_of_quest == 1)
    {
        return tmp->ans;
    }
    else
    {
        return NULL;
    }
}

void remove_spaces(char a[])
{
    int i = 0;
    int j = 0;
    while (a[i])
    {
        if (a[i] != ' ')
        {
            a[j++] = a[i];
        }
        i++;
    }
    a[j] = '\0';
}

// to check whether the node is the last node
int isLastNode(node_trie *root)
{
    for (int i = 0; i < 26; i++)
        if (root->child[i])
            return 0;
    return 1;
}

void suggestions(node_trie *root, char currPrefix[])
{
    // if we get the complete question print the entire question
    if (root->end_of_quest)
    {
        printf("%s\n", currPrefix);
    }

    // All children struct node pointers are NULL (when we reach the last node return)
    if (isLastNode(root))
    {
        return;
    }

    for (int i = 0; i < 26; i++)
    {

        if (root->child[i])
        {
            // append current character to currPrefix string

            int p = 97 + i;
            char c = (char)p;
            

            if (root->space == 1)
            {
                // strcat(currPrefix,"a");
                // currPrefix[strlen(currPrefix)] = 'a';
                currPrefix[strlen(currPrefix) - 1] = ' ';
            }
            
            strncat(currPrefix, &c, 1);

            // recur over the rest
            suggestions(root->child[i], currPrefix);

            // after we get the entire question make it a string
            int len = strlen(currPrefix);
            currPrefix[len - 1] = '\0';
        }
    }
}

// print suggestions for given query prefix.
int printAutoSuggestions(node_trie *root, char query[])
{
    node_trie *temp = root;

    // Check if prefix is present and find the node with last character of given string.
    int i;
    int n = strlen(query);
    for (i = 0; i < n; i++)
    {
        int index = (int)tolower(query[i]) - 'a';

        // no string in the Trie has this prefix
        if (!temp->child[index])
            return 0;

        temp = temp->child[index];
    }

    // If prefix is present as a question.
    int isWord = (temp->end_of_quest == 1);

    // If prefix is last node of tree (has no children)
    int isLast = isLastNode(temp);

    // If prefix is present as a question, but there is no subtree below the last matching node.
    if (isWord && isLast)
    {
        printf("\n \n");
        // puts(query);
        printf("*****Match Found*****\n\n");
        printf("%s", query);
        return -1;
    }

    // If there are are nodes below last matching character.
    if (!isLast)
    {
        char prefix[MAX];
        strcpy(prefix, query);
        printf("\n\nMatch Found :-\n");
        suggestions(temp, prefix);
        return 1;
    }
    return 1;
}
