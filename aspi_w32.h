

typedef void *LPSRB;


#define CDVDinfo_DEBUG

#define MAXADAPTERS 10
extern BYTE         NofAdapters;


#define  MAXIDLEN   64
#define  MAXCDLIST  8

#define DEFWAITLEN    4000

/***************************************************************************
 ** SCSI MISCELLANEOUS EQUATES
 ***************************************************************************/
#define SENSE_LEN                 14     /* Default sense buffer length    */
#define SRB_DIR_SCSI              0x00   /* Direction determined by SCSI   */
#define SRB_POSTING               0x01   /* Enable ASPI posting            */
#define SRB_ENABLE_RESIDUAL_COUNT 0x04   /* Enable residual byte count     */
                                         /* reporting                      */
#define SRB_DIR_IN                0x08   /* Transfer from SCSI target to   */
                                         /* host                           */
#define SRB_DIR_OUT               0x10   /* Transfer from host to SCSI     */
                                         /* target                         */
#define SRB_EVENT_NOTIFY          0x40   /* Enable ASPI event notification */
#define RESIDUAL_COUNT_SUPPORTED  0x02   /* Extended buffer flag           */
#define MAX_SRB_TIMEOUT       1080001u   /* 30 hour maximum timeout in sec */
#define DEFAULT_SRB_TIMEOUT   1080001u   /* use max.timeout by default     */


/***************************************************************************
 ** ASPI command definitions
 ***************************************************************************/
#define SC_HA_INQUIRY             0x00   /* Host adapter inquiry           */
#define SC_GET_DEV_TYPE           0x01   /* Get device type                */
#define SC_EXEC_SCSI_CMD          0x02   /* Execute SCSI command           */
#define SC_ABORT_SRB              0x03   /* Abort an SRB                   */
#define SC_RESET_DEV              0x04   /* SCSI bus device reset          */
#define SC_SET_HA_PARMS           0x05   /* Set HA parameters              */
/* This is not used under NT/WIN2000 according to microsoft!/*#define SC_GET_DISK_INFO          0x06   /* Get Disk                       */
#define SC_RESCAN_SCSI_BUS        0x07   /* Rebuild SCSI device map        */
#define SC_GETSET_TIMEOUTS        0x08   /* Get/Set target timeouts        */

/***************************************************************************
 ** SRB Status
 ***************************************************************************/
#define SS_PENDING                0x00   /* SRB being processed            */
#define SS_COMP                   0x01   /* SRB completed without error    */
#define SS_ABORTED                0x02   /* SRB aborted                    */
#define SS_ABORT_FAIL             0x03   /* Unable to abort SRB            */
#define SS_ERR                    0x04   /* SRB completed with error       */
#define SS_INVALID_CMD            0x80   /* Invalid ASPI command           */
#define SS_INVALID_HA             0x81   /* Invalid host adapter number    */
#define SS_NO_DEVICE              0x82   /* SCSI device not installed      */
#define SS_INVALID_SRB            0xE0   /* Invalid parameter set in SRB   */
#define SS_OLD_MANAGER            0xE1   /* ASPI manager doesn't support   */
                                         /* windows                        */
#define SS_BUFFER_ALIGN           0xE1   /* Buffer not aligned (replaces   */
                                         /* SS_OLD_MANAGER in Win32)       */
#define SS_ILLEGAL_MODE           0xE2   /* Unsupported Windows mode       */
#define SS_NO_ASPI                0xE3   /* No ASPI managers               */
#define SS_FAILED_INIT            0xE4   /* ASPI for windows failed init   */
#define SS_ASPI_IS_BUSY           0xE5   /* No resources available to      */
                                         /* execute command                */
#define SS_BUFFER_TO_BIG          0xE6   /* Buffer size too big to handle  */
#define SS_BUFFER_TOO_BIG         0xE6   /* Correct spelling of 'too'      */
#define SS_MISMATCHED_COMPONENTS  0xE7   /* The DLLs/EXEs of ASPI don't    */
                                         /* version check                  */
