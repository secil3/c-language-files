#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

void generateMatrix(int matrix[]);
void displayMatrix(int *matrix);
void displayMatrixWithXs(int *matrix, int *matrix_hidden);
void gameplay(int *matrix);



int main()
{
    int matrix[16];
    
    generateMatrix(matrix);
    

    gameplay(matrix);

    return 0;
}

void generateMatrix(int matrix[])
{
    
    int random_numbers_array[8] = {0,0,0,0,0,0,0,0};
    int n_numbers_choosen = 0;

    // choose 8 numbers randomly to put in the matrix
    while (n_numbers_choosen < 9)
    {
    
        // choose new random value
        int r = rand() % 9;

        // check if it is choosen before
        if (random_numbers_array[r] > 0)  //if yes
        {
            // choose another random number
            continue;
        }
        else  // if no
        {
            // mark the choosen number as 2
            random_numbers_array[r] += 2;
            n_numbers_choosen++;

        }
    }

    // place the randomly chosen values into the array randomly
    int i;
    for(i = 0; i < 16; i++)
    {
        // choose new random value
        int r = rand() % 9;

        // check if random number is in the list or is it placed before (2 times)
        if (random_numbers_array[r] > 0)
        {
            matrix[i] = r;
            random_numbers_array[r]--;
        }
        else
        {
            // repeat the same steps with choosing a new random number
            i--;
        }
    }
}

void displayMatrix(int *matrix)
{
    printf(" ----------NUMBERS MATCHING GAME----------\n");
    printf(" \t0\t1\t2\t3\n");
    int i;
    for (i = 0; i < 4; i++)
    {
        printf("%d\t", i);

        for (int j = 0; j < 4; j++)
        {
            printf("%d\t", matrix[i * 4 + j]);
        }

        printf("\n");
    }
}

void displayMatrixWithXs(int *matrix, int *matrix_hidden)
{
    printf(" \t0\t1\t2\t3\n");
    int i;
    for (i = 0; i < 4; i++)
    {
        printf("%d\t", i);

        for (int j = 0; j < 4; j++)
        {
            if (matrix_hidden[i * 4 + j] == 0)
            {
                printf("X\t");
            }
            else
            {
                printf("%d\t", matrix[i * 4 + j]);
            }
        }

        printf("\n");
    }
}

void gameplay(int *matrix)
{
    // game part
    printf(" ----------NUMBERS MATCHING GAME----------\n");

    int matrix_hidden[16] = {0};

    int n_found_numbers = 0;
    int found_numbers_array[8] = {0};

    int number_of_tries = 0;
    
    while (n_found_numbers < 8)
    {
        displayMatrixWithXs(matrix, matrix_hidden);

        int x1, y1;
        printf("Enter x and y coordinates of your first guess\n");
        scanf("%d %d", &x1, &y1);

        int n1 = x1 * 4 + y1;
        if (matrix_hidden[n1] == 1)
        {
            printf("Invalid x and y, coordinates of %d and %d is already visible\n", x1, y1);
            continue;
        }
        
        matrix_hidden[n1]++;
        displayMatrixWithXs(matrix, matrix_hidden);
        
        int x2, y2;
        printf("Enter x and y coordinates of your second guess\n");
        scanf("%d %d", &x2, &y2);

        int n2 = x2 * 4 + y2;
        if (matrix_hidden[n2] == 1)
        {
            printf("Invalid x and y, coordinates of %d and %d is already visible\n", x2, y2);
            matrix_hidden[n1]--;
            continue;
        }

        matrix_hidden[n2]++;
        displayMatrixWithXs(matrix, matrix_hidden);

        if (matrix[n1] == matrix[n2])
        {
            found_numbers_array[n_found_numbers] = matrix[n1];
            n_found_numbers++;
            printf(" ----------CORRECT GUESS----------\n");
            
        }
        else
        {
            matrix_hidden[n1]--;
            matrix_hidden[n2]--;
            
            printf(" ----------WRONG GUESS, PLEASE TRY AGAIN----------\n");
        }
        
        number_of_tries++;
        printf("total number of tries:%d\n",number_of_tries);
        printf("Found numbers:-");
        int k;
        for (k = 0; k < n_found_numbers; k++)
        {
            printf("%d-", found_numbers_array[k]);
        }
        printf("\n");
        
        // if two numbers are matching then remove the numbers in the table
        if(matrix[n1]==matrix[n2])
		{
			
         printf(" \t0\t1\t2\t3\n");
            int a,b;
			for(a = 0; a < 4; a++)
			{
				printf("%d\t",a);
				for(b = 0; b < 4;b++)
				{
					if(a == x1 && b == y1)
					{
						printf(" \t");
					}
					if(a == x2 && b == y2)
					{
						printf(" \t");
					}
					else
					{
						printf("X\t");
					}
				}
				printf("\n");
			}   	
		}
    }

    printf("congratulations, you found all numbers! total number of tries:%d\n", number_of_tries);
}
