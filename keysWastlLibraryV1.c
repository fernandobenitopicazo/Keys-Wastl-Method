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

#include "keysWastlV1.h"



/* Reserved words. */
extern char VALORNULO[NOMBREFICHERO];


/* Global variables (externs) */
extern char ficheroClaves[NOMBREFICHERO];
extern FILE * ficheroSalida;
extern struct listaDependencias * listaClaves;
extern float tiempoEjecucion;

// -------------------------------------------------------
// -------------------------------------------------------
// --------------------- COMMON FUNCTIONS ----------------
// -------------------------------------------------------
// -------------------------------------------------------

/* Free the memory for the list of nodes. */
void liberarListaNodos (struct listaNodos * lista) {
	struct listaNodos * aux;
	struct listaNodos * tmp;

	aux = lista;
	while (aux != NULL) {
		tmp = aux -> sig;
		free (aux);
		aux = tmp;
	}
}



/* Free the memory for the list of functional dependencies. */
void liberarListaDependencias (struct listaDependencias * lista) {
	struct listaDependencias * aux;
	struct listaDependencias * tmp;
	aux = lista;
	while (aux != NULL) {
		tmp = aux -> sig;
		liberarListaNodos (aux -> izq);
		liberarListaNodos (aux -> dcha);
		free (aux);
		aux = tmp;
	}
}


/* Procedure for closing file. */
void cerrarFichero (FILE * fichero) {
	if(!fclose(fichero)) {
		//printf("Fichero cerrado\n");
	} else {
		printf("Error al cerrar el fichero\n");
		exit(-1);	
	}
}


/* Insert (at the beginning) a new node with the information of 'token' into the list of nodes 'list'.*/
struct listaNodos * insertarNodo (struct listaNodos * lista, char * token) {
	struct listaNodos * nodo = (struct listaNodos *) malloc (sizeof (struct listaNodos));	
	strcpy (nodo -> cadena, token);
	nodo -> sig = lista;
	lista = nodo;
	return lista;
}


/* Create a list of functional dependencies with the information from the input file (parameter).
The input file structure follows:
- ODD lines represent left-hand side of the functional dependency.
- EVEN lines represent right-hand side of the functional dependency.
That's why we use variable 'i' along with the module 2.
Remember that 'i' begins at zero. */
struct listaDependencias * crearListaDependenciasDesdeFichero (char * nombre) {
	struct listaDependencias * lista = NULL;
	struct listaNodos * listaIzq = NULL;
	struct listaNodos * listaDcha = NULL;

	FILE * fichero;
	char aux[TAMDEPENDENCIA] = "";
	char * token; // = (char *) malloc(strlen(aux) * sizeof (char));
	int i = 0;
	
	fichero = fopen (nombre, "r"); // Open the file
	if (fichero) {
		while (fgets (aux, TAMDEPENDENCIA, fichero) != NULL) {
			if (i % 2 == 0) { // Left-Hand side
				token = strtok (aux, DELIMITADOR);
				listaIzq = insertarNodo (listaIzq, replace(token, "\n", ""));
				while ((token = strtok (NULL, DELIMITADOR)) != NULL) {
					listaIzq = insertarNodo (listaIzq, replace(token, "\n", ""));
				}
			} else { // Right-Hand side
				token = strtok (aux, DELIMITADOR);
				listaDcha = insertarNodo (listaDcha, replace(token, "\n", ""));
				while ((token = strtok (NULL, DELIMITADOR)) != NULL) {
					listaDcha = insertarNodo (listaDcha, replace(token, "\n", ""));
				}				
				lista = insertarDependencia (lista, listaIzq, listaDcha);			
				listaIzq = NULL;
				listaDcha = NULL;
				token = NULL;
			}						
			i++;
		}
	} else {
		printf("Error opening the file\n");
		exit(-1);
	}
	cerrarFichero (fichero);
	//printf("Longitud: %d\n",longitudListaDependencias(lista));
	return lista;
}


/* Insert a new functional dependency at the beginning of the list. */
struct listaDependencias * insertarDependencia (struct listaDependencias * lista, struct listaNodos * parteIzq, struct listaNodos * parteDcha) {
	struct listaDependencias * nueva; 

	if (parteIzq != NULL) { 
		nueva = (struct listaDependencias *) malloc (sizeof (struct listaDependencias)); 
		nueva -> izq = parteIzq;
		nueva -> dcha = parteDcha;
		nueva -> sig = lista;
		lista = nueva;
	}	
	return lista;
}



