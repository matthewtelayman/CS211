/* Matt Layman - CS211 - symTable.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <assert.h>
#include <symTable.h>
#define HASH_MULTIPLIER 65599
#define DEFAULT_TABLE_SIZE 61

/* Hash table size */
int htsize = DEFAULT_TABLE_SIZE;

/* Sym Table Node */
struct SymTable{
	void *item;        //symbol (key)
	int *count;        //number of occurences of key
	struct SymTable *next;  //pointer to next node in hash table bucket
};

/* Function prototypes */
unsigned int hash(const char *);

/* Main function */

int main(int argc, char *argv[])
{
   SymTable_T **Table;			// hash table
   int rv;
   char *line = NULL;  		// line buffer argument to getline()
   size_t length = 0;  		// buffer size argument to getline()
   void *key;				// key returned by strtok()
   int *value;
   char *delim = " .,;:!\"?\n";	// delimiter characters for strtok()

   /* Create empty hash table */
   Table = symTable_create();
   if (Table == NULL) {
      fprintf(stderr, "Could not allocate hash table\n");
      return 1;
   }

   /* Parse lines of input text; extract and insert keys into hash table */
   while (1) {
      if (getline(&line, &length, stdin) == -1)		// read next line
         break;										// exit loop when no more lines
	  key = strtok(line, delim);					// extract next key from line
	  while (token != NULL) {
	     rv = symTable_insert(Table, key, value, sizeof(key));
	     if (!rv) {
	        fprintf(stderr, "Insert failed\n");
		    return 1;
		 }
         key = strtok(NULL, delim);				// extract next key
  	  }
   }
   free(line);			    // free line buffer
   symTable_print(Table)    // print hash table
   symTable_destroy(Table);	// empty hash table
   return 0;
}

/* Hash key to a hash table bucket in the range [0, htsize-1] */
static unsigned int hash(const char *key, const int htsize)
{
int i;
unsigned int h = 0U;
for (i = 0; key[i] != '\0'; i++)
h = h * HASH_MULTIPLIER + (unsigned char) key[i];
return h % htsize;
}

/* Create symbol Table */

SymTable_T symTable_create(void)
{
   SymTable_T *SymTable;

   SymTable = (SymTable_T *) calloc(htsize, sizeof(struct SymTable));
   if (stack == NULL)
      return NULL;

  return SymTable;
}

/* Destroy symbol table */
void symTable_destroy(SymTable_T symTable)
{
   SymTable_T *p, *nextp;
   int i;

   assert(symTable != NULL);

   for (i = 0; i < htsize; i++) {
      for (p = symTable[i]; p != NULL; p = nextp) {
         nextp = p->next;
         assert(p->item != NULL);
         free(p->item);
         free(p->count);
         free(p);
      }
   }
   free(symTable);
   return;
}

/* Returns size of symbol table */
int symTable_size(SymTable_T symTable)
{
   assert(symTable != NULL);

   return symTable->count;
}

/* Inserts symbol into Table */
int symTable_insert(SymTable_T symTable, const char *key, const void *value, size_t valuesize)
{
   SymTable_T *p, *prevp;
   char *symbol;
   int h;

   assert(symTable != NULL);

   symbol = key;
   if (symbol == NULL)	// could not allocate space for key
      return 0;					// insert failed: return 0

   /* Get hash of symbol */
   h = hash(symbol);

   /* Search for symbol in its hash table bucket */

   for (p = symTable[h]; p != NULL; prevp = p, p = p->next) {

   /*  symbol is found: increment its count */
      assert(p->item != NULL);
      if (strcmp(p->item, symbol) == 0) {
        (p->count)++;
        free(symbol);		// no need to insert: free symbol
	    return 1;
      }
   }

   /* symbol is not in table: insert new node for it at end of list */

   p = (SymTable_T *) malloc( sizeof(SymTable_T) );
   if (p == NULL)
      return 0;
   p->item = symbol;	// set p->item to point to symbol
   p->count = value;			// initialize count to value
   p->next = NULL;
   if (symTable[h] == NULL)
      symTable[h] = p;
   else
      prevp->next = p;
   return 1;
}

/* Searches symbol table for key. Returns 1 if success, 0 if failed. */
int symTable_search(SymTable_T symTable, const char *key, void *value, size_t valuesize)
{
   SymTable_T *p, *prevp;
   char *symbol;

   assert(symTable != NULL);

   symbol = key;
   if (symbol == NULL)	// could not allocate space for key
      return 0;					// search failed: return 0


   /* Search for symbol in its hash table bucket */

   for (p = symTable[h]; p != NULL; prevp = p, p = p->next) {

   /*  symbol is found */
      assert(p->item != NULL);
      if (strcmp(p->item, symbol) == 0) {
        free(symbol);		//free symbol
	    return 1;
      }
   }
}

/* Deletes key and value from the table and frees allocated space. Returns 1 on success, 0 on failure. */
int symTable_delete(SymTable_T symTable, const char *key)
{
   SymTable_T *p, *prevp;
   char *symbol;

   assert(symTable != NULL);

   symbol = key;
   if (symbol == NULL)	// could not allocate space for key
      return 0;					// delete failed: return 0

   /* Search for symbol in its hash table bucket */

   for (p = symTable[h]; p != NULL; prevp = p, p = p->next) {

   /*  symbol is found: delete key */
      assert(p->item != NULL);
      if (strcmp(p->item, symbol) == 0) {
        free(p->item);		//free symbol
        free(p->count);     //free value
	    return 1;
      }
   }
}
