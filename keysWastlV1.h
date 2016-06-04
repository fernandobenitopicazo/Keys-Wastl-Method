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

HEADERS FILE
*/


/* Types and Headers file */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define TAMCELDA 30
#define TAMDEPENDENCIA 1024
#define DELIMITADOR " "
#define NOMBREFICHERO 256


/* Data structures */
// Node
struct listaNodos {
	char cadena[TAMCELDA];
	struct listaNodos * sig;
};

// Functional dependency, FD.
struct listaDependencias {
	struct listaNodos * izq;
	struct listaNodos * dcha;
	struct listaDependencias * sig;
};



/* Functions and procedures headers. */

// -------------------------------------------------------
// ------------------- WASTL and SHARED ------------------
// -------------------------------------------------------

struct listaDependencias * hacerCopiaListaDepedencias (struct listaDependencias * );
struct listaDependencias * reverse (struct listaDependencias *);
void liberarListaNodos (struct listaNodos *);
void liberarListaDependencias (struct listaDependencias *);
void cerrarFichero(FILE *);
struct listaNodos * insertarNodo (struct listaNodos *, char *);
struct listaNodos * insertarListaNodos (struct listaNodos *, struct listaNodos *);
struct listaDependencias * crearListaDependenciasDesdeFichero (char *);
struct listaDependencias * generarDependenciasWastl(struct listaDependencias *);
void obtenerNodo(char *, struct listaNodos *);
void mostrarListaNodos (struct listaNodos *);
void mostrarListaDependencias (struct listaDependencias *);
struct listaDependencias * insertarDependencia (struct listaDependencias *, struct listaNodos *, struct listaNodos *);
struct listaDependencias * raizTableaux (struct listaDependencias *);
char * replace (char *, char *, char *);
int esta (char *, struct listaNodos *);
int longitudListaDependencias (struct listaDependencias *);
int longitudListaNodos (struct listaNodos *);
struct listaNodos * eliminarElemTableaux (struct listaNodos *, char *);
struct listaNodos * insertarElemParteTableaux (struct listaNodos *, struct listaNodos *);
int interseccionVacia (struct listaNodos *, struct listaNodos *);
int existenCandidatos (struct listaDependencias *, struct listaDependencias *, struct listaNodos *);
struct listaDependencias * hacerCopiaTableaux (struct listaDependencias *);
struct listaNodos * hacerCopiaL (struct listaNodos *);
void escribirListaClavesFichero (struct listaDependencias *, char *);
char * generarClaveSalida (struct listaDependencias *);
struct listaDependencias * insertarClave (struct listaDependencias *, struct listaDependencias *);
int contenida (struct listaNodos *, struct listaNodos *);
void reglaK1Wastl (struct listaDependencias *, struct listaDependencias *, struct listaNodos *);
void escribirDatosAlgoritmo (char *);


// =====================================================
// =====================================================
// =================== End of File =====================
// =====================================================
// =====================================================
