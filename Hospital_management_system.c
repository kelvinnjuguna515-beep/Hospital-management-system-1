#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100
#define MAX_DOCTORS 50
#define MAX_APPOINTMENTS 100

#define PATIENT_FILE "patients.dat"
#define DOCTOR_FILE "doctors.dat"
#define APPOINTMENT_FILE "appointments.dat"

/* =========================
   STRUCTURES
   ========================= */

struct Patient {
    int id;
    char name[50];
    int age;
    char gender[10];
    char phone[20];
    char disease[100];
};

struct Doctor {
    int id;
    char name[50];
    char specialization[50];
    char phone[20];
};

struct Appointment {
    int id;
    int patientId;
    int doctorId;
    char date[20];
    char time[20];
};

/* =========================
   GLOBAL VARIABLES
   ========================= */

struct Patient patients[MAX_PATIENTS];
struct Doctor doctors[MAX_DOCTORS];
struct Appointment appointments[MAX_APPOINTMENTS];

int patientCount = 0;
int doctorCount = 0;
int appointmentCount = 0;

/* =========================
   FUNCTION DECLARATIONS
   ========================= */

void loadData();
void saveData();

void addPatient();
void viewPatients();
void searchPatient();
void updatePatient();
void deletePatient();

void addDoctor();
void viewDoctors();
void searchDoctor();

void bookAppointment();
void viewAppointments();

int findPatient(int id);
int findDoctor(int id);

/* =========================
   MAIN FUNCTION
   ========================= */

int main() {

    int choice;

    loadData();

    while (1) {

        printf("\n============================================\n");
        printf("        HOSPITAL MANAGEMENT SYSTEM\n");
        printf("============================================\n");

        printf("1. Add Patient\n");
        printf("2. View Patients\n");
        printf("3. Search Patient\n");
        printf("4. Update Patient\n");
        printf("5. Delete Patient\n");
        printf("6. Add Doctor\n");
        printf("7. View Doctors\n");
        printf("8. Search Doctor\n");
        printf("9. Book Appointment\n");
        printf("10. View Appointments\n");
        printf("11. Exit\n");

        printf("============================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                addPatient();
                break;

            case 2:
                viewPatients();
                break;

            case 3:
                searchPatient();
                break;

            case 4:
                updatePatient();
                break;

            case 5:
                deletePatient();
                break;

            case 6:
                addDoctor();
                break;

            case 7:
                viewDoctors();
                break;

            case 8:
                searchDoctor();
                break;

            case 9:
                bookAppointment();
                break;

            case 10:
                viewAppointments();
                break;

            case 11:
                saveData();

                printf("\nData saved successfully.\n");
                printf("Thank you for using the system.\n");

                return 0;

            default:
                printf("\nInvalid choice. Try again.\n");
        }
    }

    return 0;
}

/* =========================
   SAVE DATA
   ========================= */

void saveData() {

    FILE *file;

    /* Save patients */
    file = fopen(PATIENT_FILE, "wb");

    if (file != NULL) {

        fwrite(&patientCount,
               sizeof(int),
               1,
               file);

        fwrite(patients,
               sizeof(struct Patient),
               patientCount,
               file);

        fclose(file);
    }

    /* Save doctors */
    file = fopen(DOCTOR_FILE, "wb");

    if (file != NULL) {

        fwrite(&doctorCount,
               sizeof(int),
               1,
               file);

        fwrite(doctors,
               sizeof(struct Doctor),
               doctorCount,
               file);

        fclose(file);
    }

    /* Save appointments */
    file = fopen(APPOINTMENT_FILE, "wb");

    if (file != NULL) {

        fwrite(&appointmentCount,
               sizeof(int),
               1,
               file);

        fwrite(appointments,
               sizeof(struct Appointment),
               appointmentCount,
               file);

        fclose(file);
    }
}

/* =========================
   LOAD DATA
   ========================= */

void loadData() {

    FILE *file;

    /* Load patients */
    file = fopen(PATIENT_FILE, "rb");

    if (file != NULL) {

        fread(&patientCount,
              sizeof(int),
              1,
              file);

        fread(patients,
              sizeof(struct Patient),
              patientCount,
              file);

        fclose(file);
    }

    /* Load doctors */
    file = fopen(DOCTOR_FILE, "rb");

    if (file != NULL) {

        fread(&doctorCount,
              sizeof(int),
              1,
              file);

        fread(doctors,
              sizeof(struct Doctor),
              doctorCount,
              file);

        fclose(file);
    }

    /* Load appointments */
    file = fopen(APPOINTMENT_FILE, "rb");

    if (file != NULL) {

        fread(&appointmentCount,
              sizeof(int),
              1,
              file);

        fread(appointments,
              sizeof(struct Appointment),
              appointmentCount,
              file);

        fclose(file);
    }
}

