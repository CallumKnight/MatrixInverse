// Description ---------------------------------------------------------

/* 

This program is capable of performing the following operations: 

- Convert a vector into a square matrix of given size (if possible). If 
not possible an error message will be prompted to the user indicating why.

- Convert a matrix into a flattened vector.

- Calculate the inverse of any given matrix. If matrix provided is not 
invertible an error message will be prompted to the user indicating why.

- Calculate the determinant of a matrix of any given size.

- Perform matrix multiplication between two given matrices (this can also handle Nx1 vectors).

- Perform matrix addition between two given matrices (this can also handle Nx1 vectors).

- Print matrix values to screen.

*/

// Includes ------------------------------------------------------------

#include <vector>
#include <iostream>
#include <cmath>

// Function prototypes -------------------------------------------------

bool convertVectorToSquareMatrix(std::vector<std::vector<double>> &matrix, std::vector<double> vector, int8_t matrixDimension);
void convertMatrixToVector(std::vector<double> &vector, std::vector<std::vector<double>> matrix);
bool matrixInverse(std::vector<std::vector<double>> &inverseMatrix, std::vector<std::vector<double>> matrix);
double calculateDeterminant(std::vector<std::vector<double>> matrix);
bool matrixMultiply(std::vector<std::vector<double>> &result, const std::vector<std::vector<double>> matrix1, const std::vector<std::vector<double>> matrix2);
bool matrixAddition(std::vector<std::vector<double>> &result, const std::vector<std::vector<double>> matrix1, const std::vector<std::vector<double>> matrix2);
void printMatrix(std::vector<std::vector<double>> matrix);

// Main -----------------------------------------------------------------

int main(){
    // Enter matrix to be inverted here (outer vector contains rows, inner vector contains column elements)
    std::vector<std::vector<double>> matrix = {{-1,-1,2},{2,1,1},{3,4,5}};
    std::vector<std::vector<double>> inverse;

    if(matrixInverse(inverse, matrix)){
        printMatrix(inverse);
    };

    return 0;
}

// Function implementations ----------------------------------------------

bool convertVectorToSquareMatrix(std::vector<std::vector<double>> &matrix, std::vector<double> vector, int8_t matrixDimension) {

    bool successful = true;

    // Ensure result vector is empty
    matrix.clear();

    if(vector.size() % matrixDimension != 0){ // Matrix dimension is not appropriate for converting vector into square matrix
        
        successful = false;

        std::cout << "Vector cannot be converted into a square matrix for the matrix dimension given." << std::endl;
    }
    else{ // Matrix dimension is appropriate for converting vector into square matrix
        
        std::vector<double> row;

        // Convert Nx1 covariance vector into a N/matrixDimension x N/matrixDimension covariance matrix
        for(int8_t i = 1; i <= vector.size(); i++){

            row.push_back(vector[i-1]);
            
            if(i % matrixDimension == 0){
                
                matrix.push_back(row);
                row.clear();
            }
        }
    }

    return successful; 
}

// ----------------------------------------------------------------------

void convertMatrixToVector(std::vector<double> &vector, std::vector<std::vector<double>> matrix) {

    // Ensure result vector is empty
    vector.clear();
    
    for(int8_t i = 0; i < matrix.size(); i++){

        for(int8_t j = 0; j < matrix[0].size(); j++){
            vector.push_back(matrix[i][j]);
        }
    }
}

// ----------------------------------------------------------------------

