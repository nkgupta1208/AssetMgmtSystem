int getAssetByMySingleId( char* myid, int socket )
{
           FILE* fp = NULL;
           assetEntry data;
           DIR *dir1,*dir2;
           char path[200]= "/home/navin/linux/assignment/29aug/miniproj/asset";
           char assetpath[200]= "/home/navin/linux/assignment/29aug/miniproj/asset/";
           struct dirent *myfile;
           int count = 0;
           int len = strlen(assetpath);
		dir2 = opendir(path);   

		if(dir2){
		 while( ( myfile=readdir(dir2) )){
                       if(strcmp(myfile->d_name,".")==0 || strcmp(myfile->d_name,"..")==0 )
                           continue;
                       strcat(assetpath,myfile->d_name);
                       if(NULL==(fp=fopen(assetpath,"r")))
                          printf("\tMessage : Error opening file\n");
                           fread(&data,sizeof(data),1,fp);
                           if( 0==strcmp(data.ownerId,myid) ){
                      		count++;
				printf("%s %s \n",data.ownerId,myid);
			}
			if(fclose(fp))
                          printf("Error closing file\n ");
                      	assetpath[len]='\0';
              }
              printf("\t\t\tout of while loop\n");
              closedir(dir2);
		}
	printf("count is %d \n",count);
	send(socket,&count,sizeof(count),0);


          dir1  = opendir(path);
          if(dir1){
                    printf("\tdirectory :%s is now opened\n",path);
                    printf("\tS.No: \t Id \t Name \t Serial \t Owner \n");
               while( ( myfile=readdir(dir1) )){
                       if(strcmp(myfile->d_name,".")==0 || strcmp(myfile->d_name,"..")==0 )
                           continue;
                       strcat(assetpath,myfile->d_name);
                       if(NULL==(fp=fopen(assetpath,"r")))
                          printf("\tMessage : Error opening file\n");
                           fread(&data,sizeof(data),1,fp);
			   if( 0==strcmp(data.ownerId,myid) )
				send(socket,&data,sizeof(data),0);
                      	  if(fclose(fp))
                          printf("Error closing file\n ");
                      assetpath[len]='\0';
              }
              printf("\t\t\tout of while loop\n");
              if(closedir(dir1))
                  printf("\t\tMessage : Error closing directory\n");
          }
	  return count;
}

