***********
README FILE
***********

---------------------------------
Fernando Benito-Picazo
SICUMA Researching Group
Computer Science Dpt.
University of Málaga
Spain
Lab 3.3.11
+(34) 952 137141
fbenito@lcc.uma.es
---------------------------------

*************************
*** WASTL KEYS METHOD ***
*************************

This repository contains the necessary files for running the implementation of R. Wastl's method to infer all the keys from relational schemas.

https://github.com/fernandobenitopicazo/Keys-Wastl-Method/

-------------------------

Source Files:

Main file: keysWastlV1.c
Headers file: keysWastlV1.h
Functions and procedures file: keysWastlLibraryV1.c

Executable file: keysWastlV1

In order to get this executable file we recommend to use the 'makefile' file. 
In any event, having gcc compiler installed, we can also run the following command to get the executable file:
gcc -g -o keysWastlV1 keysWastlV1.c keysWastlLibraryV1.c

--------------------------

Besides, here we can find several files (sources) in order to run experiments, these are:
a3rojo.txt
ejemplo001.txt
elmasri1.txt
intermedio02.txt
restaurantesPaper.txt
wastl2.txt
wastl10.txt
wastl13.txt

Last three ones are generated as from the examples shown in Wastl's paper [1].

[1] R. Wastl, Linear derivations for keys of a database relation schema., J. 125 UCS 4 (11) (1998) 883-897.



********************************
********* INSTRUCTIONS *********
********************************

To run experiments we need the executable file and the source file in the same folder. Then, we only need to run the executable accordingly to the following signature:

./keysWastlV1 <DependenciesFileName> <MethodName> 

For instance:

./keysWastlV1 wastl10.txt keysWastl 

Or:

./keysWastlV1 ejemplo001.txt keysWastl


Thereafter, the software will generate a file containing all the keys. This file will be named as: Keys-<name of source>.txt This file contains a key per line.

For instance:

Keys-wastl10.txt




Fernando Benito-Picazo. 
University of Malaga, Spain.
fbenito@lcc.uma.es
======================================================

==================== End of File ====================
=
======================================================









