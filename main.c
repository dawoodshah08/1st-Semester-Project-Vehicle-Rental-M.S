#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>
// ------------------------------
// STRUCTURES
// ------------------------------

typedef struct {
    int id;
    char model[5];
    char company[30];
    char color[20];
    int rentPerDay;
    int available;  // 1 = Available, 0 = Rented
} Vehicle;

typedef struct {
    int id;
    char name[30];
    char cnic[15];
    char phone[13];
    char rentdate[30];
    char returndate[30];
} Customer;

typedef struct {
    int rentID;
    int vehicleID;
    int customerID;
    int days;
    int totalRent;
    char custname[30];
    char rentDate[30];
    char returnDate[30];
} Rental;

// ------------------------------
// Colors
// ------------------------------

// Reset
#define RESET   "\033[0m"
// Regular Colors
#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\033[0;33m"
#define BLUE    "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN    "\033[0;36m"
#define WHITE   "\033[0;37m"


// Bold Colors
#define BOLD_YELLOW  "\033[1;33m"
#define BOLD_BLUE    "\033[1;34m"
#define BOLD_MAGENTA "\033[1;35m"
#define BOLD_CYAN    "\033[1;36m"
#define BOLD_WHITE   "\033[1;37m"

#define GOLD          "\033[38;5;220m"
#define RUBY          "\033[38;5;160m"
#define SAPPHIRE      "\033[38;5;21m"
#define AMETHYST      "\033[38;5;127m"
#define ORANGE        "\033[38;5;208m"

// ------------------------------
// FILE NAMES
// ------------------------------

#define VEHICLE_FILE "vehicles.txt"
#define CUSTOMER_FILE "customers.txt"
#define RENTAL_FILE "rentals.txt"

// ------------------------------
// FUNCTION DECLARATIONS
// ------------------------------
void adminMenu();
void userMenu();
void about_us();
int authenticateAdmin();

void addVehicle();
void viewVehicles();
void updateVehicle();
void deleteVehicle();
void checkAvailability();
void searchvehicle();
void searchCustomer();
void listCustomers();
void viewActiveRentals();
void addMultipleVehicles();

void showAvailableVehicleIDs();
void rentVehicle();
void returnVehicle();
void track_bill();
void generateBill();

void saveVehicleToFile(Vehicle v);
void saveCustomerToFile(Customer c);
void saveRentalToFile(Rental r);
void cleanDateString(char *date);

// ------------------------------
// FOR CURRENT DATE AND TIME
// ------------------------------

void getDateTime(char *buffer) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buffer, 50, "%Y-%m-%d %H:%M:%S", t);
}

// ------------------------------
// MAIN FUNCTION
// ------------------------------

int main() {
    int choice;
    srand(time(0)); // Seed for random number generation
    while (1) {
      system("cls");   
    printf("%s*_____________________________________________*\n",ORANGE);
	printf("|                                             |\n");
	printf("|        %sVEHICLE RENTAL MANAGEMENT%s            |\n",BOLD_CYAN,ORANGE);
	printf("|_____________________________________________|\n");
	printf("|     |----------------------------------|    |\n");
	printf("|     |            %sMAIN MENU%s             |    |\n",RED,ORANGE);
	printf("|     |----------------------------------|    |\n");
	printf("|     |    %s> [1] Admin Interface%s         |    |\n",RESET,ORANGE);
	printf("|     |    %s> [2] User Interface%s          |    |\n",RESET,ORANGE);
	printf("|     |    %s> [3] About Us%s                |    |\n",RESET,ORANGE);
	printf("|     |    %s> [0] Exit Program%s            |    |\n",RESET,ORANGE);
	printf("|     |__________________________________|    |\n");
	printf("|_____________________________________________|\n");
	printf("|  %s> Choose an option:%s                        |\n",RESET,ORANGE);
	printf("|_____________________________________________|%s\n",RESET);
    printf("  --> ");
        if (scanf("%d", &choice) != 1) {
            printf(RED "Invalid input! Please enter a number.\n" RESET);
            while (getchar() != '\n');
            Sleep(1000);
            continue;
        }

        switch (choice) {
            case 1: 
                    if(authenticateAdmin()==1)
                    adminMenu(); break;

            case 2: userMenu(); break;
            case 3: about_us(); break;
            case 0: 
                printf(GOLD"\nExiting program... Thank You For Reaching Out!\n"RESET);
                Sleep(1200);
                exit(0);
            default:
                    printf(RED"Invalid choice! Try again...\n"RESET);
                    Sleep(1000);
        }
        
    }

    return 0;
}

// ------------------------------
// ADMIN MENU
// ------------------------------

void adminMenu() {
    int choice;
    while (1) {
      system("cls");
printf("%s*_____________________________________________*%s\n",ORANGE,RESET);
printf("%s|                                             |%s\n",ORANGE,RESET);
printf("%s|%s          %sVEHICLE RENTAL MANAGEMENT%s          %s|%s\n",ORANGE,RESET,BOLD_CYAN,RESET,ORANGE,RESET);
printf("%s|_____________________________________________|%s\n",ORANGE,RESET);
printf("%s|     |----------------------------------|    |%s\n",ORANGE,RESET);
printf("%s|     |%s           %sADMIN MENU%s             %s|    |%s\n",ORANGE,RESET,RUBY,RESET,ORANGE,RESET);
printf("%s|     |----------------------------------|    |%s\n",ORANGE,RESET);
printf("%s|     |%s    > [1] Add Vehicle             %s|    |%s\n",ORANGE,RESET,ORANGE,RESET);
printf("%s|     |%s    > [2] View All Vehicles       %s|    |%s\n",ORANGE,RESET,ORANGE,RESET);
printf("%s|     |%s    > [3] Update Vehicle          %s|    |%s\n",ORANGE,RESET,ORANGE,RESET);
printf("%s|     |%s    > [4] Delete Vehicle          %s|    |%s\n",ORANGE,RESET,ORANGE,RESET);
printf("%s|     |%s    > [5] Vehicle Availability    %s|    |%s\n",ORANGE,RESET,ORANGE,RESET);
printf("%s|     |%s    > [6] Search Vehicle          %s|    |%s\n",ORANGE,RESET,ORANGE,RESET);
printf("%s|     |%s    > [7] Search Customer         %s|    |%s\n",ORANGE,RESET,ORANGE,RESET);
printf("%s|     |%s    > [8] List All Customers      %s|    |%s\n",ORANGE,RESET,ORANGE,RESET);
printf("%s|     |%s    > [9] Active Rentals          %s|    |%s\n",ORANGE,RESET,ORANGE,RESET);
printf("%s|     |%s    > [0] Back to Main Menu       %s|    |%s\n",ORANGE,RESET,ORANGE,RESET);
printf("%s|     |__________________________________|    |%s\n",ORANGE,RESET);
printf("%s|_____________________________________________|%s\n",ORANGE,RESET);
printf("%s|%s  > Choose an option:                        %s|%s\n",ORANGE,RESET,ORANGE,RESET); 
printf("%s|_____________________________________________|%s\n",ORANGE,RESET);
printf("  --> ");
    if (scanf("%d", &choice) != 1) {
            printf(RED "Invalid input! Please enter a number.\n" RESET);
            while (getchar() != '\n');
            Sleep(1000);
            continue;   
        }


        switch (choice) {
            case 1: addMultipleVehicles(); break;
            case 2: viewVehicles(); break;
            case 3: updateVehicle(); break;
            case 4: deleteVehicle(); break;
            case 5: checkAvailability(); break;
            case 6: searchvehicle(); break;
            case 7: searchCustomer(); break;
            case 8: listCustomers(); break;
            case 9: viewActiveRentals(); break;
            case 0: return;
            default: 
                printf("Invalid choice! Try again...\n");
                Sleep(1000);
        }
    }
}

// ------------------------------
// USER MENU
// ------------------------------

