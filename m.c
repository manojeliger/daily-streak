#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Car {
    int id;
    char name[20];
    char type[20];
    float pricePerDay;
    int isRented;
};

// Save cars to file
void saveCarsToFile(struct Car cars[], int n) {
    FILE *fp = fopen("cars.txt", "w");
    if (fp == NULL) {
        printf("Error saving to file.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d %s %s %.2f %d\n", cars[i].id, cars[i].name, cars[i].type, cars[i].pricePerDay, cars[i].isRented);
    }

    fclose(fp);
}

// Load cars from file
int loadCarsFromFile(struct Car cars[]) {
    FILE *fp = fopen("cars.txt", "r");
    int i = 0;

    if (fp == NULL) {
        printf("No car data file found. Creating sample data...\n");

        // Create sample data
        cars[0] = (struct Car){1, "Toyota", "SUV", 2000, 0};
        cars[1] = (struct Car){2, "Honda", "Sedan", 1800, 0};
        cars[2] = (struct Car){3, "Mahindra", "SUV", 2200, 0};
        cars[3] = (struct Car){4, "Tata", "Hatch", 1500, 0};
        cars[4] = (struct Car){5, "Suzuki", "Sedan", 1600, 0};

        saveCarsToFile(cars, 5);
        return 5;
    }

    while (fscanf(fp, "%d %s %s %f %d", &cars[i].id, cars[i].name, cars[i].type, &cars[i].pricePerDay, &cars[i].isRented) == 5) {
        i++;
    }

    fclose(fp);
    return i;
}

void viewAvailableCars(struct Car cars[], int n) {
    printf("\nAvailable Cars:\n");
    printf("ID\tName\t\tType\t\tPrice/Day\n");
    for (int i = 0; i < n; i++) {
        if (!cars[i].isRented) {
            printf("%d\t%s\t\t%s\t\t%.2f\n", cars[i].id, cars[i].name, cars[i].type, cars[i].pricePerDay);
        }
    }
}

void rentCar(struct Car cars[], int n) {
    int id, days, found = 0;
    printf("\nEnter Car ID to rent: ");
    scanf("%d", &id);

    for (int i = 0; i < n; i++) {
        if (cars[i].id == id && !cars[i].isRented) {
            printf("Enter number of days: ");
            scanf("%d", &days);
            float cost = days * cars[i].pricePerDay;
            cars[i].isRented = 1;

            saveCarsToFile(cars, n);

            printf("Car rented successfully! Total cost: ₹%.2f\n", cost);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Invalid ID or car already rented.\n");
    }
}

void returnCar(struct Car cars[], int n) {
    int id, found = 0;
    printf("\nEnter Car ID to return: ");
    scanf("%d", &id);

    for (int i = 0; i < n; i++) {
        if (cars[i].id == id && cars[i].isRented) {
            cars[i].isRented = 0;
            saveCarsToFile(cars, n);
            printf("Car returned successfully.\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Invalid ID or car is not rented.\n");
    }
}

int main() {
    struct Car cars[MAX];
    int count = loadCarsFromFile(cars);
    int choice;

    do {
        printf("\n--- Car Rental System ---\n");
        printf("1. View Available Cars\n");
        printf("2. Rent a Car\n");
        printf("3. Return a Car\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: viewAvailableCars(cars, count); break;
            case 2: rentCar(cars, count); break;
            case 3: returnCar(cars, count); break;
            case 4: printf("Thank you for using the system.\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 4);

    return 0;
}