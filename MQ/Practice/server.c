#include "selvan_head.h"


struct Node* head = NULL;
int  value, pos;
char choice;
int val;
int main(int argc, char **argv){

    fd_set readfds;
    char buffer[MSG_BUFFER_SIZE];
    int msgq_fd = 0;

    if(argc <= 1){
        printf("provide a reciepient msgQ name : format </msgq-name>\n");
        return 0;
    }

    /*To set msgQ attributes*/
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    if ((msgq_fd  = mq_open (argv[1], O_RDONLY | O_CREAT, QUEUE_PERMISSIONS, &attr)) == -1) {
        printf ("Server: mq_open failed, errno = %d", errno);
        exit (1);
    }
    do{
        printf ("\nChoose a option from given menu:\n");
        printf ("1. Insert Node\n");
        printf ("2. Delete Node\n");
        printf ("3. Display linked list\n");
        printf ("4. Find value at position\n");
        printf ("5. Exit\n");
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
                while(1){
                    FD_ZERO(&readfds);
                    FD_SET( msgq_fd, &readfds);
                    printf("Server blocked on select()....\n");
                    select(msgq_fd + 1, &readfds, NULL, NULL, NULL);
                    if(FD_ISSET(msgq_fd, &readfds)){
                        printf("Msg recvd msgQ %s\n", argv[1]);

                        memset(buffer, 0, MSG_BUFFER_SIZE);
                        if (mq_receive (msgq_fd, buffer, MSG_BUFFER_SIZE, NULL) == -1) {
                            printf ("mq_receive error, errno = %d\n", errno);
                            exit (1);
                        }
                        printf("Msg recieved from Queue = %s\n", buffer);

                        int value = atoi(buffer);
                        if(value == -1) break;
                    }
                }
                struct Node *ptr = findValueAtPosition (head, value);
                if (ptr != NULL)
                  printf ("The value is => %d\n", ptr->data);
                break;
            case '5':
                printf ("Bye Bye.. Tata\n");
                break;

            default:
                printf ("Invalid choice!\n");
                break;
        }
    } while( choice != '4' );




    mq_close(msgq_fd);
    mq_unlink(argv[1]);

    return 0;
}
