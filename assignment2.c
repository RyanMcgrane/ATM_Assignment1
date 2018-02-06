/* Program Description: Assignment #2 Encrypting and Decrypting codes.
    Date: 28/02/17
    Author: Ryan Mcgrane.
*/

#include <stdio.h>
#include <stdlib.h>
#define SIZE 4

//initialising prototypes and passing them by reference.

void Enter_Pin (int*, int*, int*, int*, int*);
void Encrypt_Pin (int*, int*, int*, int*, int*, int*, int*);
void Compare (int*, int*, int*, int*, int*);
void Decrypt_Pin (int*, int*, int*, int*);
void Pin_counter (int*, int*);
void END ();


// Implement function Enter_pin()
void Enter_Pin ( int* Pin_code, int* first_pin, int* Encrypt_twice, int* decrypt_twice, int *Encryption_first)
{
    // Initialising a counter to 0 for the loop.
    int counter = 0;
    int i;
    
    
    // Just a condition that allows me to error check for user input.
    while( counter == 0 )
    {
        *Encrypt_twice = 0;
        *decrypt_twice = 0;
        
        //This is to make sure the user encrypts their code first before decrypting
        *Encryption_first = 1;
        
        int counter1 = 0;
        int digit_counter = 0; // Counts the digits entered by the user.
        int i = 0;
        
        printf("Please enter in your pin\n");
        
        //While the counter1 is set at 0 do this function.
        while ( counter1 == 0 )
        {
            //scans in each digit entered in by the user
            scanf("%d", Pin_code+i );
            digit_counter++;
         
            //If statement to make sure the user enters in one digit at a time.
            if( *(Pin_code + i) > 9 )
            {
                printf("\n Sorry you must enter in a single digit at a time\n");
                counter1++;
            }
            
            
            else
            {
                // Makes sure the pin is 4 digits long.
                if ( digit_counter == SIZE )
                {
                    
                    //Allows us to jump out of the function
                    counter1++;
                    counter++;
                }
            }
            
            // Allows the user to enter in the full code. because its not in a for loop.
            i++;
            
        }
    }
    
    printf("-------Your pin is:-------\n");
    
    //For loop which displays each digit entered in by the user
    for ( i = 0; i < SIZE; i++ )
    {
        printf("%d", *(Pin_code + i) );
    }
    
    // Sets first pin to 1. This makes sure the user enters in a code before encrypting.
    *first_pin = 1;
        
}

//Implement function Encrypt_pin
void Encrypt_Pin (int *Pin_code, int *access_code ,int *Correctly_entered , int  *Incorrectly_entered, int *first_pin, int *Encrypt_twice, int *Encryption_first)
{
    int i;
    
    // if statement to make sure the user entered in a pin first
    if(*first_pin == 1)
    {
        //if statement to make sure the user doesnt encrypt twice in a row
        if(*Encrypt_twice == 0)
        {
            *Encryption_first = 0;
            int tmp;
        
            //Encryption algorithm for option 2. Swaping 1st number with the 3rd.
            tmp = *Pin_code;
            *Pin_code = *(Pin_code + 2);
            *(Pin_code + 2) = tmp;
                
            //Swaping 2nd number with the 4th.
            tmp = *(Pin_code + 1);
            *(Pin_code + 1) = *(Pin_code + 3);
            *(Pin_code + 3) = tmp;
                
            //for loop to add 1 to each number.
            for( i = 0; i < SIZE; i++ )
            {
                (*(Pin_code + i))++;
                
                //If statement to turn any number thats a 10 to a 0
                if( *(Pin_code + i) == 10)
                {
                    *(Pin_code + i) = 0;
                }
                
            }
            
            printf("\n ------ Your Encryped code is ------\n");
            
            //For loop to print the Encrypted pin.
            for ( i = 0; i < SIZE; i++ )
            {
                printf("%d", *(Pin_code + i) );
            }
            
            //Sets the counter to 1 so you cant encrypt twice.
            *Encrypt_twice = 1;
        }
        
        else 
        {
            printf("\n Sorry you cannot enrypt your code twice\n");
        }
        
    
    }
    
    else
    {
        printf("\n *** You must enter in a pin before encrypting *** \n" );
    }
    
    //call function compare
    Compare(Pin_code, access_code, Correctly_entered, Incorrectly_entered, Encrypt_twice);
}

//implement function compare.
void Compare( int *Pin_code, int *access_code, int* Correctly_entered, int *Incorrectly_entered, int *Encrypt_twice)
{
    // Boolean true or false statement.
    bool mark = true;
    int i;
    
    //For loop which access eacg digit of both codes and compares them.
    for ( i = 0; i < SIZE; i++ )
    {
        // If each digit is not the same in each code the boolean flag gets marked as false and it jumps out of the statment.
        if( *(Pin_code + i) != *(access_code + i) )
        {
            mark = false;
            break;
        }
    }
    
    // if the boolean statement is true it does whats inside this.
    if (mark)
    {
        printf("\nCorrect code!\n");
        (*Correctly_entered)++;
    }
    
    // IF not true it does this.
    else
    {
        printf("\n Error code!\n");
        (*Incorrectly_entered)++;
    }
    
    // Makes sure you can't encrypt twice in a row.
    *Encrypt_twice = 1;
}

