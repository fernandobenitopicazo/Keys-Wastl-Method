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

MAIN FILE
*/


/* 
Main file of the software containing the main procedure.
It must be invoked using the following statement.
./keysWastl <DependenciesFileName> <MethodName> 
*/

#include "keysWastlV1.h"


/* Reserved Words */
char VALORNULO[NOMBREFICHERO] = "NULO\n";


/* Global variables */
char ficheroClaves[NOMBREFICHERO]; // = "experimentKeys.txt";
struct listaDependencias * listaClaves = NULL;

FILE * ficheroSalida;

// Counter
float tiempoEjecucion = 0.0;


/*
   ====================================================
   ==================================================== 
*/


/* Global variables of main file */
char * nombreFichero = NULL;
char * nombreMetodo = NULL;


struct listaDependencias * lista;
struct listaDependencias * listaDepWastl = NULL;
struct listaDependencias * nodo = NULL;
struct listaNodos * L = NULL;

clock_t inicio, fin;



/* Headers of the main file. */
void wastlPuro ();
void leerInformacionFicherosWastl ();

void liberarMemoria ();



// =======================================================
// ------------------------- WASTL -----------------------
// =======================================================


void wastlPuro () {
	printf("--------------------------------------\n");
	printf("WASTL\n");
	printf("---------\n");
	// Creamos la lista de DFs desde el fichero
	lista = crearListaDependenciasDesdeFichero (nombreFichero);
	printf("List of dependencies\n");
	printf("--------------------\n");
	mostrarListaDependencias (lista);
	listaDepWastl = generarDependenciasWastl (lista);
	//listaDepWastl = reverse(listaDepWastl);
	printf("List of Wastl dependencies (UNIT)\n");
	printf("---------------------------------\n");
	mostrarListaDependencias (listaDepWastl);

	printf("--------------------------------------\n");
	nodo = raizTableaux (listaDepWastl);
	printf("Root Tableaux (K2)\n");
	mostrarListaDependencias (nodo);

	printf("--------------------------------------\n");
	printf("K1 Rule Wastl\n");
	reglaK1Wastl (listaDepWastl, nodo, L);

	printf("--------------------------------------\n");
	printf("--------------------------------------\n");
	printf("----------- Wastl's Keys -------------\n");
	printf("--------------------------------------\n");
	printf("--------------------------------------\n");
	mostrarListaDependencias (listaClaves);
}

// =============================================================
// =============================================================
// ========================== M A I N ==========================
// =============================================================
// =============================================================

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("--------------------------------------\n");
		printf("--------------------------------------\n");
		printf("-------- Wrong program call ----------\n");
		printf("--------------------------------------\n");
		printf("-------- Correct signature: ----------\n");
		printf("./<executableName> <dependenciesFile>.txt keysWastl\n");
		printf("--------------------------------------\n");
		printf("--------------------------------------\n");
		exit(0);
	}

	// Read the input file(functional dependencies).
	nombreFichero = argv[1];

	// Name of the resulting keys file.
	sprintf(ficheroClaves, "Keys-%s", nombreFichero);

	/* Read the selected method. 
	This is prepared for further development where other methods may be implemented.
	*/
	//metodo = (int) atoi(argv[2]);
	nombreMetodo = argv[2];
		
	// Timer begins
	inicio = time (NULL);
	
	// Call the method for execution
	if (strcmp (nombreMetodo, "keysWastl") == 0) {
		wastlPuro ();
	} else {
		printf("--------------------------------------\n");
		printf("--------------------------------------\n");
		printf("------------ Wrong Method ------------\n");
		printf("--------------------------------------\n");
		printf("--------------------------------------\n");
		exit(0);
	}

	// Timer ends
	fin = time (NULL);
	tiempoEjecucion = (float) (fin-inicio);

	printf("Time = %f secs\n", tiempoEjecucion);
	printf("Number of keys = %d\n", longitudListaDependencias (listaClaves));

	// Write the output keys file.
	escribirListaClavesFichero (listaClaves, ficheroClaves);

	
	liberarMemoria ();

	//exit(0); 

	// =====================================================
	// =====================================================
	// ================= End of execution ==================
	// =====================================================
	// =====================================================
}


/* Free all remaining memory. */
void liberarMemoria () {
	liberarListaDependencias (lista);
	liberarListaDependencias (nodo);
	liberarListaNodos (L);	
	liberarListaDependencias (listaDepWastl);	
	liberarListaDependencias (listaClaves);
}


// =====================================================
// =====================================================
// ==================== End of File ====================
// =====================================================
// =====================================================