/* =========================
   FIND PATIENT
   ========================= */

int findPatient(int id) {

    for (int i = 0; i < patientCount; i++) {

        if (patients[i].id == id) {
            return i;
        }
    }

    return -1;
}

/* =========================
   FIND DOCTOR
   ========================= */

int findDoctor(int id) {

    for (int i = 0; i < doctorCount; i++) {

        if (doctors[i].id == id) {
            return i;
        }
    }

    return -1;
}

/* =========================
   ADD PATIENT
   ========================= */

void addPatient() {

    int id;

    if (patientCount >= MAX_PATIENTS) {

        printf("\nPatient limit reached.\n");
        return;
    }

    printf("\n========== ADD PATIENT ==========\n");

    printf("Enter patient ID: ");
    scanf("%d", &id);

    if (findPatient(id) != -1) {

        printf("Patient ID already exists.\n");
        return;
    }

    patients[patientCount].id = id;

    printf("Enter patient name: ");
    scanf(" %[^\n]", patients[patientCount].name);

    printf("Enter age: ");
    scanf("%d", &patients[patientCount].age);

    printf("Enter gender: ");
    scanf("%s", patients[patientCount].gender);

    printf("Enter phone number: ");
    scanf("%s", patients[patientCount].phone);

    printf("Enter disease/condition: ");
    scanf(" %[^\n]", patients[patientCount].disease);

    patientCount++;

    saveData();

    printf("\nPatient added successfully!\n");
}

/* =========================
   VIEW PATIENTS
   ========================= */

void viewPatients() {

    printf("\n========== PATIENT LIST ==========\n");

    if (patientCount == 0) {

        printf("No patients found.\n");
        return;
    }

    for (int i = 0; i < patientCount; i++) {

        printf("\nPatient %d\n", i + 1);

        printf("ID       : %d\n",
               patients[i].id);

        printf("Name     : %s\n",
               patients[i].name);

        printf("Age      : %d\n",
               patients[i].age);

        printf("Gender   : %s\n",
               patients[i].gender);

        printf("Phone    : %s\n",
               patients[i].phone);

        printf("Condition: %s\n",
               patients[i].disease);

        printf("----------------------------------\n");
    }
}

/* =========================
   SEARCH PATIENT
   ========================= */

void searchPatient() {

    int id;

    printf("\n========== SEARCH PATIENT ==========\n");

    printf("Enter patient ID: ");
    scanf("%d", &id);

    int index = findPatient(id);

    if (index == -1) {

        printf("\nPatient not found.\n");
        return;
    }

    printf("\nPatient found!\n");

    printf("ID       : %d\n",
           patients[index].id);

    printf("Name     : %s\n",
           patients[index].name);

    printf("Age      : %d\n",
           patients[index].age);

    printf("Gender   : %s\n",
           patients[index].gender);

    printf("Phone    : %s\n",
           patients[index].phone);

    printf("Condition: %s\n",
           patients[index].disease);
}

/* =========================
   UPDATE PATIENT
   ========================= */

void updatePatient() {

    int id;

    printf("\n========== UPDATE PATIENT ==========\n");

    printf("Enter patient ID: ");
    scanf("%d", &id);

    int index = findPatient(id);

    if (index == -1) {

        printf("\nPatient not found.\n");
        return;
    }

    printf("Enter new name: ");
    scanf(" %[^\n]", patients[index].name);

    printf("Enter new age: ");
    scanf("%d", &patients[index].age);

    printf("Enter new gender: ");
    scanf("%s", patients[index].gender);

    printf("Enter new phone: ");
    scanf("%s", patients[index].phone);

    printf("Enter new disease/condition: ");
    scanf(" %[^\n]", patients[index].disease);

    saveData();

    printf("\nPatient updated successfully!\n");
}

/* =========================
   DELETE PATIENT
   ========================= */

void deletePatient() {

    int id;

    printf("\n========== DELETE PATIENT ==========\n");

    printf("Enter patient ID: ");
    scanf("%d", &id);

    int index = findPatient(id);

    if (index == -1) {

        printf("\nPatient not found.\n");
        return;
    }

    for (int i = index; i < patientCount - 1; i++) {

        patients[i] = patients[i + 1];
    }

    patientCount--;

    saveData();

    printf("\nPatient deleted successfully!\n");
}

