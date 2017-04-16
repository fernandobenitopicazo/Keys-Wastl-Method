/*
---------------------------------
Fernando Benito-Picazo
SICUMA Researching Group
Computer Science Dpt.
University of Málaga
Spain
Lab 3.3.11
+(34) 952 137141
---------------------------------

*************************
*** WASTL KEYS METHOD ***
*************************

FUNCTIONS AND PROCEDURES FILE
*/


/* Library file containing the implementation of all required procedures and functions. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "keysWastlV1.h"


/* Reserved words. */
extern char NULLVALUE[FILENAME];


/* Global variables (externs) */
extern char keysFile[FILENAME];
extern FILE * outputFile;
extern struct dependenciesList * keysList;
extern float runningTime;

// -------------------------------------------------------
// -------------------------------------------------------
// --------------------- COMMON FUNCTIONS ----------------
// -------------------------------------------------------
// -------------------------------------------------------

/* Free the memory for the list of nodes. */
void freeNodesList (struct nodesList * list) {
	struct nodesList * aux;
	struct nodesList * tmp;

	aux = list;
	while (aux != NULL) {
		tmp = aux -> next;
		free (aux);
		aux = tmp;
	}
}



/* Free the memory for the list of functional dependencies. */
void freeDependenciesList (struct dependenciesList * list) {
	struct dependenciesList * aux;
	struct dependenciesList * tmp;
	aux = list;
	while (aux != NULL) {
		tmp = aux -> next;
		freeNodesList (aux -> left);
		freeNodesList (aux -> right);
		free (aux);
		aux = tmp;
	}
}


/* Procedure for closing file. */
void closeFile (FILE * file) {
	if(!fclose(file)) {
		//printf("File closed\n");
	} else {
		printf("Error close file\n");
		exit(-1);	
	}
}


/* Insert (at the beginning) a new node with the information of 'token' into the list of nodes 'list'.*/
struct nodesList * insertNode (struct nodesList * list, char * token) {
	struct nodesList * node = (struct nodesList *) malloc (sizeof (struct nodesList));	
	strcpy (node -> stringChar, token);
	node -> next = list;
	list = node;
	return list;
}


/* Create a list of functional dependencies with the information from the input file (parameter).
The input file structure follows:
- ODD lines represent left-hand side of the functional dependency.
- EVEN lines represent right-hand side of the functional dependency.
That's why we use variable 'i' along with the module 2.
Remember that 'i' begins at zero. */
struct dependenciesList * createDependenciesListFromFile (char * name) {
	struct dependenciesList * list = NULL;
	struct nodesList * leftList = NULL;
	struct nodesList * rightList = NULL;

	FILE * auxFile;
	char aux[DEPENDENCYSIZE] = "";
	char * token; // = (char *) malloc(strlen(aux) * sizeof (char));
	int i = 0;
	
	auxFile = fopen (name, "r"); // Open the file
	if (auxFile) {
		while (fgets (aux, DEPENDENCYSIZE, auxFile) != NULL) {
			if (i % 2 == 0) { // Left-Hand side
				token = strtok (aux, MARKER);
				leftList = insertNode (leftList, replace(token, "\n", ""));
				while ((token = strtok (NULL, MARKER)) != NULL) {
					leftList = insertNode (leftList, replace(token, "\n", ""));
				}
			} else { // Right-Hand side
				token = strtok (aux, MARKER);
				rightList = insertNode (rightList, replace(token, "\n", ""));
				while ((token = strtok (NULL, MARKER)) != NULL) {
					rightList = insertNode (rightList, replace(token, "\n", ""));
				}				
				list = insertDependency (list, leftList, rightList);			
				leftList = NULL;
				rightList = NULL;
				token = NULL;
			}						
			i++;
		}
	} else {
		printf("Error opening the file\n");
		exit(-1);
	}
	closeFile (auxFile);
	//printf("Size: %d\n",sizeDepedenciesList(list));
	return list;
}


/* Insert a new functional dependency at the beginning of the list. */
struct dependenciesList * insertDependency (struct dependenciesList * list, struct nodesList * leftSide, struct nodesList * rightSide) {
	struct dependenciesList * aux; 