void userMenu() {
    int choice;
    while (1) {
       system("cls");
printf("%s*_____________________________________________*%s\n",ORANGE,RESET);
printf("%s|                                             |%s\n",ORANGE,RESET);
printf("%s|%s          %sVEHICLE RENTAL MANAGEMENT%s          %s|%s\n",ORANGE,RESET,BOLD_CYAN,RESET,ORANGE,RESET);
printf("%s|_____________________________________________|%s\n",ORANGE,RESET);
printf("%s|     |----------------------------------|    |%s\n",ORANGE,RESET);
printf("%s|     | %s          %sUSER MENU%s              %s|    |%s\n",ORANGE,RESET,RUBY,RESET,ORANGE,RESET);
printf("%s|     |----------------------------------|    |%s\n",ORANGE,RESET);
printf("%s|     |%s    > [1] View All Vehicles       %s|    |%s\n",ORANGE,RESET,ORANGE,RESET);
printf("%s|     |%s    > [2] Search Vehicle          %s|    |%s\n",ORANGE,RESET,ORANGE,RESET);
printf("%s|     |%s    > [3] Rent a Vehicles         %s|    |%s\n",ORANGE,RESET,ORANGE,RESET);
printf("%s|     |%s    > [4] Return a Vehicle        %s|    |%s\n",ORANGE,RESET,ORANGE,RESET);
printf("%s|     |%s    > [5] Track your Bill         %s|    |%s\n",ORANGE,RESET,ORANGE,RESET);
printf("%s|     |%s    > [0] Back to Main Menu       %s|    |%s\n",ORANGE,RESET,ORANGE,RESET);
printf("%s|     |__________________________________|    |%s\n",ORANGE,RESET);
printf("%s|_____________________________________________|%s\n",ORANGE,RESET);
printf("%s|%s  > Choose an option:                        %s|%s\n",ORANGE,RESET,ORANGE,RESET);
printf("%s|_____________________________________________|%s\n",ORANGE,RESET);
printf("  --> ");
    if (scanf("%d", &choice) != 1) {
            printf(RED "Invalid input! Please enter a number.\n" RESET);
            while (getchar() != '\n');
            Sleep(1000);
            continue;   
        }

        switch (choice) {
            case 1: viewVehicles(); break;
            case 2: searchvehicle(); break;
            case 3: rentVehicle(); break;
            case 4: returnVehicle(); break;
            case 5: track_bill(); break;
            case 0: return;
            default: printf("%sInvalid choice! Try again...%s\n",RED,RESET);
            Sleep(1000);
        }
    }
}

// ------------------------------
// password protection
// ------------------------------

int authenticateAdmin() {
    	system("cls");
    char password[50];
	int j=3;
    while (j>=0){
	    printf("------------------------------------------\n");
        printf("Enter Admin Password: "BOLD_CYAN);
	    int i = 0;
        char ch;
    
	    while (1) { // for masking the input by user
	        ch = getch();  
	
	        if (ch == 13) { 
	            password[i] = '\0'; 
	            break;
	        } else if (ch == 8) { 
	            if (i > 0) {
	                i--;
	                printf("\b \b"); //to erase the *
	            }
	        } else {
	            password[i++] = ch;
	            printf("*"); // to show '*' instead of the actual character
	        }
	    }
		printf(RESET);
	   if (strcmp(password, "admin123") == 0){
        system("cls");
            printf("\n=========================================\n");
            printf(GREEN"Access Granted. Welcome Boss!\n"RESET);
            printf("=========================================\n");
            Sleep(2500);
            return 1;
        }
        else
        {
            if(j==0){
                printf("\a");
                printf(AMETHYST"\n---------------------------------------------------\n");
                printf("Too many wrong attempts. Returning to Main Menu...\n");
                printf("---------------------------------------------------\n"RESET);
                Sleep(3000);
                return 0;}
            system("cls");
            printf("\a");
            printf(RED"\nWrong Password!!! Try Again.\n%d Attempts left!\n"RESET,j);
            j--;
        }
	    }
	}

// ------------------------------
// MULTIPLE VEHICLE ADD FUNC
// ------------------------------

void addMultipleVehicles() {
    int n, i;

    printf("\n%sHow many vehicles do you want to add: %s",GOLD,RESET);
    
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf(RED "Invalid number!\n" RESET);
        Sleep(1000);
        while (getchar() != '\n');
        return;
    }

    for (i = 1; i <= n; i++) {
        printf(ORANGE "\n--- Adding Vehicle %d of %d ---\n" RESET, i, n);
        Sleep(1000);
        addVehicle();
    }
}

// ------------------------------
// ADD VEHICLE
// ------------------------------

void addVehicle() {
    system("cls");
    Vehicle v;
    while(1){
        int found =0, id;
        printf("\nEnter Vehicle ID (i.e: 1234): ");
        scanf("%5d", &id);
        while (getchar() != '\n');
        FILE *x;
        x=fopen(VEHICLE_FILE, "r");
        while(fscanf(x, "%d [%[^]]] [%[^]]] [%[^]]] %d %d", &v.id, v.model, v.company, v.color, &v.rentPerDay, &v.available) != EOF){
            if (v.id == id) {
            found = 1;
            printf("\a");
            printf(RED"Vehicle id already exists!!! Try again...\n"RESET);
            break;
            }
        }
        fclose(x);
        if(!found){
            v.id=id;
            break;
        }

    }
    printf("Enter Model (i.e: 1990): ");
    scanf(" %s", v.model);
    printf("Enter Company (i.e: honda civic): "BOLD_YELLOW);
    scanf(" %[^\n]", v.company);
    printf(RESET"Enter Color: ");
    scanf(" %[^\n]", v.color);
    printf("Enter Rent Per Day: ");
    scanf("%d", &v.rentPerDay);

    v.available = 1;

    saveVehicleToFile(v);

    printf("\n%sVehicle added successfully!%s\n",GREEN,RESET);
    printf(BLUE"Press "RED"Enter"BLUE" to continue..."RESET);
    getchar(); 
    getchar();
}

void saveVehicleToFile(Vehicle v) {
    FILE *fp = fopen(VEHICLE_FILE, "a");
    
    fprintf(fp, "%-5d [%-4s] [%-20s] [%-15s] %-10d %d\n", v.id, v.model, v.company, v.color, v.rentPerDay, v.available);
    fclose(fp);
}

// ------------------------------
// VIEW VEHICLES
// ------------------------------

void viewVehicles() {
    system("cls");
    FILE *fp = fopen(VEHICLE_FILE, "r");   
    if(fp==NULL){
        printf("%sERROR opening Vehicle File!%s\n",RED,RESET);
        Sleep(1000);
        return;
    }
    if (!fp) {
        printf("\a");
        printf("%sNo vehicles found!%s\n",RED,RESET);         
        return;     
    }      
    int totalcars=0;
    Vehicle v; 
    printf("%s*______________________________________________________________________________________________*%s\n",ORANGE,RESET);
    printf("%s|                                                                                              |%s\n",ORANGE,RESET);
    printf("%s|%s                                %s VEHICLE RENTAL MANAGEMENT%s                                    %s|%s\n",ORANGE,RESET,BOLD_CYAN,RESET,ORANGE,RESET);
    printf("%s|______________________________________________________________________________________________|%s\n",ORANGE,RESET);
    printf("%s|     |-----------------------------------------------------------------------------------|    |%s\n",ORANGE,RESET);
    printf("%s|     |%s                                %s VEHICLE LIST %s                                    %s |    |%s\n",ORANGE,RESET,RUBY,RESET,ORANGE,RESET);
    printf("%s|     |-----------------------------------------------------------------------------------|    |%s\n",ORANGE,RESET);
    printf("%s|     |%s   %sID:%s    %s|%s %sCOMPANY:%s            %s|%s %sMODEL:%s %s|%s %sCOLOR:%s          %s|%s %sRENT/DAY:%s %s|%s %sSTATUS:%s   %s|    |%s\n",ORANGE,RESET,BOLD_BLUE,RESET,ORANGE,RESET,BOLD_BLUE,RESET,ORANGE,RESET,BOLD_BLUE,RESET,ORANGE,RESET,BOLD_BLUE,RESET,ORANGE,RESET,BOLD_BLUE,RESET,ORANGE,RESET,BOLD_BLUE,RESET,ORANGE,RESET); 
    printf("%s|     |__________|_____________________|________|_________________|___________|___________|    |%s\n",ORANGE,RESET);     

    while (fscanf(fp, "%d [%[^]]] [%[^]]] [%[^]]] %d %d", &v.id, v.model, v.company, v.color, &v.rentPerDay, &v.available) != EOF) { 
        
					char status[50];

						if (v.available)
    					sprintf(status, "%sAvailable%s %s|    |%s", GREEN, RESET, ORANGE, RESET);
						else
    					sprintf(status, "%sRented%s    %s|    |%s", RED, RESET, ORANGE, RESET);
        printf("%s|     |%s   %-6d %s|%s %-20s%s|%s %-6s %s|%s %-15s %s|%s %-9d %s|%s %-10s\n", ORANGE,RESET,v.id,ORANGE,RESET,v.company,ORANGE,RESET, v.model,ORANGE,RESET, v.color,ORANGE,RESET, v.rentPerDay,ORANGE,RESET, status);

        printf("%s|     |__________|_____________________|________|_________________|___________|___________|    |%s\n",ORANGE,RESET); 
        totalcars++;
    } 
    printf("%s|______________________________________________________________________________________________|%s\n",ORANGE,RESET); 
   printf("%s|%s                                                                  "GOLD"TOTAL VEHICLES: "GREEN"%5d"RESET"       %s|%s\n",ORANGE,RESET, totalcars,ORANGE,RESET);
    printf("%s|______________________________________________________________________________________________|%s\n",ORANGE,RESET);     
    fclose(fp);

    printf(BLUE"Press "RED"Enter"BLUE" to continue..."RESET);
    getchar();
    getchar();
}

