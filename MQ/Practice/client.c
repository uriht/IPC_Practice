#include "selvan_head.h"

int main(int argc, char **argv){

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

    if ((msgq_fd  = mq_open (argv[1], O_WRONLY | O_CREAT, QUEUE_PERMISSIONS, &attr)) == -1) {
        printf ("Client: mq_open failed, errno = %d", errno);
        exit (1);
    }

    printf("Enter a value to find in the linked list: ");
    memset(buffer, 0, MSG_BUFFER_SIZE);
    scanf("%s", buffer);

    if (mq_send (msgq_fd, buffer, strlen (buffer) + 1, 0) == -1) {
        perror ("Client: Not able to send message to server");
        exit (1);
    }

    mq_close(msgq_fd);
    return 0;
}
