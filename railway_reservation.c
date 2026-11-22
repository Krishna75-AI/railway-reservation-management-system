#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TRAINS 5
#define MAX_SEATS 10
#define NAME_LEN 50
#define PLACE_LEN 40

#define WAITING 0
#define CONFIRMED 1

typedef struct {
    int trainId;
    char trainName[NAME_LEN];
    char source[PLACE_LEN];
    char destination[PLACE_LEN];
    int totalSeats;
    int seats[MAX_SEATS]; /* 0 = available; otherwise stores booking ID */
} Train;

typedef struct Booking {
    int bookingId;
    int trainId;
    char passengerName[NAME_LEN];
    int age;
    int status;
    int seatNo;
    struct Booking *next;
} Booking;

typedef struct WaitNode {
    int bookingId;
    int trainId;
    struct WaitNode *next;
} WaitNode;

Train trains[MAX_TRAINS] = {
    {101, "Kaveri Express", "Bengaluru", "Chennai", MAX_SEATS, {0}},
    {102, "Shatabdi Express", "Bengaluru", "Mysuru", MAX_SEATS, {0}},
    {103, "Udyan Express", "Bengaluru", "Mumbai", MAX_SEATS, {0}},
    {104, "Hampi Express", "Bengaluru", "Hubballi", MAX_SEATS, {0}},
    {105, "Brindavan Express", "Chennai", "Bengaluru", MAX_SEATS, {0}}
};

Booking *bookingHead = NULL;
WaitNode *waitFront = NULL;
WaitNode *waitRear = NULL;
int nextBookingId = 1001;

