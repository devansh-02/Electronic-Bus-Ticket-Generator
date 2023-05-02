#include <stdio.h>
#include <string.h>

struct Bus {
    int fare;
    char route[20];
    char name[20];
    int number;
    int seats;
    int mseats;
};

void printBus(struct Bus b) {
    printf("Fare: %d\n", b.fare);
    printf("Route: %s\n", b.route);
    printf("Name: %s\n", b.name);
    printf("Number: %d\n", b.number);
    printf("Number of seats available:%d\n",b.seats);
}
void searchBus(struct Bus buses[], int numBuses) {
    char searchRoute[20];
    int found = 0;
    printf("\nEnter route to search for: ");
    scanf("%s", searchRoute);
    
    printf("\nBuses with route %s:\n", searchRoute);
    for (int i = 0; i < numBuses; i++) {
        if (strcmp(buses[i].route, searchRoute) == 0) {
            printBus(buses[i]);
            found = 1;
        }
    }
    if (!found) {
        printf("No buses found with route %s.\n", searchRoute);
    }
}
void bookSeat(struct Bus buses[], int numBuses,int maxseats) {
    int busIndex, seatNum;
    int found=0;
    int copy;
    printf("\nEnter bus number to book a seat on: ");
    scanf("%d", &busIndex);

    for(int i=0;i<=numBuses;i++){
        if(buses[i].number==busIndex){
            found++;
            copy=i;
            break;
        }
    }
    if(found==0){
        printf("No BUS with this Number");
        return;
    }
    printf("\n");
    printf("\n");
    printf("\nEnter number of seats to book: ");
    scanf("%d", &seatNum);
    if (seatNum < 0 || seatNum >= buses[copy].seats || seatNum>=maxseats) {
        printf("\nInvalid seat number.\n");
        return;
    }
    else{
        buses[copy].seats=
        buses[copy].seats=buses[copy].seats-(seatNum);
        printf("\n Seats booked Succesfully\n");
    }
}
void delete_bus(struct Bus buses[], int numBuses){
    int busno;
    printf("\nEnter bus no to delete: ");
    scanf("%d", &busno);
    int index = -1;
    for (int i = 0; i < numBuses; i++) {
        if (buses[i].number == busno) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("\nInvalid bus no!");
        return;
    }
    for (int i = index; i <numBuses; i++) {
        buses[i] = buses[i + 1];
    }
    numBuses--;
    printf("\nBus deleted successfully!");
}
void save_buses(struct Bus buses[], int numBuses){
     FILE *fp = fopen("savebus.txt", "w");
    if (fp == NULL)
    {
        printf("Error: Failed to open file.\n");
        return;
    }

    for (int i = 0; i <numBuses; i++)
    {
        fprintf(fp, "%s,%d,%d,%d,%s\n", buses[i].name, buses[i].number, buses[i].fare, buses[i].seats, buses[i].route);
    }

    fclose(fp);
    printf("Details saved successfully.\n");
}
void load_buses(struct Bus buses[], int maxBuses, int* numBusesLoaded) {
    FILE* fp = fopen("savebus.txt", "r");
    if (fp == NULL) {
        printf("Error: Failed to open file.\n");
        return;
    }

    int i = 0;
    while (i < maxBuses && fscanf(fp, "%[^,],%d,%d,%d,%[^\n]\n", buses[i].name, &buses[i].number, &buses[i].fare, &buses[i].seats, buses[i].route) == 5) {
        i++;
    }

    fclose(fp);

    *numBusesLoaded = i;
    printf("Loaded %d buses from file.\n", *numBusesLoaded);
}
void update_bus(struct Bus buses[], int numBuses) {
    int busno;
    printf("\nEnter bus no to update: ");
    scanf("%d", &busno);
    int index =-1;
    for (int i = 0; i < numBuses; i++) {
        if (buses[i].number == busno) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("\nInvalid bus no!");
        return;
    }
    int choice;
    printf("\nSelect an option to update:");
    printf("\n1. Bus no");
    printf("\n2. Bus Name");
    printf("\n3. Route");
    printf("\n4. Fare");
    printf("\n5. Seats");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            printf("\nEnter new bus no: ");
            scanf("%d", &buses[index].number);
            printf("\nBus no updated successfully!");
            break;
        case 2:
            printf("\nEnter new name: ");
            scanf("%s", buses[index].name);
            printf("\nBus Name updated successfully!");
            break;
        case 3:
            printf("\nEnter new destination: ");
            scanf("%s", buses[index].route);
            printf("\nroute updated successfully!");
            break;
        case 4:
            printf("\nEnter new fare: ");
            scanf("%d", &buses[index].fare);
            printf("\nFare updated successfully!");
            break;
        case 5:
            printf("\nEnter new number of seats: ");
            scanf("%d",&buses[index].seats);
            printf("\nSeats updated successfully!");
            break;
        default:
            printf("\nInvalid choice!");
            return;
    }
}

