#include <include.h>

char* sys_command_run_return_file(char *_acCMD) {
    FILE *fFp = NULL;
    char *pcTmp = NULL, acCmdRetBuff[MAX_BUFFER_LENGTH] = {}, acTmp[MAX_FILE_PATH_LENGTH] = {};
    size_t iRead = 0, iFdTmp = 0, iWrite = 0;

    strcat(_acCMD, " 2>&1 ");
    pcTmp = (char *) malloc(MAX_FILE_PATH_LENGTH);
    snprintf(pcTmp, MAX_FILE_PATH_LENGTH, "/tmp/sys_cmd_ret_tmp-XXXXXX");

    if (0 > (iFdTmp = mkstemp(pcTmp))) {
        perror("Create tempfile error");
        free(pcTmp);
        exit(1);
    }

    snprintf(pcTmp, MAX_FILE_PATH_LENGTH, "/proc/self/fd/%ld", iFdTmp);
    readlink(pcTmp, acTmp, MAX_FILE_PATH_LENGTH);
    snprintf(pcTmp, MAX_FILE_PATH_LENGTH, "%s", acTmp);

    if (NULL == (fFp = popen(_acCMD, "r"))) {
        goto cleanup;
    }

    while (0 < (iRead = fread(acCmdRetBuff, sizeof(char), MAX_BUFFER_LENGTH - 1, fFp))) {
        iWrite = write(iFdTmp, acCmdRetBuff, iRead);
        if (iRead != iWrite) {
            printf("Write file error : READ %ld, WRITE %ld\n", iRead, iWrite);
            goto cleanup;
        }
    }

    if (0 == iRead) {
        printf("Finish running cmd %s, result in %s\n", _acCMD, pcTmp);
        close(iFdTmp);
        pclose(fFp);
        return pcTmp;
    }

    printf("Read result error! Cleanup.\n");

cleanup:
    if (0 != remove(pcTmp)) {
        printf("Delete file %s failed!\n", pcTmp);
    }
    free(pcTmp);
    close(iFdTmp);
    pclose(fFp);
    return NULL;
}
