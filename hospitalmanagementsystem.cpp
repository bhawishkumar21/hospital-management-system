#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Structures
typedef struct {
    int id;
    char name[50];
    int age;
    char problem[100];
} Patient;

typedef struct {
    int id;
    char name[50];
    char specialization[50];
} Doctor;

typedef struct {
    int id;
    int patientId;
    int doctorId;
    char date[11];
    char time[6];
} Appointment;

typedef struct {
    int id;
    int patientId;
    float amount;
    char date[11];
    int isPaid;
} Bill;

// Global arrays
Patient patientList[100];
Doctor doctorList[50];
Appointment appointmentList[100];
Bill billList[100];
int patientCount=0, doctorCount=0, appointmentCount=0, billCount=0;
int currentPatientID=1, currentDoctorID=1, currentAppointmentID=1, currentBillID=1;

// Function prototypes
int login();
void displayMainMenu();
void saveData();
void loadData();

int main() {
    if(!login()) {
        printf("Too many failed attempts. Exiting...\n");
        return 0;
    }
    
    loadData();
    int choice;
    
    do {
        displayMainMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: case 2: case 3: case 4: // Handled by Adil and Hoor
            case 5: saveData(); break;
            case 6: printf("Exiting...\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while(choice != 6);
    
    return 0;
}

// Login system
int login() {
    int attempts = 3;
    char username[20], password[20];
    
    while(attempts > 0) {
        printf("\n=== HOSPITAL LOGIN ===\n");
        printf("Username: ");
        scanf("%19s", username);
        printf("Password: ");
        scanf("%19s", password);
        
        if(strcmp(username, "HBAhospital") == 0 && 
           strcmp(password, "123") == 0) {
            return 1;
        }
        printf("Invalid credentials! Attempts left: %d\n", --attempts);
    }
    return 0;
}

void displayMainMenu() {
    printf("\n=== MAIN MENU ===\n");
    printf("1. Patient Management\n");
    printf("2. Doctor Management\n");
    printf("3. Appointment Management\n");
    printf("4. Billing Management\n");
    printf("5. Save Data\n");
    printf("6. Exit\n");
    printf("=================\n");
}

// File Handling
void saveData() {
    FILE *pFile = fopen("patients.dat", "w");
    FILE *dFile = fopen("doctors.dat", "w");
    FILE *aFile = fopen("appointments.dat", "w");
    FILE *bFile = fopen("bills.dat", "w");
    
    // Save patients
    for(int i = 0; i < patientCount; i++) {
        fprintf(pFile, "%d,%s,%d,%s\n",
                patientList[i].id,
                patientList[i].name,
                patientList[i].age,
                patientList[i].problem);
    }
    
    // Save doctors
    for(int i = 0; i < doctorCount; i++) {
        fprintf(dFile, "%d,%s,%s\n",
                doctorList[i].id,
                doctorList[i].name,
                doctorList[i].specialization);
    }
    
    // Save appointments
    for(int i = 0; i < appointmentCount; i++) {
        fprintf(aFile, "%d,%d,%d,%s,%s\n",
                appointmentList[i].id,
                appointmentList[i].patientId,
                appointmentList[i].doctorId,
                appointmentList[i].date,
                appointmentList[i].time);
    }
    
    // Save bills
    for(int i = 0; i < billCount; i++) {
        fprintf(bFile, "%d,%d,%.2f,%s,%d\n",
                billList[i].id,
                billList[i].patientId,
                billList[i].amount,
                billList[i].date,
                billList[i].isPaid);
    }
    
    fclose(pFile);
    fclose(dFile);
    fclose(aFile);
    fclose(bFile);
    printf("Data saved successfully!\n");
}

void loadData() {
    // Load patients
    FILE *pFile = fopen("patients.dat", "r");
    if(pFile) {
        while(fscanf(pFile, "%d,%49[^,],%d,%99[^\n]\n",
                    &patientList[patientCount].id,
                    patientList[patientCount].name,
                    &patientList[patientCount].age,
                    patientList[patientCount].problem) == 4) {
            if(patientList[patientCount].id >= currentPatientID) {
                currentPatientID = patientList[patientCount].id + 1;
            }
            patientCount++;
        }
        fclose(pFile);
    }
    
    // Load doctors
    FILE *dFile = fopen("doctors.dat", "r");
    if(dFile) {
        while(fscanf(dFile, "%d,%49[^,],%49[^\n]\n",
                    &doctorList[doctorCount].id,
                    doctorList[doctorCount].name,
                    doctorList[doctorCount].specialization) == 3) {
            if(doctorList[doctorCount].id >= currentDoctorID) {
                currentDoctorID = doctorList[doctorCount].id + 1;
            }
            doctorCount++;
        }
        fclose(dFile);
    }
    
    // Load appointments
    FILE *aFile = fopen("appointments.dat", "r");
    if(aFile) {
        while(fscanf(aFile, "%d,%d,%d,%10[^,],%5[^\n]\n",
                    &appointmentList[appointmentCount].id,
                    &appointmentList[appointmentCount].patientId,
                    &appointmentList[appointmentCount].doctorId,
                    appointmentList[appointmentCount].date,
                    appointmentList[appointmentCount].time) == 5) {
            if(appointmentList[appointmentCount].id >= currentAppointmentID) {
                currentAppointmentID = appointmentList[appointmentCount].id + 1;
            }
            appointmentCount++;
        }
        fclose(aFile);
    }
    
    // Load bills
    FILE *bFile = fopen("bills.dat", "r");
    if(bFile) {
        while(fscanf(bFile, "%d,%d,%f,%10[^,],%d\n",
                    &billList[billCount].id,
                    &billList[billCount].patientId,
                    &billList[billCount].amount,
                    billList[billCount].date,
                    &billList[billCount].isPaid) == 5) {
            if(billList[billCount].id >= currentBillID) {
                currentBillID = billList[billCount].id + 1;
            }
            billCount++;
        }
        fclose(bFile);
    }
}
