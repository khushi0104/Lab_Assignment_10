#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


struct Trie {
    struct Trie* children[26];
    bool endOfWord;
    int count;
};

struct Trie* createNode() {
    struct Trie* node = (struct Trie*)malloc(sizeof(struct Trie));
    
    for (int i = 0; i < 26; i++) {
        node->children[i] = NULL;
    }
    node->endOfWord = false;
    node->count = 0;

    return node;
    
}

void insert(struct Trie **ppTrie, char *word) 
{
    if (*ppTrie == NULL) {
        *ppTrie = createNode();
    }
    
    struct Trie* n = *ppTrie;

    for (int i = 0; word[i] != '\0'; i++) {
        int idx = word[i] - 'a';
        if (n->children[idx] == NULL) {
            n->children[idx] = createNode();
        }
        n = n->children[idx];
    }
    n->endOfWord = true;
    n->count++;

}

int numberOfOccurances(struct Trie *pTrie, char *word) 
{
    struct Trie *temp = pTrie; 
    for (int i = 0; word[i] != '\0'; i++) {
        int idx = word[i] - 'a';
        if (temp->children[idx] == NULL) {
            return 0;
        }
        temp = temp->children[idx];
    }

    if (temp->endOfWord) {
        return temp->count;
    }
    else {
        return 0;
    }
}

struct Trie *deallocateTrie(struct Trie *pTrie) 
{
    if (pTrie == NULL) {
        return NULL;
    }

    for (int i = 0; i < 26; i++) {
        if (pTrie->children[i] != NULL) {
            pTrie->children[i] = deallocateTrie(pTrie->children[i]);
        }
    }
    free(pTrie);
    return NULL;
}

int main(void)
{
    struct Trie* trie = NULL;
    
    //read the number of the words in the dictionary
    int n;
    scanf("%d", &n);
    getchar();

    // parse line  by line, and insert each word to the trie data structure
    char word[100];
    for (int i = 0; i < n; i++) {
        fgets(word, sizeof(word), stdin);
        word[strcspn(word, "\n")] = '\0';
        insert(&trie, word);
    }

    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i=0;i<5;i++)
    {
        printf("\t%s : %d\n",pWords[i], numberOfOccurances(trie, pWords[i]));
    }
    trie = deallocateTrie(trie);
    if (trie != NULL)
       printf("There is an error in this program\n");
    return 0;
}