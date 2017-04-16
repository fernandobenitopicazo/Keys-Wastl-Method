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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "keysWastlV1.h"


/* Reserved Words */
char NULLVALUE[FILENAME] = "NULO\n";


/* Global variables */
char keysFile[FILENAME]; // = "experimentKeys.txt";
struct dependenciesList * keysList = NULL;

FILE * outputFile;

// Counter
float runningTime = 0.0;


/*
   ====================================================
   ==================================================== 
*/


/* Global variables of main file */
char * fileIdentifier = NULL;
char * methodIdentifier = NULL;


struct dependenciesList * list;
struct dependenciesList * wastlDependenciesList = NULL;
struct dependenciesList * node = NULL;
struct nodesList * L = NULL;

clock_t initialTime, endTime;



/* Headers of the main file. */
void pureWastl ();
void freeMemory ();



// =======================================================
// ------------------------- WASTL -----------------------
// =======================================================


void pureWastl () {
	printf("--------------------------------------\n");
	printf("WASTL\n");
	printf("---------\n");
	// generate the list of dependencies from file
	list = createDependenciesListFromFile (fileIdentifier);
	printf("List of dependencies\n");
	printf("--------------------\n");
	paintDependenciesList (list);
	wastlDependenciesList = createDependenciesWastl (list);
	//wastlDependenciesList = reverse(wastlDependenciesList);
	printf("List of Wastl dependencies (UNIT)\n");
	printf("---------------------------------\n");
	paintDependenciesList (wastlDependenciesList);

	printf("--------------------------------------\n");
	node = rootTableaux (wastlDependenciesList);
	printf("Root Tableaux (K2)\n");
	paintDependenciesList (node);

	printf("--------------------------------------\n");
	printf("K1 Rule Wastl\n");
	wastlK1InferenceRule (wastlDependenciesList, node, L);

	printf("--------------------------------------\n");
	printf("--------------------------------------\n");
	printf("----------- Wastl's Keys -------------\n");
	printf("--------------------------------------\n");
	printf("--------------------------------------\n");
	paintDependenciesList (keysList);
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
	fileIdentifier = argv[1];

	// Name of the resulting keys file.
	sprintf(keysFile, "Keys-%s", fileIdentifier);

	/* Read the selected method. 
	This is prepared for further development where other methods may be implemented.
	*/
	//methodIdentifier = (int) atoi(argv[2]);
	methodIdentifier = argv[2];
		
	// Timer begins
	initialTime = time (NULL);
	
	// Call the method for execution
	if (strcmp (methodIdentifier, "keysWastl") == 0) {
		pureWastl ();
	} else {
		printf("--------------------------------------\n");
		printf("--------------------------------------\n");
		printf("------------ Wrong Method ------------\n");
		printf("--------------------------------------\n");
		printf("--------------------------------------\n");
		exit(0);
	}

	// Timer ends
	endTime = time (NULL);
	runningTime = (float) (endTime-initialTime);

	printf("Time = %f secs\n", runningTime);
	printf("Number of keys = %d\n", sizeDepedenciesList (keysList));

	// Write the output keys file.
	saveKeysListToFile (keysList, keysFile);

	
	freeMemory ();

	//exit(0); 

	// =====================================================
	// =====================================================
	// ================= End of execution ==================
	// =====================================================
	// =====================================================
}


/* Free all remaining memory. */
void freeMemory () {
	freeDependenciesList (list);
	freeDependenciesList (node);
	freeNodesList (L);	
	freeDependenciesList (wastlDependenciesList);	
	freeDependenciesList (keysList);
}


// =====================================================
// =====================================================
// ==================== End of File ====================
// =====================================================
// =====================================================