	if (leftSide != NULL) { 
		aux = (struct dependenciesList *) malloc (sizeof (struct dependenciesList)); 
		aux -> left = leftSide;
		aux -> right = rightSide;
		aux -> next = list;
		list = aux;
	}	
	return list;
}



/* Show the list of nodes 'list'. */
void paintNodesList (struct nodesList * list) {
	char res[DEPENDENCYSIZE] = "";
	struct nodesList * aux = list;
	while (aux != NULL) {
		strcat(res, aux -> stringChar);
		aux = aux -> next;
	}
	printf("Node: %s\n", res);
}



// Store in 'node' the content of 'list'.
void getNode (char * nodo, struct nodesList * list) {
	char res[DEPENDENCYSIZE] = "";
	struct nodesList * aux = list;
	while (aux != NULL) {
		strcat(nodo, aux -> stringChar);
		aux = aux -> next;
	}
}


// Show the list of functional dependencies 'list'.
void paintDependenciesList (struct dependenciesList * list) {
	struct dependenciesList * aux = list;
	char nodoIzq[DEPENDENCYSIZE] = "";
	char nodoDcha[DEPENDENCYSIZE] = "";

	printf("Length of the list = %d\n", sizeDepedenciesList(list));

	while (aux != NULL) {
		getNode(nodoIzq, aux -> left);
		//printf("NODO IZQ: %s\n", nodoIzq);
		getNode(nodoDcha, aux -> right);
		//printf("NODO DCHA: %s\n", nodoDcha);
		printf("DEP: %s -> %s\n", nodoIzq, nodoDcha);
		memset(nodoIzq, 0, sizeof(nodoIzq));
		memset(nodoDcha, 0, sizeof(nodoDcha));
		aux = aux -> next;
	}
}


/* Replace 'orig' for 'repl' into 'st' string.
For instance: replace("Hola mundo!", "mundo", "Fer") => Hola Fer! */
char * replace (char * st, char * orig, char * repl) {
	static char buffer[DEPENDENCYSIZE];
	char * ch;
	if (!(ch = strstr(st, orig)))
   		return st;
	strncpy(buffer, st, ch - st);  
	buffer[ch - st] = 0;
  	sprintf(buffer + (ch - st), "%s%s", repl, ch + strlen(orig));
	return buffer;
}



// Function that returns the number of FD in 'list'.
int sizeDepedenciesList (struct dependenciesList * list) {
	struct dependenciesList * aux = list;
	int res = 0;
	while (aux != NULL) {
		res++;
		aux = aux -> next;
	}
	return res;
}


// Function that returns the number of nodes in 'list'.
int sizeNodesList (struct nodesList * list) {
	struct nodesList * aux = list;
	int res = 0;
	while (aux != NULL) {
		res++;
		aux = aux -> next;
	}
	return res;
}


/* Check whether an element exists or not in the list of nodes 'list'. 
* Return 1 if exists, 0 otherwise. */
int exists (char * elem, struct nodesList * list) {
	int res = 0;
	struct nodesList * aux = list;
	while (aux != NULL && !res) {
		if (strcmp(elem, aux -> stringChar) == 0) 
			res = 1; // See strcmp
		aux = aux -> next;
	}
	return res;
}


/* Return the element at the position 'pos' within the list of nodes 'list'. */
char * findElement (struct nodesList * list, int pos) {
	struct nodesList * aux = list;
	int i = 0;
	while (i != pos) {
		i++; 
		aux = aux -> next;
	}
	return aux -> stringChar;
}


/* Return 1 if 'baseList' contains 'list',0 otherwise. */
int includeIn (struct nodesList * list, struct nodesList * baseList) {
	struct nodesList * aux = list;
	int res = 1;
	while (aux != NULL && res) {
		if (!exists (aux -> stringChar, baseList))
			res = 0;
		aux = aux -> next;
	}
	return res;
}



/* This function inserts the new superkey that comes at the input 'superKey' into the current list of keys 'list' .  
*/
struct dependenciesList * insertKey (struct dependenciesList * list, struct dependenciesList * superKey) {
	struct dependenciesList * aux;

	list = insertDependency (list, makeCopyL (superKey -> left), makeCopyL (superKey -> right));
	return list;
}