//Implement the decryption algorithm.
void Decrypt_Pin ( int *Pin_code, int *first_pin, int *decrypt_twice, int *Encryption_first)
{
    int tmp;
    int i;
    
    // Makes sure the user enters in a pin before decrypting
    if(*first_pin == 1 )
    {
        // Makes sure the user encrypts first before decrypting
        if(*Encryption_first == 0)
        {
            //make sure you cannot decrypt twice
            if(*decrypt_twice == 0 )
            {
                //For loop to subtract one from each number.
                for( i = 0; i < SIZE; i++ )
                {
                    (*(Pin_code + i))--;
                    
                    //If statement to make any number thats a minus 1 turn into a 9.
                    if( *(Pin_code + i) == (-1))
                    {
                        *(Pin_code + i) = 9;
                    }
                    
                }
                
                //Swaping the 1st number with the third number.
                tmp = *Pin_code;
                *Pin_code = *(Pin_code + 2);
                *(Pin_code + 2) = tmp;
                
                //Swaping 2nd number with the 4th.
                tmp = *(Pin_code + 1);
                *(Pin_code + 1) = *(Pin_code + 3);
                *(Pin_code + 3) = tmp;
                
                printf("\n------ Your Decrypted code is ------\n");
                
                //For loop to print out each digit of the code.
                for ( i = 0; i < SIZE; i++ )
                {
                    printf("%d", *(Pin_code + i) );
                }
                
                // incrementing the counter to make sure you cannot decrypt twice in a row.
                *decrypt_twice = 1;
            }
            
            else
            {
                printf("\nYou cannot decrypt your code twice\n");
            }
        }
        
        else
        {
            printf("\n *** You must encrypt before you decrypt your code *** \n" );
        }
    }
    
    else 
    {
        printf("\n *** You must enter in a code first before decrypting *** \n ");
    }
            
}

// Implemmet function to count how many times the user entered in the code inccorrectly and correctly
void Pin_counter( int *Correctly_entered , int *Incorrectly_entered )
{
    printf("\nThe pin has been entered in %d times successfully\n", *(Correctly_entered));    
    printf("\nThe pin has been entered in %d times Unsuccessfully\n", *(Incorrectly_entered));    
    
}
        
//Implement function for ending the program.
void END(void)
{
    printf("\n\t\t ------------Thank you for choosing us------------ ");
}
 
int main()
{
    // Initialising all the variables for the main and for passing through functions.
    int Pin_code[4];
    int access_code[] = {4, 5, 2, 3};
    int option;
    int decrypt_two = 0;
    int Encrypt_two = 0;
    int Correctly_Entered1 = 0;
    int Incorrectly_Entered1 = 0;
    int Encryption_first1 = 0;
    int pin_one = 0;
    int *Correctly_entered;
    int *Incorrectly_entered;
    int *Encrypt_twice;
    int *decrypt_twice;
    int *first_pin;
    int *Encryption_first;
    
   
    // making sure my pointer variables are assigned an area to point to.
    Encryption_first = &Encryption_first1;
    decrypt_twice = &decrypt_two;
    Encrypt_twice = &Encrypt_two;
    first_pin = &pin_one;
    Correctly_entered = &Correctly_Entered1;
    Incorrectly_entered = &Incorrectly_Entered1;
    

    do
    {
        //All the printfs Which display the menu thorughout the program.
        printf("\n********************************** Please select an option from one of the following: **********************************\n\n");
        printf("1: Please Enter code\n");
        printf("2: Encrypt code and verify if it is correct\n");
        printf("3: Decrypt the code\n");
        printf("4: Display the number of times the code was entered\n (i) Successfully\n (ii)Unsucessfully\n");
        printf("5: Exit the program\n");
        scanf("%d", &option);
        
        // Catches if the user enters something thats not on the menu
        if( option > 0 && option < 6 )
        {
            printf("---------- You have selected option %d ---------- \n", option);
        }
        
        else 
        {
            printf("\n **** You must select an option from the menu please ****\n");
        }
        
        //switch statement to drive the menu numbers and call functions.
        switch (option)
        {
            case 1:
            {
                //Call function Enter_pin
                Enter_Pin( Pin_code, first_pin, Encrypt_twice, decrypt_twice, Encryption_first);  //Can't use a (&) for pass by reference because your passing an array. this would pass the address of the first element of the array.
                break;
                
            }
            
            case 2:
            {
                //Call function Encrypt_Pin
                Encrypt_Pin( Pin_code, access_code, Correctly_entered, Incorrectly_entered, first_pin, Encrypt_twice, Encryption_first);
                break;
            }
            
            case 3:
            {
                //call function Decrypt_Pin
                Decrypt_Pin( Pin_code, first_pin, decrypt_twice, Encryption_first);
                break;
            }
            
            case 4:
            {
                //call function Pin_counter
                Pin_counter( Correctly_entered, Incorrectly_entered );
                break;
            }
        
        } 
    // The counter statement to the do while loop.
    } while (option != 5);
    
    printf("\t\t\n - - - - - - - - - - - - - - - - - - - - - Thank you for choosing our services - - - - - - - - - - - - - - - - - - - - -\n");
    
    getchar();
    getchar();
    return 0;
}