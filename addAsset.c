int addAsset(assetEntry* temp)
{
        if( checkAssetExists(temp->assetId) )
                return -2;
        FILE* fp = NULL;
        int count = 0;
        char path[200]= "/home/navin/linux/assignment/29aug/miniproj/asset/";
        strcat(path,temp->assetId);

        printf("the filename is %s \n",path);
                fp = fopen(path,"wb");              // open the file 
                if( fwrite(temp,sizeof(*temp),1,fp) == 1 )
                {
                        printf("Asset added successfully \n");
                        fclose(fp);
                        return 0;
                }
                else{
                        printf(" error writting data \n");
                       if(fclose(fp))                             // close the file 
                           printf("Error closing the file\n");
                        return -1;
                }
}

