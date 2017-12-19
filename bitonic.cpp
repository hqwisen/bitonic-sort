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
  string level_name;
  if (level == DEBUG){
    level_name = "DEBUG";
  }else if(level == INFO){
    level_name = "INFO";
  }else if(level == ERROR){
    level_name = "ERROR";
  }else{
    level_name = "UNKNOWN LEVEL";
  }
  if(level >= LOG_LEVEL && level < OFF){
    cout<<"["<<level_name<<"] "<<message<<endl;
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

int max_node_id(int rank){
  return 2 * rank + 1;
}

int min_node_id(int rank){
  return 2 * rank + 2;
}

int merge(int seq[], int n, int rank){
  log(INFO, "merge(n=" + to_string(n) + ") on " + arr_str(seq, n));
  if(n < 2){
    // nothing to do
  }
  else if(n == 2){
    // swap
  }else{
    int k = n / 2;
    int max_seq[k], min_seq[k];
    build_max_seq(seq, max_seq, n);
    log(INFO, "max seq " + arr_str(max_seq, k));
    build_min_seq(seq, min_seq, n);
    log(INFO, "min seq " + arr_str(min_seq, k));
    log(INFO, "Sending MAX_seq from "
              + to_string(rank) + "to " + to_string(max_node_id(rank)));
    MPI_Send(max_seq, k, MPI_INT, max_node_id(rank), 0, MPI_COMM_WORLD);
    log(INFO, "Sending MIN_seq from "
              + to_string(rank) + "to " + to_string(min_node_id(rank)));
    MPI_Send(min_seq, k, MPI_INT, min_node_id(rank), 0, MPI_COMM_WORLD);
    // MPI_Isend(&buffer,count,type,max_node_id(rank),tag,comm, &request)
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
      int A[n] = {14, 16, 15, 11, 9, 8, 7, 5, 4, 2, 1, 3, 6, 10, 12, 13};
      log(INFO, "Starting bitonic sort on " + arr_str(A, n));
      // merge(A, n, rank);
      // int max_seq[k], min_seq[k];
      //build_max_seq(A, max_seq, n);
      // build_min_seq(A, min_seq, n);
      // log(INFO, "max seq of A " + arr_str(max_seq, k));
      // log(INFO, "min seq of A " + arr_str(min_seq, k));
      // d seq and e seq
      // transfter d e seqs to nodes
      // Wait for solution
      // MPI_Send(A, n, MPI_INT, 1, 1, MPI_COMM_WORLD);
    }else{
      int rec_level = rank + (rank % 2);
      int buffer[n];
      // MPI_Recv(buffer, n, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG,
      //         MPI_COMM_WORLD, &status);
      log(INFO, "Rank " + to_string(rank) + " recv " + arr_str(buffer, n));
    //    if(k == 2){
          // swap
    //    }else{
          // build min max
          // send min max
    //    }
    }
	}

  MPI_Finalize();
	return 0;
}