/* Show the list of nodes 'list'. */
void mostrarListaNodos (struct listaNodos * lista) {
	char res[TAMDEPENDENCIA] = "";
	struct listaNodos * aux = lista;
	while (aux != NULL) {
		strcat(res, aux -> cadena);
		aux = aux -> sig;
	}
	printf("Node: %s\n", res);
}



// Store in 'node' the content of 'list'.
void obtenerNodo (char * nodo, struct listaNodos * lista) {
	char res[TAMDEPENDENCIA] = "";
	struct listaNodos * aux = lista;
	while (aux != NULL) {
		strcat(nodo, aux -> cadena);
		aux = aux -> sig;
	}
}


// Show the list of functional dependencies 'list'.
void mostrarListaDependencias (struct listaDependencias * lista) {
	struct listaDependencias * aux = lista;
	char nodoIzq[TAMDEPENDENCIA] = "";
	char nodoDcha[TAMDEPENDENCIA] = "";

	printf("Length of the list = %d\n", longitudListaDependencias(lista));

	while (aux != NULL) {
		obtenerNodo(nodoIzq, aux -> izq);
		//printf("NODO IZQ: %s\n", nodoIzq);
		obtenerNodo(nodoDcha, aux -> dcha);
		//printf("NODO DCHA: %s\n", nodoDcha);
		printf("DEP: %s -> %s\n", nodoIzq, nodoDcha);
		memset(nodoIzq, 0, sizeof(nodoIzq));
		memset(nodoDcha, 0, sizeof(nodoDcha));
		aux = aux -> sig;
	}
}


/* Replace 'orig' for 'repl' into 'st' string.
For instance: replace("Hola mundo!", "mundo", "Fer") => Hola Fer! */
char * replace (char * st, char * orig, char * repl) {
	static char buffer[TAMDEPENDENCIA];
	char * ch;
	if (!(ch = strstr(st, orig)))
   		return st;
	strncpy(buffer, st, ch - st);  
	buffer[ch - st] = 0;
  	sprintf(buffer + (ch - st), "%s%s", repl, ch + strlen(orig));
	return buffer;
}



// Function that returns the number of FD in 'list'.
int longitudListaDependencias (struct listaDependencias * lista) {
	struct listaDependencias * aux = lista;
	int res = 0;
	while (aux != NULL) {
		res++;
		aux = aux -> sig;
	}
	return res;
}


// Function that returns the number of nodes in 'list'.
int longitudListaNodos (struct listaNodos * lista) {
	struct listaNodos * aux = lista;
	int res = 0;
	while (aux != NULL) {
		res++;
		aux = aux -> sig;
	}
	return res;
}


/* Check whether an element exists or not in the list of nodes 'list'. 
* Return 1 if exists, 0 otherwise. */
int esta (char * elem, struct listaNodos * lista) {
	int res = 0;
	struct listaNodos * aux = lista;
	while (aux != NULL && !res) {
		if (strcmp(elem, aux -> cadena) == 0) 
			res = 1; // See strcmp
		aux = aux -> sig;
	}
	return res;
}


/* Return the element at the position 'pos' within the list of nodes 'list'. */
char * buscarElemento (struct listaNodos * lista, int pos) {
	struct listaNodos * aux = lista;
	int i = 0;
	while (i != pos) {
		i++; 
		aux = aux -> sig;
	}
	return aux -> cadena;
}


/* Return 1 if 'listBase' contains 'list',0 otherwise. */
int contenida (struct listaNodos * lista, struct listaNodos * listaBase) {
	struct listaNodos * aux = lista;
	int res = 1;
	while (aux != NULL && res) {
		if (!esta (aux -> cadena, listaBase))
			res = 0;
		aux = aux -> sig;
	}
	return res;
}



/* This function inserts the new superkey that comes at the input 'superKey' into the current list of keys 'list' .  
*/
struct listaDependencias * insertarClave (struct listaDependencias * lista, struct listaDependencias * superClave) {
	struct listaDependencias * aux;

	
	lista = insertarDependencia (lista, hacerCopiaL (superClave -> izq), hacerCopiaL (superClave -> dcha));
	return lista;
}



/* Return 1 if the insersection of 'L' and 'list' is void, 0 otherwise. */
int interseccionVacia (struct listaNodos * L, struct listaNodos * lista) {
	struct listaNodos * aux = lista;
	int res = 1;
	int encontrado = 0;
	while (aux != NULL && !encontrado) {
		if(esta(aux -> cadena, L)) {
			encontrado = 1;
			res = 0;
		}
		aux = aux -> sig;
	}
	return res;
}



