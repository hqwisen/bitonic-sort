#include <stdio.h>
#include "mpi.h"

int main( int argc, char **argv) {

        MPI_Init( &argc, &argv );
        int rank, nb_instance;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nb_instance);
	MPI_Status status;

	int cnodes = nb_instance - 1;
	int n = cnodes * 2;

	if (n == 16){
		if(rank == 0){
			int A[n] = {14, 16, 15, 11, 9, 8, 7, 5, 4, 2, 1, 3, 6, 10, 12, 13};
		}
	}
	return 0;
}
