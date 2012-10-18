int assignOwner(assetEntry temp)
{
        FILE* fp = NULL;
        DIR* dir1 = NULL;
        assetEntry data;
        char path[200]= "/home/navin/linux/assignment/29aug/miniproj/asset/";
        int items = 0;
        strcat(path,temp.assetId);
        
        fp = fopen(path,"r+");
        if(fp==NULL){
                printf("AssetID error\n");
                return -2;
        }

        items = fread(&data,sizeof(data),1,fp);
                if(items!=1)
                        printf("\tMessage : File  Read Error \n");
                
                if(strcmp(data.ownerId,"samsung@samsung.com")==0){
                        strcpy(data.ownerId,temp.ownerId);
                        fseek(fp, 0L, SEEK_SET);
                        fwrite(&data,sizeof(data),1,fp);
                        fclose(fp);
                        return 0;
                }
                else{
                        printf("Asset already assigned to %s\n",data.ownerId);
                        fclose(fp);
                        return -1;
                }
}

