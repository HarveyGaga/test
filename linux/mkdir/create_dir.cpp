#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>

#define err(msg) perror(msg)
#if 0
static void imkdirs(const char *dir)
{
	char tmp[1024];
	char *p;

        if (strlen(dir) == 0 || dir == NULL) {
                printf("strlen(dir) is 0 or dir is NULL./n");
                return;
        }

        memset(tmp, 0, sizeof(tmp));
        strncpy(tmp, dir, strlen(dir));
        if (tmp[0] == '/' && tmp[1]== '/') 
                p = strchr(tmp + 2, '/');
        else 
                p = strchr(tmp, '/');

        if (p) {
                *p = '/0';
                mkdir(tmp,0777);
  chdir(tmp);
        } else {
                mkdir(tmp,0777);
                chdir(tmp);
                return;
        }

        mkdirs(p + 1);
}
#endif
int mkdirs(const char *dir) {
    std::string strPath;

    if (strlen(dir) == 0 || dir == NULL) {
        printf("strlen(dir) is 0 or dir is NULL./n");
        return -1;
    }

    if (access(dir, R_OK | W_OK | F_OK) == 0) {
        printf("%s allready exists.", dir);
        return 0;
    }

    strPath = dir;

    size_t nPos = 0, nIndex = 0;
    std::string strSub;
    while ((nPos = strPath.find('/', nIndex)) != std::string::npos) {
        strSub = strPath.substr(0, nPos);
        if (!strSub.empty() && strSub != "." && strSub != "..") {
		if (access(strSub.c_str(), 0) != 0) {
            if (mkdir(strSub.c_str(), 0755) == -1) {
		printf("mkdir[%s] failed:%s", strSub.c_str(), strerror(errno));
                return -1;
            }
		printf("mkdir[%s] ok.\n", strSub.c_str());
		}
	}
	
        nIndex = nPos + 1;

        while (strPath.length() > nIndex && strPath.at(nIndex) == '/') {
            strPath.replace(nPos, 2, "/");
        }
    }

    return 0;
}

int main(void)
{
	mkdirs("./1//2//3//4");

	return 0;
}