// ------------------------------
// UPDATE VEHICLE
// ------------------------------

void updateVehicle() {
    system("cls");
    FILE *fp = fopen(VEHICLE_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");
    Vehicle v;
    int id, found = 0;
    if(fp==NULL){
        printf("%sERROR opening Vehicle File!%s\n",RED,RESET);
        Sleep(1000);
        return;
    }
    if(temp==NULL){
        printf("%sERROR opening Temporary Vehicle File!%s\n",RED,RESET);
        Sleep(1000);
        return;
    }

    int vehicles;
    showAvailableVehicleIDs(&vehicles);
    if (!vehicles) {
        printf(RED"No vehicles added yet!\n"RESET);
        fclose(fp);
        fclose(temp);
        Sleep(1500);
        return;
    }

    printf("Enter Vehicle ID to update: ");
    scanf("%d", &id);
    
    while (fscanf(fp, "%d [%[^]]] [%[^]]] [%[^]]] %d %d", &v.id, v.model, v.company, v.color, &v.rentPerDay, &v.available) != EOF) {

        if (v.id == id) {
            found = 1;
            printf("Enter new rent per day: ");
            scanf("%d", &v.rentPerDay);
        }
        fprintf(temp, "%-5d [%-4s] [%-20s] [%-15s] %-6d %d\n", v.id, v.model, v.company, v.color, v.rentPerDay, v.available);
    }

    fclose(fp);
    fclose(temp);
    remove(VEHICLE_FILE);
    rename("temp.txt", VEHICLE_FILE);

    if (found){
        printf("\a");
        printf("%sVehicle updated successfully!%s\n",GREEN,RESET);}
    else{
        printf("\a");
        printf("%sVehicle ID not found!%s\n",RED,RESET);}
    
    printf(BLUE"Press "RED"Enter"BLUE" to continue..."RESET);
    getchar(); 
    getchar();
}

// ------------------------------
// FOR SHOWING CAR IDs BEFORE RENTING
// ------------------------------

void showAvailableVehicleIDs(int *found) {
    FILE *fp = fopen(VEHICLE_FILE, "r");
    Vehicle v;
    *found = 0;
    if(fp==NULL){
        printf("%sERROR opening Vehicle File!%s\n",RED,RESET);
        Sleep(1000);
        return;
    }
    printf("\nAvailable Vehicle IDs:\n");
    printf("----------------------\n");

    while (fscanf(fp, "%d [%[^]]] [%[^]]] [%[^]]] %d %d", &v.id, v.model, v.company, v.color, &v.rentPerDay, &v.available) != EOF) {

        if (v.available == 1) {
            printf("- %-6d %s\n", v.id,v.company);
            *found = 1;
        }
    }
    fclose(fp);

    if (!(*found)) {
        printf("\a");
        printf(RED"\nSorry! No vehicles available for rent at the moment.\n"RESET);
    }

    printf("----------------------------\n");
}

// ------------------------------
// DELETE VEHICLE
// ------------------------------

void deleteVehicle() {
    system("cls");
    FILE *fp = fopen(VEHICLE_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");
    if(fp==NULL){
            printf("%sERROR opening Vehicle File!%s\n",RED,RESET);
            Sleep(1000);
            return;
    }
    if(temp==NULL){
            printf("%sERROR opening Temporary Vehicle File!%s\n",RED,RESET);
            Sleep(1000);
            return;
    }
    Vehicle v;
    int id, found = 0;

    printf("Enter Vehicle ID to delete: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d [%[^]]] [%[^]]] [%[^]]] %d %d",&v.id, v.model, v.company, v.color, &v.rentPerDay, &v.available) != EOF) {

        if (v.id != id) {
            fprintf(temp, "%-5d [%-4s] [%-20s] [%-15s] %-6d %d\n", v.id, v.model, v.company, v.color, v.rentPerDay, v.available);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);
    remove(VEHICLE_FILE);
    rename("temp.txt", VEHICLE_FILE);

    if (found){
        printf("\a");
        printf("%sVehicle deleted successfully!%s\n",GREEN,RESET);}
    else{
        printf("\a");
        printf("%sVehicle ID not found!%s\n",RED,RESET);}

    printf(BLUE"Press "RED"Enter"BLUE" to continue..."RESET);
    getchar(); 
    getchar();
}

// ------------------------------
// CHECK AVAILABILITY
// ------------------------------

void checkAvailability() {
    system("cls");
    FILE *fp = fopen(VEHICLE_FILE, "r");
    if(fp==NULL){
            printf("%sERROR opening Vehicle File!%s\n",RED,RESET);
            Sleep(1000);
            return;
        }
    Vehicle v;
            printf("%s*_______________________________________________________________________*\n",ORANGE); 
            printf("%s|                                                                       |\n",ORANGE); 
            printf("%s|                      %sVEHICLE RENTAL MANAGEMENT                        %s|\n",ORANGE,BOLD_CYAN,ORANGE); 
            printf("%s|_______________________________________________________________________|\n",ORANGE);
            printf("%s|     |-----------------------------------------------------------|     |\n",ORANGE);             
            printf("%s|     |                     %sAVAILABLE VEHICLES                    %s|     |\n",ORANGE,RUBY,ORANGE); 
            printf("%s|     |-----------------------------------------------------------|     |\n",ORANGE);
            printf("%s|     |%s    ID:    %s|%s            NAME:             %s|%s Rent: Rs./day %s |     |%s\n",ORANGE,RESET,ORANGE,RESET,ORANGE,RESET,ORANGE,RESET);
            printf("%s|     |-----------|------------------------------|----------------|     |\n",ORANGE);
            while (fscanf(fp, "%d [%[^]]] [%[^]]] [%[^]]] %d %d", &v.id, v.model, v.company, v.color, &v.rentPerDay, &v.available) != EOF)
            {
                if (v.available == 1) 
                {            
            printf("%s|     |%s    %-6d %s|%s %-20s %-6s  %s|%s %10d     %s|     |%s \n",ORANGE,RESET, v.id, ORANGE,RESET,v.company, v.model,ORANGE,RESET, v.rentPerDay,ORANGE,RESET); 
            
                }
            }
            printf("%s|     |___________________________________________________________|     |\n",ORANGE);
            printf("%s|_______________________________________________________________________|\n",ORANGE);
            printf("%s|                                                                       |\n",ORANGE);
            printf("%s|_______________________________________________________________________|\n",ORANGE);



    fclose(fp);
    printf(BLUE"Press "RED"Enter"BLUE" to continue..."RESET);
    getchar();
    getchar();
}

// ------------------------------
// SEARCH CUSTOMER
// ------------------------------

void searchCustomer() {
    system("cls");
    FILE *fp = fopen(CUSTOMER_FILE, "r");
    if (fp == NULL) {
        printf("%sERROR opening Customer file!%s\n",RED,RESET);
        Sleep(1000);
        return;
    }
    Customer c;
    int choice, id, found = 0;
    char searchName[50];

    printf("Search Customer By:\n");
    printf("1. Customer ID\n");
    printf("2. Customer Name\n");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    getchar(); 

    switch (choice) {

    
    case 1:
        printf(YELLOW"\nEnter Customer ID to search: ");
        scanf("%d", &id);
        printf(RESET);

        while (fscanf(fp, "%d [%[^]]] %s %s [%[^]]] [%[^]]]", &c.id, c.name, c.cnic, c.phone, c.rentdate, c.returndate) != EOF) {
            cleanDateString(c.rentdate);
            cleanDateString(c.returndate);

            if (c.id == id) {
                printf(GREEN"\nSearch Results For: %d\n"RESET, id);
                printf("%s*______________________________________________________________________________________________________________________*%s\n",ORANGE,RESET); 
                printf("%s|                                                                                                                      |%s\n",ORANGE,RESET); 
                printf("%s|%s                                              %sVEHICLE RENTAL MANAGEMENT%s                                               %s|%s\n",ORANGE,RESET,BOLD_CYAN,RESET,ORANGE,RESET); 
                printf("%s|______________________________________________________________________________________________________________________|%s\n",ORANGE,RESET); 
                printf("%s|     |-----------------------------------------------------------------------------------------------------------|    |%s\n",ORANGE,RESET); 
                printf("%s|     |%s                                             %s CUSTOMER FOUND %s                                              %s|    |%s\n",ORANGE,RESET,GREEN,RESET,ORANGE,RESET); 
                printf("%s|     |-----------------------------------------------------------------------------------------------------------|    |%s\n",ORANGE,RESET); 
                printf("%s|     |%s   %sID:%s    %s|%s %sNAME:%s               %s|%s    %sCNIC:%s      %s|%s    %sPHONE:%s   %s|%s   %sLAST RENT D/T:%s    %s|%s     %sRETURN D/T:%s      %s|    |%s\n",ORANGE,RESET,BOLD_BLUE,RESET,ORANGE,RESET,BOLD_BLUE,RESET,ORANGE,RESET,BOLD_BLUE,RESET,ORANGE,RESET,BOLD_BLUE,RESET,ORANGE,RESET,BOLD_BLUE,RESET,ORANGE,RESET,BOLD_BLUE,RESET,ORANGE,RESET); 
                printf("%s|     |__________|_____________________|_______________|_____________|_____________________|______________________|    |%s\n",ORANGE,RESET); 

                printf("%s|     |%s %-8d %s|%s %-20s %s|%s %13s %s|%s %11s %s|%s",ORANGE,RESET,c.id, ORANGE,RESET, c.name,ORANGE,RESET, c.cnic,ORANGE,RESET, c.phone,ORANGE,RESET);

                if (strlen(c.rentdate) > 0)
                    printf("%20s %s|%s %20s %s|    |%s\n", c.rentdate,ORANGE,RESET, c.returndate,ORANGE,RESET);
                    printf("%s|     |__________|_____________________|_______________|_____________|_____________________|______________________|    |%s\n",ORANGE,RESET);
                    printf("%s|______________________________________________________________________________________________________________________|%s\n",ORANGE,RESET); 
                    printf("%s|                                                                                                                      |%s\n",ORANGE,RESET); 
                    printf("%s|______________________________________________________________________________________________________________________|%s\n",ORANGE,RESET);   

                found = 1;
            }
        }
        break;

  
    case 2:
        printf(YELLOW"\nEnter Customer Name to search: ");
        scanf(" %[^\n]",searchName);
        printf(RESET);
        searchName[strcspn(searchName, "\n")] = '\0';

        for (int i=0; searchName[i];i++){
            searchName[i]=tolower(searchName[i]);
        } 

        printf(GREEN"\nSearch Results For: %s\n"RESET, searchName);
        printf("%s*______________________________________________________________________________________________________________________*%s\n",ORANGE,RESET); 
        printf("%s|                                                                                                                      |%s\n",ORANGE,RESET); 
        printf("%s|%s                                              %sVEHICLE RENTAL MANAGEMENT%s                                               %s|%s\n",ORANGE,RESET,BOLD_CYAN,RESET,ORANGE,RESET); 
        printf("%s|______________________________________________________________________________________________________________________|%s\n",ORANGE,RESET); 
        printf("%s|     |-----------------------------------------------------------------------------------------------------------|    |%s\n",ORANGE,RESET); 
        printf("%s|     |%s                                             %s CUSTOMER SEARCH %s                                             %s|    |%s\n",ORANGE,RESET,YELLOW,RESET,ORANGE,RESET); 
        printf("%s|     |-----------------------------------------------------------------------------------------------------------|    |%s\n",ORANGE,RESET); 
        printf("%s|     |%s   %sID:%s    %s|%s %sNAME:%s               %s|%s    %sCNIC:%s      %s|%s    %sPHONE:%s   %s|%s   %sLAST RENT D/T:%s    %s|%s     %sRETURN D/T:%s      %s|    |%s\n",ORANGE,RESET,BOLD_BLUE,RESET,ORANGE,RESET,BOLD_BLUE,RESET,ORANGE,RESET,BOLD_BLUE,RESET,ORANGE,RESET,BOLD_BLUE,RESET,ORANGE,RESET,BOLD_BLUE,RESET,ORANGE,RESET,BOLD_BLUE,RESET,ORANGE,RESET); 
        printf("%s|     |-----------------------------------------------------------------------------------------------------------|    |%s\n",ORANGE,RESET);
        while (fscanf(fp, "%d [%[^]]] %s %s [%[^]]] [%[^]]]", &c.id, c.name, c.cnic, c.phone, c.rentdate, c.returndate) != EOF) {
            cleanDateString(c.rentdate);
            cleanDateString(c.returndate);
            char namelower[50];
            strcpy(namelower, c.name);

            for(int i=0; namelower[i]; i++){
            namelower[i]=tolower(namelower[i]);
          }
            // exact match OR partial match
            if (strcmp(namelower, searchName) == 0 || strstr(namelower, searchName) != NULL) { 
                printf("%s|     |%s  %-7d %s|%s %-19s %s|%s %13s %s|%s %11s %s|%s",ORANGE,RESET,c.id, ORANGE,RESET, c.name,ORANGE,RESET, c.cnic,ORANGE,RESET, c.phone,ORANGE,RESET);

                if (strlen(c.rentdate) > 0)
                    printf("%20s %s|%s %20s %s|    |%s\n", c.rentdate,ORANGE,RESET, c.returndate,ORANGE,RESET);  

                found = 1;
               
            }
        
        }
        printf("%s|     |__________|_____________________|_______________|_____________|_____________________|______________________|    |%s\n",ORANGE,RESET);
        printf("%s|______________________________________________________________________________________________________________________|%s\n",ORANGE,RESET); 
        printf("%s|                                                                                                                      |%s\n",ORANGE,RESET); 
        printf("%s|______________________________________________________________________________________________________________________|%s\n",ORANGE,RESET);
        break;

    default:
        printf(RED"\nInvalid choice!\n"RESET);
    } 

    fclose(fp);

    if (!found) {
        printf("\a");
        printf("%s\nCustomer not found!%s\n", RED, RESET);
    }

    printf(BLUE "Press " RED "Enter" BLUE " to continue..." RESET);
    getchar();
    getchar();
}


// ------------------------------
// SEARCH VEHICLE
// ------------------------------

void searchvehicle() {
    system("cls");
    FILE *fp = fopen(VEHICLE_FILE, "r");
    if(fp==NULL){
            printf("%sERROR opening Vehicle File!%s\n",RED,RESET);
            Sleep(1000);
            return;
    }
    Vehicle v;
    char search[50];
    int found = 0;
    
    printf("Enter vehicle name to search:%s ",CYAN);
    scanf(" %[^\n]", search);
    
    //userinput to lower case...
    for(int i = 0; search[i]; i++) {
        search[i] = tolower(search[i]);
    }
    printf("%s",RESET);
    
    printf(GREEN"\nSearch Results For: %s\n"RESET, search);
    printf("%s*______________________________________________________________________________________________*%s\n",ORANGE,RESET); 
    printf("%s|                                                                                              |%s\n",ORANGE,RESET); 
    printf("%s|%s                                %s VEHICLE RENTAL MANAGEMENT%s                                    %s|%s\n",ORANGE,RESET,BOLD_CYAN,RESET,ORANGE,RESET); 
    printf("%s|______________________________________________________________________________________________|%s\n",ORANGE,RESET); 
    printf("%s|     |-----------------------------------------------------------------------------------|    |%s\n",ORANGE,RESET); 
    printf("%s|     |%s                                 %s SEARCH VEHICLE %s                                 %s |    |%s\n",ORANGE,RESET,RUBY,RESET,ORANGE,RESET); 
    printf("%s|     |-----------------------------------------------------------------------------------|    |%s\n",ORANGE,RESET); 
    printf("%s|     |%s   %sID:%s    %s|%s %sCOMPANY:%s            %s|%s %sMODEL:%s %s|%s %sCOLOR:%s          %s|%s %sRENT/DAY:%s %s|%s %sSTATUS:%s   %s|    |%s\n",ORANGE,RESET,BOLD_BLUE,RESET,ORANGE,RESET,BOLD_BLUE,RESET,ORANGE,RESET,BOLD_BLUE,RESET,ORANGE,RESET,BOLD_BLUE,RESET,ORANGE,RESET,BOLD_BLUE,RESET,ORANGE,RESET,BOLD_BLUE,RESET,ORANGE,RESET); 
    printf("%s|     |__________|_____________________|________|_________________|___________|___________|    |%s\n",ORANGE,RESET);     

    
       while (fscanf(fp, "%d [%[^]]] [%[^]]] [%[^]]] %d %d", &v.id, v.model, v.company, v.color, &v.rentPerDay, &v.available) != EOF) {
    
    char nameLower[50];
    strcpy(nameLower, v.company);
    for(int i = 0; nameLower[i]; i++) {
        nameLower[i] = tolower(nameLower[i]);
    }
    
    // exact match OR partial match
    if (strcmp(nameLower, search) == 0 || strstr(nameLower, search) != NULL) {
        found = 1;
        
        char status[50];
        if (v.available)
            sprintf(status, "%sAvailable%s %s|    |%s", GREEN, RESET, ORANGE, RESET);
        else
            sprintf(status, "%sRented%s    %s|    |%s", RED, RESET, ORANGE, RESET);
        
        printf("%s|     |%s   %-6d %s|%s %-20s%s|%s %-6s %s|%s %-15s %s|%s %-9d %s|%s %-10s\n", 
               ORANGE, RESET, v.id, ORANGE, RESET,
               v.company, ORANGE, RESET, v.model, ORANGE, RESET, 
               v.color, ORANGE, RESET, v.rentPerDay, ORANGE, RESET, status);
        
        printf("%s|     |__________|_____________________|________|_________________|___________|___________|    |%s\n", ORANGE, RESET); 
    }
}
        
    
    
    printf("%s|______________________________________________________________________________________________|%s\n",ORANGE,RESET); 
    printf("%s|                                                                                              |%s\n",ORANGE,RESET); 
    printf("%s|______________________________________________________________________________________________|%s\n",ORANGE,RESET);   
    fclose(fp);
    
    if (!found) {
        printf("\a");
        printf(RED"\nNo vehicles found for '%s'!\n"RESET, search);
    }
    
    printf(BLUE"Press "RED"Enter"BLUE" to continue..."RESET);
    getchar();
    getchar();
}

// ------------------------------
// LIST CUSTOMERS
// ------------------------------

void listCustomers() {
	system("cls");
    FILE *fp = fopen(CUSTOMER_FILE, "r");
    if(fp==NULL){
            printf("%sERROR opening Customer File or No List of Customers!%s\n",RED,RESET);
            Sleep(1000);
            return;
        }
    Customer c;

    
    printf("%s*___________________________________________________________________________*%s\n",ORANGE,RESET); 
    printf("%s|                                                                           |%s\n",ORANGE,RESET); 
    printf("%s|%s                         %sVEHICLE RENTAL MANAGEMENT%s                         %s|%s\n",ORANGE,RESET,BOLD_CYAN,RESET,ORANGE,RESET); 
    printf("%s|___________________________________________________________________________|%s\n",ORANGE,RESET); 
    printf("%s|     |---------------------------------------------------------------|     |%s\n",ORANGE,RESET); 
    printf("%s|     |%s                        %s CUSTOMER LIST %s                        %s|     |%s\n",ORANGE,RESET,RUBY,RESET,ORANGE,RESET); 
    printf("%s|     |---------------------------------------------------------------|     |%s\n",ORANGE,RESET); 
    printf("%s|     |%s %sID:%s      %s|%s %sNAME:%s                %s|%s %sCNIC:%s         %s|%s %sPHONE:%s      %s|     |%s\n", ORANGE, RESET, BOLD_BLUE, RESET,ORANGE, RESET, BOLD_BLUE, RESET, ORANGE, RESET, BOLD_BLUE, RESET, ORANGE, RESET, BOLD_BLUE, RESET, ORANGE,RESET,BOLD_BLUE,RESET,ORANGE,RESET,BOLD_BLUE,RESET,ORANGE,RESET); 
    printf("%s|     |----------|----------------------|---------------|-------------|     |%s\n",ORANGE,RESET); 
    while (fscanf(fp, "%d [%[^]]] %s %s [%[^]]] [%[^]]]", &c.id, c.name, c.cnic, c.phone, c.rentdate, c.returndate) != EOF) {
        cleanDateString(c.rentdate);
        cleanDateString(c.returndate);
        printf("%s|     |%s %-8d %s|%s %-20s %s|%s %-13s %s|%s %-11s %s|     |%s\n",ORANGE ,RESET,c.id,ORANGE,RESET, c.name,ORANGE,RESET, c.cnic,ORANGE,RESET, c.phone,ORANGE,RESET);
        printf("%s|     |__________|______________________|_______________|_____________|     |%s\n",ORANGE,RESET); 
    }
    printf("%s|___________________________________________________________________________|%s\n",ORANGE,RESET); 
    printf("%s|                                                                           |%s\n",ORANGE,RESET); 
    printf("%s|___________________________________________________________________________|%s\n",ORANGE,RESET);

    fclose(fp);
    printf(BLUE"Press "RED"Enter"BLUE" to continue...",RESET);
    getchar();
    getchar();
}

// ------------------------------
// VIEW ACTIVE RENTALS
// ------------------------------

void viewActiveRentals() {
    system("cls");
    FILE *fp = fopen(RENTAL_FILE, "r");
    Rental r;
    int found = 0;
    
    if (fp == NULL) {
        printf("%sNo rental records found yet!%s\n", YELLOW, RESET);
        Sleep(1500);
        return;
    }

    printf("%s*_____________________________________________________*%s\n", ORANGE, RESET);
    printf("%s|                                                     |%s\n", ORANGE, RESET);
    printf("%s|              %sVEHICLE RENTAL MANAGEMENT%s              %s|%s\n", ORANGE, BOLD_CYAN, RESET, ORANGE, RESET);
    printf("%s|_____________________________________________________|%s\n", ORANGE, RESET);
    printf("%s|     |-----------------------------------------|     |%s\n", ORANGE, RESET);
    printf("%s|     |             %sACTIVE RENTALS%s              %s|     |%s\n", ORANGE, RUBY, RESET, ORANGE, RESET);
    printf("%s|     |-----------------------------------------|     |%s\n", ORANGE, RESET);
    
    // Read all rental records
    while (fscanf(fp, "%d %d %d [%[^]]] %d %d [%[^]]] [%[^]]]",&r.rentID, &r.vehicleID, &r.customerID, r.custname, &r.days, &r.totalRent, r.rentDate, r.returnDate) != EOF) {
        
        cleanDateString(r.rentDate);
        cleanDateString(r.returnDate);
        
        if (strcmp(r.returnDate, "N/A") == 0) {
            found = 1;
            
            printf("%s|     |%s  > Rent ID       : %-21d%s|     |%s\n", ORANGE, RESET, r.rentID, ORANGE, RESET);
            printf("%s|     |%s  > Vehicle ID    : %-21d%s|     |%s\n", ORANGE, RESET, r.vehicleID, ORANGE, RESET);
            printf("%s|     |%s  > Customer ID   : %-21d%s|     |%s\n", ORANGE, RESET, r.customerID, ORANGE, RESET);
            printf("%s|     |%s  > Customer Name : %-21s%s|     |%s\n", ORANGE, RESET, r.custname, ORANGE, RESET);
            printf("%s|     |%s  > Rent Date     : %-19s %s|     |%s\n", ORANGE, RESET, r.rentDate, ORANGE, RESET);
            printf("%s|     |%s  > Days Booked   : %-21d%s|     |%s\n", ORANGE, RESET, r.days, ORANGE, RESET);
            printf("%s|     |%s  > Status        : %sACTIVE%s               %s|     |%s\n", ORANGE, RESET, GREEN, RESET, ORANGE, RESET);
            printf("%s|     |%s  > Total Rent    : Rs.%-18d%s|     |%s\n", ORANGE, RESET, r.totalRent, ORANGE, RESET);
            printf("%s|     |-----------------------------------------|     |%s\n", ORANGE, RESET);
        }
    }
    
    printf("%s|_____________________________________________________|%s\n", ORANGE, RESET);
    fclose(fp);
    
    if (!found) {
        printf("\n%sNo active rentals found. All vehicles have been returned.%s\n", YELLOW, RESET);
    }
    
    printf(BLUE"Press "RED"Enter"BLUE" to continue..."RESET);
    getchar();
    getchar();
}

// ------------------------------
// RENT VEHICLE
// ------------------------------

void rentVehicle() {
    system("cls");
    FILE *fp = fopen(VEHICLE_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");
    FILE *f1 = fopen (CUSTOMER_FILE, "a+");
    if(fp == NULL || temp == NULL || f1 == NULL){
        printf("\a");
        printf(RED"Error opening file or doesn't exist!\n"RESET);
        Sleep(1500);
        return;
    }

    Vehicle v;
    Rental r;
    Customer c;

    int id, found = 0, confirm;
    int rentID = 0;  // Store rentID for bill generation

    printf("\n");
    int vehicles;
    showAvailableVehicleIDs(&vehicles);
    if (!vehicles) {
        fclose(fp);
        fclose(temp);
        fclose(f1);
        Sleep(1500);
        return;
    }
    printf("Enter Vehicle ID to rent: ");
    scanf("%d", &id);

    // Read vehicle data
    while (fscanf(fp, "%d [%[^]]] [%[^]]] [%[^]]] %d %d", &v.id, v.model, v.company, v.color, &v.rentPerDay, &v.available) != EOF) {

        if (v.id == id && v.available == 1 && !found) {
            found = 1;
            int uniqueID=0;
            do{
                printf("Enter Customer ID: ");
                scanf("%4d", &r.customerID);
                
                uniqueID=1;
                rewind(f1);
                while (fscanf(f1, "%d [%[^]]] %s %s [%[^]]] [%[^]]]", &c.id, c.name, c.cnic, c.phone, c.rentdate, c.returndate) != EOF){
                    cleanDateString(c.rentdate);
                    cleanDateString(c.returndate);
                    if(c.id==r.customerID){
                        uniqueID=0;
                        printf("\a");
                        printf(RED"ID already exists. Please Try Again with Unique ID.\n"RESET);
                        break;
                    }
                }
            }
            while(!uniqueID);
            
            printf("Enter Customer Name: ");
            scanf(" %[^\n]", r.custname);

            printf("Enter CNIC: ");
            scanf(" %s", c.cnic);
			c.cnic[13] = 0;
            printf("Enter Phone: ");
            scanf(" %s", c.phone);
            c.phone[11]=0;
            c.id = r.customerID;
            strcpy(c.name, r.custname);

            printf("Enter days you want to rent: ");
            scanf("%d", &r.days);

            r.totalRent = r.days * v.rentPerDay;
            r.rentID = rand() % 10000;
            r.vehicleID = id;
            rentID = r.rentID; 

            getDateTime(r.rentDate);
            strcpy(r.returnDate, "N/A");

            strcpy(c.rentdate, r.rentDate);
            strcpy(c.returndate, r.returnDate);
            //confirming before renting...
            printf("\nENTER %s1%s to %sCONFIRM%s Booking\nENTER %s0%s to %sCANCEL%s Booking\n",GREEN,RESET,GREEN,RESET,RED,RESET,RED,RESET);
            scanf("%d", &confirm);
            
            if (confirm == 1) {
                v.available = 0;  
                saveCustomerToFile(c);
                saveRentalToFile(r);
                printf("\a");
                printf("\n%sVehicle rented! Bill Generated Successfully.%s\n", GREEN, RESET);
                generateBill(rentID);  // Generate bill 
            } else {
                printf("\a");
                printf("Booking cancelled.\n");
                v.available = 1;  
            }
        }

        fprintf(temp, "%-5d [%-4s] [%-20s] [%-15s] %-9d %d\n", v.id, v.model, v.company, v.color, v.rentPerDay, v.available);
    }

    fclose(fp);
    fclose(temp);
    fclose(f1);

    remove(VEHICLE_FILE);
    rename("temp.txt", VEHICLE_FILE);


    if (!found) {
        printf("\a");
        printf("%sVehicle already rented or ID not found!%s\n", RED, RESET);
    }

    printf(BLUE"Press "RED"Enter"BLUE" to continue..."RESET);
    getchar();  
    getchar();
}

void saveRentalToFile(Rental r) {
    FILE *fp = fopen(RENTAL_FILE, "a");
    
    char returnDatePadded[30];
    if (strcmp(r.returnDate, "N/A") == 0) {
        sprintf(returnDatePadded, "N/A_________________");  //padded with '_' for reading without error
    } else {
        strcpy(returnDatePadded, r.returnDate);
    }
    
    fprintf(fp, "%-5d %-5d %-5d [%-20s] %-3d %-10d [%-20s] [%-20s]\n", r.rentID, r.vehicleID, r.customerID, r.custname, r.days, r.totalRent, r.rentDate, returnDatePadded);
    fclose(fp);
}

void saveCustomerToFile(Customer c) {
    FILE *fp = fopen(CUSTOMER_FILE, "a");
    char rentDatePadded[30], returnDatePadded[30];
    
    if (strcmp(c.rentdate, "N/A") == 0 || strlen(c.rentdate) == 0) {
        sprintf(rentDatePadded, "N/A_________________");
    } else {
        strcpy(rentDatePadded, c.rentdate);
    }
    
    if (strcmp(c.returndate, "N/A") == 0 || strlen(c.returndate) == 0) {
        sprintf(returnDatePadded, "N/A_________________");
    } else {
        strcpy(returnDatePadded, c.returndate);
    }
    
    fprintf(fp, "%-5d [%-20s] %-15s %-15s [%-20s] [%-20s]\n", c.id, c.name, c.cnic, c.phone, rentDatePadded, returnDatePadded);
    fclose(fp);
}

// ------------------------------
// RETURN VEHICLE
// ------------------------------

void returnVehicle() {
    system ("cls");
    FILE *fp = fopen(VEHICLE_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");
    if(fp==NULL){
        printf("%sERROR opening Vehicle File!%s\n",RED,RESET);
        Sleep(1000);
        return;
    }
    if(temp==NULL){
        printf("%sERROR creating Temporary File for vehicle!%s\n",RED,RESET);
        Sleep(1000);
        return;
    }
    Vehicle v;
    int rentPerDay = 0; 
    int id, found = 0;

    printf("Enter Vehicle ID to return: ");
    scanf("%d", &id);

    // ---- for updating vehicle availibity
    while (fscanf(fp, "%d [%[^]]] [%[^]]] [%[^]]] %d %d",  &v.id, v.model, v.company, v.color, &v.rentPerDay, &v.available) != EOF) {

        if (v.id == id && v.available == 0) {
            v.available = 1;
            rentPerDay = v.rentPerDay; // Save the rent per day
            found = 1;
        }
        fprintf(temp, "%-5d [%-4s] [%-20s] [%-15s] %-10d %d\n", v.id, v.model, v.company, v.color, v.rentPerDay, v.available);
    }

    fclose(fp);
    fclose(temp);
    remove(VEHICLE_FILE);
    rename("temp.txt", VEHICLE_FILE);

    if (!found) {
        printf("\a");
        printf("%sVehicle ID not found or already returned!%s\n", RED, RESET);
        Sleep(1500);
        return;
    }

    // ---- Update Rental Record & Generate Bill ----
    FILE *rentFile = fopen(RENTAL_FILE, "r");
    FILE *rentTemp = fopen("rentTemp.txt", "w");
    if(rentFile==NULL){
        printf("%sERROR opening Rental File!%s\n",RED,RESET);
        Sleep(1000);
        return;
    }
    if(rentTemp==NULL){
        printf("%sERROR opening Temporary rental File!%s\n",RED,RESET);
        Sleep(1000);
        return;
    }
    Rental r;
    int rentIDForBill = 0; // to store rent ID for bill generation
    int customerIDForUpdate = 0; 
    char returnDateTime[30] = {0}; 

    while (fscanf(rentFile, "%d %d %d [%[^]]] %d %d [%[^]]] [%[^]]]", &r.rentID, &r.vehicleID, &r.customerID, r.custname, &r.days, &r.totalRent, r.rentDate, r.returnDate) != EOF) {
        cleanDateString(r.rentDate);
        cleanDateString(r.returnDate);
        
        if (r.vehicleID == id && strcmp(r.returnDate, "N/A") == 0) {
            printf("How many days did you use the vehicle? ");
            scanf("%d", &r.days);

            r.totalRent = r.days * rentPerDay;

            getDateTime(r.returnDate);   
            strcpy(returnDateTime, r.returnDate); 
            customerIDForUpdate = r.customerID; // Save customer ID
            rentIDForBill = r.rentID; // Save for bill generation
            printf("\a");
            printf("\n%sBill Generated Successfully!%s\n", GREEN, RESET);
        }
        
        // padded date strings for writing
        char rentDateBuffer[30], returnDateBuffer[30];
        
        if (strcmp(r.rentDate, "N/A") == 0 || strlen(r.rentDate) == 0) {
            sprintf(rentDateBuffer, "N/A_________________");
        } else {
            strcpy(rentDateBuffer, r.rentDate);
        }
        
        if (strcmp(r.returnDate, "N/A") == 0 || strlen(r.returnDate) == 0) {
            sprintf(returnDateBuffer, "N/A_________________");
        } else {
            strcpy(returnDateBuffer, r.returnDate);
        }
        
        fprintf(rentTemp, "%-5d %-5d %-5d [%-20s] %-4d %-10d [%-20s] [%-20s]\n", 
                r.rentID, r.vehicleID, r.customerID, r.custname, 
                r.days, r.totalRent, rentDateBuffer, returnDateBuffer);
    }

    fclose(rentFile);
    fclose(rentTemp);
    remove(RENTAL_FILE);
    rename("rentTemp.txt", RENTAL_FILE);

    // Generate bill AFTER updating the file
    if (rentIDForBill > 0) {
        generateBill(rentIDForBill);
    }

    // ---- Update Customer Return Date ----
    if (customerIDForUpdate > 0 && strlen(returnDateTime) > 0) {
        FILE *custmFile = fopen(CUSTOMER_FILE, "r");
        FILE *custmTemp = fopen("custmTemp.txt", "w");
        if(custmFile==NULL){
            printf("%sERROR opening Customer File!%s\n",RED,RESET);
            Sleep(1000);
            return;
        }
        if(custmTemp==NULL){
            printf("%sERROR opening Temporary Customer File!%s\n",RED,RESET);
            Sleep(1000);
            return;
        }
        Customer c;
        
        while (fscanf(custmFile, "%d [%[^]]] %s %s [%[^]]] [%[^]]]", &c.id, c.name, c.cnic, c.phone, c.rentdate, c.returndate) != EOF) {
            cleanDateString(c.rentdate);
            cleanDateString(c.returndate);
            
            if (c.id == customerIDForUpdate && strcmp(c.returndate, "N/A") == 0) {
                strcpy(c.returndate, returnDateTime);
            }

            // Prepare padded date strings for writing
            char rentDateBuffer[30], returnDateBuffer[30];
            
            if (strcmp(c.rentdate, "N/A") == 0 || strlen(c.rentdate) == 0) {
                sprintf(rentDateBuffer, "N/A_________________");
            } else {
                strcpy(rentDateBuffer, c.rentdate);
            }
            
            if (strcmp(c.returndate, "N/A") == 0 || strlen(c.returndate) == 0) {
                sprintf(returnDateBuffer, "N/A_________________");
            } else {
                strcpy(returnDateBuffer, c.returndate);
            }
            
            fprintf(custmTemp, "%-5d [%-20s] %-15s %-15s [%-20s] [%-20s]\n", c.id, c.name, c.cnic, c.phone, rentDateBuffer, returnDateBuffer);
        }
        
        fclose(custmFile);
        fclose(custmTemp);
        remove(CUSTOMER_FILE);
        rename("custmTemp.txt", CUSTOMER_FILE);
    } 

    printf(BLUE"Press "RED"Enter"BLUE" to continue..."RESET);
    getchar();  
    getchar();
}

// ------------------------------
// Tracking Bill
// ------------------------------
void track_bill() {
    system("cls");
    FILE *fr = fopen(RENTAL_FILE, "r");
    if (fr == NULL) {
        printf("%sError opening rental file!%s\n",RED,RESET);
        Sleep(1000);
        return;
    }
    
    Rental r;
    int choice, search_id;
   while (1) {
      system("cls");   
    printf("%s*_____________________________________________*\n",ORANGE);
	printf("|                                             |\n");
	printf("|        %sVEHICLE RENTAL MANAGEMENT%s            |\n",BOLD_CYAN,ORANGE);
	printf("|_____________________________________________|\n");
	printf("|     |----------------------------------|    |\n");
	printf("|     |            %sTrack Bill%s            |    |\n",RED,ORANGE);
	printf("|     |----------------------------------|    |\n");
	printf("|     |    %s> [1] Rent ID%s                 |    |\n",RESET,ORANGE);
	printf("|     |    %s> [2] Vehicle ID%s              |    |\n",RESET,ORANGE);
	printf("|     |    %s> [3] Customer ID%s             |    |\n",RESET,ORANGE);
	printf("|     |    %s> [0] Return Back%s             |    |\n",RESET,ORANGE);
	printf("|     |__________________________________|    |\n");
	printf("|_____________________________________________|\n");
	printf("|  %s> Choose an option:%s                        |\n",RESET,ORANGE);
	printf("|_____________________________________________|%s\n",RESET);
    printf("  --> ");
        if (scanf("%d", &choice) != 1) {
            printf(RED "Invalid input! Please enter a number.\n" RESET);
            while (getchar() != '\n');
            Sleep(1000);
            continue;   
        }
    
    
    int flag=1;
    while(flag){
        flag=0;
        switch(choice) {
            case 1: 
                printf("\nEnter your Rent ID: ");
                scanf("%d", &search_id);
                break;
            case 2:
                printf("\nEnter your Vehicle ID: ");
                scanf("%d", &search_id);
                break;
            case 3:
                printf("\nEnter your Customer ID: ");
                scanf("%d", &search_id);
                break;
            case 0:
                fclose (fr);
                return;
            default:
                printf("\a");
                flag=1;
                printf("\nInvalid choice! Try Again\n");
        }
    }
    break;
 }

    while(getchar() != '\n');
    int found=0;
    while(fscanf(fr, "%d %d %d [%[^]]] %d %d [%[^]]] [%[^]]]",&r.rentID, &r.vehicleID, &r.customerID, r.custname, &r.days, &r.totalRent, r.rentDate, r.returnDate) != EOF) {
        
        if ((choice == 1 && search_id == r.rentID) ||
            (choice == 2 && search_id == r.vehicleID) ||
            (choice == 3 && search_id == r.customerID)) {
            
            found = 1;
            printf("\a");
            printf(GREEN"Bill Generated Successfully...\n"RESET);
            generateBill(r.rentID);
            break; 
        }
    }
    
    if (!found) {
        printf("\a");
        printf(RED"No bill found with the given ID!\n"RESET);
    }
    fclose(fr);
    printf(BLUE"Press "RED"Enter"BLUE" to continue..."RESET);
    getchar();  
}
// ------------------------------
// Bill Generation
// ------------------------------

void generateBill(int rentID) {
    FILE *fp = fopen(RENTAL_FILE, "r");
    if(fp==NULL){
        printf("%sERROR opening Rental File!%s\n",RED,RESET);
        Sleep(1000);
        return;
    }
    Rental r;
    int found = 0;

    while (fscanf(fp, "%d %d %d [%[^]]] %d %d [%[^]]] [%[^]]]", &r.rentID, &r.vehicleID, &r.customerID,r.custname, &r.days, &r.totalRent, r.rentDate, r.returnDate) != EOF) {

        cleanDateString(r.rentDate);
        cleanDateString(r.returnDate);
        if (r.rentID == rentID) {
            found = 1;

printf("%s*_____________________________________________________*%s\n", ORANGE, RESET);
printf("%s|                                                     |%s\n", ORANGE, RESET);
printf("%s|              %sVEHICLE RENTAL MANAGEMENT%s              %s|%s\n",ORANGE, BOLD_CYAN, RESET,ORANGE,RESET);
printf("%s|_____________________________________________________|%s\n", ORANGE, RESET);
printf("%s|     |-----------------------------------------|     |%s\n", ORANGE, RESET);
printf("%s|     |              %sBILL RECEIPT%s               %s|     |%s\n",ORANGE, RUBY, RESET,ORANGE,RESET);
printf("%s|     |-----------------------------------------|     |%s\n", ORANGE, RESET);
printf("%s|     |%s  > Rent ID       : %-21d%s|     |%s\n",ORANGE,RESET, r.rentID, ORANGE, RESET);
printf("%s|     |%s  > Vehicle ID    : %-21d%s|     |%s\n",ORANGE,RESET, r.vehicleID,ORANGE,  RESET);
printf("%s|     |%s  > Customer ID   : %-21d%s|     |%s\n",ORANGE,RESET, r.customerID, ORANGE, RESET);
printf("%s|     |%s  > Days Booked   : %-21d%s|     |%s\n",ORANGE,RESET, r.days,ORANGE, RESET);
printf("%s|     |%s  > Rent Date     : %-19s %s|     |%s\n",ORANGE,RESET, r.rentDate,ORANGE,  RESET);
printf("%s|     |%s  > Return Date   : %-21s%s|     |%s\n",ORANGE,RESET, r.returnDate,ORANGE,  RESET);
printf("%s|     |%s  > Total Rent    : Rs.%-18d%s|     |%s\n",ORANGE,RESET, r.totalRent,ORANGE, RESET);
printf("%s|     |-----------------------------------------|     |%s\n", ORANGE, RESET);
printf("%s|_____________________________________________________|%s\n", ORANGE, RESET);

            break;
        }
    }

    fclose(fp);

    if (!found){
    printf("\a");
    printf("%sSorry! Bill record not found.%s\n",RED,RESET);}
}

// ------------------------------
// Function to clean N/A with underscores
// ------------------------------
void cleanDateString(char *date) {
    if (strncmp(date, "N/A", 3) == 0) {
        date[3] = '\0';  // Truncated after "N/A"
    }
}

// ------------------------------
// ABOUT DEVELEPORS
// ------------------------------

void about_us(){
    system("cls");
    printf("%s*________________________________________________________________________________________________________________*%s\n", ORANGE, RESET);
    printf("%s|                                                                                                                |%s\n", ORANGE, RESET);
    printf("%s|                                           %sVEHICLE RENTAL MANAGEMENT%s                                            %s|%s\n", ORANGE, BOLD_CYAN, RESET, ORANGE, RESET);
    printf("%s|________________________________________________________________________________________________________________|%s\n", ORANGE, RESET);
    printf("%s|     |----------------------------------------------------------------------------------------------------|     |%s\n", ORANGE, RESET);
    printf("%s|     |                                              %sABOUT US%s                                              %s|     |%s\n", ORANGE, RUBY, RESET, ORANGE, RESET);
    printf("%s|     |----------------------------------------------------------------------------------------------------|     |%s\n", ORANGE, RESET);
    printf("%s|     |%s  "BOLD_WHITE"Developed By: "RESET"                                                                                    %s|     |%s\n", ORANGE, RESET, ORANGE, RESET);
    printf("%s|     |%s  "BOLD_CYAN"> Dawood Shah"RESET"                                                                                     %s|     |%s\n", ORANGE, RESET, ORANGE, RESET);
    printf("%s|     |%s  "BOLD_BLUE"--> "RESET"\e]8;;https://www.linkedin.com/in/dawood-shah-4b648622b/\aClick to connect on "BLUE"LinkedIn"RESET".\e]8;;\a                                                                 %s|     |%s\n", ORANGE, RESET, ORANGE, RESET);
    printf("%s|     |%s                                                                                                    %s|     |%s\n", ORANGE, RESET, ORANGE, RESET);
    printf("%s|     |%s  "BOLD_CYAN"> Ahmad Bilal"RESET"                                                                                     %s|     |%s\n", ORANGE, RESET, ORANGE, RESET);
    printf("%s|     |%s  "BOLD_BLUE"--> "RESET"\e]8;;https://www.linkedin.com/in/ahmad-bilal-14a5b4373/\aClick to connect on "BLUE"LinkedIn"RESET".\e]8;;\a                                                                 %s|     |%s\n", ORANGE, RESET, ORANGE, RESET);
    printf("%s|     |%s                                                                                                    %s|     |%s\n", ORANGE, RESET, ORANGE, RESET);
    printf("%s|     |%s "BOLD_WHITE" Degree"RESET"    : BS Computer Science                                                                   %s|     |%s\n", ORANGE, RESET, ORANGE, RESET);
    printf("%s|     |%s  "BOLD_WHITE"Institute"RESET" : "BOLD_CYAN"FAST NUCES"RESET"                                                                            %s|     |%s\n", ORANGE, RESET, ORANGE, RESET);
    printf("%s|     |%s                                                                                                    %s|     |%s\n", ORANGE, RESET, ORANGE, RESET);
    printf("%s|     |%s  "GOLD"Description :"RESET"                                                                                     %s|     |%s\n", ORANGE, RESET, ORANGE, RESET);
    printf("%s|     |%s  "YELLOW"This project has been developed by Dawood Shah and Ahmad Bilal, students of Computer Science,"RESET"     %s|     |%s\n", ORANGE, RESET, ORANGE, RESET);
    printf("%s|     |%s  "YELLOW"as part of an academic requirement. The Vehicle Rental System is implemented using the C"RESET"          %s|     |%s\n", ORANGE, RESET, ORANGE, RESET);
    printf("%s|     |%s  "YELLOW"programming language and demonstrates the application of core programming concepts including"RESET"      %s|     |%s\n", ORANGE, RESET, ORANGE, RESET);
    printf("%s|     |%s  "YELLOW"file handling, data structures, and modular programming. The project reflects their efforts"RESET"       %s|     |%s\n", ORANGE, RESET, ORANGE, RESET);
    printf("%s|     |%s  "YELLOW"to design a reliable, efficient, and user-friendly system while strengthening foundational"RESET"        %s|     |%s\n", ORANGE, RESET, ORANGE, RESET);
    printf("%s|     |%s  "YELLOW"software development skills. This project is aimed to create a simple and efficient Vehicle"RESET"       %s|     |%s\n", ORANGE, RESET, ORANGE, RESET);
    printf("%s|     |%s  "YELLOW"Rental System while improving practical programming skills.  "RESET"                                     %s|     |%s\n", ORANGE, RESET, ORANGE, RESET);
    printf("%s|     |%s                                                                                                    %s|     |%s\n", ORANGE, RESET, ORANGE, RESET);
    printf("%s|     |%s  "BOLD_WHITE"> Technologies Used:"RESET"                                                                              %s|     |%s\n", ORANGE, RESET, ORANGE, RESET);
    printf("%s|     |%s  "BOLD_WHITE"-->"RESET" Programming Language : "GREEN"C language"RESET"                                                             %s|     |%s\n", ORANGE, RESET, ORANGE, RESET);
    printf("%s|     |%s  "BOLD_WHITE"-->"RESET" File Handling        : "GREEN"Text Files (.txt)"RESET"                                                      %s|     |%s\n", ORANGE, RESET, ORANGE, RESET);
    printf("%s|     |%s  "BOLD_WHITE"-->"RESET" Platform             : "GREEN"Console Application "RESET"                                                   %s|     |%s\n", ORANGE, RESET, ORANGE, RESET);
    printf("%s|     |----------------------------------------------------------------------------------------------------|     |%s\n", ORANGE, RESET);
    printf("%s|________________________________________________________________________________________________________________|%s\n", ORANGE, RESET);

    printf(BLUE"Press "RED"Enter"BLUE" to continue..."RESET);
    getchar();
    getchar();
}
