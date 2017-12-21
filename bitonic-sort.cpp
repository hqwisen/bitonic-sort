#include <stdio.h>
#include <string>
#include <iostream>
#include <math.h>
#include "mpi.h"

#define DEBUG 10
#define INFO  20
#define ERROR 30
#define OFF 50
#define LOG_LEVEL OFF

using namespace std;

void logger(int level, const string& message, bool endline = true,
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
  string result = "";
  for (int i = 0; i < size - 1; i++){
    result += std::to_string(a[i]) + " ";
  }
  result += to_string(a[size - 1]) + "";
  return result;
}


int main( int argc, char **argv) {

  int rank, nb_instance;
  MPI_Init( &argc, &argv );
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nb_instance);
	MPI_Status status;

	int cnodes = nb_instance - 1;
	int n = cnodes * 2;
  int iterations = int(log(n) / log(2)); // log_2(n)
  if (n == 16){
		if(rank == 0){
      logger(INFO, "Running bitonic sort with 2k=" + to_string(n));
      int A[n] = {14, 16, 15, 11, 9, 8, 7, 5, 4, 2, 1, 3, 6, 10, 12, 13};
      logger(INFO, "Starting bitonic sort on " + arr_str(A, n));
      int cmpbuf[2];
      int k = n;
      int offset, cnode;
      int indices[cnodes];
      for(int i=0; i < iterations; i++){
        k = k / 2;
        offset = 0;
        cnode = 1;
        for (int b=0; b < n/(k*2); b++){
          for(int t=0; t < k; t++){
            indices[cnode] = offset + t;
            cmpbuf[0] = A[offset + t];
            cmpbuf[1] = A[offset + t + k];
            logger(INFO, "Sending " + arr_str(cmpbuf, 2) + " to " + to_string(cnode));
            MPI_Send(cmpbuf, 2, MPI_INT, cnode, 0, MPI_COMM_WORLD);
            cnode++;
          }
          logger(INFO, "A=" + arr_str(A, n));
          offset += k*2;
        }
        for(int c=1; c < cnodes+1 ; c++){
          MPI_Recv(cmpbuf, 2, MPI_INT, c, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
          logger(INFO, "Master recieved from " + to_string(c) + ": " + arr_str(cmpbuf, 2));
          A[indices[c]] = cmpbuf[0];
          A[indices[c] + k] = cmpbuf[1];
        }

      }

      cout<<"Sorted sequence : "<<arr_str(A, n)<<endl;

    }else{
      // Computing nodes only compare
      int buf[2];
      for(int i=0; i < iterations; i++){
        MPI_Recv(buf, 2, MPI_INT, 0, MPI_ANY_TAG,
                  MPI_COMM_WORLD, &status);
        logger(INFO, " Node #" + to_string(rank) + ": " + arr_str(buf, 2)
                  + " → ", false);
        if(buf[0] > buf[1]){
          int tmp = buf[0];
          buf[0] = buf[1];
          buf[1] = tmp;
        }
        logger(INFO, arr_str(buf, 2), true, false);
        MPI_Send(buf, 2, MPI_INT, 0, 0, MPI_COMM_WORLD);
      }
    }
	}

  MPI_Finalize();
	return 0;
}
