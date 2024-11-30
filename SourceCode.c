#include <stdio.h>
#include <string.h>
// Structure to store customer data
struct Customer {
    char name[50];
    char phonenumber[15];
    float usage;        
    float totalBill;// Total bill in dollars
};

//global variables
struct Customer customers[100];//array to store customer data
int customercount=0;//variable to keep track of the number of customers
const char *filename="customer_records.txt";//file to store records

//user defined funtion used in this code
void loadrecords();
void saverecord();
void addrecord();
void viewrecords();
void modifyrecord(char phonenumber[]);
void viewpayment(char phonenumber[]);
void deleterecord(char phonenumber[]);
void displaymenu();

int main() {
    int choice;
    char phonenumber[15];
    //load existing records from the file
    loadrecords();
    // Main menu loop
    while (1) 
    {
        displaymenu();
        printf("Enter your choice:    ");
        scanf("%d", &choice);

        //useing Switch case  and taking user's input
        switch (choice) {
            case 1:
                addrecord();
                break;
            case 2:
                viewrecords();
                break;
            case 3:
                printf("\nEnter phone number to modify record: ");
                scanf("%s", phonenumber);
                modifyrecord(phonenumber);
                break;
            case 4:
                printf("\nEnter phone number to view payment: ");
                scanf("%s", phonenumber);
                viewpayment(phonenumber);
                break;
            case 5:
                printf("\nEnter phone number to delete record: ");
                scanf("%s", phonenumber);
                deleterecord(phonenumber);
                break;
            case 6:
                saverecord(); // Save records before exiting
                printf("Exiting the program. Goodbye!\n");
                return 0;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }

    return 0;
}

// Function to load records from the file
void loadrecords() 
{
    FILE *file = fopen(filename,"r");
    if (file == NULL)
    {
        printf("No existing data found. Starting fresh.\n");
        return;
    }
    
//Reading custumor data from file
    customercount= 0;
    while (fscanf(file, "%49[^,],%14[^,],%f,%f\n",
                  customers[customercount].name,
                  customers[customercount].phonenumber,
                  &customers[customercount].usage,
                  &customers[customercount].totalBill) != EOF) {
        customercount++;
    }
    fclose(file);
}

//Saving custumor records
void saverecord() 
{
    FILE *file = fopen(filename, "w");
    if (file == NULL) 
    {
        printf("Error saving records!\n");
        return;
    }

// Writing each data in file 

    for (int i=0;i<customercount;i++) 
    {
        fprintf(file, "%s,%s,%.2f,%.2f\n",
                customers[i].name,
                customers[i].phonenumber,
                customers[i].usage,
                customers[i].totalBill);
    }
fclose(file);
}

//Adding new custumor record
void addrecord() 
{
    if (customercount < 100)
{
     printf("\nEnter name: ");
     scanf(" %[^\n]s", customers[customercount].name);
     printf("Enter phone number: ");
     scanf("%s", customers[customercount].phonenumber);
     printf("Enter usage (in minutes): ");
     scanf("%f", &customers[customercount].usage);


    // Calculate total bill based on usage
    customers[customercount].totalBill = customers[customercount].usage * 0.1;
    customercount++;
    printf("\nRecord added successfully!\n");

        // Save the updated records to the file
        saverecord();
} 
    else
 {
        printf("\nMaximum number of records reached!\n");
    }
}

// Function to view the list of customer records
void viewrecords() {
    if (customercount == 0) {
    printf("\nNo records to display.\n");
        return;
    }

    printf("\nName\tPhone Number\tUsage(min)\tTotal Bill($)\n");
    for (int i = 0; i < customercount; i++) {
        printf("%s\t%s\t%.2f\t\t%.2f\n", customers[i].name,
               customers[i].phonenumber,
               customers[i].usage,
               customers[i].totalBill);
    }
}


// Function to modify a customer record
void modifyrecord(char phonenumber[]) {
    for (int i = 0; i < customercount; i++) {
        if (strcmp(customers[i].phonenumber, phonenumber) == 0) {
        printf("\nEnter new usage (in minutes) for %s: ", customers[i].name);
        scanf("%f", &customers[i].usage); // used to update total bill for new customer
            customers[i].totalBill = customers[i].usage * 0.1;
        printf("\nRecord modified successfully!\n"); //will save the new record to the file
        saverecord();
            return;
        }
    }
    printf("\nRecord not found!\n");
}

// to view Payment details of customer
void viewpayment(char phonenumber[])
 {
    for (int i = 0; i < customercount; i++) 
    {
        if (strcmp(customers[i].phonenumber, phonenumber) == 0) 
        {
            printf("%s\t%s\t%.2f\t\t%.2f\n", customers[i].name,
                   customers[i].phonenumber,
                   customers[i].usage,
                   customers[i].totalBill);
            return;
        }
    }
    printf("\nRecord not found!\n");
}
// Function to delete a customer record
void deleterecord(char phonenumber[])
 {
    for (int i = 0; i < customercount; i++) 
    {
        if (strcmp(customers[i].phonenumber, phonenumber) == 0) 
        {
            //Shift all records-after the deleted record
        for(int j=i;j<customercount-1;j++) 
        {
        customers[j]=customers[j + 1];
        }
        customercount--;
        printf("\nRecord deleted successfully!\n");// Save the updated records to the file
            saverecord();
            return;
        }
    }
    printf("\nRecord not found!\n");
}

// THis funtion display all the operation which can be performed

void displaymenu() {
printf("\n1. Add New Record\n");
printf("2. View List of Records\n");
printf("3. Modify Record\n");
printf("4. View Payment\n");
printf("5. Delete Record\n");
printf("6. Exit\n");
}
