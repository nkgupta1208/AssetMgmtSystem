int unAssignAsset(char* id)
{
        FILE* fp = NULL;
        DIR* dir1 = NULL;
        assetEntry data;
        char file[200]= "/home/navin/linux/assignment/29aug/miniproj/asset/";
        int items = 0;
        strcat(file,id);

        fp = fopen(file,"r+");
        if(fp==NULL){
                printf("AssetID error\n");
                return -2;
        }
        items = fread(&data,sizeof(data),1,fp);
                if(items!=1){
                        printf("\tMessage : File  Read Error \n");
                        return -2;
                }

                if(strcmp(data.ownerId,"samsung@samsung.com")==0){
                                     printf("Asset assigned to None\n");
                        fclose(fp);
                        return -1;
                }
                else{
                        strcpy(data.ownerId,defaultOwner);
                        fseek(fp, 0L, SEEK_SET);
                        fwrite(&data,sizeof(data),1,fp);
                        fclose(fp);
                        return 0;
               }
}

