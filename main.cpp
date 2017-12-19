#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
	int id, nb_instance, len, value;
	char processor_name[MPI_MAX_PROCESSOR_NAME];
  
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &nb_instance);

	MPI_Get_processor_name(processor_name, &len);
	printf ("Hello world! I'm %d of %d on %s\n", id, nb_instance, processor_name);
	
        do {
            	if (nb_instance == 0) scanf( "%d", &value );
                MPI_Bcast( &value, 1, MPI_INT, 0, MPI_COMM_WORLD );
                printf( "Process %d got %d\n", id, value );
        } while (value >= 0);

	MPI_Finalize();
	return 0;
}
