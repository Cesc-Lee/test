#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]){
	int id;
	int p;

	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	printf("Process %d: Hello Word!\n", id);

	MPI_Finalize();

	return 0;
}
