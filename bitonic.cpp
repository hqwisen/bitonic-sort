#include <stdio.h>
#include <string>
#include <iostream>
#include "mpi.h"

#define DEBUG 10
#define INFO  20
#define ERROR 30
#define OFF 50
#define LOG_LEVEL DEBUG

using namespace std;

void log(int level, const string& message){

  if(level >= LOG_LEVEL){
    cout<<"["<<level<<"] "<<message<<endl;
  }
}


string arr_str(const int a[], int size){
  string result = "[";
  for (int i = 0; i < size - 1; i++){
    result += std::to_string(a[i]) + ", ";
  }
  result += to_string(a[size - 1]) + "]";
  return result;
}

void build_max_seq(int A[], int seq[], int n){
  int k = n / 2;
  for(int i = 0; i < k; i++){
    seq[i] = (A[i] > A[k+i]) ? A[i] : A[k+i];
  }
}

void build_min_seq(int A[], int seq[], int n){
  int k = n / 2;
  for(int i = 0; i < k; i++){
    seq[i] = (A[i] < A[k+i]) ? A[i] : A[k+i];
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

  if (n == 16){
		if(rank == 0){
      log(INFO, "Running bitonic sort with 2k=" + to_string(n));
      int k = n / 2;
      int A[n] = {14, 16, 15, 11, 9, 8, 7, 5, 4, 2, 1, 3, 6, 10, 12, 13};
      std::cout << "Starting bitonic sort on " << arr_str(A, n) << std::endl;
      int max_seq[k], min_seq[k];
      build_max_seq(A, max_seq, n);
      build_min_seq(A, min_seq, n);
      log(INFO, "max seq of A " + arr_str(max_seq, k));
      log(INFO, "min seq of A " + arr_str(min_seq, k));
      // d seq and e seq
      // transfter d e seqs to nodes
    }else{
        // sorting nodes

    }
	}

  MPI_Finalize();
	return 0;
}
