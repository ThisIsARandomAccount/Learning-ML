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
}

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
}

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
}

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
}

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
}

///  Returns pointer to copy of provided matrix
/// - Parameter to_copy: Matrix to copy
Matrix* full_copy(Matrix* to_copy){
    Matrix* to_return = create(to_copy->rows, to_copy->cols);
    copy(to_return, to_copy->data);
    return to_return;
}

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
}

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
}

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
}

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
}

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
}

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
}

/// Performs and returns dot product of an m1 (MxN) and m2 (NxP). The return is dimension MxP.
/// - Parameters:
///   - m1: A matrix
///   - m2: Another matrix
Matrix* dot(Matrix* m1, Matrix* m2){
    if(m1->cols == m2->rows){
        Matrix* to_return = create(m1->rows, m2->cols);
        for(int i = 0; i < m1->rows; i++){ // For every row
            for(int j = 0; j < m2->cols; j++){ // For every column
                double sum = 0;
                for(int k = 0; k < m1->cols; k++){ // For every column in the row and every row in the column
                    sum += m1->data[i][k] * m2->data[k][j];
                }
                to_return->data[i][j] = sum;
            }
        }
        return to_return;
    }
    else{
        printf("Improper matrix dimensions: dot\n");
        exit(1);
    }
}

/// Performs and returns addition of two matrices m1 and m2. m1 and m2 must have same dimensions. returned matrix is same dimension as well
/// - Parameters:
///   - m1: A matrix
///   - m2: Another matrix
Matrix* add(Matrix* m1, Matrix* m2){
    if((m1->rows != m2->rows)||(m1->cols != m2->cols)){
        printf("Improper matrix dimenstions: add\n");
        exit(1);
    }
    Matrix* to_return = create(m1->rows,m1->cols);
    for(int i = 0; i < m1->rows; i++){
        for(int j = 0; j < m1->cols; j++){
            to_return->data[i][j] = m1->data[i][j] + m2->data[i][j];
        }
    }
    return to_return;
}

/// Performs and returns subtraction of two matrices m1 and m2 that are the same dimensions. returned matrix is also same dimesion. In the expression a - b, a would be the minuend and b would be the subtrahend.
/// - Parameters:
///   - m1: The minuend matrix
///   - m2: The subtrahend matrix
Matrix* subtract(Matrix* m1, Matrix* m2){
    if((m1->rows != m2->rows)||(m1->cols != m2->cols)){
        printf("Improper matrix dimenstions: subtract\n");
        exit(1);
    }
    Matrix* to_return = create(m1->rows,m1->cols);
    for(int i = 0; i < m1->rows; i++){
        for(int j = 0; j < m1->cols; j++){
            to_return->data[i][j] = m1->data[i][j] - m2->data[i][j];
        }
    }
    return to_return;
}

/// Applys provided function to each entry in a matrix and returns a new matrix with these new values
/// - Parameters:
///   - m: Matrix to apply it to
///   - func: function to apply
Matrix* apply(Matrix* m, double(*func)(double)){
    Matrix* to_return = create(m->rows,m->cols);
    for(int i = 0; i < m->rows; i++){
        for(int j = 0; j < m->cols; j++){
            to_return->data[i][j] = func(m->data[i][j]);
        }
    }
    return to_return;
}

/// Scales matrix by scalar num
/// - Parameters:
///   - m: Matrix to scale
///   - num: Scalar num
Matrix* scale(Matrix* m, double num){
    Matrix* to_return = create(m->rows,m->cols);
    for(int i = 0; i < m->rows; i++){
        for(int j = 0; j < m->cols; j++){
            to_return->data[i][j] = num * m->data[i][j];
        }
    }
    return to_return;
}

/// Switches rows and columns of matrix
/// - Parameter m: Matrix to transpose
Matrix* transpose(Matrix* m){
    Matrix* to_return = create(m->cols,m->rows);
    for(int i = 0; i < m->cols; i++){
        for(int j = 0; j < m->rows; j++){
            to_return->data[i][j] = m->data[j][i];
        }
    }
    return to_return;
}