#define SS_NO_ADAPTERS            0xE8   /* No host adapters to manager    */
#define SS_INSUFFICIENT_RESOURCES 0xE9   /* Couldn't allocate resources    */
                                         /* needed to init                 */
#define SS_ASPI_IS_SHUTDOWN       0xEA   /* Call came to ASPI after        */
                                         /* PROCESS_DETACH                 */
#define SS_BAD_INSTALL            0xEB   /* The DLL or other components    */
                                         /* are installed wrong            */

#define READERRREC    0x01
#define CDRPARMS      0x0D
#define CDRAUDIOCTL   0x0E
#define CDRCAPS       0x2A

typedef struct
 {
   BYTE  HaID;
   BYTE  TargetID;
   BYTE  LunID;
 }
 SCSI_adapter;

     typedef struct
    {
        BYTE        SRB_Cmd;            // ASPI command code
        BYTE        SRB_Status;         // ASPI command status byte
        BYTE        SRB_HaId;           // ASPI host adapter number
        BYTE        SRB_Flags;          // ASPI request flags
        DWORD       SRB_Hdr_Rsvd;       // Reserved, MUST = 0
    } SRB_Header;

/***************************************************************************
 ** SRB - HOST ADAPTER INQUIRIY - SC_HA_INQUIRY (0)
 ***************************************************************************/

 typedef struct
    {
        BYTE        SRB_Cmd;            // ASPI command code = SC_HA_INQUIRY
        BYTE        SRB_Status;         // ASPI command status byte
        BYTE        SRB_HaId;           // ASPI host adapter number
        BYTE        SRB_Flags;          // ASPI request flags
        DWORD       SRB_Hdr_Rsvd;       // Reserved, MUST = 0
        BYTE        HA_Count;           // Number of host adapters present
        BYTE        HA_SCSI_ID;         // SCSI ID of host adapter
        BYTE        HA_ManagerId[16];   // String describing the manager
        BYTE        HA_Identifier[16];  // String describing the host adapter
        BYTE        HA_Unique[16];      // Host Adapter Unique parameters
        WORD        HA_Rsvd1;
    } SRB_HAInquiry, *PSRB_HAInquiry;

/***************************************************************************
 ** SRB - GET DEVICE TYPE - SC_GET_DEV_TYPE (1)
 ***************************************************************************/
typedef struct
{
  BYTE     SRB_Cmd;           /* 00/000 ASPI cmd code == SC_GET_DEV_TYPE   */
  BYTE     SRB_Status;        /* 01/001 ASPI command status byte           */
  BYTE     SRB_HaID;          /* 02/002 ASPI host adapter number           */
  BYTE     SRB_Flags;         /* 03/003 Reserved, must = 0                 */
  DWORD    SRB_Hdr_Rsvd;      /* 04/004 Reserved, must = 0                 */
  BYTE     SRB_Target;        /* 08/008 Target's SCSI ID                   */
  BYTE     SRB_Lun;           /* 09/009 Target's LUN number                */
  BYTE     SRB_DeviceType;    /* 0a/010 Target's peripheral device type    */
  BYTE     SRB_Rsvd1;         /* 0b/011 Reserved, must = 0                 */
} SRB_GDEVBlock;

/***************************************************************************
 ** SRB - EXECUTE SCSI COMMAND - SC_EXEC_SCSI_CMD (2)
 ***************************************************************************/

