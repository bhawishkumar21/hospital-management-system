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
void managePatients();
void manageDoctors();
void manageAppointments();
void manageBilling();
void addNewPatient();
void viewAllPatients();
void updatePatient();
void deletePatient();
void addNewDoctor();
void viewAllDoctors();
void updateDoctor();
void deleteDoctor();
void addAppointment();
void viewAllAppointments();
void updateAppointment();
void deleteAppointment();
void addBill();
void viewAllBills();
void updateBill();
void deleteBill();
int validateDate(const char *date);
int validateTime(const char *time);
int isNumber(const char *str);
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
            case 1: managePatients(); break;
            case 2: manageDoctors(); break;
            case 3: manageAppointments(); break;
            case 4: manageBilling(); break;
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
        
        if(strcmp(username, "NBAhospital") == 0 && 
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

// Patient Management
void managePatients() {
    int choice;
    do {
        printf("\n--- PATIENT MANAGEMENT ---\n");
        printf("1. Add New Patient\n");
        printf("2. View All Patients\n");
        printf("3. Update Patient\n");
        printf("4. Delete Patient\n");
        printf("5. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: addNewPatient(); break;
            case 2: viewAllPatients(); break;
            case 3: updatePatient(); break;
            case 4: deletePatient(); break;
            case 5: break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 5);
}

void addNewPatient() {
    if(patientCount >= 100) {
        printf("Patient database full!\n");
        return;
    }
    
    Patient p;
    p.id = currentPatientID++;
    
    printf("\nEnter patient details:\n");
    printf("Name: ");
    scanf(" %49[^\n]", p.name);
    
    printf("Age: ");
    while(scanf("%d", &p.age) != 1 || p.age < 0) {
        printf("Invalid age! Enter positive number: ");
        while(getchar() != '\n');
    }
    
    printf("Medical Problem: ");
    scanf(" %99[^\n]", p.problem);
    
    patientList[patientCount++] = p;
    printf("Patient added! ID: %d\n", p.id);
}

void viewAllPatients() {
    printf("\n=== PATIENT LIST (%d) ===\n", patientCount);
    for(int i = 0; i < patientCount; i++) {
        printf("ID: %d | Name: %s | Age: %d | Problem: %s\n",
               patientList[i].id,
               patientList[i].name,
               patientList[i].age,
               patientList[i].problem);
    }
}

void updatePatient() {
    int searchID;
    printf("Enter Patient ID to update: ");
    scanf("%d", &searchID);
    
    for(int i = 0; i < patientCount; i++) {
        if(patientList[i].id == searchID) {
            printf("Enter new name: ");
            scanf(" %49[^\n]", patientList[i].name);
            
            printf("Enter new age: ");
            while(scanf("%d", &patientList[i].age) != 1 || patientList[i].age < 0) {
                printf("Invalid age! Enter positive number: ");
                while(getchar() != '\n');
            }
            
            printf("Enter new problem: ");
            scanf(" %99[^\n]", patientList[i].problem);
            
            printf("Patient updated!\n");
            return;
        }
    }
    printf("Patient ID %d not found!\n", searchID);
}

void deletePatient() {
    int searchID;
    printf("Enter Patient ID to delete: ");
    scanf("%d", &searchID);
    
    for(int i = 0; i < patientCount; i++) {
        if(patientList[i].id == searchID) {
            // Delete related appointments and bills
            for(int j = 0; j < appointmentCount; j++) {
                if(appointmentList[j].patientId == searchID) {
                    for(int k = j; k < appointmentCount-1; k++) {
                        appointmentList[k] = appointmentList[k+1];
                    }
                    appointmentCount--;
                    j--;
                }
            }
            
            for(int j = 0; j < billCount; j++) {
                if(billList[j].patientId == searchID) {
                    for(int k = j; k < billCount-1; k++) {
                        billList[k] = billList[k+1];
                    }
                    billCount--;
                    j--;
                }
            }
            
            // Delete patient
            for(int j = i; j < patientCount-1; j++) {
                patientList[j] = patientList[j+1];}
