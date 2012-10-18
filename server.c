#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<error.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdbool.h>
#include<sys/stat.h>
#include<dirent.h>
#include<errno.h>
#include<fcntl.h>
// project headers includes
#include "asset.h"
// project cpp includes
#include "addAsset.c"
#include "checkAssetExists.c"
#include "countAsset.c"
#include "listAsset.c"
#include "assignOwner.c"
#include "removeAsset.c"
#include "unAssignAsset.c"
#include "getAssetById.c"
#include "getAssetByMySingleId.c"

int main(int argc, char **argv)
{
	struct sockaddr_in server;
	struct sockaddr_in  client;
	int sock, new;
	int sockaddr_len = sizeof(struct sockaddr_in);
	int data_len;
	char data[MAXDATA];
	char id[100],myid[100];
	int choice,count,numbytes,retval;
	assetEntry temp;
	assetEntry* tptr = NULL;
	bool isConnected = false;
	bool isListening = false;
	/* Here we create a socket for server */
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) == ERROR){
		perror("server socket: ");
		exit(-1);
	}
	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[1]));
	server.sin_addr.s_addr = INADDR_ANY;
//	bzero(&server.sin_zero, 8);
	/* Now bind the sock with server */		
	if((bind(sock, (struct sockaddr *)&server, sockaddr_len)) == ERROR){
		perror("bind : ");
		exit(-1);
	}
	if((listen(sock, MAX_CLIENTS)) == ERROR){
		perror("listen");
		exit(-1);
	}
	else
		isListening = true;
	/* port binded now server listening on the specified port*/

	while( isListening ){
	    if((new = accept(sock, (struct sockaddr *)&client, &sockaddr_len)) == ERROR){
		perror("accept");
	 	exit(-1);
	    }
	    else{
	      isConnected = true;
	      printf("New Client connected from port no %d and IP %s\n",ntohs(client.sin_port), inet_ntoa(client.sin_addr));
	    }
  	    send(new, msg, strlen(msg), 0);	/* send the menu message to take choice */
		while( isConnected ){
            		numbytes=recv(new, &choice, MAXDATA, 0);	/* receive the choice given by client */  
			printf("Bytes Received : %d Choice received is %d\n",numbytes,choice);
			if(choice == 1)
			{
				numbytes=recv(new,&temp,MAXDATA,0);
				retval = addAsset(&temp);	
				printf("return value of  add asset is %d\n",retval);
				send(new,&retval,sizeof(retval),0);
				printf("\n%d records added successully\n",retval);
			}
			else if (choice == 2){
	//			printf("Feature Disabled \n ");
			        count=listAsset(new);	
				printf("%d assets listed on client\n",count);
			}	
			else if(choice == 3){	// assign asset
				numbytes = recv(new,&temp,MAXDATA,0);
				retval = assignOwner(temp);
				send(new,&retval,sizeof(retval),0);		
			}
			else if(choice == 4){	// un-assign asset
				numbytes = recv(new,&id,MAXDATA,0);	
				retval = unAssignAsset(&id);
				if(retval == 0 )
                                        printf("Asset %s unassigned  successfully\n",id);
                                if( retval == -1 )
                                        printf("asset owned by none\n");
                                if( retval == -2 )
                                        printf("assetId incorrect : asset doesnot exist \n");
				send(new,&retval,sizeof(retval),0);
			}
			else if(choice == 5){  // remove asset
                        	count = countAsset();
				send(new,&count,sizeof(count),0);
				printf("Total assets = %d\n",count);
				recv(new,&id,sizeof(id),0);
				retval = removeAsset(&id);
				send(new,&retval,sizeof(retval),0);
			}
			else if(choice == 6){ // search by MySingle id 
                        	recv(new,&myid,sizeof(myid),0);
				retval = getAssetByMySingleId(&myid,new);
				if(retval >0)
					printf("\t%d assets found and listed on client\n",retval);

			}
			else if(choice == 7){ // search by Asset Id
                		numbytes = recv(new,&id,MAXDATA,0);
				printf("\tThe id  is %s\n",id);
				retval = getAssetById(&temp,&id);
				printf("\tReturn value is %d\n",retval);
				send(new,&retval,sizeof(retval),0);	
				if( 0==retval ){
      			                printf("\tThe asset Details are :");
                                        printf("\tName  : %s\n",temp.name);
                                        printf("\tId    : %s\n",temp.assetId);
                                        printf("\tSerial: %s\n",temp.serial);
                                        printf("\tOwner : %s\n",temp.ownerId);
					send(new,&temp,sizeof(temp),0);
				}
				else
					printf("Asset %s not found \n",id);
			}
			else if(choice == 8){	//Exit (Disconnect)
				isConnected = false;
				close(new);
				printf("Client disconnected\n");
				break;
                        }
			else if(choice==9){/*
				FILE* fp1 = fopen("/home/navin/log.txt","w+");
				char d;
			
				
				
				while(1){
					rc=recv(new,&d,1,0);
					printf(" %d ",rc);
					if(rc<0)
					break;
					 fwrite(&d,sizeof(d),1,fp1);
					}
					fclose(fp1);
				printf("written files");
				char aa[8];
				rc=recv(new,aa,8,0);
				if(rc)
					{
					printf("exit");
				}
				*/
			}
			else {
                                printf("Service Not Available : Please enter correct choice\n");
                        }
		}	// end of while for accepting the choice from new client 
	}	// end of server listening loop
	close(sock);	
return 0;
}

