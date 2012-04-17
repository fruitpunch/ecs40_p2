#include "permission.h"
typedef struct Directory{

	struct Directory *previousDir;
	char name[80];
	int time, subN;
	Permission *umask;
	struct Directory *subDir[3];
}Directory;