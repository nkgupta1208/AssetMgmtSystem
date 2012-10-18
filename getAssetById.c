int getAssetById(assetEntry* data,char* id)
{
	if(!checkAssetExists(id))
		return -2;

        FILE* fp = NULL;
        char path[200]= "/home/navin/linux/assignment/29aug/miniproj/asset/";
        strcat(path,id);
	printf("The file opened is %s \n",path);
	fp = fopen(path,"r");
	if(fp){
		printf("File opened .. Reading data \n");
		fread(data,sizeof(*data),1,fp);
		fclose(fp);
		return 0;
	}
        return -1;
}

