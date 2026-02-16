#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SEATS 24
#define SIZE 20

struct seat {
    int id;
    int taken;
    char first[SIZE];
    char last[SIZE];
};

// Function prototypes
void init(struct seat s[]);
void menu2(struct seat s[], const char *filename);
void empty_count(struct seat s[]);
void empty_list(struct seat s[]);
void alpha_list(struct seat s[]);
void assign(struct seat s[]);
void remove_seat(struct seat s[]);
void loadSeats(struct seat s[], const char *filename);
void saveSeats(struct seat s[], const char *filename);

int main() {
    struct seat outbound[SEATS];
    struct seat inbound[SEATS];
    char choice;

    init(outbound);
    init(inbound);

    loadSeats(outbound, "outbound.dat");
    loadSeats(inbound, "inbound.dat");

    while (1) {
        printf("\nMain Menu\n");
        printf("a) Outbound Flight\n");
        printf("b) Inbound Flight\n");
        printf("c) Quit\n");
        printf("Choice: ");
        scanf(" %c", &choice);
        choice = tolower(choice);

        if (choice == 'a')
            menu2(outbound, "outbound.dat");
        else if (choice == 'b')
            menu2(inbound, "inbound.dat");
        else if (choice == 'c')
            break;
        else
            printf("Invalid choice\n");
    }

    return 0;
}

// Initialize seats
void init(struct seat s[]) {
    for (int i = 0; i < SEATS; i++) {
        s[i].id = i + 1;
        s[i].taken = 0;
        strcpy(s[i].first, "");
        strcpy(s[i].last, "");
    }
}

// Load seat data from file
void loadSeats(struct seat s[], const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file != NULL) {
        fread(s, sizeof(struct seat), SEATS, file);
        fclose(file);
    }
}

// Save seat data to file
void saveSeats(struct seat s[], const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file != NULL) {
        fwrite(s, sizeof(struct seat), SEATS, file);
        fclose(file);
    }
}

// Seat menu
void menu2(struct seat s[], const char *filename) {
    char choice;

    while (1) {
        printf("\nSeat Menu\n");
        printf("a) Show number of empty seats\n");
        printf("b) Show list of empty seats\n");
        printf("c) Show alphabetical list\n");
        printf("d) Assign seat\n");
        printf("e) Delete seat assignment\n");
        printf("f) Return to main menu\n");
        printf("Choice: ");
        scanf(" %c", &choice);
        choice = tolower(choice);

        if (choice == 'a')
            empty_count(s);
        else if (choice == 'b')
            empty_list(s);
        else if (choice == 'c')
            alpha_list(s);
        else if (choice == 'd') {
            assign(s);
            saveSeats(s, filename);
        }
        else if (choice == 'e') {
            remove_seat(s);
            saveSeats(s, filename);
        }
        else if (choice == 'f')
            return;
        else
            printf("Invalid choice\n");
    }
}

// Count empty seats
void empty_count(struct seat s[]) {
    int count = 0;
    for (int i = 0; i < SEATS; i++) {
        if (!s[i].taken)
            count++;
    }
    printf("Empty seats: %d\n", count);
}

// List empty seats
void empty_list(struct seat s[]) {
    printf("Empty seats:\n");
    for (int i = 0; i < SEATS; i++) {
        if (!s[i].taken)
            printf("Seat %d\n", s[i].id);
    }
}

// Show seats alphabetically by last name
void alpha_list(struct seat s[]) {
    struct seat temp[SEATS];
    struct seat swap;

    for (int i = 0; i < SEATS; i++) {
        temp[i] = s[i];
    }

    for (int i = 0; i < SEATS - 1; i++) {
        for (int j = i + 1; j < SEATS; j++) {
            if (strcmp(temp[i].last, temp[j].last) > 0) {
                swap = temp[i];
                temp[i] = temp[j];
                temp[j] = swap;
            }
        }
    }

    for (int i = 0; i < SEATS; i++) {
        if (temp[i].taken) {
            printf("Seat %d: %s %s\n",
                   temp[i].id,
                   temp[i].first,
                   temp[i].last);
        }
    }
}

// Assign seat
void assign(struct seat s[]) {
    int num;

    printf("Enter seat number (1-24, 0 to cancel): ");
    scanf("%d", &num);

    if (num == 0)
        return;

    if (num < 1 || num > 24 || s[num - 1].taken) {
        printf("Invalid or taken seat\n");
        return;
    }

    printf("First name: ");
    scanf("%s", s[num - 1].first);
    printf("Last name: ");
    scanf("%s", s[num - 1].last);

    s[num - 1].taken = 1;
    printf("Seat assigned\n");
}

// Remove seat assignment
void remove_seat(struct seat s[]) {
    int num;

    printf("Enter seat number to delete (0 to cancel): ");
    scanf("%d", &num);

    if (num == 0)
        return;

    if (num < 1 || num > 24 || !s[num - 1].taken) {
        printf("Seat already empty or invalid\n");
        return;
    }

    s[num - 1].taken = 0;
    strcpy(s[num - 1].first, "");
    strcpy(s[num - 1].last, "");

    printf("Seat assignment removed\n");
}
