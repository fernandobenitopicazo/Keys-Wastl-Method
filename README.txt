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

Main file: keysWastl.c
Headers file: keysWastl.h
Functions and procedures file: keysWastlLibrary.c

Executable file: keysWastl

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

./keysWastl <DependenciesFileName> <MethodName> 

For instance:

./keysWastlV1 wastl10.txt keysWastl 

Or:

./keysWastlV1 ejemplo001.txtkeysWastl


Thereafter, the software will generate a file containing all the keys. This file will be named as: Keys-<name of source>.txt This file contains a key per line.

For instance:

Keys-wastl10.txt




Fernando Benito-Picazo. University of Malaga, Spain.
fbenito@lcc.uma.es
======================================================

==================== End of File ====================
=
======================================================