/* Return 1 if the insersection of 'L' and 'list' is void, 0 otherwise. */
int voidIntersection (struct nodesList * L, struct nodesList * list) {
	struct nodesList * aux = list;
	int res = 1;
	int flag = 0;
	while (aux != NULL && !flag) {
		if(exists(aux -> stringChar, L)) {
			flag = 1;
			res = 0;
		}
		aux = aux -> next;
	}
	return res;
}



/* Write in 'name' file the list 'list'. It will be the resulting keys file. */
void saveKeysListToFile (struct dependenciesList * list, char * name) {
	struct dependenciesList * aux = list;
	FILE * auxFile;

	auxFile = fopen (name, "a");
	while (aux != NULL) { 
		fputs(generateOutputKey (aux), auxFile);
		aux = aux -> next;
	}
	closeFile (auxFile);
}


// -------------------------------------------------------
// -------------------------------------------------------
// ------------------------ WASTL ------------------------
// -------------------------------------------------------
// -------------------------------------------------------


/* Remove the node containing 'elem' in he list of nodes 'list'.*/
struct nodesList * removeElemFromTableaux (struct nodesList * list, char * elem){
	if (list == NULL) {
		return list;
	} else if (strcmp (list -> stringChar, elem) == 0) { // Found it
		struct nodesList * aux = list -> next;
		free (list); // Free node
		list = aux;
	} else { // Not found, recursive
		list -> next = removeElemFromTableaux (list -> next, elem);
	}
	return list;
}


/* IMPORTANT.
Function that performs R. Wastl's inference rule K2.
It calculates the tableaux root.
* - Wastl K2 inference rule -
* EJ: A -> B, C -> D => AC -> D 
*/
struct dependenciesList * rootTableaux(struct dependenciesList * list) {
	struct dependenciesList * aux = list;
	struct dependenciesList * res = NULL;
	if (list != NULL) {
		res = (struct dependenciesList *) malloc (sizeof (struct dependenciesList));
		res -> left = NULL;	
		res -> right = NULL;
		while (aux != NULL) {
			res -> left = insertElemToTableaux (aux -> left, res -> left);
			if (aux -> next == NULL) 
				res -> right = insertElemToTableaux (aux -> right, res -> right);
			aux = aux -> next;
		}
		res -> next = NULL;
	}
	return res;
}



/* Insert into 'baseList' the elements of 'listNew' avoiding duplicates. */
struct nodesList * insertElemToTableaux (struct nodesList * newList, struct nodesList * baseList) {
	struct nodesList * aux = newList;
	while (aux != NULL) {
		if (!exists (aux -> stringChar, baseList)) 
			baseList = insertNode (baseList, aux -> stringChar);
		aux = aux -> next;
	}
	return baseList;
}



/* IMPORTANT.
This function returns the list of UNIT functional dependencies from the original list 'list'.
* For instance: Let F = {A -> BC}, Wastl's method needs to convert F into: F = {A -> B y A -> C} */
struct dependenciesList * createDependenciesWastl (struct dependenciesList * list) {
	struct dependenciesList * aux = list;
	struct nodesList * right = NULL;
	struct nodesList * node;
	struct dependenciesList * res = NULL;
	int size, i;

	while (aux != NULL) {
		size = sizeNodesList (aux -> right);
		if (size == 1) {
			res = insertDependency (res, makeCopyL (aux -> left), makeCopyL (aux -> right));	
		} else {
			for (i = 0; i < size; i++) {
				right = insertNode (right, findElement(aux -> right, i));
				res = insertDependency (res, makeCopyL (aux -> left), right);
				right = NULL;
			}	
		}
		aux = aux -> next;
	}
	return res;
}


/* Receives the whole dependencies list 'lista', the current node of the tableaux 'tableaux' and the path list 'L'. 
Returns: 1 is there exists any functional dependency that holds Wastl's K1 infer rule, 0 otherwise.*/
int existCandidates (struct dependenciesList * list, struct dependenciesList * tableaux, struct nodesList * L) {
	struct dependenciesList * aux = list;
	int flag = 0;
	while (aux != NULL && !flag) {
		if (exists (aux -> right -> stringChar, tableaux -> left) && (voidIntersection (L, aux -> left))) {
			flag = 1;
		}
		aux = aux -> next;
	}
	return flag;
}


