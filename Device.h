#ifndef __SENDCOMMAND_H__
#define __SENDCOMMAND_H__

#define OS_UNKNOWN  -1
#define OS_WIN95    0
#define OS_WIN98    1
#define OS_WINNT35  2
#define OS_WINNT4   3
#define OS_WIN2K    4

struct Inquiry
{
	unsigned char devType;
	char interfx[1];
	char reserved1[6];
	char Vendor[49];
};

class Device
{
public:
	static DWORD makeDeviceList(void);

	Device *next;
	Device *prev;
    
	// V prvem koraku
	char letter[1];
	BYTE HaId;
	BYTE Target;
	BYTE Lun;
	char name[50];
	char interfacex[1];
	DWORD type;
	char vendor_name[25];
	char firmware_version[5];
	char extra_info[29];

	// V zanki Toshiba
	bool if_toshiba; // For Toshiba drives
	char fw_code[25]; // For Toshiba drives
	char tosh_model[35]; // For Toshiba drives

	// V zanki capability MODE SENSE 10/GET CONFIGURATION
	bool cdRRead;
	bool cdRWRead;
	bool cdMethod2Read;
	bool dvdRomRead;
	bool dvdRRead;
	bool dvdRWRead;    
	bool dvdRamRead;
	bool dvdPRRead;
	bool dvdPRWRead;
        
	bool cdRWrite;
	bool cdRWWrite;
	bool testWrite;
	bool dvdRWrite;
	bool dvdRWWrite;
	bool dvdRamWrite;
	bool dvdPRWrite;
	bool dvdPRWWrite;

 	bool audioplay;
  	bool composite;
  	bool digport1;
  	bool digport2;
  	bool mode1form;
   	bool mode2form;
   	bool multisession;
   	bool buffunder;
   	bool ISRC;
   	bool UPC;
   	bool barcode;
   	bool mtrainier;
    char mechanism[50];

	int read_s;
	int write_s;

	bool isdvdDrive;
	bool iscdDrive;
	bool iscdRRead;
	bool iscdRWrite;

    int buffersize;
    int levels;

	char serial[12];

	bool drive_status;
	char region_status[30];
	int user;
	int manufactor;
	char current_region[10];
    
	DWORD SendCommand(BYTE *CDBByte, BYTE CDBLen, BYTE SRB_Flags,
		BYTE *BufPointer, DWORD BufLen) const;
	DWORD Device::SendSPTICommand(BYTE *CDBByte, BYTE CDBLen, DWORD dwFlags, DWORD InOut,
	    BYTE *BufPointer, DWORD BufLen) const;
};


extern Device *devices;
extern int deviceCount;
//extern char LogFileDir[255];

extern HANDLE event;

#endif // __SENDCOMMAND_H__
