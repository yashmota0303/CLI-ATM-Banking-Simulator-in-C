#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main()
{ 
    int saved_pin = 12345;
    float balance = 100000.0f;
    int entered_pin, attempt = 0, is_authenticate = 0;
    float daily_withdraw = 0, daily_limit = 25000, min_balance = 10000;

    printf("\n-----------\nWelcome to the ATM System\n-----------\n");

    while ( attempt < 3)
    {
        printf("\nPlease enter your pin ( 5 digits ) :");
        scanf("%d", &entered_pin);

        if ( entered_pin == saved_pin)
        {
            printf("LOG IN successful\n");
            is_authenticate = 1;
            break; // exit login loop
        }
        else 
        {
            attempt++;
            printf("Incorrect pin. Try again. You have %d attempts left\n", 3 - attempt);
        }
        
    }

    if ( is_authenticate == 0) // lock account if 3 wrong attempts
    {
        printf("ACCOUNT LOCKED. Too many failed attempts.\n");
        return 0;// exit program
    }

    // main loop starts
    int choice;
    float amt;

    while ( attempt < 3)
    {
        printf("\n-----------\nATM MENU LIST\n-----------\n");
        printf(" 1. check Balance\n 2. Withdraw Money\n 3. Deposit Money\n 4. Change Pin\n 5. Fast cash \n\n Enter your choice :");
        scanf("%d", &choice);

        switch ( choice )
        {
            case 1:
            { 
                printf(" Your current balance is %f\n", balance);
                break;
            }
            
            case 2:
            { 
                printf("Enter amount to withdraw :");
                scanf("%f", &amt);

                if ( amt <= 0 )
                {
                    printf("Invalid amount. Please a bigger value.\n");
                }

                else if ( amt < balance)
                {
                    balance -= amt;
                    printf("Successfully withdrew %f\n ", amt);
                    printf("Updated balance is %f\n", balance);
                }

                else if ( balance - amt < min_balance )
                {
                    printf("Transaction denied. You must maintain minimum balance of 10000.");
                }

                else if (daily_withdraw + amt > daily_limit)
                {
                    printf("Limit exceeded. Daily limit is %f", daily_limit );
                    printf("\nMaximum that can be withdrawn is %f", daily_limit - daily_withdraw);
                }

                break;
            }


            case 3:
            { 
                printf("Enter amount to deposit :");
                scanf("%f", &amt);

                if ( amt <= 0)
                {
                    printf("Invalid amount. Try a bigger value.\n");
                }

                else 
                {
                    balance += amt;
                    printf("Sucessfully deposited %f", amt);
                    printf("Updated balance is %f", balance);
                }
                break;
            }

            case 4:
            { 
                int old_pin, new_pin;
                printf("Enter current pin :");
                scanf("%d", &old_pin);

                if ( old_pin == saved_pin)
                {
                    printf("Enter new pin :");
                    scanf("%d", &new_pin);

                    saved_pin = new_pin;
                    printf("Pin changed successfully.\n");
                }

                else 
                {
                    printf("INcorrect current pin, can not change the pin.");
                }
                break;
            }
            
            default :
                printf("Invalid choice. take better decisions.\n");

        }
    } 
}
