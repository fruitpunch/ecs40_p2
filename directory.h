typedef struct Directory{

	struct Directory *previousDir;
	char name[80];
	int time, umask, subN;
	struct Directory *subDir[3];
}Directory;