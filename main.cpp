#include <vector>
#include <iostream>
#include <cmath>


// Function prototypes
std::vector<std::vector<double>> calculateInverseOfMatrix(std::vector<std::vector<double>> matrix);
double calculateDeterminant(std::vector<std::vector<double>> matrix);
void printMatrix(std::vector<std::vector<double>> matrix);


// Main
int main(){
    
    std::vector<std::vector<double>> testMatrix = {{1,2,1,3,4},{2,1,2,5,8},{1,2,2,1,1},{9,9,9,9,9},{7,6,1,1,2}};
    //std::vector<std::vector<double>> testMatrix = {{1,2,1},{2,1,2},{1,2,2}};
    //std::vector<std::vector<double>> testMatrix = {{1,2,3},{4,5,6},{7,8,9}}; // No inverse
    //std::vector<std::vector<double>> testMatrix = {{1,2},{3,4}};
    //std::vector<std::vector<double>> testMatrix = {{1,1},{2,2}}; // No inverse
    //std::vector<std::vector<double>> testMatrix = {{2}};
    //std::vector<std::vector<double>> testMatrix = {{0}}; // No inverse
    std::vector<std::vector<double>> testInverse;

    testInverse = calculateInverseOfMatrix(testMatrix);

    printMatrix(testInverse);

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


    if(matrix[0].size() == 1){
        
        std::vector<double> inverseRow;

        if(matrix[0][0] != 0){

            inverseRow.push_back(1 / matrix[0][0]);
            inverseMatrix.push_back(inverseRow);

            std::cout << "Inverse calculated." << std::endl;
        }
        else{

            inverseRow.push_back(0);
            inverseMatrix.push_back(inverseRow);

            std::cout << "Inverse does not exist for this matrix." << std::endl;
        }
        
        
    }
    else{
        
        // Construct sign matrix
        for(int i = 1; i < matrix[0].size()+1; i++){
            
            std::vector<double> signRow;
            
            // Populate the row
            for(int j = 1; j < matrix[0].size()+1; j++){ 
                signRow.push_back(pow(-1, i+j));
            }

            // Add row to matrix
            signMatrix.push_back(signRow);    
        }

        std::cout << "Sign matrix constructed." << std::endl;
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

                    // Add row to temporary minor matrix if it does not equal to the row of the minor being calculated  
                    if(k != i){
                        
                        reducedMatrix.push_back(reducedRow);
                    }
                }
                
                minorRow.push_back(calculateDeterminant(reducedMatrix));
            }

            minorMatrix.push_back(minorRow); 
        }

        std::cout << "Minor matrix constructed." << std::endl;
        printMatrix(minorMatrix);

        // Construct cofactor matrix
        for(int i = 0; i < matrix[0].size(); i++){
            
            std::vector<double> cofactorRow;

            for(int j = 0; j < matrix[0].size(); j++){
                cofactorRow.push_back(signMatrix[i][j]*minorMatrix[i][j]);
            }

            cofactorMatrix.push_back(cofactorRow);
        }

        std::cout << "Cofactor matrix constructed." << std::endl;
        printMatrix(cofactorMatrix);

        // Transpose cofactor matrix
        for(int i = 0; i < matrix[0].size(); i++){

            std::vector<double> transposeRow;
            
            for(int j = 0; j < matrix[0].size(); j++){
                transposeRow.push_back(cofactorMatrix[j][i]);
            }

            cofactorMatrixTranspose.push_back(transposeRow);
        }

        std::cout << "Cofactor matrix transposed." << std::endl;
        printMatrix(cofactorMatrixTranspose);

        // Calculate determinant
        for(int i = 0; i < matrix[0].size(); i++){
            
            determinant += (signMatrix[0][i]*minorMatrix[0][i]*matrix[0][i]);
        }

        std::cout << "Determinant calculated." << std::endl;
        std::cout << determinant << std::endl;

        // Calculate inverse matrix
        if(determinant == 0){
            
            std::vector<double> inverseRow;

            inverseRow.push_back(0);
            inverseMatrix.push_back(inverseRow);

            std::cout << "Inverse does not exist for this matrix." << std::endl;
        }
        else{

            for(int i = 0; i < matrix[0].size(); i++){
                
                std::vector<double> inverseRow;
                
                for(int j = 0; j < matrix[0].size(); j++){
                    inverseRow.push_back(cofactorMatrixTranspose[i][j] / determinant);
                }

                inverseMatrix.push_back(inverseRow);
            }

            std::cout << "Inverse calculated." << std::endl;
        }        
        
    }

    return inverseMatrix;
}


double calculateDeterminant(std::vector<std::vector<double>> matrix) {

    std::vector<double> signRow;
    std::vector<double> minorRow;
    double determinant = 0;
    
    // If matrix dimension == 1, return the value within the matrix
    if(matrix[0].size() == 1){ 
        
        determinant = matrix[0][0];
    }
    // Else calculate determinant using standard approach
    else{ 

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

                // Add row to temporary minor matrix  
                reducedMatrix.push_back(reducedRow);
            }
            
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

    for(int i = 0; i < matrix[0].size(); i++){
        
        for(int j = 0; j < matrix[0].size(); j++){
            
            std::cout << matrix[i][j] << "\t";
        }

        std::cout << std::endl;
    }
}