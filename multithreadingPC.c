
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
pthread_mutex_t mutex;

struct ThreadData{
int size1, size2, row, col;
    int **M1, **M2, **result;
    int ID;
};
// Function prototype
void createAndJoinThreads(int size1, int** M1, int size2, int** M2, int** result) ;
void intializeMatrices(int size1, int size2, int** M1, int** M2, int** result);
void generateRandomMatrix(int size, int** matrix);
void inputMatrixValues(int size, int** matrix);
void multiplyAndSum(int size1, int size2, int** M1, int** M2, int** result);
void* matrixMultiplyThread(void* threadData);
void printMatrix(int size, int** matrix);
int** memAllocForArrays(int size);
void freeMemory(int **matrix, int size);

int main(){
    int size1, size2;
    printf("**************************************************************** ");
    printf("Note: \n");
    printf("1- M1 matrix size must be les than M2 size. \n ");
    printf("2-The output size will be always same size of M1. \n ");
    printf("3-the final output resalt matrix will be printed in the end. \n ");
    printf("**************************************************************** ");

    printf("Enter the size for Matrix M1: ");
    scanf("%d", &size1);
    printf("Enter the size for Matrix M2: ");
    scanf("%d", &size2);

    // Allocate memory for matrices
    int **M1 = memAllocForArrays(size1);
    int **M2 = memAllocForArrays(size2);
    int **result = memAllocForArrays(size1);

   // Initialize or input matrices
    intializeMatrices(size1, size2, M1, M2, result);
    // Display the matrices
    printf("\nMatrix M1:\n");
    printMatrix(size1, M1);
    printf("\nMatrix M2:\n");
    printMatrix(size2, M2);
pthread_mutex_init(&mutex, NULL);
    // Perform matrix multiplication
    createAndJoinThreads(size1, M1, size2, M2, result);

    // Display the result
    printf("\nOutput matrix (result for overlapping region):\n");
    printMatrix(size1, result);

    // Free dynamically allocated memory
    freeMemory(M1, size1);
    freeMemory(M2, size2);
    freeMemory(result, size1);
pthread_mutex_destroy(&mutex);
    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void createAndJoinThreads(int size1, int** M1, int size2, int** M2, int** result){
    pthread_t threads[size1][size1];
    struct ThreadData threadData[size1][size1];
    int threadID=1;
    for (int row = 0; row < size1; row++)
        for (int col = 0; col < size1; col++)
        {
            // Initialize thread data
            threadData[row][col].size1 = size1;
            threadData[row][col].size2 = size2;
            threadData[row][col].M1 = M1;
            threadData[row][col].M2 = M2;
            threadData[row][col].result = result;
            threadData[row][col].row = row;
            threadData[row][col].col = col;
            threadData[row][col].ID=threadID;
            threadID++;
            // Create a thread for each element
            pthread_create(&threads[row][col], NULL, matrixMultiplyThread, &threadData[row][col]);


        }
            // Wait for all threads to finish
            for (int i = 0; i < size1; i++)
            for (int j = 0; j < size1; j++)
            pthread_join(threads[i][j], NULL);


}
//////////////////////////
void* matrixMultiplyThread(void* threadData){
    struct ThreadData* data = (struct ThreadData*)threadData;
    int row = data->row;//i
    int col = data->col;  ///j
    int size1=data->size1;
    int size2=data->size2;
     pthread_mutex_lock(&mutex);
     data->result[row][col] =0;
     pthread_mutex_unlock(&mutex);
 for (int row2= 0; row2 < size2; row2++) {
        for (int col2 = 0; col2 < size2; col2++) {
            int rowM1 = row + row2;
            int colM1 = col + col2;

            if (rowM1 < size1 && colM1 < size1) {



                data->result[row][col] += data->M1[rowM1][colM1] * data->M2[row2][col2];


            }
        }
    }
    // Acquire lock before updating result matrix
       pthread_mutex_lock(&mutex);

    printf("output with thread of Num[%d] \n \n ",data->ID  );
    printMatrix(size1,data->result);

        pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
    return NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void intializeMatrices(int size1, int size2, int** M1, int** M2, int** result)
{
    srand(time(NULL));
    int choice;
    printf("Choose an option:\n");
    printf("1. Generate random matrices\n2. Input matrix values manually\n Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1){
        generateRandomMatrix(size1, M1);
        generateRandomMatrix(size2, M2);
    }
    else if (choice == 2){
        inputMatrixValues(size1, M1);
        inputMatrixValues(size2, M2);
    }
    else{
        printf("Invalid choice. Exiting.\n");
        exit(1);
    }
    // Initialize the result matrix to -1
    for (int i = 0; i < size1; i++)
        for (int j = 0; j < size1; j++)
            result[i][j] =-1;
}
/////////////////////////////
void generateRandomMatrix(int size, int** matrix){
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            matrix[i][j] = rand() % 10;
}
/////////////////////////////////
void inputMatrixValues(int size, int** matrix){
    printf("Enter matrix values:\n");
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++){
            printf("Enter value for M[%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
}
//////////////////////////////
int** memAllocForArrays(int size){
    int **matrix = malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++)
        matrix[i] = malloc(size * sizeof(int));

    return matrix;
}
///////////////////////
void freeMemory(int **matrix, int size){
    for (int i = 0; i < size; i++)
        free(matrix[i]);

    free(matrix);
}
//////////////////////////
void printMatrix(int size, int** matrix){

    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++)
            printf("%d   ", matrix[i][j]);

        printf("\n \n");
    }
    printf("----------------------------\n");

}