bool matrixInverse(std::vector<std::vector<double>> &inverseMatrix, std::vector<std::vector<double>> matrix) {
        
    bool successful = true;
    std::vector<std::vector<double>> signMatrix;
    std::vector<std::vector<double>> minorMatrix;
    std::vector<std::vector<double>> cofactorMatrix;
    std::vector<std::vector<double>> cofactorMatrixTranspose;
    double determinant = 0;

    // Ensure result vector is empty
    inverseMatrix.clear();
    
    if(matrix.size() != matrix[0].size()){ // Matrix is not NxN dimensional, therefor inverse does not exist

        successful = false;
        std::cout << "Inverse does not exist for this matrix, matrix must be NxN dimensional." << std::endl;
    }
    else if(matrix.size() == 1){ // Matrix dimension equals 1, inverse is simply the reciprocal of the matrix value

        if(matrix[0][0] != 0){ // Matrix value is not equal to 0, reciprocal exists, therefore inverse exists

            std::vector<double> inverseRow;

            inverseRow.push_back(1 / matrix[0][0]);
            inverseMatrix.push_back(inverseRow);
        }
        else{ // Matrix value equals 0, reciprocal value does not exist, therefore inverse does not exist

            successful = false;
            std::cout << "Inverse does not exist for this matrix, cannot divide by zero." << std::endl;
        }  
    }
    else{ // Matrix dimension is > 1, and matrix is NxN dimensional - inverse algorithm is used

        // Construct sign matrix
        for(int8_t i = 1; i < matrix.size()+1; i++){
            
            std::vector<double> signRow;
            
            for(int8_t j = 1; j < matrix[0].size()+1; j++){ 
                signRow.push_back(pow(-1, i+j));
            }

            signMatrix.push_back(signRow);    
        }
        
        // Construct minorMatrix
        for(int8_t i = 0; i < matrix.size(); i++){

            std::vector<double> minorRow;
            
            for(int8_t j = 0; j < matrix[0].size(); j++){
                
                std::vector<std::vector<double>> reducedMatrix;

                // Construct reduced matrix with the row and column of minor being calculated removed
                for(int8_t k = 0; k < matrix.size(); k++){

                    std::vector<double> reducedRow;

                    for(int8_t l = 0; l < matrix[0].size(); l++){
                        
                        // Copy elements that are not equal to the column of the minor being calculated
                        if(l != j){
                            
                            reducedRow.push_back(matrix[k][l]);
                        }
                    }

                    // Add row to reduced matrix if it does not equal to the row of the minor being calculated  
                    if(k != i){
                        
                        reducedMatrix.push_back(reducedRow);
                    }
                }
                
                // Calculate determinant of reduced matrix, append result to the row of minors
                minorRow.push_back(calculateDeterminant(reducedMatrix));
            }

            // Append row of minors to the matrix of minors
            minorMatrix.push_back(minorRow); 
        }

        // Construct cofactor matrix
        for(int8_t i = 0; i < matrix.size(); i++){
            
            std::vector<double> cofactorRow;

            for(int8_t j = 0; j < matrix[0].size(); j++){
                cofactorRow.push_back(signMatrix[i][j]*minorMatrix[i][j]);
            }

            cofactorMatrix.push_back(cofactorRow);
        }

        // Transpose cofactor matrix
        for(int8_t i = 0; i < matrix.size(); i++){

            std::vector<double> transposeRow;
            
            for(int8_t j = 0; j < matrix[0].size(); j++){
                transposeRow.push_back(cofactorMatrix[j][i]);
            }

            cofactorMatrixTranspose.push_back(transposeRow);
        }

        // Calculate determinant
        for(int8_t i = 0; i < matrix[0].size(); i++){
            
            determinant += (signMatrix[0][i]*minorMatrix[0][i]*matrix[0][i]);
        }

        // Calculate inverse matrix
        if(determinant == 0){ // Determinant equals 0, cannot divide by 0, therefore inverse does not exist 
            
            successful = false;
            std::cout << "Inverse does not exist for this matrix, determinant is equal to zero." << std::endl;
        }
        else{ // Determinant is not equal to 0, therefore inverse does exist

            for(int8_t i = 0; i < matrix.size(); i++){
                
                std::vector<double> inverseRow;
                
                for(int8_t j = 0; j < matrix[0].size(); j++){
                    inverseRow.push_back(cofactorMatrixTranspose[i][j] / determinant);
                }

                inverseMatrix.push_back(inverseRow);
            }
        }   
        
    }

    return successful;
}

