#include <stdio.h>
#include <string>
#include "mpi.h"
#include <iostream>

#define DEBUG 1
#define INFO  2
#define ERROR 3
#define LOG_LEVEL ERROR

void log(int level, std::string message){

  if(level >= LOG_LEVEL){
    std::cout<<"["<<level<<"] "<<message<<std::endl;
  }
}

int main( int argc, char **argv) {

  int rank, nb_instance;
  MPI_Init( &argc, &argv );
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nb_instance);
	MPI_Status status;

	int cnodes = nb_instance - 1;
	int n = cnodes * 2;
  printf("In rank %d\n", rank);
  log(DEBUG, "this is a debug message");
  log(INFO, "this is a info message");


  if (n == 16){
		if(rank == 0){
      printf("Starting in bitonic-sort\n");
    	int A[n] = {14, 16, 15, 11, 9, 8, 7, 5, 4, 2, 1, 3, 6, 10, 12, 13};
      // d seq and e seq
      // transfter d e seqs to nodes
    }else{
        // sorting nodes

    }
	}

  MPI_Finalize();
	return 0;
}
