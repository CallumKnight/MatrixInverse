#include <vector>
#include <iostream>
#include <cmath>


// Function prototypes
std::vector<std::vector<double>> calculateInverseOfMatrix(std::vector<std::vector<double>> matrix);
double calculateDeterminant(std::vector<std::vector<double>> matrix);
void printMatrix(std::vector<std::vector<double>> matrix);


// Main
int main(){
    // Enter matrix to be inverted here (outer vector contains rows, inner vector contains column elements)
    std::vector<std::vector<double>> matrix = {{-1,-1,2},{2,1,1},{3,4,5}};
    std::vector<std::vector<double>> inverse;

    inverse = calculateInverseOfMatrix(matrix);

    return 0;
}


// Function implementations
std::vector<std::vector<double>> calculateInverseOfMatrix(std::vector<std::vector<double>> matrix) {
        
    std::vector<std::vector<double>> inverseMatrix;
    std::vector<std::vector<double>> signMatrix;
    std::vector<std::vector<double>> minorMatrix;
    std::vector<std::vector<double>> cofactorMatrix;
    std::vector<std::vector<double>> cofactorMatrixTranspose;
    double determinant = 0;

    std::cout << "Calculating inverse of:" << std::endl;
    printMatrix(matrix);
    
    if(matrix[0].size() == 1){ // Matrix dimension equals 1, inverse is simply the reciprocal of the matrix value

        if(matrix[0][0] != 0){ // Matrix value is not equal to 0, reciprocal exists, therefore inverse exists

            std::vector<double> inverseRow;

            inverseRow.push_back(1 / matrix[0][0]);
            inverseMatrix.push_back(inverseRow);

            std::cout << "Inverse:" << std::endl;
            printMatrix(inverseMatrix);
        }
        else{ // Matrix value equals 0, reciprocal value does not exist, therefore inverse does not exist

            std::vector<double> inverseRow;

            inverseRow.push_back(0);
            inverseMatrix.push_back(inverseRow);

            std::cout << "Inverse does not exist for this matrix, cannot divide by zero." << std::endl;
        }  
    }
    else{ // Matrix dimension is > 1, inverse algorithm is used

        if(matrix.size() != matrix[0].size()){ // Matrix is not NxN dimensional, therefore inverse does not exist

            std::vector<double> inverseRow;

            inverseRow.push_back(0);
            inverseMatrix.push_back(inverseRow);

            std::cout << "Inverse does not exist for this matrix, matrix must be NxN dimensional." << std::endl;
        }
        else{ // Matrix is NxN dimensional

            // Construct sign matrix
            for(int i = 1; i < matrix[0].size()+1; i++){
                
                std::vector<double> signRow;
                
                for(int j = 1; j < matrix[0].size()+1; j++){ 
                    signRow.push_back(pow(-1, i+j));
                }

                signMatrix.push_back(signRow);    
            }

            std::cout << "Sign matrix:" << std::endl;
            printMatrix(signMatrix);
            
            // Construct minorMatrix
            for(int i = 0; i < matrix[0].size(); i++){

                std::vector<double> minorRow;
                
                for(int j = 0; j < matrix[0].size(); j++){
                    
                    std::vector<std::vector<double>> reducedMatrix;

                    // Construct reduced matrix with the row and column of minor being calculated removed
                    for(int k = 0; k < matrix[0].size(); k++){

                        std::vector<double> reducedRow;

                        for(int l = 0; l < matrix[0].size(); l++){
                            
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

            std::cout << "Minor matrix:" << std::endl;
            printMatrix(minorMatrix);

            // Construct cofactor matrix
            for(int i = 0; i < matrix[0].size(); i++){
                
                std::vector<double> cofactorRow;

                for(int j = 0; j < matrix[0].size(); j++){
                    cofactorRow.push_back(signMatrix[i][j]*minorMatrix[i][j]);
                }

                cofactorMatrix.push_back(cofactorRow);
            }

            std::cout << "Cofactor matrix:" << std::endl;
            printMatrix(cofactorMatrix);

            // Transpose cofactor matrix
            for(int i = 0; i < matrix[0].size(); i++){

                std::vector<double> transposeRow;
                
                for(int j = 0; j < matrix[0].size(); j++){
                    transposeRow.push_back(cofactorMatrix[j][i]);
                }

                cofactorMatrixTranspose.push_back(transposeRow);
            }

            std::cout << "Cofactor matrix transposed:" << std::endl;
            printMatrix(cofactorMatrixTranspose);

            // Calculate determinant
            for(int i = 0; i < matrix[0].size(); i++){
                
                determinant += (signMatrix[0][i]*minorMatrix[0][i]*matrix[0][i]);
            }

            std::cout << "Determinant:" << std::endl;
            std::cout << determinant << std::endl;

            // Calculate inverse matrix
            if(determinant == 0){ // Determinant equals 0, cannot divide by 0, therefore inverse does not exist 
                
                std::vector<double> inverseRow;

                inverseRow.push_back(0);
                inverseMatrix.push_back(inverseRow);

                std::cout << "Inverse does not exist for this matrix, determinant is equal to zero." << std::endl;
            }
            else{ // Determinant is not equal to 0, therefore inverse does exist

                for(int i = 0; i < matrix[0].size(); i++){
                    
                    std::vector<double> inverseRow;
                    
                    for(int j = 0; j < matrix[0].size(); j++){
                        inverseRow.push_back(cofactorMatrixTranspose[i][j] / determinant);
                    }

                    inverseMatrix.push_back(inverseRow);
                }

                std::cout << "Inverse:" << std::endl;
                printMatrix(inverseMatrix);
            }   
        }     
        
    }

    return inverseMatrix;
}


double calculateDeterminant(std::vector<std::vector<double>> matrix) {

    std::vector<double> signRow;
    std::vector<double> minorRow;
    double determinant = 0;
    
    
    if(matrix[0].size() == 1){ // Matrix dimension equals 1, return the value within the matrix
        
        determinant = matrix[0][0];
    }
    else{ // Calculate determinant using standard approach

        // Populate the row of signs
        for(int i = 0; i < matrix[0].size(); i++){ 
            
            signRow.push_back(pow(-1, 2+i));
        }  
        
        // Populate the row of minors
        for(int i = 0; i < matrix[0].size(); i++){
            
            std::vector<std::vector<double>> reducedMatrix;

            // Construct reduced matrix with the row and column of minor being calculated removed
            for(int k = 1; k < matrix[0].size(); k++){

                std::vector<double> reducedRow;

                for(int l = 0; l < matrix[0].size(); l++){
                    
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
        for(int i = 0; i < matrix[0].size(); i++){
            
            determinant += (signRow[i]*minorRow[i]*matrix[0][i]);
        }
    }

    return determinant;
}


void printMatrix(std::vector<std::vector<double>> matrix){

    for(int i = 0; i < matrix.size(); i++){
        
        for(int j = 0; j < matrix[0].size(); j++){
            
            std::cout << matrix[i][j] << "  ";
        }

        std::cout << std::endl;
    }
}