/* =========================
   ADD DOCTOR
   ========================= */

void addDoctor() {

    int id;

    if (doctorCount >= MAX_DOCTORS) {

        printf("\nDoctor limit reached.\n");
        return;
    }

    printf("\n========== ADD DOCTOR ==========\n");

    printf("Enter doctor ID: ");
    scanf("%d", &id);

    if (findDoctor(id) != -1) {

        printf("Doctor ID already exists.\n");
        return;
    }

    doctors[doctorCount].id = id;

    printf("Enter doctor name: ");
    scanf(" %[^\n]", doctors[doctorCount].name);

    printf("Enter specialization: ");
    scanf(" %[^\n]", doctors[doctorCount].specialization);

    printf("Enter phone number: ");
    scanf("%s", doctors[doctorCount].phone);

    doctorCount++;

    saveData();

    printf("\nDoctor added successfully!\n");
}

/* =========================
   VIEW DOCTORS
   ========================= */

void viewDoctors() {

    printf("\n========== DOCTOR LIST ==========\n");

    if (doctorCount == 0) {

        printf("No doctors found.\n");
        return;
    }

    for (int i = 0; i < doctorCount; i++) {

        printf("\nDoctor %d\n", i + 1);

        printf("ID             : %d\n",
               doctors[i].id);

        printf("Name           : %s\n",
               doctors[i].name);

        printf("Specialization : %s\n",
               doctors[i].specialization);

        printf("Phone          : %s\n",
               doctors[i].phone);

        printf("----------------------------------\n");
    }
}

/* =========================
   SEARCH DOCTOR
   ========================= */

void searchDoctor() {

    int id;

    printf("\n========== SEARCH DOCTOR ==========\n");

    printf("Enter doctor ID: ");
    scanf("%d", &id);

    int index = findDoctor(id);

    if (index == -1) {

        printf("\nDoctor not found.\n");
        return;
    }

    printf("\nDoctor found!\n");

    printf("ID             : %d\n",
           doctors[index].id);

    printf("Name           : %s\n",
           doctors[index].name);

    printf("Specialization : %s\n",
           doctors[index].specialization);

    printf("Phone          : %s\n",
           doctors[index].phone);
}

/* =========================
   BOOK APPOINTMENT
   ========================= */

void bookAppointment() {

    int patientId;
    int doctorId;

    if (appointmentCount >= MAX_APPOINTMENTS) {

        printf("\nAppointment limit reached.\n");
        return;
    }

    printf("\n========== BOOK APPOINTMENT ==========\n");

    printf("Enter patient ID: ");
    scanf("%d", &patientId);

    if (findPatient(patientId) == -1) {

        printf("Patient not found.\n");
        return;
    }

    printf("Enter doctor ID: ");
    scanf("%d", &doctorId);

    if (findDoctor(doctorId) == -1) {

        printf("Doctor not found.\n");
        return;
    }

    appointments[appointmentCount].id =
        appointmentCount + 1;

    appointments[appointmentCount].patientId =
        patientId;

    appointments[appointmentCount].doctorId =
        doctorId;

    printf("Enter appointment date (DD/MM/YYYY): ");
    scanf("%s",
          appointments[appointmentCount].date);

    printf("Enter appointment time: ");
    scanf("%s",
          appointments[appointmentCount].time);

    appointmentCount++;

    saveData();

    printf("\nAppointment booked successfully!\n");
}

/* =========================
   VIEW APPOINTMENTS
   ========================= */

void viewAppointments() {

    printf("\n========== APPOINTMENTS ==========\n");

    if (appointmentCount == 0) {

        printf("No appointments found.\n");
        return;
    }

    for (int i = 0; i < appointmentCount; i++) {

        int patientIndex =
            findPatient(appointments[i].patientId);

        int doctorIndex =
            findDoctor(appointments[i].doctorId);

        printf("\nAppointment ID: %d\n",
               appointments[i].id);

        printf("Patient       : ");

        if (patientIndex != -1) {
            printf("%s",
                   patients[patientIndex].name);
        }

        printf("\nDoctor        : ");

        if (doctorIndex != -1) {
            printf("%s",
                   doctors[doctorIndex].name);
        }

        printf("\nDate          : %s",
               appointments[i].date);

        printf("\nTime          : %s\n",
               appointments[i].time);

        printf("----------------------------------\n");
    }
}
