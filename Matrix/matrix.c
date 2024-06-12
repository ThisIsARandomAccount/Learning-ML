#include "matrix.h"

/// Instantiate matrix structure, allocating necessary space, returns pointer to matrix
/// - Parameters:
///   - rows: number of rows the matrix has
///   - cols: number of columns the matrix has
Matrix* create(int rows, int cols){
    
    Matrix* matrix;
    
    // Allocate space for struct
    matrix = (Matrix*)malloc(sizeof(*matrix));
    
    // Assign members
    matrix->rows = rows;
    matrix->cols = cols;
    
    // Allocate space for data member
    matrix->data = (double**)malloc(matrix->rows*sizeof(double*));
    if(matrix->data == NULL){
        perror("Failed to allocate memory");
    }
    for(int i = 0; i < matrix->rows; i++){
        matrix->data[i] = (double*)malloc(matrix->cols * sizeof(double));
        if(matrix->data[i] == NULL){
            perror("Failed to allocate memory");
        }
    }
    
    return matrix;
} // SUCCESS

/// Fill matrix with single value
/// - Parameters:
///   - matrix: matrix structure to fill
///   - num: value to fill matrix with
void fill(Matrix* matrix, double num){
    for(int i = 0; i < matrix->rows; i++){
        for(int j = 0; j < matrix->cols; j++){
            matrix->data[i][j] = num;
        }
    }
    return;
} // SUCCESS

/// Copy data into matrix
/// - Parameters:
///   - matrix: matrix structure to fill
///   - data: data to copy into the matrix;
void copy(Matrix* matrix, double** data){
    for(int i = 0; i < matrix->rows; i++){
        for(int j = 0; j < matrix->cols; j++){
            matrix->data[i][j] = data[i][j];
        }
    }
    return;
} // SUCCESS

/// Free matrix structure and all members
/// - Parameter matrix: matrix to free
void free_matrix(Matrix* matrix){
    for(int i = 0; i < matrix->rows; i++){
        free(matrix->data[i]);
    }
    free(matrix->data);
    free(matrix);
    matrix = NULL;
    return;
} // SUCCESS

/// Prints the matrix structure. Rows are enclosed by | character and separated by newline. Entries are separated by tabspace
/// - Parameter matrix: Matrix to print
void print_matrix(Matrix* matrix){
    printf("-- START MATRIX --\n");
    for(int i = 0; i < matrix->rows; i++){
        for(int j = 0; j < matrix->cols; j++){
            printf("%lf\t",matrix->data[i][j]);
        }
        printf("\n");
    }
    printf("-- END MATRIX --\n");
    return;
} // SUCCESS

///  Returns pointer to copy of provided matrix
/// - Parameter to_copy: Matrix to copy
Matrix* full_copy(Matrix* to_copy){
    Matrix* to_return = create(to_copy->rows, to_copy->cols);
    copy(to_return, to_copy->data);
    return to_return;
} // SUCCESS

/// Saves matrix to file.
/// First number is rows, second number is columns.
/// Afterwards the numbers are stored.
/// All numbers are stored on their own line.
/// - Parameters:
///   - to_save: Matrix to save to file
///   - path: File path to save matrix to (must be .txt)
void save(Matrix* to_save, char* path){
    FILE* file = fopen(path, "w");
    if(file == NULL){
        perror("Failed to open file");
    }
    fprintf(file, "%d\n", to_save->rows);
    fprintf(file, "%d\n", to_save->cols);
    for(int i = 0; i < to_save->rows; i++){
        for(int j = 0; j< to_save->cols; j++){
            fprintf(file, "%lf\n", to_save->data[i][j]);
        }
    }
    printf("Saved to %s\n",path);
    fclose(file);
    return;
} // SUCCESS

/// Load matrix from file
/// - Parameter path: File path to load matrix form (must be .txt)
Matrix* load(char* path){
    string data = reader(path);
    int rows = -1;
    int cols = -1;
    rows = atoi(strtok(data.data, "\n"));
    cols = atoi(strtok(NULL, "\n"));
    double** new_data = (double**)malloc(sizeof(double*)*rows);
    if(new_data == NULL){
        perror("Failed to allocate memory");
    }
    for(int i = 0; i < rows; i++){
        new_data[i] = (double*)malloc(sizeof(double)*cols);
        if(new_data[i] == NULL){
            perror("Failed to allocate memory");
        }
    }
    char* temp;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            new_data[i][j] = strtod(strtok(NULL,"\n"), &temp);
        }
    }
    Matrix* matrix = create(rows, cols);
    copy(matrix,new_data);
    printf("Loaded from %s\n", path);
    return matrix;
} // SUCCESS

int main(void){
    return 0;
}
