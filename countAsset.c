int countAsset()
{
        FILE* fp = NULL;
        int count = 0;
        DIR* dir1;
        char path[200]= "/home/navin/linux/assignment/29aug/miniproj/asset";
        struct dirent *myfile;
        dir1  = opendir(path);
        if(dir1){
	        while( myfile=readdir(dir1) )
                        count++;
	        closedir(dir1);
		count-=2;
                return count;
        }
        else
		return 0;
}