typedef struct
{
  BYTE     SRB_Cmd;           /* 00/000 ASPI cmd code == SC_EXEC_SCSI_CMD  */
  BYTE     SRB_Status;        /* 01/001 ASPI command status byte           */
  BYTE     SRB_HaID;          /* 02/002 ASPI host adapter number           */
  BYTE     SRB_Flags;         /* 03/003 Reserved, must = 0                 */
  DWORD    SRB_Hdr_Rsvd;      /* 04/004 Reserved, must = 0                 */
  BYTE     SRB_Target;        /* 08/008 Target's SCSI ID                   */
  BYTE     SRB_Lun;           /* 09/009 Target's LUN                       */
  WORD     SRB_Rsvd1;         /* 0a/010 Reserved for alignment             */
  DWORD    SRB_BufLen;        /* 0c/012 Data Allocation Length             */
  BYTE FAR *SRB_BufPointer;   /* 10/016 Data Buffer Pointer                */
  BYTE     SRB_SenseLen;      /* 14/020 Sense Allocation Length            */
  BYTE     SRB_CDBLen;        /* 15/021 CDB Length                         */
  BYTE     SRB_HaStat;        /* 16/022 Host Adapter Status                */
  BYTE     SRB_TargStat;      /* 17/023 Target Status                      */
  VOID FAR *SRB_PostProc;     /* 18/024 Post routine                       */
  BYTE     SRB_Rsvd2[20];     /* 1c/028 Reserved, must = 0                 */
  BYTE     CDBByte[16];       /* 30/048 SCSI CDB                           */
  BYTE SenseArea[SENSE_LEN+2]; /* 40/064 Request Sense buffer              */
} SRB_ExecSCSICmd, *PSRB_ExecSCSICmd, FAR *LPSRB_ExecSCSICmd;


typedef struct
{
  char vendor[9];
  char prodId[17];
  char rev[5];
  char vendSpec[21];
  char RPCInfoChecked;
  char nofUserChanges;
  char nofVendorReset;
  char typeCode;
  unsigned char regionMask;
  char RPCScheme;
  char ReportKeyData[21];
  char InquiryData[101];
  char AnsiVersion[1];
  char cdRReadSupport;
  char cdRwReadSupport;
  char cdMetod2ReadSupport;
  char dvdRomReadSupport;
  char dvdRReadSupport;
  char dvdRamReadSupport;
  char cdRWriteSupport;
  char cdRwWriteSupport;
  char dvdRWriteSupport;
  char dvdRamWriteSupport;
  char dvdDrive;
  char cdDrive;
  char maxSpeedReadCd;
  char maxSpeedWriteCd;
  char cdRRead;
  char cdRWrite;
} CDINFO, *PCDINFO, FAR *LPCDINFO;

typedef BYTE ReadErrorRecoveryParmsMask[8];
typedef BYTE CDRomParmsMask[8];
typedef BYTE CDRomCapabilitiesStatusMask[20];
typedef BYTE CDRomAudioControlMask[16];

typedef struct
{
  ReadErrorRecoveryParmsMask  rer;
  CDRomParmsMask              cpm;
  CDRomCapabilitiesStatusMask ccsm;
  CDRomAudioControlMask       cacm;
  BOOL                        rerAvail;
  BOOL                        cpmAvail;
  BOOL                        ccsmAvail;
  BOOL                        cacmAvail;
} SENSEMASK, *PSENSEMASK, FAR *LPSENSEMASK;

typedef struct
{
  BYTE      ha;
  BYTE      tgt;
  BYTE      lun;
  BYTE      pad;
  char      id[MAXIDLEN + 1];
  CDINFO    info;
  /*AKA hack below*/
  BYTE      readType;
  BOOL      used;
  BOOL      bMSF;
  BOOL      bInit;
  SENSEMASK sm;
  BOOL      smRead;
  //CDREADFN  pfnRead;
 // CDDEINIT  pfnDeinit;
  int       numCheck;     // used for jitter correction
  int       numOverlap;   // ...
  int       readMode;

} CDREC, *PCDREC, FAR *LPCDREC;

typedef struct
{
  BYTE      max;
  BYTE      num;
  CDREC     cd[MAXCDLIST];
} CDLIST, *PCDLIST, FAR *LPCDLIST;


int  loadASPI( void );
int  getNumAdapters( void );
void FindDevices( LPCDLIST cd );
void GetDriveInfo( BYTE ha, BYTE tgt, BYTE lun, LPCDREC cdrec );
void GetRPCInfo(  LPCDREC cdrec );
void GetProfileInfo(  LPCDREC cdrec );
int readCDParameters( LPCDREC cdrec /* HCDROM hCD, BOOL bChangeMask*/ );
void write_debug_info(char *debug_string);
void start_debug();