/* Write in 'name' file the list 'list'. It will be the resulting keys file. */
void escribirListaClavesFichero (struct listaDependencias * lista, char * nombre) {
	struct listaDependencias * aux = lista;
	FILE * fichero;

	fichero = fopen (nombre, "a");
	while (aux != NULL) { 
		fputs(generarClaveSalida (aux), fichero);
		aux = aux -> sig;
	}
	cerrarFichero (fichero);
}


// -------------------------------------------------------
// -------------------------------------------------------
// ------------------------ WASTL ------------------------
// -------------------------------------------------------
// -------------------------------------------------------


/* Remove the node containing 'elem' in he list of nodes 'list'.*/
struct listaNodos * eliminarElemTableaux (struct listaNodos * lista, char * elem){
	if (lista == NULL) {
		return lista;
	} else if (strcmp (lista -> cadena, elem) == 0) { // Found it
		struct listaNodos * aux = lista -> sig;
		free (lista); // Free node
		lista = aux;
	} else { // Not found, recursive
		lista -> sig = eliminarElemTableaux (lista -> sig, elem);
	}
	return lista;
}


/* IMPORTANT.
Function that performs R. Wastl's inference rule K2.
It calculates the tableaux root.
* - Wastl K2 inference rule -
* EJ: A -> B, C -> D => AC -> D 
*/
struct listaDependencias * raizTableaux(struct listaDependencias * lista) {
	struct listaDependencias * aux = lista;
	struct listaDependencias * res = NULL;
	if (lista != NULL) {
		res = (struct listaDependencias *) malloc (sizeof (struct listaDependencias));
		res -> izq = NULL;	
		res -> dcha = NULL;
		while (aux != NULL) {
			res -> izq = insertarElemParteTableaux (aux -> izq, res -> izq);
			if (aux -> sig == NULL) 
				res -> dcha = insertarElemParteTableaux (aux -> dcha, res -> dcha);
			aux = aux -> sig;
		}
		res -> sig = NULL;
	}
	return res;
}



/* Insert into 'listaBase' the elements of 'listNew' avoiding duplicates. */
struct listaNodos * insertarElemParteTableaux (struct listaNodos * listaNueva, struct listaNodos * listaBase) {
	struct listaNodos * aux = listaNueva;
	while (aux != NULL) {
		if (!esta (aux -> cadena, listaBase)) 
			listaBase = insertarNodo (listaBase, aux -> cadena);
		aux = aux -> sig;
	}
	return listaBase;
}



/* IMPORTANT.
This function returns the list of UNIT functional dependencies from the original list 'list'.
* For instance: Let F = {A -> BC}, Wastl's method needs to convert F into: F = {A -> B y A -> C} */
struct listaDependencias * generarDependenciasWastl (struct listaDependencias * lista) {
	struct listaDependencias * aux = lista;
	struct listaNodos * dcha = NULL;
	struct listaNodos * nodo;
	struct listaDependencias * res = NULL;
	int longitud, i;

	while (aux != NULL) {
		longitud = longitudListaNodos (aux -> dcha);
		if (longitud == 1) {
			res = insertarDependencia (res, hacerCopiaL (aux -> izq), hacerCopiaL (aux -> dcha));	
		} else {
			for (i = 0; i < longitud; i++) {
				dcha = insertarNodo (dcha, buscarElemento(aux -> dcha, i));
				res = insertarDependencia (res, hacerCopiaL (aux -> izq), dcha);
				dcha = NULL;
			}	
		}
		aux = aux -> sig;
	}
	return res;
}


/* Receives the whole dependencies list 'lista', the current node of the tableaux 'tableaux' and the path list 'L'. 
Returns: 1 is there exists any functional dependency that holds Wastl's K1 infer rule, 0 otherwise.*/
int existenCandidatos (struct listaDependencias * lista, struct listaDependencias * tableaux, struct listaNodos * L) {
	struct listaDependencias * aux = lista;
	int encontrado = 0;
	while (aux != NULL && !encontrado) {
		if (esta (aux -> dcha -> cadena, tableaux -> izq) && (interseccionVacia (L, aux -> izq))) {
			encontrado = 1;
		}
		aux = aux -> sig;
	}
	return encontrado;
}


