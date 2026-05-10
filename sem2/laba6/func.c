#include "header.h"

double dist_euclidean(double hx, double hy, double px, double py) {         // Вылічэнне еўклідавай адлегласці.
    return sqrt(pow(px - hx, 2) + pow(py - hy, 2));
}

double dist_manhattan(double hx, double hy, double px, double py) {         // Вылічэнне манхэтэнскай адлегласці.
    return fabs(px - hx) + fabs(py - hy);
}

DistanceFunc get_func_by_type(int type) {                                   // Выбар функцыі па яе лічбавым кодзе.
    if (type == 2) return dist_manhattan;
    return dist_euclidean; 
}

Hospital create_hospital(int id, double x, double y, int beds, DistanceFunc func) { // Стварэнне новай бальніцы.
    Hospital h;
    h.id = id; h.x = x; h.y = y;
    h.total_beds = beds; h.free_beds = beds;
    h.get_distance = func;
    
    h.patients_names = (char**)malloc(beds * sizeof(char*));                // Выдзяленне памяці пад масіў імёнаў.
    for (int i = 0; i < beds; i++) {
        h.patients_names[i] = (char*)malloc(MAX_NAME_LEN * sizeof(char));
        h.patients_names[i][0] = '\0'; 
    }
    return h;
}

void free_hospital(Hospital *h) {                                           // Вызваленне памяці ўсіх радкоў і масіва.
    for (int i = 0; i < h->total_beds; i++) free(h->patients_names[i]);
    free(h->patients_names);
}

void enqueue(HospitalQueue *q, Hospital h) {                                // Даданне бальніцы ў канец чаргі.
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->data = h;
    new_node->next = NULL;

    if (q->rear == NULL) {
        q->front = new_node;
        q->rear = new_node;
    } else {
        q->rear->next = new_node;
        q->rear = new_node;
    }
    q->size++;
}

Hospital dequeue(HospitalQueue *q) {                                        // Выдаленне бальніцы з пачатку чаргі.
    if (q->front == NULL) {
        Hospital empty = {0};
        return empty;
    }
    Node *temp = q->front;
    Hospital h = temp->data;
    q->front = q->front->next;
    
    if (q->front == NULL) q->rear = NULL;
    
    free(temp);
    q->size--;
    return h;
}

void free_queue(HospitalQueue *q) {                                         // Ачыстка ўсёй чаргі з памяці.
    while (q->size > 0) {
        Hospital h = dequeue(q);
        free_hospital(&h);
    }
}

void admit_patient(HospitalQueue *q, const char *name, double px, double py) {
    int n = q->size;
    if (n == 0) return;

    double min_dist = -1.0;
    int best_id = -1;

    for (int i = 0; i < n; i++) {                                           // Пошук бліжэйшай бальніцы са свабоднымі месцамі.
        Hospital current = dequeue(q);
        if (current.free_beds > 0) {
            double dist = current.get_distance(current.x, current.y, px, py);
            if (min_dist < 0 || dist < min_dist) {
                min_dist = dist;
                best_id = current.id;
            }
        }
        enqueue(q, current);
    }

    if (best_id == -1) {                                                    // Калі ўсе бальніцы цалкам занятыя.
        printf("Sorry, no free beds available in any hospital.\n");
        return;
    }

    for (int i = 0; i < n; i++) {                                           // Запіс пацыента ў знойдзеную бальніцу.
        Hospital current = dequeue(q);
        if (current.id == best_id) {
            for (int j = 0; j < current.total_beds; j++) {
                if (current.patients_names[j][0] == '\0') {
                    strcpy(current.patients_names[j], name);
                    current.free_beds--;
                    printf("Success: %s admitted to Hospital ID %d (Distance: %.2f)\n", name, best_id, min_dist);
                    break;
                }
            }
        }
        enqueue(q, current);
    }
}

void discharge_patient(HospitalQueue *q, const char *name) {
    int n = q->size;
    int found = 0;

    for (int i = 0; i < n; i++) {                                           // Праход па бальніцах і пошук пацыента.
        Hospital current = dequeue(q);
        for (int j = 0; j < current.total_beds; j++) {
            if (strcmp(current.patients_names[j], name) == 0) {
                current.patients_names[j][0] = '\0';                        // Сціранне імя і вызваленне месца ў масіве.
                current.free_beds++;
                found = 1;
                printf("Success: %s discharged from Hospital ID %d.\n", name, current.id);
                break; 
            }
        }
        enqueue(q, current);
    }
    if (!found) printf("Error: Patient '%s' not found.\n", name);
}

void print_queue_status(HospitalQueue *q) {                                 // Вывад стану ўсіх бальніц у табліцы.
    int n = q->size;
    
    printf("\n=================================================================================================\n");
    printf("| %-3s | %-14s | %-10s | %-13s | %-37s |\n", "ID", "Loc (X, Y)", "Beds (F/T)", "Distance Func", "Patients");
    printf("|=====|================|============|===============|=======================================|\n");
    
    for (int i = 0; i < n; i++) {
        Hospital current = dequeue(q);
        
        char patients_str[256] = "";                                        // Буфер для аб'яднання ўсіх імёнаў у адзін радок.
        int printed_patients = 0;
        for (int j = 0; j < current.total_beds; j++) {
            if (current.patients_names[j][0] != '\0') {
                if (printed_patients > 0) strcat(patients_str, ", ");
                strcat(patients_str, current.patients_names[j]);
                printed_patients++;
            }
        }
        if (printed_patients == 0) strcpy(patients_str, "None");

        char loc_str[20];                                                   // Падрыхтоўка адфарматаваных радкоў для табліцы.
        snprintf(loc_str, sizeof(loc_str), "(%.1f, %.1f)", current.x, current.y);
        
        char beds_str[15];
        snprintf(beds_str, sizeof(beds_str), "%d / %d", current.free_beds, current.total_beds);
        
        const char *dist_name = (current.get_distance == dist_euclidean) ? "Euclidean" : "Manhattan";

        printf("| %-3d | %-14s | %-10s | %-13s | %-37.37s |\n",
               current.id, loc_str, beds_str, dist_name, patients_str);

        enqueue(q, current);
    }
    printf("=================================================================================================\n");
}

