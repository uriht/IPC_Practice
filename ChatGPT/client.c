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

    // create a new node to send to the server
    Node node;
    node.data = 42;
    node.next = NULL;

    // serialize the node and send it to the server
    write(client_fd, &node, sizeof(Node));

    // receive a response from the server
    char buffer[256];
    read(client_fd, buffer, 256);

    printf("Server response: %s\n", buffer);

    // close the connection
    close(client_fd);

    return 0;
}