/// Returns pointer to row echelon version of inputted matrix
/// - Parameter m: Matrix to "row-echelon-ize"
Matrix* row_echelon(Matrix* m){
    Matrix* to_return = full_copy(m);
    for(int i = 0; i < m->rows-1; i++){
        for(int k = i+1; k < m->rows; k++){
            double multiplier = 1;
            int divide_by_zero_flag = 0;
            if(to_return->data[i][i] != 0){
                multiplier = (to_return->data[k][i]/to_return->data[i][i]);
            }
            else{
                divide_by_zero_flag = 1;
            }
            for(int j = 0; j < m->cols; j++){
                if(!divide_by_zero_flag){
                    to_return->data[k][j] -= to_return->data[i][j] * multiplier;
                }
            }
        }
    }
    return to_return;
}

/// Calculates determinant of matrix. Internally calculates row echelon form (does not require row echelon matrix)
/// - Parameter m: Matrix
double determinant(Matrix* m){
    if(m->rows != m->cols){
        printf("Improper dimensions: determinant requires square matrix\n");
        exit(1);
    }
    Matrix* simple = row_echelon(m);
    double determinant = 1;
    for(int i = 0; i < simple->rows; i++){
        determinant *= simple->data[i][i];
    }
    free_matrix(simple);
    return determinant;
}

/// Calculates determinant of matrix
/// - Parameter simple: Matrix in row echelon form
double r_determinant(Matrix* simple){
    if(simple->rows != simple->cols){
        printf("Improper dimensions: determinant requires square matrix\n");
        exit(1);
    }
    double determinant = 1;
    for(int i = 0; i < simple->rows; i++){
        determinant *= simple->data[i][i];
    }
    return determinant;
}

/// Calculates trace of matrix
/// - Parameter m: Matrix to calculate trace of
double trace(Matrix* m){
    if(m->rows == m->cols){
        double trace = 0;
        for(int i = 0; i < m->rows; i++){
            trace += m->data[i][i];
        }
        return trace;
    }
    printf("Improper dimensions: trace\n");
    exit(1);
}

/// Calculates cofactor matrix
/// - Parameter m: Matrix to calculate cofactor of
Matrix* cofactor(Matrix* m){
    if(m->rows != m->cols){
        printf("Improper dimensions: cofactor requires square matrix\n");
        exit(1);
    }
    Matrix* to_return = create(m->rows, m->cols);
    Matrix* temp = create(m->rows - 1, m->cols - 1);
    for(int i = 0; i < m->rows; i++){
        for(int j = 0; j < m->cols; j++){
            int c = 0;
            int r = 0;
            double mult = pow(-1,i+j);
            for(int k = 0; k < m->rows; k++){
                for(int a = 0; a < m->cols; a++){
                    if(k != i && a != j){
                        temp->data[r][c] = m->data[k][a];
                        c++;
                        if((c/temp->cols)==1){
                            c = 0;
                            r++;
                        }
                    }
                }
            }
            to_return->data[i][j] = mult* determinant(temp);
        }
    }
    free_matrix(temp);
    return to_return;
}

/// Calculates adjugate matrix
/// - Parameter m: Matrix to get adjugate of
Matrix* adjugate(Matrix* m){
    if(m->rows != m->cols){
        printf("Improper dimensions: adjugate requires square matrix\n");
        exit(1);
    }
    return(transpose(cofactor(m)));
}

/// Calculates inverse of matrix m. If inverse does not exist due to determinant = 0, returns null ptr
/// - Parameter m: Matrix to inverse
Matrix* inverse(Matrix* m){
    if(m->rows != m->cols){
        printf("Improper dimensions: inverse requires square matrix\n");
        exit(1);
    }
    double deter = determinant(m);
    if(deter == 0){
        return NULL;
    }
    return(scale(adjugate(m),1.0/deter));
}

int main(void){
    srand((unsigned int)time(NULL));
    Matrix* original = create(100,100);
    randomize(original,0,10);
    Matrix* cofac = inverse(original);
    if(cofac == NULL){
        printf("No inverse\n");
    }
    print_matrix(original);
    if(cofac != NULL){
        print_matrix(cofac);}
    free_matrix(cofac);
    free_matrix(original);
    return 0;
}
