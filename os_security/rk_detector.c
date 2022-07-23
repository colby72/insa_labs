#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>

/*
1ere liste: recupérer la liste des process d'une snap process
2eme liste: on brute force tous les PIDs (env. 65560) et on stocke les PIDs qui
répondent dans une liste
*/

struct plist {
    int pid;
    char name[256];
} typedef plist;

void SetDebugPrivilege()
{
    //Declaration des variables
    TOKEN_PRIVILEGES privilege;
    LUID Luid;
    HANDLE handle1;
    HANDLE handle2;

    // On modifie son PROPRE token pour avoir le droit de sortir de notre session,
    // pour se faire, il faut d'avoir ouvrir notre propore processus
    handle1 = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetCurrentProcessId());

    // Ensuite, on modifie notre token
    OpenProcessToken(handle1, TOKEN_ALL_ACCESS, &handle2);

    // SE_DEBUG_NAME est le privilege que l'on veut activer. Même si on est admin, il n'est pas active par défaut
    // comme on l'a vu dans Process Explorer
    LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &Luid);
    privilege.PrivilegeCount = 1;
    privilege.Privileges[0].Luid = Luid;
    privilege.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    AdjustTokenPrivileges(handle2, FALSE, &privilege, sizeof(privilege), NULL, NULL);
    CloseHandle(handle2);
    CloseHandle(handle1);
}

int main()
{
    // METHODE 1
    HANDLE proc_snap;
    PROCESSENTRY32 proc;
    int nb1 = 0;
    plist list1[256];

    printf("#### METHOD 1 ####\n");

    proc_snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (proc_snap == INVALID_HANDLE_VALUE) {
        printf("getting processes failed !\n");
        return -1;
    }

    if (Process32First(proc_snap, &proc)) {
        do {
            printf("PID: %d\tName: %s\n", proc.th32ProcessID, proc.szExeFile);
            list1[nb1].pid = proc.th32ProcessID;
            strncpy(list1[nb1].name, proc.szExeFile, sizeof(proc.szExeFile));
            nb1++;
        } while (Process32Next(proc_snap, &proc));
    }

    printf("Nombre de processus: %d\n", nb1);
    CloseHandle(proc_snap);

    // METHODE 2
    int i, nb2=0;
    HANDLE proc2;
    HMODULE hMod;
    DWORD cbNeeded;
    char name_buff[48];
    plist list2[256];

    printf("\n#### METHOD 2 ####\n");

    for (i=0; i<65501; i++) {
        if (i%4==0) {
            proc2 = OpenProcess(PROCESS_ALL_ACCESS, 0, i);
            if ((proc2 != INVALID_HANDLE_VALUE) && (proc2 != NULL)) {
                if (EnumProcessModules(proc2, &hMod, sizeof(hMod), &cbNeeded)) {
                    GetModuleBaseName(proc2, hMod, name_buff, 48);
                }
                printf("PID: %d\tName: %s\n", i, name_buff);
                list2[nb2].pid = i;
                strncpy(list2[nb2].name, name_buff, sizeof(name_buff));
                nb2++;
            }
        }
    }

    printf("Nombre de processus: %d\n", nb2);
    CloseHandle(proc2);

    // DIFF des deux listes
    int j;
    BOOL rk;

    printf("\n#### Possible Rootkits ####\n");

    for (i=0; i<nb1; i++) {
            rk = TRUE;
            for (j=0; j<nb2; j++) {
                if (list1[i].pid == list2[j].pid)
                    rk = FALSE;
            }
            if (rk)
                    printf("Possible Rootkit:\t%d\t%s\n", list1[i].pid, list1[i].name);
    }
    system("pause");
    return 0;
}
