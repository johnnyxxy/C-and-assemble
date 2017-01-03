#pragma once
#pragma warning(disable:4201)
#pragma warning(disable:4100)
#define NDIS_WDM
#define NDIS630
#include<wdm.h>
#include<ndis.h>


/*#define RECV_POOL_MAX 300*/
#define PACKET_DATA_MAX 1518
#define FILTER_MAJOR_NDIS_VERSION   NDIS_FILTER_MAJOR_VERSION
#define FILTER_MINOR_NDIS_VERSION   NDIS_FILTER_MINOR_VERSION
#define NETCFGGUID L"{5cbf81bd-5055-47cd-9055-a76b2b4e3697}"
#define SERVICENAME L"ZlzNdisLwf"
#define DEVICE_NAME L"\\Device\\Zlz Ndis6.30 Filter Kernel-Mode Device"
#define SYM_NAME L"\\??\\Zlz Ndis6.30 Filter SymbolLink"
#define PATH_MAX 255

#define IOCTL_SHOWADAPTER (ULONG)CTL_CODE(FILE_DEVICE_UNKNOWN,0x911,METHOD_BUFFERED,FILE_WRITE_DATA|FILE_READ_DATA) 
#define IOCTL_GETRAWDATA (ULONG)CTL_CODE(FILE_DEVICE_UNKNOWN,0x912,METHOD_BUFFERED,FILE_WRITE_DATA|FILE_READ_DATA) 

#define PACKET_TYPE_ADAPTERINFO 1
#define PACKET_TYPE_NETPACKET 2

PDRIVER_DISPATCH devcon;
typedef struct _AdapterInfo
{
	WCHAR DevPathName[PATH_MAX];
	WCHAR DevName[PATH_MAX];
}AdapterInfo, *PAdapterInfo;
typedef struct _IO_Packet
{
	int Type;
	union 
	{
		struct 
		{
			int Num;
			AdapterInfo AdapterInfo[20];
		}ShowAdapter;
		struct
		{
			int Num;
			UCHAR Buffer[300][2000];
		}Net_Packet;
		unsigned u;
	}Packet;
}IO_Packet,*PIO_Packet;
typedef struct _S_PACKET
{
	LIST_ENTRY PacketList;
	int size;
	int MdlNumber;
	BOOLEAN IsSendPacket;
	PNET_BUFFER_LIST buffer;
	PMDL *mdllist;
}S_PACKET, *PS_PACKET;
typedef struct _FILTER_CONTEXT
{
	char magic[8];
	NDIS_STRING DevPathName;                    //设备路径名
	NDIS_STRING DevName;                        //设备名字 
	NDIS_HANDLE FilterHandle;                   //过滤设备区别句柄
	NDIS_HANDLE NetBufferPool;                  //包池句柄
	BOOLEAN IsRunning;                          //该过滤器是否处于运行中
	BOOLEAN IsFiltering;                        //该过滤器是否对数据包进行过滤
	int FliterIndex;                            //过滤句柄在GLOBAL.context中的索引数
	int CurrentRecvNum;                         //当前接收链表存在的包数
	LIST_ENTRY PacketRecvList;                  //接收链表
	KSPIN_LOCK NetBufferListLock;               //链表同步访问锁
}FILTER_CONTEXT, *PFILTER_CONTEXT;
typedef struct _GLOBAL
{
	NDIS_HANDLE DriverHandle;          //注册过滤设备后获得的句柄
	int contextnum;                    //绑定设备数
	PFILTER_CONTEXT context[20];       //绑定设备上下文
	PDEVICE_OBJECT FilterDev;          //R3 R0 I/O传输设备
	UNICODE_STRING symname;            //链接符号名
	int RecvPoolMax;                   //包池最大大小
}GLOBAL, *PGLOBAL;
typedef struct _MAC
{
	UCHAR dst[6];
	UCHAR sou[6];
	UCHAR type[2];
}MAC,*PMAC;
GLOBAL Global;