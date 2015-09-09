#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    char * cuser_id_str;
    uid_t euid, uid;
    gid_t gid, egid;
    
    cuser_id_str = (char *) cuserid(NULL);
    printf("cuserid: %s\n", cuser_id_str);

    uid = getuid();
    euid = geteuid();
    gid = getgid();
    egid = getegid();

    // print them...

    return EXIT_SUCCESS;
}