/* Function that receives a dependency 'dependency', the current node of the tableaux 'tableaux' and the path list 'L'.
Returns 1 if both following conditions hold:
1.- Right-hand side of 'dependency' is included in 'tableaux'.
2.- Left-hand side of 'dependency' is NOT already in 'L'.
Returns 0 if any prior conditions fail.*/
int isCandidate(struct dependenciesList * dependency, struct dependenciesList * tableaux, struct nodesList * L) {
	
	return (exists(dependency -> right -> stringChar, tableaux -> left) && (voidIntersection(L, dependency -> left)));
}



/* Function that returns a copy allocated in its own memory of the tableaux that receives as input.*/
struct dependenciesList * makeCopyTableaux (struct dependenciesList * list) {	
	struct dependenciesList * res = NULL;
	struct nodesList * resLeft = NULL;
	struct nodesList * resRight = NULL;

	// Left-hand side
	struct nodesList * aux = list -> left;
	while (aux != NULL) {
		resLeft = insertNode (resLeft, aux -> stringChar);
		aux = aux -> next;
	}
	// Right-hand side
	aux = list -> right;
	while (aux != NULL) {
		resRight = insertNode (resRight, aux -> stringChar);
		aux = aux -> next;
	}
	res = insertDependency (res, resLeft, resRight);
	return res;
}


/* Function that returns a copy allocated in its own memory of the list of nodes that receives as input.*/
struct nodesList * makeCopyL (struct nodesList * list) {
	struct nodesList * res = NULL;
	struct nodesList * aux = list;
	if (list != NULL) {
		while (aux != NULL) {
			res = insertNode (res, aux -> stringChar);
			aux = aux -> next;
		}
	}	
	return res;
}




/* IMPORTANT.
This procedure is responsible for building the tableaux tree by applying Wastl's K1 infer rule successively.
- Wastl K1 infer rule -
x -> A, YA -> B  => XY -> B.
When we reach to a node that cannot expand any more, it means we reached a leaf of the tableaux tree, i.e. a key of the relation. Therefore, we save it in the list of keys by applying the function 'insertKey'.
Once we reach a node that cannot be expanded, it uses the procedure called 'generateOutputKey' in order to save in 'auxFile' the left-hand side of the current tableaux, i.e. a key. */
void wastlK1InferenceRule (struct dependenciesList * list, struct dependenciesList * tableaux, struct nodesList * L) {
	
	struct dependenciesList * aux;
	struct dependenciesList * auxTableaux;
	struct nodesList * auxL;

	if (list == NULL) {
		// Nothing
	} else if (!existCandidates (list, tableaux, L)) {
		// We reached a leaf of the tree, i.e. a key.
		keysList = insertKey (keysList, tableaux);
	} else {
		aux = list;
		while (aux != NULL) {
			if (isCandidate (aux, tableaux, L)) {
				// We save a copy of tableaux and L
				auxTableaux = makeCopyTableaux (tableaux);
				auxL = makeCopyL (L);	
				auxTableaux -> left = removeElemFromTableaux (auxTableaux -> left, aux -> right -> stringChar);
				auxL = insertNode (auxL, aux -> right -> stringChar);
				
				wastlK1InferenceRule (list, auxTableaux, auxL);
				freeDependenciesList (auxTableaux);
				freeNodesList (auxL);
				auxTableaux = NULL;
				auxL = NULL;
			}
			aux = aux -> next;
		}
	}
}


/* Function that receives a dependency 'list' and returns a pointer to string filled with the left-hand side of the dependency. In short, this function is meant to generate and return the key within the input dependency, i.e. its left-hand side.*/
char * generateOutputKey (struct dependenciesList * list) {
	static char res[DEPENDENCYSIZE] = "";
	memset(res, 0, sizeof(res));
	if (list != NULL) {
		struct nodesList * aux = list -> left;
		while (aux -> next != NULL) {
			strcat(res, aux -> stringChar);
			strcat(res, " ");
			aux = aux -> next;
		}
		strcat(res, aux -> stringChar);
		strcat(res, "\n");
	} else {
		strcat(res, NULLVALUE);
	}
	return res;
}


// =====================================================
// =====================================================
// ==================== End of File ====================
// =====================================================
// =====================================================
