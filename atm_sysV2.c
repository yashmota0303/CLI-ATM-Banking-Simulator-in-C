#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main()
{ 
    int saved_pin = 12345, admin_pin = 99999;
    float balance = 1000000.0f;   // setup
    int dummy_acc = 2002;//dummy acc for transfering money
    float dummy_balance = 20000;
    int last_type = 0;    //last transaction tracker menu choices
    float last_amt = 0;
    int entered_pin, attempt = 0, is_authenticate = 0;  // authenticaton varables
    float daily_withdraw = 0, daily_limit = 25000, min_balance = 10000;   //limits
    int is_lock = 0; // account lock flag
    float fd_balance = 0.0f;   // fd variables
    int fd_tenure = 0;
    int otp, user_otp;     // otp security

    float max_loan_limit = 7500;   // loan 
    float loan_taken = 0;

    srand(time(0));

    otp = (rand() % 9000) + 1000;

    printf("\n-----------\nWelcome to the ATM System\n-----------\n");

    //login loop
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

        else if ( entered_pin == admin_pin )
        {
            printf("\n------------\nADMIN MODE \n------------\n");
            printf("User account balance :%f\nDummy account :%f\nDaily limit :%f\nMinimum balance required :%f\nSystem Vault :%f\n", balance, dummy_acc, daily_limit, min_balance, dummy_balance + balance);
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
        printf(" 1. check Balance\n 2. Withdraw Money\n 3. Deposit Money\n 4. Change Pin\n 5. Fast cash \n 6. Savings \n7. Last transcation Statement\n8. FD Creator\n9. Utility bill payment\10. Currency converter\n11. Account health and Risk analysis\n13. Account Tier status\nEnter your choice :");
        scanf("%d", &choice);

        switch ( choice )
        {
            case 1:
            { 
                printf(" Your current balance is %f\n", balance);

                if ( balance <= min_balance + 5000.0)
                {
                    printf("WARNING. Your balance is near minimum balance limit.");
                }
                break;
            }
            
            case 2: // Withdraw Money with Anti-Fraud & Cash Dispenser
            { 
                int withdraw_amt;

                printf("\n--- CASH WITHDRAWAL ---\n");
                printf("Enter amount to withdraw: Rs. ");
                scanf("%d", &withdraw_amt);

                // Standard Validations
            if (withdraw_amt <= 0) 
            {
                printf("Invalid amount.\n");
            }
                
            else if (withdraw_amt % 100 != 0) 
            {
                printf("Amount must be in multiples of 100.\n");
            }
                
            else if (withdraw_amt > balance) 
            {
                printf("Insufficient balance.\n");
            }
            
            else if (balance - withdraw_amt < min_balance) 
            {
                printf("Transaction denied. Must maintain minimum balance of Rs. %.2f\n", min_balance);
            }
                
            else if (daily_withdraw + withdraw_amt > daily_limit) 
            {
                printf("Daily limit exceeded.\n");
            }
            else 
            {
        // --- ANTI-FRAUD VERIFICATION CHECK ---
        if (withdraw_amt >= (balance * 0.80f)) 
        {
            printf("\nANTI-FRAUD ALERT High-value transaction requested.\n");
            
            int security_code = (rand() % 9000) + 1000;
            int user_code, reenter_pin;

            printf("Security Verification Code: %d\n", security_code);
            printf("Enter Code: ");
            scanf("%d", &user_code);

            printf("Re-enter PIN to authorize: ");
            scanf("%d", &reenter_pin);

            if (user_code != security_code || reenter_pin != saved_pin) 
            {
                printf("SECURITY BLOCK Verification failed. Transaction canceled.\n");
                break;
            }
            printf("VERIFIED Authorization granted.\n");
        }

        // --- DISPENSE CASH ---
        int temp = withdraw_amt;
        int notes500 = temp / 500; temp %= 500;
        int notes200 = temp / 200; temp %= 200;
        int notes100 = temp / 100;

        balance -= withdraw_amt;
        daily_withdraw += withdraw_amt;
        last_amt = (float)withdraw_amt;
        last_type = 2;

        printf("\nDISPENSING CASH Total: Rs. %d\n", withdraw_amt);
        if (notes500 > 0) printf("  Rs. 500 Notes : %d\n", notes500);
        if (notes200 > 0) printf("  Rs. 200 Notes : %d\n", notes200);
        if (notes100 > 0) printf("  Rs. 100 Notes : %d\n", notes100);
        printf("Updated Balance: Rs. %.2f\n", balance);
    }
    break;
}


            case 3:   //deposit
            { 
                float loan_paid;
                int deposit_choice;
                printf("\n1. Deposit money\n2. Repay Active loan\n\n");
                printf("Enter your choice :");
                scanf("%d", &deposit_choice);

                if ( deposit_choice == 1)
                {  
                    if ( amt <= 0)
                    {
                        printf("Invalid amount. Try a bigger value.\n");
                    }

                    else 
                    {
                        balance += amt;
                        last_amt = amt;
                        last_type = 1;
                        printf("Sucessfully deposited %f", amt);
                        printf("Updated balance is %f", balance);
                    }
                    break;
                }

                if ( deposit_choice == 2)
                {
                    printf("----- REPAY LOAN PORTAL ------\n\n");
                    
                    if ( loan_taken <= 0)
                    {
                        printf("You have no active loans.");
                    }

                    else 
                    {
                        printf("Outstanding loan amount :%0.2f\n Current acailable balance :%0.2f", loan_taken, balance);

                        if ( balance < loan_taken )
                        {
                            printf("Insufficient balance to clear out loans.");
                        }

                        else 
                        {
                            printf("Enter the amount of loan you want to repay now :");
                            scanf("%0.2f", &loan_paid);
                            balance -= loan_paid;
                            printf("loan of %0.2f paid successfully.", loan_paid);

                            if ( loan_paid == loan_taken )
                            printf (" You are free of all your debts.");

                            else if (loan_paid < loan_taken )
                            printf("You have remaining loan of %0.2f to pay back.", loan_taken - loan_paid);

                            printf("Updated bank balance is %0.2f", balance);
                        }
                    }
                    break;

                }

            case 4:     // forgot pin
            { 
                int old_pin, new_pin;
                printf("Enter current pin :");
                scanf("%d", &old_pin);

                printf("\n OTP SENT : %d", otp);
                printf("Enter the OTP to proceed to change pin : ");
                scanf("%d", &user_otp);

                if ( old_pin == saved_pin && otp == user_otp)
                {
                    printf("Enter new pin :");
                    scanf("%d", &new_pin);

                    saved_pin = new_pin;
                    printf("Pin changed successfully.\n");
                }

                else if ( user_otp != otp)
                {
                    printf("Invalid OTP. Transcation stopped.");
                    break;
                }

                else if ( old_pin != saved_pin )
                {
                    printf("Incorrect current pin, can not change the pin.");
                }
                break;
            }

            case 5:
            { 
                int fast_choice;
                float fast_amt = 0;
                float request_loan;

                printf("\n-------\nFAST CASH\n---------\n");
                printf("\n1. 500\n 2. 1000\n 3. 2000\n 4. 5000\nSelect an option :\n\n");
                scanf("%d", &fast_choice);

                if ( fast_choice == 1 )
                    fast_amt = 500;
                else if ( fast_choice == 2) 
                    fast_amt = 1000;
                else if ( fast_choice == 3)
                    fast_amt = 2000;
                else if ( fast_choice == 4)
                    fast_amt = 5000;
                else
                {
                    printf("Invalid fast cash option.");
                    break;
                }

                if ( balance - fast_amt < min_balance )
                {
                    printf("Transcation Failed. Maintain minimum balance in account.\n.");
                    printf("---- Emergency Micro Loan in cash ---\n");
                    printf("Current active loan Debt :%f", loan_taken);

                    if ( loan_taken > 0)
                    {
                         printf("You have an active loan of %0.2f", loan_taken);
                         break;
                    }

                    printf("Enter requested loan amount  : ");
                    scanf("%f", &request_loan);

                    if ( request_loan <= 0 || request_loan > max_loan_limit )
                    {
                        printf("Max limit reached. No loan.");
                        break;
                    }

                    else 
                    {
                        loan_taken = request_loan;
                        balance += request_loan;//not done
                        
                    }
                }
                else if ( daily_withdraw + fast_amt > daily_limit)
                {
                    printf("Daily limit exceeded.\n");
                }
                else 
                {
                    balance -= fast_amt;
                    daily_withdraw += fast_amt;
                    last_amt = fast_amt;
                    last_type = 2;
                    printf("Withdrew = %f\n Updating balance = %f\n", fast_amt, balance);
                }

                break;
            }

            case 6 ://interest calculator
            {
                float rate = 4.5f;
                printf("\n------ SAVINGS ACCOUNT PREVIEW ------\n");
                printf("Current balance :%f\n ", balance );
                printf("1year interest :%f --> total :%f\n\n ", ( balance*rate*1)/ 100, balance + (balance*rate*1) / 100);
                printf(" 3year interest :%f --> Total :%f\n\n", (balance*rate*3) / 100, balance + (balance*rate*3) / 100);
                printf("5Year interest :%f --> Total : %f", (balance*rate*5) / 100, balance + (balance*rate*5) / 100);
            }

            break;

            case 7: // last transaction trackin
            {
                printf("LAST TRANSACTION STATEMENT--\n\n");

                if ( last_type == 0)
                {
                    printf("No transcations are performed.");
                }

                else 
                {
                    if (last_type == 1)
                    printf("Type 1 : Deposit\n");
                    else if (last_type == 2)
                    printf("Type 2 : Withdraw\n");
                    else if ( last_type == 3 )
                    printf("Type 3 : Fund transfer\n");
                    else 
                    printf("No recent transcations.");

                    printf("Amount : %f\nBalance : %f", last_amt, balance);
                    break;
                }
                break;
            }

            case 8: // fd creator
            {
                float fd_amt;
                int yr;

                printf("\n----- FIXED DEPOSIT CREATOR ------\n");
                printf("Active FD balance = %f\nAcailable balance = %f", fd_balance, balance);

                printf("Enter amount to lock in FD :");
                scanf("%f", &fd_amt);

                if ( fd_amt <= 0 || fd_amt > balance - min_balance )
                {
                    printf("Invalid amount. minimum balance problems.");
                    break;
                }

                printf("Enter the tenure of FD :");
                scanf("%d", &yr);

                if ( yr < 1 || yr > 11)
                {
                    printf("Invalid tenure. Enter the tenure within limit.");
                    break;
                }

                // otp authenticates
                int otp, user_otp;
                int bill_choice;
                otp = (rand() % 9000) + 1000;
                printf("Security verification. Your OTP is : %d", otp);
                printf("Enter the OTP sent :");
                scanf("%d", &user_otp);

                if ( user_otp != otp)
                {
                    printf("Incorrect OTP. Try again");
                    break;
                }

                // process FD
                float interest_earned = ( fd_amt * 6.5 * yr) / 100.0;
                float maturity_amt = fd_amt + interest_earned;

                balance -= fd_amt;
                fd_balance += fd_amt;

                printf(" \nFD CREATED successfulyl\n");
                printf("Locked principal  :%0.2f\nTenure  :%dyears\nInterest rate  :6.5%%\nMaturity Returns  :%0.2f\nBalance  :%0.2f\n", fd_amt, yr, maturity_amt, balance);
                break;

            }

            case 9 :  // utility bill payments
            {
                float bill_amt;
                int bill_choice;
                float elec, wifi, mobile, water, gas;

                printf("\n--- UTILITY BILL PAYMENTS ---\n");
                printf("1. Electricity Bill\n");
                printf("2. Internet / Broadband\n");
                printf("3. Mobile Postpaid\n");
                printf("4. Gas bill");
                printf("Select bill type : ");
                scanf("%d", &bill_choice);

                if ( bill_choice < 1 || bill_choice > 4)
                {
                    printf("Invalid choice.");
                    break;
                }

                printf("Enter the bill amount to pay :");
                scanf("%f", &bill_amt);

                if ( bill_amt < 0 )
                {
                     printf("Invalid amount.");
                }

                else if ( balance - bill_amt < min_balance)
                {
                    printf("Payment Failed. manitain minimum balance.");
                }

                else 
                {
                    balance -= bill_amt;
                    last_amt = bill_amt;
                    last_type =4; // bill payment

                    printf("BILL PAYMENT successfully.");
                    printf("\nDeducted amount  :%0.2f\n Updated Bank Balance  :%0.2f\n", bill_amt, balance);
                }
                break;
            }

            case 10 :   // Multi-Currency Converter 
            {
                
                int curr_choice;
                float usd_rate = 95.50f, eur_rate = 111.20f;

                printf("\n--- INTERNATIONAL CURRENCY VIEW ---\n");
                printf("1. View Balance in USD ($)\n2. View Balance in EUR (€)\nChoice: ");
                scanf("%d", &curr_choice);

                if (curr_choice == 1) 
                {
                    printf("Balance in USD: $%.2f (Rate: 1 USD = Rs. %.2f)\n", balance / usd_rate, usd_rate);
                } 
                
                else if (curr_choice == 2) 
                {
                    printf("Balance in EUR: €%.2f (Rate: 1 EUR = Rs. %.2f)\n", balance / eur_rate, eur_rate);
                } 
                
                else 
                {
                    printf("Invalid choice.\n");
                }
                    break;
            }

            case 11: // account health , risk
            {
                int score = 100;
                
                printf("\n --------- ACCOUNT HEALTH AND RISK ANALYSIS --------- \n");

                // low balance 
                if ( balance < min_balance )
                score -= 40;

                else if ( balance < min_balance + 5000 )
                score -= 20;

                // high withdrawal 
                if ( daily_withdraw >= daily_limit * 0.8)
                score -= 15;

                // active loans
                if ( loan_taken > 0)
                score -= 30;

                printf("--- OVERALL ACCOUNT SCORE ---\n");
                
                if ( score >= 80)
                printf("Status: EXCELLENT");

                else if ( score >= 60 )
                printf("Status: Moderate");

                else 
                printf("Status: LOW score. HIGH RISK.");
            }
            
            case 13:  // Account Tier Status
            { 
                printf("\n--- ACCOUNT MEMBERSHIP TIER ---\n");

                if (balance >= 800000.0f) 
                {
                    daily_limit = 100000.0f; // Higher limit for VIP
                    printf("Current Status: PLATINUM VIP\n");
                    printf("Perk: Daily Limit upgraded to Rs. 100,000.00\n");
                } 
                
                else if (balance >= 450000.0f) 
                {
                    daily_limit = 50000.0f;
                    printf("Current Status: GOLD MEMBER\n");
                    printf("Perk: Daily Limit upgraded to Rs. 50,000.00\n");
                } 
                
                else 
                {
                    daily_limit = 25000.0f;
                    printf("Current Status: SILVER MEMBER\n");
                    printf("Maintain > Rs. 1,00,000 for Gold Upgrade.\n");
                }
                break;
            }
             
            
            default :
            { 
                printf("Invalid choice. take better decisions.\n");
                break;
            }
        }
    } 
}
