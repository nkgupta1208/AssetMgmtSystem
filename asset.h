	#define ERROR   -1
	#define MAX_CLIENTS     20
	#define MAXDATA 1024

	typedef struct Asset{
	        char assetId[100];
        	char name[100];
	        char serial[100];
        	char ownerId[100];
	}assetEntry;

	char fileName[200]  = "/home/navin/linux/assignment/29aug/miniproj/asset/";
	char userFiles[200]  = "/home/navin/linux/assignment/29aug/miniproj/users/";
        const char logFile[200]   = "/home/navin/linux/assignment/29aug/miniproj/asset/log.txt";
	const char defaultOwner[] = "samsung@samsung.com";
	
        const char msg[] = "----------------------------MENU-----------------------\n \
        \t1. ADD ASSET\n\
        \t2. LIST ASSETS\n\
        \t3. ASSIGN ASSET\n\
        \t4. UNASSIGN ASSET\n\
        \t5. REMOVE  ASSET\n\
        \t6. FIND ASSET BY MYSINGLE ID\n\
        \t7. FIND ASSET BY ASSET ID\n\
        \t8. EXIT/DISCONNECT\n\
        --------------------------------------------------------\n\
                        Please Enter your choice\n\
        --------------------------------------------------------\n";

