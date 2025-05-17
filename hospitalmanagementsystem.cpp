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
void addNewPatient();
void viewAllPatients();
void updatePatient();
void deletePatient();

void manageDoctors();
void addNewDoctor();
void viewAllDoctors();
void updateDoctor();
void deleteDoctor();

void manageAppointments();
void addAppointment();
void viewAllAppointments();
void updateAppointment();
void deleteAppointment();

void manageBilling();
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

// Module 1: Patient Management
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
                patientList[j] = patientList[j+1];
				}
                patientCount--;
            printf("Patient and related records deleted!\n");
            return;
        }
    }
    printf("Patient ID %d not found!\n", searchID);
}
// Module 2: Doctor Management 
void manageDoctors() {
    int choice;
    do {
        printf("\n--- DOCTOR MANAGEMENT ---\n");
        printf("1. Add New Doctor\n");
        printf("2. View All Doctors\n");
        printf("3. Update Doctor\n");
        printf("4. Delete Doctor\n");
        printf("5. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: addNewDoctor(); break;
            case 2: viewAllDoctors(); break;
            case 3: updateDoctor(); break;
            case 4: deleteDoctor(); break;
            case 5: break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 5);
}

void addNewDoctor() {
    if(doctorCount >= 50) {
        printf("Doctor database full!\n");
        return;
    }
    
    Doctor d;
    d.id = currentDoctorID++;
    
    printf("\nEnter doctor details:\n");
    printf("Name: ");
    scanf(" %49[^\n]", d.name);
    
    printf("Specialization: ");
    scanf(" %49[^\n]", d.specialization);
    
    doctorList[doctorCount++] = d;
    printf("Doctor added! ID: %d\n", d.id);
}

void viewAllDoctors() {
    printf("\n=== DOCTOR LIST (%d) ===\n", doctorCount);
    for(int i = 0; i < doctorCount; i++) {
        printf("ID: %d | Name: %s | Specialization: %s\n",
               doctorList[i].id,
               doctorList[i].name,
               doctorList[i].specialization);
    }
}

void updateDoctor() {
    int searchID;
    printf("Enter Doctor ID to update: ");
    scanf("%d", &searchID);
    
    for(int i = 0; i < doctorCount; i++) {
        if(doctorList[i].id == searchID) {
            printf("Enter new name: ");
            scanf(" %49[^\n]", doctorList[i].name);
            
            printf("Enter new specialization: ");
            scanf(" %49[^\n]", doctorList[i].specialization);
            
            printf("Doctor updated!\n");
            return;
        }
    }
    printf("Doctor ID %d not found!\n", searchID);
}

void deleteDoctor() {
    int searchID;
    printf("Enter Doctor ID to delete: ");
    scanf("%d", &searchID);
    
    for(int i = 0; i < doctorCount; i++) {
        if(doctorList[i].id == searchID) {
            // Delete related appointments
            for(int j = 0; j < appointmentCount; j++) {
                if(appointmentList[j].doctorId == searchID) {
                    for(int k = j; k < appointmentCount-1; k++) {
                        appointmentList[k] = appointmentList[k+1];
                    }
                    appointmentCount--;
                    j--;
                }
            }
            
            // Deletion of Stored doctor data
            for(int j = i; j < doctorCount-1; j++) {
                doctorList[j] = doctorList[j+1];
            }
            doctorCount--;
            printf("Doctor and related appointments deleted!\n");
            return;
        }
    }
    printf("Doctor ID %d not found!\n", searchID);
}
// Modeule 3: Appointment Management
void manageAppointments() {
    int choice;
    do {
        printf("\n--- APPOINTMENT MANAGEMENT ---\n");
        printf("1. Add New Appointment\n");
        printf("2. View All Appointments\n");
        printf("3. Update Appointment\n");
        printf("4. Delete Appointment\n");
        printf("5. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: addAppointment(); break;
            case 2: viewAllAppointments(); break;
            case 3: updateAppointment(); break;
            case 4: deleteAppointment(); break;
            case 5: break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 5);
}

void addAppointment() {
    if(appointmentCount >= 100) {
        printf("Appointment database full!\n");
        return;
    }
    
    Appointment a;
    a.id = currentAppointmentID++;
    
    printf("\nEnter appointment details:\n");
    
    printf("Patient ID: ");
    scanf("%d", &a.patientId);
    printf("Doctor ID: ");
    scanf("%d", &a.doctorId);
    
    int validPatient = 0, validDoctor = 0;
    for(int i = 0; i < patientCount; i++) {
        if(patientList[i].id == a.patientId) validPatient = 1;
    }
    for(int i = 0; i < doctorCount; i++) {
        if(doctorList[i].id == a.doctorId) validDoctor = 1;
    }
    
    if(!validPatient || !validDoctor) {
        printf("Invalid Patient/Doctor ID!\n");
        return;
    }
    
    do {
        printf("Date (DD-MM-YYYY): ");
        scanf(" %10s", a.date);
    } while(!validateDate(a.date));
    
    do {
        printf("Time (HH:MM): ");
        scanf(" %5s", a.time);
    } while(!validateTime(a.time));
    
    appointmentList[appointmentCount++] = a;
    printf("Appointment added! ID: %d\n", a.id);
}

void viewAllAppointments() {
    printf("\n=== APPOINTMENT LIST (%d) ===\n", appointmentCount);
    for(int i = 0; i < appointmentCount; i++) {
        printf("ID: %d | Patient: %d | Doctor: %d | Date: %s | Time: %s\n",
               appointmentList[i].id,
               appointmentList[i].patientId,
               appointmentList[i].doctorId,
               appointmentList[i].date,
               appointmentList[i].time);
    }
}

void updateAppointment() {
    int searchID;
    printf("Enter Appointment ID to update: ");
    scanf("%d", &searchID);
    
    for(int i = 0; i < appointmentCount; i++) {
        if(appointmentList[i].id == searchID) {
            printf("New Patient ID: ");
            scanf("%d", &appointmentList[i].patientId);
            printf("New Doctor ID: ");
            scanf("%d", &appointmentList[i].doctorId);
            
            int validPatient = 0, validDoctor = 0;
            for(int j = 0; j < patientCount; j++) {
                if(patientList[j].id == appointmentList[i].patientId) validPatient = 1;
            }
            for(int j = 0; j < doctorCount; j++) {
                if(doctorList[j].id == appointmentList[i].doctorId) validDoctor = 1;
            }
            
            if(!validPatient || !validDoctor) {
                printf("Invalid Patient/Doctor ID! Update failed.\n");
                return;
            }
            
            do {
                printf("New Date (DD-MM-YYYY): ");
                scanf(" %10s", appointmentList[i].date);
            } while(!validateDate(appointmentList[i].date));
            
            do {
                printf("New Time (HH:MM): ");
                scanf(" %5s", appointmentList[i].time);
            } while(!validateTime(appointmentList[i].time));
            
            printf("Appointment updated!\n");
            return;
        }
    }
    printf("Appointment ID %d not found!\n", searchID);
}

void deleteAppointment() {
    int searchID;
    printf("Enter Appointment ID to delete: ");
    scanf("%d", &searchID);
    
    for(int i = 0; i < appointmentCount; i++) {
        if(appointmentList[i].id == searchID) {
            for(int j = i; j < appointmentCount-1; j++) {
                appointmentList[j] = appointmentList[j+1];
            }
            appointmentCount--;
            printf("Appointment deleted!\n");
            return;
        }
    }
    printf("Appointment ID %d not found!\n", searchID);
}

void manageBilling() {
    int choice;
    do {
        printf("\n--- BILLING MANAGEMENT ---\n");
        printf("1. Add New Bill\n");
        printf("2. View All Bills\n");
        printf("3. Update Bill\n");
        printf("4. Delete Bill\n");
        printf("5. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: addBill(); break;
            case 2: viewAllBills(); break;
            case 3: updateBill(); break;
            case 4: deleteBill(); break;
            case 5: break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 5);
}

void addBill() {
    if(billCount >= 100) {
        printf("Billing database full!\n");
        return;
    }
    
    Bill b;
    b.id = currentBillID++;
    
    printf("\nEnter bill details:\n");
    printf("Patient ID: ");
    scanf("%d", &b.patientId);
    
    int validPatient = 0;
    for(int i = 0; i < patientCount; i++) {
        if(patientList[i].id == b.patientId) validPatient = 1;
    }
    if(!validPatient) {
        printf("Invalid Patient ID!\n");
        return;
    }
    
    printf("Amount: ");
    while(scanf("%f", &b.amount) != 1 || b.amount < 0) {
        printf("Invalid amount! Enter positive number: ");
        while(getchar() != '\n');
    }
    
    do {
        printf("Date (DD-MM-YYYY): ");
        scanf(" %10s", b.date);
    } while(!validateDate(b.date));
    
    printf("Paid? (1=Yes/0=No): ");
    scanf("%d", &b.isPaid);
    
    billList[billCount++] = b;
    printf("Bill added! ID: %d\n", b.id);
}

void viewAllBills() {
    printf("\n=== BILL LIST (%d) ===\n", billCount);
    for(int i = 0; i < billCount; i++) {
        printf("ID: %d | Patient: %d | Amount: $%.2f | Date: %s | Status: %s\n",
               billList[i].id,
               billList[i].patientId,
               billList[i].amount,
               billList[i].date,
               billList[i].isPaid ? "Paid" : "Unpaid");
    }
}

void updateBill() {
    int searchID;
    printf("Enter Bill ID to update: ");
    scanf("%d", &searchID);
    
    for(int i = 0; i < billCount; i++) {
        if(billList[i].id == searchID) {
            printf("New Patient ID: ");
            scanf("%d", &billList[i].patientId);
            
            int validPatient = 0;
            for(int j = 0; j < patientCount; j++) {
                if(patientList[j].id == billList[i].patientId) validPatient = 1;
            }
            if(!validPatient) {
                printf("Invalid Patient ID! Update failed.\n");
                return;
            }
            
            printf("New Amount: ");
            while(scanf("%f", &billList[i].amount) != 1 || billList[i].amount < 0) {
                printf("Invalid amount! Enter positive number: ");
                while(getchar() != '\n');
            }
            
            do {
                printf("New Date (DD-MM-YYYY): ");
                scanf(" %10s", billList[i].date);
            } while(!validateDate(billList[i].date));
            
            printf("New Payment Status (1=Paid/0=Unpaid): ");
            scanf("%d", &billList[i].isPaid);
            
            printf("Bill updated!\n");
            return;
        }
    }
    printf("Bill ID %d not found!\n", searchID);
}

void deleteBill() {
    int searchID;
    printf("Enter Bill ID to delete: ");
    scanf("%d", &searchID);
    
    for(int i = 0; i < billCount; i++) {
        if(billList[i].id == searchID) {
            for(int j = i; j < billCount-1; j++) {
                billList[j] = billList[j+1];
            }
            billCount--;
            printf("Bill deleted!\n");
            return;
        }
    }
    printf("Bill ID %d not found!\n", searchID);
}

// Validation functions
int validateDate(const char *date) {
    if(strlen(date) != 10 || date[2] != '-' || date[5] != '-') {
        printf("Invalid date format! Use DD-MM-YYYY\n");
        return 0;
    }
    return 1;
}

int validateTime(const char *time) {
    if(strlen(time) != 5 || time[2] != ':') {
        printf("Invalid time format! Use HH:MM\n");
        return 0;
    }
    return 1;
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