void cancelseat(struct Bus buses[], int numBuses,int maxseats) {
    int busno;
    printf("\nEnter bus no: ");
    scanf("%d", &busno);
    int index=-1;
    for (int i = 0; i < numBuses; i++) {
        if (buses[i].number == busno) {
        index = i;
        break;
        }
    }
    if (index == -1) {
        printf("\nInvalid bus no!");
        return;
    }
    int seat_no;
    printf("\nEnter number of seats to cancel: ");
    scanf("%d", &seat_no);
    if (seat_no < 1 || seat_no >maxseats || ((seat_no)+buses[index].seats)>(buses[index].mseats)) {
        printf("\nInvalid amount of seats!");
        return;
    }
    else{
        buses[index].seats=buses[index].seats+(seat_no);
    }
    printf("\nSeats cancelled successfully!");
}

int main() {
    struct Bus buses[50];
    int numBuses = 0;
    int choice = 0;
    int numBusesLoaded=0;
    load_buses(buses, numBuses,&numBusesLoaded);
    int maxseats=400;
    do {
        printf("\nChoose an option:\n");
        printf("1. Add a bus\n");
        printf("2. Search for buses with a specific route\n");
        printf("3. Book Seats\n");
        printf("4. Delete a Bus\n");
        printf("5. Update Details\n");
        printf("6: Cancel Seats\n");
        printf("7. Exit\n");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                if (numBuses < 50) {
                    printf("Enter fare: ");
                    scanf("%d", &buses[numBuses].fare);
                    printf("Enter route: ");
                    scanf("%s", buses[numBuses].route);
                    printf("Enter name: ");
                    scanf("%s", buses[numBuses].name);
                    printf("Enter number: ");
                    scanf("%d", &buses[numBuses].number);
                    label:
                    printf("Enter number of seats: ");
                    scanf("%d",&buses[numBuses].seats);
                    if(buses[numBuses].seats>maxseats){
                        printf("Enter correct number of seats please\n");
                        goto label;
                    }
                    printf("\nBus added successfully!\n\n");
                    buses[numBuses].mseats=buses[numBuses].seats;
                    numBuses++;
                } 
                else {
                    printf("\nMaximum number of buses reached.\n");
                }
                break;    
            case 2:
                searchBus(buses, numBuses);
                break;
            case 3:
                bookSeat(buses,numBuses,maxseats);
                break;
            case 4:
                delete_bus(buses,numBuses);
                break;
            case 5:
                update_bus(buses,numBuses);
                break;
            case 6:
                cancelseat(buses,numBuses,maxseats);
                break;
            case 7:
                save_buses(buses,numBuses);
                printf("\nSaving Details\n");
                printf("\nExiting program.\n");
                break;  
            default:
                printf("\nInvalid choice. Try again.\n");
                break;
        }
    } while (choice != 7);
    return 0;
}
