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
#define CELLSIZE 30
#define DEPENDENCYSIZE 1024
#define MARKER " "
#define FILENAME 256


/* Data structures */
// Node
struct nodesList {
	char stringChar[CELLSIZE];
	struct nodesList * next;
};

// Functional dependency, FD.
struct dependenciesList {
	struct nodesList * left;
	struct nodesList * right;
	struct dependenciesList * next;
};



/* Functions and procedures headers. */

// -------------------------------------------------------
// ------------------- WASTL and SHARED ------------------
// -------------------------------------------------------

struct dependenciesList * makeCopyDependenciesList (struct dependenciesList * );
struct dependenciesList * reverse (struct dependenciesList *);
void freeNodesList (struct nodesList *);
void freeDependenciesList (struct dependenciesList *);
void closeFile(FILE *);
struct nodesList * insertNode (struct nodesList *, char *);
struct nodesList * insertNodeList (struct nodesList *, struct nodesList *);
struct dependenciesList * createDependenciesListFromFile (char *);
struct dependenciesList * createDependenciesWastl(struct dependenciesList *);
void getNode(char *, struct nodesList *);
void paintNodesList (struct nodesList *);
void paintDependenciesList (struct dependenciesList *);
struct dependenciesList * insertDependency (struct dependenciesList *, struct nodesList *, struct nodesList *);
struct dependenciesList * rootTableaux (struct dependenciesList *);
char * replace (char *, char *, char *);
int exists (char *, struct nodesList *);
char * findElement (struct nodesList *, int);
int sizeDepedenciesList (struct dependenciesList *);
int sizeNodesList (struct nodesList *);
struct nodesList * removeElemFromTableaux (struct nodesList *, char *);
struct nodesList * insertElemToTableaux (struct nodesList *, struct nodesList *);
int voidIntersection (struct nodesList *, struct nodesList *);
int existCandidates (struct dependenciesList *, struct dependenciesList *, struct nodesList *);
int isCandidate(struct dependenciesList *, struct dependenciesList *, struct nodesList *);
struct dependenciesList * makeCopyTableaux (struct dependenciesList *);
struct nodesList * makeCopyL (struct nodesList *);
void saveKeysListToFile (struct dependenciesList *, char *);
char * generateOutputKey (struct dependenciesList *);
struct dependenciesList * insertKey (struct dependenciesList *, struct dependenciesList *);
int includeIn (struct nodesList *, struct nodesList *);
void wastlK1InferenceRule (struct dependenciesList *, struct dependenciesList *, struct nodesList *);
void saveAlgorithmData (char *);


// =====================================================
// =====================================================
// =================== End of File =====================
// =====================================================
// =====================================================
