# MatrixInverse
Calculates the inverse of a given matrix of any size.

This program is designed using vector notation.

It was developed with simplicity and readability in mind.

The algorithm contains two main components: 
1. Inverse function.
2. Determinant function. 

The inverse function carries out the following calculation: 

Inverse = (1/Determinant) * CofactorTranspose

It calculates the Determinant and CofactorTranspose using the Sign Matrix and the Matrix of Minors. 

The determinant function is recursive, enabling this program to calculate the inverse of any sized matrix.

The program outputs all steps of the process on the terminal displaying:
1. Matrix for which inverse must be obtained.
2. Sign matrix.
3. Minor matrix.
4. Cofactor matrix.
5. Cofactor matrix transposed.
6. Determinant.
7. Inverse.

If an inverse does not exist for the given matrix, a message indicating this will be displayed on the terminal when run.


