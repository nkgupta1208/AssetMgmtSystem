#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdbool.h>
				// project headers includes
#include "asset.h"

int main(int argc, char *argv[])
{
	int sockfd, numbytes;
	char buf[MAXDATA];
	char id[100],myid[100];
	struct hostent *he;
	struct sockaddr_in their_addr; // connector's address information
	int check =0;
	int sock,choice,count,retval;
	bool isConnected = false;
	assetEntry temp;
	if (argc != 3) {
		fprintf(stderr,"usage: ./client <host_ip> <host_port>\n");
		exit(1);
	}
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
	else
		isConnected = true;

	if ((numbytes=recv(sockfd, buf, MAXDATA, 0)) == -1) {
		perror("recv");
		exit(1);
	}
	buf[numbytes] = '\0';
	printf("%s\n",buf);
        
	while( isConnected ){
			char ch[10];
                        printf("Enter your choice from menu\n");
	                scanf("%s",ch);
			if(isdigit(ch[0]))
				choice = atoi(ch);
			else 
				choice = 10;
			send(sockfd,&choice,sizeof(choice),0);
			if(choice == 1){	
	        	        printf("Enter the name of asset(Max 100 chars)\n");
		                        scanf("%s",temp.name);
	                	printf("Enter the id of asset : %s \n",temp.name);
		                        scanf("%s",temp.assetId);
		                printf("Enter the serial of asset :%s\n",temp.name);
		               	        scanf("%s",temp.serial);
                		printf("Enter the owner of asset : %s  [default : samsung@samsung ] :\n",temp.name);
		                        scanf("%s",temp.ownerId);
		               send(sockfd, &temp, sizeof(temp), 0);	// send the input details to server
			       recv(sockfd,&retval,sizeof(retval),0);
			       if( retval == 0 )
					printf("\tMessage : Asset added successfully\n\n");
			       else  if(retval == -2)
					printf("\tMessage : AssetId already Exists(Please enter valid data again)\n");
			       else  if(retval == -1)
					printf("\tMessage : File write Error\n");
			}	
			else if (choice == 2){
//				printf("Feature Disabled\n");
				count = 0;
				printf("Listing Available assets on the server \n ");
				printf("S.No : \t Name  \t  Id  \t  Serial  \t  OwnerId  \n");
				assetEntry t;	
				int totalfiles = 0;

				numbytes=recv(sockfd,&totalfiles,sizeof(totalfiles),0);
				if( 0==totalfiles )
					printf("No assets available\n");
				while(totalfiles--){
					count++ ;
					numbytes=recv(sockfd,&t,MAXDATA,0);
					if(numbytes<0)
						printf("Error receiving data\n");
				printf(" %d  : \t %s  \t  %s  \t  %s  \t  %s  \n",count,t.assetId,t.name,t.serial,t.ownerId);
				}
			}
			else if(choice == 3){	// assign asset
				temp.name[0]   = "\0";
				temp.serial[0] = "\0";
				printf("Enter the assetId\t");
				scanf("%s",temp.assetId);
				printf("Enter your mysingleId\t");
				scanf("%s",temp.ownerId);
				send(sockfd,&temp,sizeof(temp),0);
				recv(sockfd,&retval,sizeof(retval),0);
				if(retval == 0 )
					printf("Asset : %s assigned to %s successfully\n",temp.assetId,temp.ownerId);
				if( retval == -1 )
					printf("asset already owned by some person\n");
				if( retval == -2 )
					printf("assetId incorrect : asset doesnot exist \n");

			}	
			else if(choice == 4){
                                printf("Enter the assetId\t");
                                scanf("%s",id);
                                send(sockfd,&id,sizeof(id),0);
                                recv(sockfd,&retval,sizeof(retval),0);
                                if(retval == 0 )
                                        printf("Asset %s unassigned  successfully\n",id);
                                if( retval == -1 )
                                        printf("asset owned by none\n");
                                if( retval == -2 )
                                        printf("assetId incorrect : asset doesnot exist \n");
			}
			else if(choice == 5){
				recv(sockfd,&count,sizeof(count),0);
                                printf("Total assets available are %d\n",count);
				printf("Enter the id of asset to remove \n");
				scanf("%s",id);
				send(sockfd,&id,sizeof(id),0);
				recv(sockfd,&retval,sizeof(retval),0);
				if(retval == 0)
					printf("Asset %s removed successfully \n",id);
				else if(retval == -1)
					printf("\tAsset Id Error : Asset does not exist \n");
				else if(retval == -2)
					printf("\tMessage : Asset Not removed :You dont have permission\n");
				
                        }
			else if(choice == 6){
                      	printf("\tEnter your mySingle Id \t ");
			scanf("%s",myid);
			send(sockfd, &myid, sizeof(myid), 0);
			recv(sockfd, &count, sizeof(count), 0);	
			int cnt =0;
			assetEntry t;
			if(count)
			      printf("\tS.No: \t Id \t Name \t Serial \t Owner \n");
			while(count--)
			{
			    ++cnt;
			    recv(sockfd,&t,sizeof(t),0);
     			    if(numbytes<0)	printf("Error receiving data\n");
                            printf(" %d  : \t %s  \t  %s  \t  %s  \t  %s  \n",cnt,t.assetId,t.name,t.serial,t.ownerId);
			}
			printf("\t %d assets owned by %s\n",cnt,myid);
			}
			else if(choice == 7){
                        	printf("Enter the assetId\t");	
				scanf("%s",id);
				send(sockfd,&id,sizeof(id),0);
				recv(sockfd,&retval,sizeof(retval),0);
				if(retval == 0 ){
					printf("Asset %s Exists\n",id);
					recv(sockfd, &temp, sizeof(temp),0);
					printf("\tThe asset Details are :");
					printf("\tName  : %s\n",temp.name);
					printf("\tId    : %s\n",temp.assetId);
					printf("\tSerial: %s\n",temp.serial);
					printf("\tOwner : %s\n",temp.ownerId);
				}
				else if( retval == -2)
					printf("Asset not available\n");
				else if(retval == -1)
					printf("Error in receiving \n");
			}
			else if(choice == 8){
                                isConnected = false;
				printf("Warning : Client disconnecting from server\n");
                        }
			else if(choice==9){ /*
				FILE* fp = fopen("/home/navin/linux/sh/log.txt","r");
				int hasData = 1,count=0;
				char buffer;
				send(sockfd,&hasData,sizeof(hasData),0);
				while(!feof(fp){
					count=fread(&buffer,sizeof(buffer),1,fp);
					send(sockfd,&buffer,sizeof(buffer),0);
                                           }
					fclose(fp);
					printf("file sent");
					char a[8]="quit";	
					
					send(sockfd,a,8,0);
				
				*/

			}
			else {
                                printf("Please enter correct choice\n");
                        }
	}
	close(sockfd);
return 0;
}
