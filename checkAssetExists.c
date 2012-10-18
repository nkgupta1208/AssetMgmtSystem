int checkAssetExists(char* id)
{
        FILE* fp = NULL;
        int count = 0;
        assetEntry temp;

        DIR* dir1;
        char path[200]= "/home/navin/linux/assignment/29aug/miniproj/asset";
        struct dirent *myfile;
        dir1  = opendir(path);
        if(dir1){
                  printf("directory :%s is now opened\n",path);
                  printf("Listing files\n");
                  printf("\tFile Name : \t Inode Number \n");
                while( ( myfile=readdir(dir1) )){
                        printf("\t->%s\n",myfile->d_name);
                        if(strcmp(myfile->d_name,id)==0){
                                printf("Asset  Id Exists \n ");
                                closedir(dir1);
                                return 1;
                        }
                }
        }
        printf("asset not found\n");
        closedir(dir1);
        return 0;
}