void readLine(const char *prompt, char *buffer, int size) {
    int ch;
    printf("%s", prompt);
    if (fgets(buffer, size, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        if (strchr(buffer, '\n') == NULL) {
            while ((ch = getchar()) != '\n' && ch != EOF) {}
        }
    }
}

int readInt(const char *prompt) {
    char line[80];
    int value;
    char extra;
    while (1) {
        printf("%s", prompt);
        if (fgets(line, sizeof(line), stdin) == NULL)
            return -1;
        if (sscanf(line, "%d %c", &value, &extra) == 1)
            return value;
        printf("Invalid input. Please enter a number.\n");
    }
}

Train *findTrain(int trainId) {
    int i;
    for (i = 0; i < MAX_TRAINS; i++) {
        if (trains[i].trainId == trainId)
            return &trains[i];
    }
    return NULL;
}

Booking *findBooking(int bookingId) {
    Booking *current = bookingHead;
    while (current != NULL) {
        if (current->bookingId == bookingId)
            return current;
        current = current->next;
    }
    return NULL;
}

int findFreeSeat(Train *train) {
    int i;
    for (i = 0; i < train->totalSeats; i++) {
        if (train->seats[i] == 0)
            return i + 1;
    }
    return 0;
}

void addBooking(Booking *booking) {
    Booking *current;
    booking->next = NULL;

    if (bookingHead == NULL) {
        bookingHead = booking;
        return;
    }

    current = bookingHead;
    while (current->next != NULL)
        current = current->next;

    current->next = booking;
}

void enqueueWaiting(int bookingId, int trainId) {
    WaitNode *node = (WaitNode *)malloc(sizeof(WaitNode));

    if (node == NULL) {
        printf("Memory allocation failed. Booking could not be added.\n");
        return;
    }

    node->bookingId = bookingId;
    node->trainId = trainId;
    node->next = NULL;

    if (waitRear == NULL) {
        waitFront = waitRear = node;
    } else {
        waitRear->next = node;
        waitRear = node;
    }
}

void removeWaitingEntry(int bookingId) {
    WaitNode *current = waitFront;
    WaitNode *previous = NULL;

    while (current != NULL) {
        if (current->bookingId == bookingId) {
            if (previous == NULL)
                waitFront = current->next;
            else
                previous->next = current->next;

            if (current == waitRear)
                waitRear = previous;

            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

int promoteWaitingPassenger(int trainId, int seatNo) {
    WaitNode *current = waitFront;
    WaitNode *previous = NULL;

    while (current != NULL) {
        if (current->trainId == trainId) {
            Booking *booking = findBooking(current->bookingId);

            if (booking != NULL && booking->status == WAITING) {
                booking->status = CONFIRMED;
                booking->seatNo = seatNo;
                findTrain(trainId)->seats[seatNo - 1] = booking->bookingId;

                if (previous == NULL)
                    waitFront = current->next;
                else
                    previous->next = current->next;

                if (current == waitRear)
                    waitRear = previous;

                free(current);
                printf("\nWaiting-list passenger %s has been confirmed.\n",
                       booking->passengerName);
                printf("New seat number: %d\n", booking->seatNo);
                return 1;
            }
        }

        previous = current;
        current = current->next;
    }

    return 0;
}

void displayTrains(void) {
    int i, j, available;

    printf("\n---------------- AVAILABLE TRAINS ----------------\n");
    printf("%-8s %-22s %-15s %-15s %-10s\n",
           "ID", "Train Name", "Source", "Destination", "Seats");

    for (i = 0; i < MAX_TRAINS; i++) {
        available = 0;
        for (j = 0; j < trains[i].totalSeats; j++) {
            if (trains[i].seats[j] == 0)
                available++;
        }

        printf("%-8d %-22s %-15s %-15s %d/%d\n",
               trains[i].trainId, trains[i].trainName,
               trains[i].source, trains[i].destination,
               available, trains[i].totalSeats);
    }
}

void bookTicket(void) {
    int trainId, age, seatNo;
    char name[NAME_LEN];
    Train *train;
    Booking *booking;

    displayTrains();
    trainId = readInt("\nEnter train ID: ");
    train = findTrain(trainId);

    if (train == NULL) {
        printf("Invalid train ID.\n");
        return;
    }

    readLine("Enter passenger name: ", name, sizeof(name));
    if (strlen(name) == 0) {
        printf("Passenger name cannot be empty.\n");
        return;
    }

    age = readInt("Enter passenger age: ");
    if (age < 1 || age > 120) {
        printf("Please enter a valid age (1-120).\n");
        return;
    }

    booking = (Booking *)malloc(sizeof(Booking));
    if (booking == NULL) {
        printf("Memory allocation failed. Booking could not be created.\n");
        return;
    }

    booking->bookingId = nextBookingId++;
    booking->trainId = trainId;
    strcpy(booking->passengerName, name);
    booking->age = age;
    booking->seatNo = 0;

    seatNo = findFreeSeat(train);

    if (seatNo != 0) {
        booking->status = CONFIRMED;
        booking->seatNo = seatNo;
        train->seats[seatNo - 1] = booking->bookingId;
        addBooking(booking);

        printf("\nTicket booked successfully!\n");
        printf("Booking ID: %d\n", booking->bookingId);
        printf("Train: %s\n", train->trainName);
        printf("Seat number: %d\n", seatNo);
        printf("Status: CONFIRMED\n");
    } else {
        booking->status = WAITING;
        addBooking(booking);
        enqueueWaiting(booking->bookingId, trainId);

        printf("\nAll seats are occupied. Added to waiting list.\n");
        printf("Waiting-list Booking ID: %d\n", booking->bookingId);
        printf("Status: WAITING\n");
    }
}

void cancelTicket(void) {
    int bookingId;
    Booking *booking;
    Train *train;
    int oldSeat;

    bookingId = readInt("\nEnter booking ID to cancel: ");
    booking = findBooking(bookingId);

    if (booking == NULL) {
        printf("Booking ID not found.\n");
        return;
    }

    if (booking->status == WAITING) {
        removeWaitingEntry(bookingId);
        booking->status = -1;
        printf("Waiting-list booking cancelled successfully.\n");
        return;
    }

    train = findTrain(booking->trainId);
    oldSeat = booking->seatNo;

    if (train != NULL && oldSeat >= 1 && oldSeat <= train->totalSeats)
        train->seats[oldSeat - 1] = 0;

    booking->status = -1;
    booking->seatNo = 0;
    printf("Confirmed ticket cancelled successfully.\n");

    if (train != NULL)
        promoteWaitingPassenger(booking->trainId, oldSeat);
}

void displayReservations(void) {
    Booking *current = bookingHead;
    int found = 0;

    printf("\n---------------- RESERVATION RECORDS ----------------\n");
    printf("%-10s %-22s %-10s %-10s %-12s %-10s\n",
           "BookingID", "Passenger", "TrainID", "Age", "Status", "Seat");

    while (current != NULL) {
        if (current->status != -1) {
            printf("%-10d %-22s %-10d %-10d %-12s %-10d\n",
                   current->bookingId, current->passengerName,
                   current->trainId, current->age,
                   current->status == CONFIRMED ? "CONFIRMED" : "WAITING",
                   current->seatNo);
            found = 1;
        }
        current = current->next;
    }

    if (!found)
        printf("No active reservations found.\n");
}

void searchReservation(void) {
    int bookingId;
    Booking *booking;
    Train *train;

    bookingId = readInt("\nEnter booking ID: ");
    booking = findBooking(bookingId);

    if (booking == NULL || booking->status == -1) {
        printf("Active reservation not found.\n");
        return;
    }

    train = findTrain(booking->trainId);

    printf("\n----------- RESERVATION DETAILS -----------\n");
    printf("Booking ID   : %d\n", booking->bookingId);
    printf("Passenger    : %s\n", booking->passengerName);
    printf("Age          : %d\n", booking->age);
    printf("Train ID     : %d\n", booking->trainId);
    if (train != NULL)
        printf("Train Name   : %s\n", train->trainName);
    printf("Status       : %s\n",
           booking->status == CONFIRMED ? "CONFIRMED" : "WAITING");
    if (booking->status == CONFIRMED)
        printf("Seat Number  : %d\n", booking->seatNo);
}

void displayWaitingList(void) {
    WaitNode *current = waitFront;
    Booking *booking;
    int found = 0;

    printf("\n---------------- WAITING LIST ----------------\n");
    printf("%-12s %-22s %-10s\n", "Booking ID", "Passenger", "Train ID");

    while (current != NULL) {
        booking = findBooking(current->bookingId);
        if (booking != NULL && booking->status == WAITING) {
            printf("%-12d %-22s %-10d\n",
                   booking->bookingId, booking->passengerName,
                   booking->trainId);
            found = 1;
        }
        current = current->next;
    }

    if (!found)
        printf("Waiting list is empty.\n");
}

void freeMemory(void) {
    Booking *bookingCurrent;
    WaitNode *waitCurrent;

    while (bookingHead != NULL) {
        bookingCurrent = bookingHead;
        bookingHead = bookingHead->next;
        free(bookingCurrent);
    }

    while (waitFront != NULL) {
        waitCurrent = waitFront;
        waitFront = waitFront->next;
        free(waitCurrent);
    }
    waitRear = NULL;
}

int main(void) {
    int choice;

    do {
        printf("\n===============================================\n");
        printf("       RAILWAY RESERVATION MANAGEMENT SYSTEM\n");
        printf("===============================================\n");
        printf("1. View Available Trains\n");
        printf("2. Book Ticket\n");
        printf("3. Cancel Ticket\n");
        printf("4. View All Reservations\n");
        printf("5. Search Reservation\n");
        printf("6. View Waiting List\n");
        printf("7. Exit\n");

        choice = readInt("Enter your choice: ");

        switch (choice) {
            case 1:
                displayTrains();
                break;
            case 2:
                bookTicket();
                break;
            case 3:
                cancelTicket();
                break;
            case 4:
                displayReservations();
                break;
            case 5:
                searchReservation();
                break;
            case 6:
                displayWaitingList();
                break;
            case 7:
                printf("\nThank you for using the Railway Reservation System!\n");
                freeMemory();
                break;
            default:
                printf("Invalid choice. Please select from 1 to 7.\n");
        }
    } while (choice != 7);

    return 0;
}