/* Function that receives a dependency 'dependencia', the current node of the tableaux 'tableaux' and the path list 'L'.
Returns 1 if both following conditions hold:
1.- Right-hand side of 'dependencia' is included in 'tableaux'.
2.- Left-hand side of 'dependencia' is NOT already in 'L'.
Returns 0 if any prior conditions fail.*/
int esCandidato(struct listaDependencias * dependencia, struct listaDependencias * tableaux, struct listaNodos * L) {
	
	return (esta(dependencia -> dcha -> cadena, tableaux -> izq) && (interseccionVacia(L, dependencia -> izq)));
}



/* Function that returns a copy allocated in its own memory of the tableaux that receives as input.*/
struct listaDependencias * hacerCopiaTableaux (struct listaDependencias * lista) {	
	struct listaDependencias * res = NULL;
	struct listaNodos * resIzq = NULL;
	struct listaNodos * resDcha = NULL;

	// Left-hand side
	struct listaNodos * aux = lista -> izq;
	while (aux != NULL) {
		resIzq = insertarNodo (resIzq, aux -> cadena);
		aux = aux -> sig;
	}
	// Right-hand side
	aux = lista -> dcha;
	while (aux != NULL) {
		resDcha = insertarNodo (resDcha, aux -> cadena);
		aux = aux -> sig;
	}
	res = insertarDependencia (res, resIzq, resDcha);
	return res;
}


/* Function that returns a copy allocated in its own memory of the list of nodes that receives as input.*/
struct listaNodos * hacerCopiaL (struct listaNodos * lista) {
	struct listaNodos * res = NULL;
	struct listaNodos * aux = lista;
	if (lista != NULL) {
		while (aux != NULL) {
			res = insertarNodo (res, aux -> cadena);
			aux = aux -> sig;
		}
	}	
	return res;
}




/* IMPORTANT.
This procedure is responsible for building the tableaux tree by applying Wastl's K1 infer rule successively.
- Wastl K1 infer rule -
x -> A, YA -> B  => XY -> B.
When we reach to a node that cannot expand any more, it means we reached a leaf of the tableaux tree, i.e. a key of the relation. Therefore, we save it in the list of keys by applying the function 'insertarClave'.
Cada vez que llegamos a un nodo que ya no se puede seguir expandiendo, utiliza el procedimiento 'generarClaveSalida' para escribir en fichero la parte izquierda del Tableaux actual, que se corresponderá con una Clave. */
void reglaK1Wastl (struct listaDependencias * lista, struct listaDependencias * tableaux, struct listaNodos * L) {
	
	struct listaDependencias * aux;
	struct listaDependencias * auxTableaux;
	struct listaNodos * auxL;

	if (lista == NULL) {
		// Nothing
	} else if (!existenCandidatos (lista, tableaux, L)) {
		// We reached a leaf of the tree, i.e. a key.
		listaClaves = insertarClave (listaClaves, tableaux);
	} else {
		aux = lista;
		while (aux != NULL) {
			if (esCandidato (aux, tableaux, L)) {
				// We save a copy of tableaux and L
				auxTableaux = hacerCopiaTableaux (tableaux);
				auxL = hacerCopiaL (L);	
				auxTableaux -> izq = eliminarElemTableaux (auxTableaux -> izq, aux -> dcha -> cadena);
				auxL = insertarNodo (auxL, aux -> dcha -> cadena);
				
				reglaK1Wastl (lista, auxTableaux, auxL);
				liberarListaDependencias (auxTableaux);
				liberarListaNodos (auxL);
				auxTableaux = NULL;
				auxL = NULL;
			}
			aux = aux -> sig;
		}
	}
}


/* Function that receives a dependency 'lista' and returns a pointer to string filled with the left-hand side of the dependency. In short, this function is meant to generate and return the key within the input dependency, i.e. its left-hand side.*/
char * generarClaveSalida (struct listaDependencias * lista) {
	static char res[TAMDEPENDENCIA] = "";
	memset(res, 0, sizeof(res));
	if (lista != NULL) {
		struct listaNodos * aux = lista -> izq;
		while (aux -> sig != NULL) {
			strcat(res, aux -> cadena);
			strcat(res, " ");
			aux = aux -> sig;
		}
		strcat(res, aux -> cadena);
		strcat(res, "\n");
	} else {
		strcat(res, VALORNULO);
	}
	return res;
}


// =====================================================
// =====================================================
// ==================== End of File ====================
// =====================================================
// =====================================================