// ----------------------------------------------------------------------

double calculateDeterminant(std::vector<std::vector<double>> matrix) {

    std::vector<double> signRow;
    std::vector<double> minorRow;
    double determinant = 0;
    
    if(matrix.size() == 1){ // Matrix dimension equals 1, return the value within the matrix
        
        determinant = matrix[0][0];
    }
    else{ // Calculate determinant using standard approach

        // Populate the row of signs
        for(int8_t i = 0; i < matrix[0].size(); i++){ 
            
            signRow.push_back(pow(-1, 2+i));
        }  
        
        // Populate the row of minors
        for(int8_t i = 0; i < matrix[0].size(); i++){
            
            std::vector<std::vector<double>> reducedMatrix;

            // Construct reduced matrix with the row and column of minor being calculated removed
            for(int8_t k = 1; k < matrix.size(); k++){

                std::vector<double> reducedRow;

                for(int8_t l = 0; l < matrix[0].size(); l++){
                    
                    if(l != i){

                        // Copy row elements that are not equal to the column of the minor being calculated
                        reducedRow.push_back(matrix[k][l]);
                    }
                }

                // Add row to reduced matrix  
                reducedMatrix.push_back(reducedRow);
            }
            
            // Calculate determinant of reduced matrix, append result to the row of minors
            minorRow.push_back(calculateDeterminant(reducedMatrix));
        } 

        // Calculate determinant
        for(int8_t i = 0; i < matrix[0].size(); i++){
            
            determinant += (signRow[i]*minorRow[i]*matrix[0][i]);
        }
    }

    return determinant;
}

// ----------------------------------------------------------------------

bool matrixMultiply(std::vector<std::vector<double>> &result, const std::vector<std::vector<double>> matrix1, const std::vector<std::vector<double>> matrix2){
        
    bool successful = true;
    double sum = 0;

    // Ensure result vector is empty
    result.clear();
    
    if(matrix1[0].size() != matrix2.size()){ // Number of columns in matrix 1 are not equal to number of rows in matrix 2
        
        successful = false;
        std::cout << "Number of columns in matrix 1 are not equal to number of rows in matrix 2, cannot multiply." << std::endl;
    }
    else{ // Number of columns in matrix 1 are equal to number of rows in matrix 2
        
        for(int8_t i = 0; i < matrix1.size(); i++){
            
            std::vector<double> row;

            for(int8_t j = 0; j < matrix2[0].size(); j++){
                
                sum = 0;

                for(int8_t k = 0; k < matrix1[0].size(); k++){
                    sum += matrix1[i][k] * matrix2[k][j];
                }

                row.push_back(sum);
            }

            result.push_back(row);
        }
    }

    return successful;
}

// ----------------------------------------------------------------------

bool matrixAddition(std::vector<std::vector<double>> &result, const std::vector<std::vector<double>> matrix1, const std::vector<std::vector<double>> matrix2){
        
    bool successful = true;

    // Ensure result vector is empty
    result.clear();
    
    if(matrix1.size() != matrix2.size() || matrix1[0].size() != matrix2[0].size()){ // Matrices do not have the same number of rows and columns
        
        successful = false;
        std::cout << "Matrices do not have the same number of rows and columns, cannot add." << std::endl;
    }
    else{ // Matrices are of the same dimensions
        
        for(int8_t i = 0; i < matrix1.size(); i++){
            
            std::vector<double> row;

            for(int8_t j = 0; j < matrix1[0].size(); j++){
                
                row.push_back(matrix1[i][j] + matrix2[i][j]);
            }

            result.push_back(row);
        }
    }

    return successful;
}

// ----------------------------------------------------------------------

void printMatrix(std::vector<std::vector<double>> matrix){

    for(int i = 0; i < matrix.size(); i++){
        
        for(int j = 0; j < matrix[0].size(); j++){
            
            std::cout << matrix[i][j] << "  ";
        }

        std::cout << std::endl;
    }
}

// ----------------------------------------------------------------------