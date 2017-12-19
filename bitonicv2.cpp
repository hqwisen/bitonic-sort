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

void log(int level, const string& message, bool endline = true,
         bool showlvl=true){
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
    if(showlvl){
      cout<<"["<<level_name<<"]";
    }
    cout<<message;
    if(endline){
      cout<<endl;
    }
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


void send_cmp(int A[], int cnodes, int k){
  int cmpbuf[2];
  for(int i=0; i < cnodes; i++){
    cmpbuf[0] = A[i];
    cmpbuf[1] = A[k+i];
    MPI_Send(cmpbuf, 2, MPI_INT, i+1 , 0, MPI_COMM_WORLD);
  }


  for(int l=0; l < cnodes / k; l++){
    for(int i=0; i < k; i++){
      index = (l * h) + i;
    }
  }
}

void recv_cmp(int A[], int k, int rec_lvl){
  MPI_Status status;
  int cmpbuf[2];
  for(int i=0; i < k; i++){
    for(int r=0; r < rec_lvl; r++){
      MPI_Recv(cmpbuf, 2, MPI_INT, i+1, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
      A[i + k*r] = cmpbuf[0];
      A[k+(i+k*r)] = cmpbuf[1];
    }
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
      int cmpbuf[2];
      int rec_lvl = 1;
      int k = n / 2;
      while(k != 2){
        log(INFO, "Sending with (k=" + to_string(k)
                                + ", rec_lvl=" + to_string(rec_lvl) + ")");
        send_cmp(A, k, rec_lvl);
        recv_cmp(A, k, rec_lvl);
        k = k / 2;
        rec_lvl++;
        log(INFO, "Recv: " + arr_str(A, n));
      }

    }else{
      // Computing nodes only compare
      int buf[2];
      MPI_Recv(buf, 2, MPI_INT, 0, MPI_ANY_TAG,
                MPI_COMM_WORLD, &status);
      log(INFO, " Node #" + to_string(rank) + ": " + arr_str(buf, 2)
                + " → ", false);
      if(buf[0] > buf[1]){
        int tmp = buf[0];
        buf[0] = buf[1];
        buf[1] = tmp;
      }
      log(INFO, arr_str(buf, 2), true, false);
      MPI_Send(buf, 2, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
	}

  MPI_Finalize();
	return 0;
}
