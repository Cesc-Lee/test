#include <stdio.h>
#include "mpi.h"

#define INTERVALS 1000000

int main(int argc, char *argv[])
{
	int id;//process rank
	int p;//#process
	double area;//area under curve
	double xi;//midpoint of interval
	double pi = 0;//sum of rectangle height
	double ypartsum = 0;
	double ysum = 0;
	double elapsed_time;
	int i;

	MPI_Init(&argc, &argv);
	MPI_Barrier(MPI_COMM_WORLD);
	elapsed_time = - MPI_Wtime();
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	for(i = id; i < INTERVALS; i += p)
	{
		xi = (1.0/INTERVALS) * (i + 0.5);
		ypartsum += 4.0/(1.0 + xi*xi);
	}
	
	MPI_Reduce(&ypartsum, &ysum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	elapsed_time += MPI_Wtime();
	//printf("Process %d is done.\n", id);
	fflush(stdout);
	MPI_Finalize();

	if(id == 0)
	{
		pi = ysum * (1.0/INTERVALS);
		printf("PI = %.10lf\n", pi);
		printf("Time = %f\n", elapsed_time);
	}
	return 0;

}
