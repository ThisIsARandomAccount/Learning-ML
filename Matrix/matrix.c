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

/// Returns random double such that min <= x <= max. Does NOT seed random.
/// - Parameters:
///   - min: Minimum inclusive value
///   - max: Maximum inclusive value
double rand_double(double min, double max){
    double num = rand(); // 0 <= x <= RAND_MAX
    num /= (double)(RAND_MAX); // 0 <= x <= 1e
    double diff = max - min;
    num *= diff; // 0 <= x <= max-min
    num += min; // min <= x <= max
    
    return num;
} // SUCCESS

/// Populates matrix with random values such that min <= x <= max
/// - Parameters:
///   - to_randomize: Matrix to populate
///   - min: Minimum value
///   - max: Maximum value
void randomize(Matrix* to_randomize, double min, double max){
    for(int i = 0; i < to_randomize->rows; i++){
        for(int j = 0; j < to_randomize->cols; j++){
            to_randomize->data[i][j] = rand_double(min, max);
        }
    }
    return;
} // SUCCESS

/// Flattens a matrix, moving left to right primarily and top to bottom secondarily
/// - Parameters:
///   - to_flatten: Matrix to be flattened
///   - row_col_bool: A boolean indicating whether the resultant matrix should be a row or a column, 0 is a row, 1 is a column, any other value will not throw an error but be treated as a column, for simplicity
Matrix* flatten(Matrix* to_flatten, int row_col_bool){
    Matrix* matrix = (row_col_bool == 0)?create(1,to_flatten->rows*to_flatten->cols): create(to_flatten->rows * to_flatten->cols, 1);
    for(int i = 0; i < to_flatten->rows; i++){
        for(int j = 0; j < to_flatten->cols; j++){
            if(row_col_bool == 0){
                matrix->data[0][i*to_flatten->cols+j] = to_flatten->data[i][j];
            }
            else{
                matrix->data[i*to_flatten->cols+j][0] = to_flatten->data[i][j];
            }
        }
    }
    return matrix;
} // SUCCESS

/// Finds the row index (starts at 0) of the maximum value in a column of a matrix
/// - Parameters:
///   - input: The matrix to be processed
///   - col: The column of the matrix to consider
int argmax(Matrix* input, int col){
    double current_max = input->data[0][col];
    int id_max = 0;
    for(int i = 1; i < input->rows; i++){
        if(input->data[i][col] > current_max){
            current_max = input->data[i][col];
            id_max = i;
        }
    }
    return id_max;
} // SUCCESS

/// Performs and returns dot product of an Mx1 and 1xM matrix. Sets errno to -1 if the inputs have improper dimensions.
/// - Parameters:
///   - m1: First matrix to dot
///   - m2: Second matrix to dot
double primitive_dot(Matrix* m1, Matrix* m2){
    if(m1->rows != 1 && m1->cols != 1){
        printf("Improper matrix dimensions\n");
        errno = -1;
        return 0;
    }
    else if(m2->rows != 1 && m2->cols != 1){
        printf("Improper matrix dimensions\n");
        errno = -1;
        return 0;
    }
    if((m1->rows == m2->cols)&&(m1->cols == m2->rows)){
        double sum = 0;
        Matrix* p_m1 = flatten(m1, 0);
        Matrix* p_m2 = flatten(m2, 0);
        int its;
        if(m1->rows == 1){
            its = m1->cols;
        }
        else{
            its = m1->rows;
        }
        for(int i = 0; i < its ; i++){
            sum += p_m1->data[0][i] * p_m2->data[0][i];
        }
        free(p_m1);
        free(p_m2);
        return sum;
    }
    else{
        printf("Improper matrix dimensions\n");
        errno = -1;
        return 0;
    }
} // SUCCESS

/// Performs and returns dot product of an MxN and NxP matrix. The return is dimension MxP. Sets errno to -1 if inputs are of improper dimension
/// - Parameters:
///   - m1: A matrix
///   - m2: Another matrix
Matrix* dot(Matrix* m1, Matrix* m2){
    if(m1->cols == m2->rows){
        Matrix* to_return = create(m1->rows, m2->cols);
        
        return NULL;
    }
    else if(m1->rows == m2->cols){
        Matrix* to_return = create(m2->rows, m1->cols);
        return NULL;
    }
    else{
        printf("Improper matrix dimensions\n");
        errno = -1;
        return NULL;
    }
}

int main(void){
    srand((unsigned int)time(NULL));
    Matrix* first = create(2,3);
    Matrix* second = create(3,1);
    randomize(first,0,10);
    randomize(second,0,10);
    print_matrix(first);
    print_matrix(second);
    printf("Dot Product: %lf\n",primitive_dot(first,second));
    free_matrix(first);
    free_matrix(second);
    return 0;
}
