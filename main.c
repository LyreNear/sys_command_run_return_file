#include <include.h>

int main() {
    char cmd[20] = {"ll"} ,*pcCmdRetFilename = NULL;
    pcCmdRetFilename = sys_command_run_return_file(cmd);
    if (NULL != pcCmdRetFilename)
        free(pcCmdRetFilename);
    return 0;
}

