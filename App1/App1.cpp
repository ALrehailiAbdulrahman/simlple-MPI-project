
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define  ARRAYSIZE	100000000


double arr[ARRAYSIZE];



int main(int argc, char* argv[])
{
	double sum = 0;
	int size;
	int rank;
	double average = 0;
	
	double t1, t2, t3, t4, t5, t6,t7,t8;

	
	MPI_Status status;

	/***** Initializations *****/
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	printf("\nProcessor Rank %d out of %d", rank, size);

	if (rank == 0) {
		t1 = MPI_Wtime();
		srand((unsigned)time(0));
		sum = 0;
		for (int i = 0; i < ARRAYSIZE; i++) {

			arr[i] = rand();
			sum = sum + arr[i];
		}

		average = sum / ARRAYSIZE;

		t2 = MPI_Wtime();
		printf("  prints sum %0.1f and average %f the time is %f", sum, average, t2 - t1);
		MPI_Send(&arr, ARRAYSIZE, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
		MPI_Send(&arr, ARRAYSIZE, MPI_DOUBLE, 2, 0, MPI_COMM_WORLD);
		MPI_Send(&arr, ARRAYSIZE, MPI_DOUBLE, 3, 0, MPI_COMM_WORLD);

	}


     if (rank == 1) {

		MPI_Recv(&arr, ARRAYSIZE, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);
		t3 = MPI_Wtime();
		double max = arr[0];
		double min = arr[0];
		for (int i = 1; i < ARRAYSIZE-1; i++) {
			if (arr[i] > max) {
				max = arr[i];
			}
			if (arr[i] < min ) {
				min = arr[i];
			}
			
		}

			t4 = MPI_Wtime();
			printf(" prints Max %0.1f and min %0.1f the time is %f", max, min, t4 - t3);

	 }
	 if (rank == 2) {
		 MPI_Recv(&arr, ARRAYSIZE, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);

		 t5 = MPI_Wtime();


		 for (int i = 0; i < ARRAYSIZE; i++) {
			 if (arr[i] == rand()) {
				 printf(" number is found %0.1f  ", arr[i]);
				 break;
			 }



		 }
		 t6 = MPI_Wtime();

		 printf(" and the time is %f", t6 - t5);
	 }

			if (rank == 3) {
				MPI_Recv(&arr, ARRAYSIZE, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);
				int primeNum = 0;
				t7 = MPI_Wtime();
				int i;
				

				for ( i = 2; i <= ARRAYSIZE; i++) {

					if (i %2!=0)
						primeNum++;
				}
				t8 = MPI_Wtime();
				printf(" total Prime number = %d and the time is %f", primeNum,t8 - t7);

			}

		MPI_Finalize();

	}



