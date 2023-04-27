#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

int main() {
    int server_fd, client_fd, len;
    struct sockaddr_un server_addr, client_addr;

    Node* head = NULL; // initialize the linked list

    // create a Unix domain socket
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);

    // configure the server address
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, "/tmp/mysocket", sizeof(server_addr.sun_path) - 1);
    unlink(server_addr.sun_path);

    // bind the socket to the server address
    len = sizeof(server_addr);
    bind(server_fd, (struct sockaddr*)&server_addr, len);

    // listen for incoming connections
    listen(server_fd, 5);

    while(1) {
        printf("Waiting for client...\n");

        // accept a new client connection
        len = sizeof(client_addr);
        client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &len);

        printf("Client connected.\n");

        // receive the serialized node from the client
        Node node;
        read(client_fd, &node, sizeof(Node));

        // deserialize the node and add it to the linked list
        node.next = head;
        head = &node;

        printf("The Linked List: %d , %p", node.data, node.next);

        // send a response to the client
        write(client_fd, "Node added to linked list.", 26);

        // close the client connection
        close(client_fd);
    }

    return 0;
}

