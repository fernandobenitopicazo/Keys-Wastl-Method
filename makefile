CC := gcc

keysWastlV2: 
	$(CC) -g -o $@ keysWastlV1.c keysWastlLibraryV1.c
