/* 

CSPE32 Combinatorics and Graph Theory - Mini Project

Topic: Display nodes at a maximum distance of 'm' from a given source node.

Theory Implemented: Adjacency Matrix Representation of Graphs, Powers of Adjacency Matrix.

Team Members:
            Bhavika Mahajan     (106121028)
              Rahul Sriram      (106121100)
               Rishav Das       (106121102)
            Swastik Kashyap     (106121136)
            
We thank our CSPE32 professor, Dr. Sitara K for giving us this opportunity to work on, and present this project. It has helped us to 
explore more on the theoretical concepts learnt during theory classes, enabling us to convert the theory into practical, useful projects.

*/



#include <stdio.h>
#include <stdlib.h>
#include <conio.h>


// Initializing a global array to remember visited nodes. This is done to prevent duplicate elements getting printed.
int visited[100];


// This function is used to get matricx inputs from the user. For test run, I have hard-coded a matrix in the main() function. 
// In the test-run, this won't be used.
void getMatrixElements(int matrix[][10], int r, int c)
{
    printf("\nEnter elements: \n");

    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            scanf("%d", &matrix[i][j]);
        }
    }
}

// Typical function used to multiply two matrices, and store it back into the first matrix.
void multiplyMatrices(int first[][10], int second[][10], int r1, int c1, int r2, int c2)
{

    int result[r1][r1];
    for (int i = 0; i < r1; ++i)
    {
        for (int j = 0; j < c2; ++j)
        {
            result[i][j] = 0;
        }
    }

    for (int i = 0; i < r1; ++i)
    {
        for (int j = 0; j < c2; ++j)
        {
            for (int k = 0; k < c1; ++k)
            {
                result[i][j] += first[i][k] * second[k][j];
            }
        }
    }

    for (int i = 0; i < r1; ++i)                        // Copying result back to First matrix
    {
        for (int j = 0; j < c2; ++j)
        {
            first[i][j] = result[i][j];
        }
    }
}


// ====================================== MAIN FUNCTION ======================================== //

int main()
{
    // Test run sample matrix.
                    //    0  1  2  3  4  5  6  7  8  9
    int first[10][10] = {{0, 1, 0, 1, 0, 1, 0, 0, 1, 0},  /* 0 */
                         {1, 0, 1, 0, 1, 1, 0, 0, 0, 0},  /* 1 */
                         {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},  /* 2 */
                         {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},  /* 3 */
                         {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},  /* 4 */
                         {1, 1, 0, 0, 0, 0, 1, 1, 1, 0},  /* 5 */
                         {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},  /* 6 */
                         {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},  /* 7 */
                         {1, 0, 0, 0, 0, 1, 0, 0, 0, 1},  /* 8 */
                         {0, 0, 0, 0, 0, 0, 0, 0, 1, 0}}; /* 9 */

    // Initializing various variables and arrays.
    int second[10][10], result[10][10];
    int r1, c1, r2, c2, node, m;
    r1 = 10;                                      // Initialized as 10, for the test run case.


    //printf("Enter number of elements: ");       // Otherwise, we take input from user.
    //scanf("%d", &r1);

    r2 = r1;
    c1 = r1;                                      // Initializing other variables. Here rows and columns all are same.
    c2 = r1;
    m = 0;
    node = 0;

    for (int j = 0; j < 100; ++j)                 // Initializing all elements of visited array to 0
    {
        visited[j] = 0;
    }

    // getMatrixElements(first, r1, c1);          // Not to be used in test run case.


    for (int i = 0; i < r1; ++i)                  // Duplicates the first array and calls it second. This is done because first and second are the same arrays.
    {
        for (int j = 0; j < c2; ++j)
        {
            second[i][j] = first[i][j];
        }
    }

    printf("\nEnter starting node: ");            // Takes in the Starting node.
    scanf("%d", &node);
    printf("\nEnter value of m: ");               // Takes in the maximum distance 'm'.
    scanf("%d", &m);

    printf("\n\nElements at a distance 0: \n");   // Prints elements at distance 0. i.e. the starting node itself.
    printf("%d ", node);
    visited[node]++;

    for (int i = 0; i < m; i++)                   // Prints elements at distance i, which ranges from 1 to m.
    {
        printf("\n\nElements at a distance %d: \n", i + 1);
        for (int j = 0; j < c1; j++)
        {
            if (first[node][j] >= 1 && visited[j] == 0)
            {
                printf("%d ", j);
                visited[j]++;
            }
        }

        multiplyMatrices(first, second, r1, c1, r2, c2);  // Finds the higher power of matrix. Read description at the end of the code.
    }

    getch();
    return 0;
}


/* DESCRIPTION
================

Given an adjacancy matrix X, and a given node "n", we can find nodes at a maximum distance of "m", by calculating various powers of X.
Elements at distance 0 is the element itself, i.e "n".
Elements at distance 1 are the elements in matrix X, row number "n". Those elements that are adjacent to "n", i.e X[n][i] = 1 are the
elements that are neighbours to "n". Thus distance is 1.

Elements at distance 2 are the elements in matrix X^2, row number "n". Those elements that have X^2[n][i] >= 1 are the elements that can
be reached from "n" by an edge sequence of length 2. This is the same as elements at a distance 2.

Similarly for elements at distance "m", we just need to find X^m and find those elements that have X^m[n][i] >= 1. which gives the elements
that can be reached from "n" by an edge sequence of length "m". This is the same as elements at a distance m.

================ */