int removeAsset(char* id)
{
        FILE* fp = NULL;
        char file[200]= "/home/navin/linux/assignment/29aug/miniproj/asset/";
        int items = 0;
        strcat(file,id);

        fp = fopen(file,"r");
        if( NULL ==  fp ){
                printf("Asset Not Found in DataBase\n");
                return -1;
        }
        else
                fclose(fp);

        int status = remove(file);
        if( 0 ==  status){
                printf("Message : %s asset removed successfully \n");
        return status;
        }
        else{
                printf("Message: File remove error \n");
                return -2;
        }
}

