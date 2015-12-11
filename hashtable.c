/* Matt Layman CS211 hashtable.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define HASH_MULTIPLIER 65599

/*Global variables*/
int htsize;

struct NodeType{
	char *word;
	int count;
	struct NodeType *next;
};
typedef struct NodeType Node;


char *lowercase(char *str)                         //convert str to lowercase
{
   char *word, *ptr;

   if ( (word = strdup(str)) !=  NULL) {
      for (ptr = word; *ptr != '\0'; ptr++)
         *ptr = tolower(*ptr);
   }
   return word;
}

unsigned int hash(const char *str){                //hash function
	int i;
	unsigned int h = 0U;

	for (i = 0; str[i] != '\0'; i++)
		h = h * HASH_MULTIPLIER + (unsigned char) str[i];

	return h % htsize;
}

Node **ht_create(void){                            //create hash table
	Node *table = (Node *) malloc(htsize);

	if (table == NULL){                            //if table cannot be allocated
	    fprintf(stderr, "ERROR: malloc failed\n"); //print error
	    return 0;
	}

	table->word = NULL;
	return 0;
}

int ht_insert(Node **Table, const char *word){     //insert word into hash table
	int i;                 //loop variable
	int h;                 //hash variable for word
	Node *w = (Node *) malloc(sizeof(Node));
	w->word = strdup(word);
	w->count = 1;

	h = hash(word);
	for (i = 0; i <= htsize; i++){
		if (strcmp(word, Table[i]->word) == 0){          //if word is in table, incr count
			Table[i]->count += 1;
		}
		else{                                      //if word is not in table, insert
			w->next = Table[h]->next;
			Table[h]->next = w;
			return 1;
		}
	}
	return 0;
}

void ht_print(Node **Table){                       //print hash table
	int i;     //loop variable

	for (i = 0; i < htsize; i++){
		if (Table[i] != NULL)
			printf("HT[%d]: %p\n", i, &Table[i]);
		else
		    printf("ERROR: Table is empty\n");
	}
	return;
}

void ht_destroy(Node **Table){                     //destroy hash table
	int i;

	for (i = 0; i < htsize; i++){
		if (Table[i] != NULL){
			free(Table[i]);
			Table[i] = NULL;
		}
	}
	return;
}

int main(int argc, char *argv[]){
	char *line = NULL;           //line buffer argument to getline()
	size_t length = 0;           //buffer size argument to getline()
	char *token;                 //token returned by strtok()
	char *delim = " .,;:!\"?\n"; //delimiter characters for strtok()
	char *word;                  //token word in lowercase
	Node **Table;                //pointer to heap-allocated hash table

	/* Hash table size is a command line argument in argv[1] */
	if (argc <= 1){
		printf("ERROR: Usage: %s table_size\n", argv[0]);
		return 1;
	}
	htsize = atoi(argv[1]);

	Table = ht_create();  //create hash table

	/* Parse lines of input text; extract/insert words into hash table */
	while(1){
		if (getline(&line, &length, stdin) == -1) //read next line
			break;                                //exit when no more lines
		token = strtok(line, delim);
		while (token != NULL){
			word = lowercase(token);              //store lowercase token in word
			ht_insert(Table, word);               //insert word into table
			token = strtok(NULL, delim);          //extract next token
		}
	}
	free(line);        //free line buffer
	ht_print(Table);   //print table
	ht_destroy(Table); //destroy table
	return 0;
}