void load_hospitals_file(const char *filename, HospitalQueue *q) {          // Загрузка даных бальніц з тэкставага файла.
    FILE *f = fopen(filename, "r");
    if (!f) { printf("Error: Could not open %s\n", filename); return; }

    char line[256];
    if (fgets(line, sizeof(line), f) == NULL) return;                       // Пропуск першага радка з загалоўкамі слупкоў.

    int count = 0;
    while (fgets(line, sizeof(line), f)) {
        int id, beds, type; double x, y;
        if (sscanf(line, "%d %lf %lf %d %d", &id, &x, &y, &beds, &type) == 5) {
            enqueue(q, create_hospital(id, x, y, beds, get_func_by_type(type)));
            count++;
        }
    }
    fclose(f);
    printf("Loaded %d hospitals from %s\n", count, filename);
}

void load_patients_file(const char *filename, HospitalQueue *q) {           // Загрузка пацыентаў з файла і іх размеркаванне.
    FILE *f = fopen(filename, "r");
    if (!f) { printf("Error: Could not open %s\n", filename); return; }

    char line[256];
    if (fgets(line, sizeof(line), f) == NULL) return;

    int count = 0;
    while (fgets(line, sizeof(line), f)) {
        char name[MAX_NAME_LEN]; double x, y;
        if (sscanf(line, "%s %lf %lf", name, &x, &y) == 3) {
            admit_patient(q, name, x, y);
            count++;
        }
    }
    fclose(f);
    printf("Loaded and processed %d initial patients from %s\n", count, filename);
}

void load_hospitals_manual(HospitalQueue *q) {                              // Ручны ўвод параметраў бальніц з клавіятуры.
    int n;
    printf("Enter number of hospitals to add: ");
    if (scanf("%d", &n) != 1) return;
    
    for (int i = 0; i < n; i++) {
        int id, beds, type; double x, y;
        printf("Hospital %d -> Enter ID, X, Y, Total Beds, DistFunc(1-Euclid, 2-Manhattan): ", i + 1);
        scanf("%d %lf %lf %d %d", &id, &x, &y, &beds, &type);
        enqueue(q, create_hospital(id, x, y, beds, get_func_by_type(type)));
    }
}

void load_patients_manual(HospitalQueue *q) {                               // Ручны ўвод пацыентаў і іх размеркаванне.
    int n;
    printf("Enter number of initial patients to admit: ");
    if (scanf("%d", &n) != 1) return;
    
    for (int i = 0; i < n; i++) {
        char name[MAX_NAME_LEN]; double x, y;
        printf("Patient %d -> Enter Lastname, X, Y: ", i + 1);
        scanf("%s %lf %lf", name, &x, &y);
        admit_patient(q, name, x, y);
    }
}

void initialize_system(HospitalQueue *q) {                                  // Запыт у карыстальніка крыніцы даных для ініцыялізацыі.
    int choice;
    printf("=== SYSTEM INITIALIZATION ===\n");
    
    printf("Hospitals data source (1 - File 'hospitals.txt', 2 - Keyboard input): ");
    if (scanf("%d", &choice) != 1) return;
    if (choice == 1) load_hospitals_file("hospitals.txt", q);
    else load_hospitals_manual(q);

    printf("\nInitial patients data source (1 - File 'patients.txt', 2 - Keyboard, 3 - Skip): ");
    if (scanf("%d", &choice) != 1) return;
    if (choice == 1) load_patients_file("patients.txt", q);
    else if (choice == 2) load_patients_manual(q);
}

int process_user_command(HospitalQueue *q) {                                // Галоўнае меню кіравання сістэмай і апрацоўка ўводу.
    int cmd;
    printf("\n[MENU] 1: Admit | 0: Discharge | 2: Status | -1: Exit\n");
    printf("Select action: ");
    
    if (scanf("%d", &cmd) != 1) return 0;                                   // Выхад з праграмы пры памылцы ўводу або націсканні Ctrl+D.

    if (cmd == -1) {
        return 0;
    } 
    else if (cmd == 1) {
        char name[MAX_NAME_LEN]; double x, y;
        printf("Enter Patient Lastname, X, Y: ");
        scanf("%s %lf %lf", name, &x, &y);
        admit_patient(q, name, x, y);
    } 
    else if (cmd == 0) {
        char name[MAX_NAME_LEN];
        printf("Enter Patient Lastname to discharge: ");
        scanf("%s", name);
        discharge_patient(q, name);
    } 
    else if (cmd == 2) {
        print_queue_status(q);
    } 
    else {
        printf("Invalid command.\n");
    }
    
    return 1;
}