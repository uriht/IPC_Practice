#include "selvan_head.h"

int no_of_nodes;
int ins_flag;
int del_flag;

struct Node *head = NULL;
struct Node *ptr = NULL;
int  val, pos;
char choice;

int main() {
    int client_fd, len;
    struct sockaddr_un server_addr;

    // create a Unix domain socket
    client_fd = socket(AF_UNIX, SOCK_STREAM, 0);

    // configure the server address
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, "/tmp/mysocket", sizeof(server_addr.sun_path) - 1);

    // connect to the server
    len = sizeof(server_addr);
    connect(client_fd, (struct sockaddr*)&server_addr, len);
    do{
        printf ("\nChoose a option from given menu:\n");
        printf ("1. Insert Node\n");
        printf ("2. Delete Node\n");
        printf ("3. Display linked list\n");
        printf ("4. Exit\n");
        printf ("Enter your choice: ");
        scanf (" %c", &choice);
        switch (choice) {
            case '1':
                printf ("Enter the value: ");
                scanf (" %d", &val);
                printf ("Enter position to insert (0 for beginning, -1 for end): ");
                scanf ("%d", &pos);
                head = insert (head, val, pos);
                if (ins_flag == 0)
                    printf ("Node inserted successfully! at position %d\n", pos);
                break;

            case '2':
                printf ("Enter position to insert (0 for beginning, -1 for end): ");
                scanf (" %d", &pos);
                head = delete (head, pos);
                if (del_flag == 0)
                    printf ("Node deleted successfully! at position %d\n", pos);
                break;

            case '3':
                display (head);
                break;

            case '4':
                printf ("Bye Bye.. Tata\n");
                break;

            default:
                printf ("Invalid choice!\n");
                break;
        }
    } while( choice != '4' );

    // receive a value from the server
    int value;
    read(client_fd, &value, sizeof(int));
    printf("Received value from server: %d\n", value);

    // create a node to add to the linked list
    // Node node;
    // node.data = 10;
do{
    printf ("\nChoose a option from given menu:\n");
    printf ("1. Find value at position\n");
    printf ("2. Exit\n");
    display (head);

    printf ("Enter your choice: ");
    scanf (" %c", &choice);
    switch (choice) {
        case '1':
            ptr = findValueAtPosition (head, value);
            if (ptr != NULL)
                // send the serialized node to the server
                write(client_fd, &ptr, sizeof(Node));
            break;

        case '2':
            printf ("Bye Bye.. Tata\n");
            break;

        default:
            printf ("Invalid choice!\n");
            break;
    }
} while (choice != '2');


    // receive a response from the server
    char response[50];
    read(client_fd, response, 50);
    printf("Server response: %s\n", response);

    // close the connection
    close(client_fd);

    return 0;
}

