#include<stdio.h>

int main()
{
    float A[20][20]= {0},L[20][20]= {0}, U[20][20]= {0};
    float B[20]= {0}, X[20]= {0}, Y[20]= {0};
    int i,j,k,n;
    
    printf("Enter the order of square matrix: ");
    scanf("%d",&n);
    
    printf("\nEnter matrix elements:\n");
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            printf("Enter A[%d][%d] element: ", i,j);
            scanf("%f",&A[i][j]);
        }
    }
    
    printf("\nEnter the constant terms: \n");
    for(i=0; i<n; i++)
    {
        printf("B[%d]: ",i);
        scanf("%f",&B[i]);
    }
    
    // Crout's method: Decomposing A into L and U
    for(j=0; j<n; j++)
    {
        // Compute L matrix
        for(i=j; i<n; i++)
        {
            L[i][j] = A[i][j];
            for(k=0; k<j; k++)
                L[i][j] -= L[i][k] * U[k][j];
        }

        // Compute U matrix
        for(i=j; i<n; i++)
        {
            if(i == j)
                U[j][i] = 1; // Diagonal elements of U are 1
            else
            {
                U[j][i] = A[j][i];
                for(k=0; k<j; k++)
                    U[j][i] -= L[j][k] * U[k][i];
                U[j][i] /= L[j][j];
            }
        }
    }
    
    // Print L matrix
    printf("[L]: \n");
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
            printf("%9.3f",L[i][j]);
        printf("\n");
    }
    
    // Print U matrix
    printf("\n\n[U]: \n");
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
            printf("%9.3f",U[i][j]);
        printf("\n");
    }
    
    // Forward substitution to solve LY = B
    for(i=0; i<n; i++)
    {
        Y[i] = B[i];
        for(j=0; j<i; j++)
        {
            Y[i] -= L[i][j] * Y[j];
        }
        Y[i] /= L[i][i];
    }
    
    // Print Y vector
    printf("\n\n[Y]: \n");
    for(i=0; i<n; i++)
    {
        printf("%9.3f",Y[i]);
    }
    
    // Backward substitution to solve UX = Y
    for(i=n-1; i>=0; i--)
    {
        X[i] = Y[i];
        for(j=i+1; j<n; j++)
        {
            X[i] -= U[i][j] * X[j];
        }
        // No need to divide by U[i][i] since U[i][i] is 1 in Crout's method
    }
    
    // Print X vector
    printf("\n\n[X]: \n");
    for(i=0; i<n; i++)
    {
        printf("%9.3f",X[i]);
    }
    
    return 0;
}
