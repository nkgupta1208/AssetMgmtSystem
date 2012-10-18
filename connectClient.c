int sockfd;
struct hostent *he;
struct sockaddr_in their_addr; // connector's address information
if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
                perror("socket");
                exit(1);
}
else
        printf("Socket is created whose descriptor is %d\n",sockfd);
        their_addr.sin_family = AF_INET; // host byte order
        their_addr.sin_port = htons(atoi(argv[2])); // short, network byte order
        their_addr.sin_addr.s_addr = inet_addr(argv[1]);
        memset(their_addr.sin_zero, '\0', sizeof their_addr.sin_zero);

        if (connect(sockfd, (struct sockaddr *)&their_addr,sizeof(their_addr)) == -1) {
                perror("connect");
                exit(1);
        }

