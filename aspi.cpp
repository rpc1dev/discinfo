//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "aspi_w32.h"
#include "scsidefs.h"

#pragma hdrstop

//---------------------------------------------------------------------------


#ifdef CDVDinfo_DEBUG
  FILE *debug_file;
#endif

HANDLE hDll;
DWORD (*pfnGetASPI32SupportInfo)(void);
DWORD (*pfnSendASPI32Command)(LPSRB);

SCSI_adapter Adapters[MAXADAPTERS];
BYTE         NofAdapters = 0;

CDINFO cd;

int count = 0;

void GetProfileInfo(  LPCDREC cdrec )
{
  HANDLE heventSRB;
  CDREC cdrecTmp;
  SRB_ExecSCSICmd s;
  BYTE buf[65534];
  DWORD dwStatus;

  if ( cdrec )
  {
    cdrecTmp = *cdrec;

    heventSRB = CreateEvent( NULL, TRUE, FALSE, NULL );

    memset( &s, 0, sizeof( s ) );
    memset( buf, 0, 65534 );
    s.SRB_Cmd        = SC_EXEC_SCSI_CMD;
    s.SRB_HaID       = cdrecTmp.ha;
    s.SRB_Target     = cdrecTmp.tgt;
    s.SRB_Lun        = cdrecTmp.lun;
    s.SRB_Flags      = SRB_DIR_IN | SRB_EVENT_NOTIFY;
    s.SRB_BufLen     = 65534;
    s.SRB_BufPointer = buf;
    s.SRB_SenseLen   = SENSE_LEN;
    s.SRB_CDBLen     = 10; /*GET CONFIGURATION 10 bytes long...*/
    s.SRB_PostProc   = (LPVOID)heventSRB;
    s.CDBByte[0]     = SCSI_GET_CONFIG;
    s.CDBByte[1]     = 0; /*RT*/
    s.CDBByte[2]     = 0;   /*starting number*/
    s.CDBByte[3]     = 0x1E;   /*startting number*/
    s.CDBByte[7]     = 0xFF;   /*allocation length */
    s.CDBByte[8]     = 0xFE; /*allocation length */


    ResetEvent( heventSRB );
    dwStatus = pfnSendASPI32Command( (LPSRB)&s );
    if ( dwStatus == SS_PENDING )
    {
      WaitForSingleObject( heventSRB, DEFWAITLEN );
    }
    CloseHandle( heventSRB );

    *cdrec = cdrecTmp;
  }
}


void GetRPCInfo(  LPCDREC cdrec )
{
  HANDLE heventSRB;
  CDREC cdrecTmp;
  SRB_ExecSCSICmd s;
  BYTE buf[100];
  DWORD dwStatus;
  char outBuf[101];


  #ifdef CDVDinfo_DEBUG
  write_debug_info("GetRPCInfo Start\r\n");
  #endif


  if ( cdrec )
  {
    cdrecTmp = *cdrec;

    heventSRB = CreateEvent( NULL, TRUE, FALSE, NULL );

    memset( &s, 0, sizeof( s ) );
    memset( buf, 0, 100 );
    s.SRB_Cmd        = SC_EXEC_SCSI_CMD;
    s.SRB_HaID       = cdrecTmp.ha;
    s.SRB_Target     = cdrecTmp.tgt;
    s.SRB_Lun        = cdrecTmp.lun;
    s.SRB_Flags      = SRB_DIR_IN | SRB_EVENT_NOTIFY;
    s.SRB_BufLen     = 100;
    s.SRB_BufPointer = buf;
    s.SRB_SenseLen   = SENSE_LEN;
    s.SRB_CDBLen     = 12; /*REPORT KEY command is 12 bytes long...*/
    s.SRB_PostProc   = (LPVOID)heventSRB;
    s.CDBByte[0]     = SCSI_REPORT_KEY;
    s.CDBByte[7]     = 0;
    s.CDBByte[8]     = 0;
    s.CDBByte[9]     = 10; /*allocation length */
    s.CDBByte[10]    = 0x08; /*key format = 0x08h*/

    ResetEvent( heventSRB );
    dwStatus = pfnSendASPI32Command( (LPSRB)&s );
    if ( dwStatus == SS_PENDING )
    {
      WaitForSingleObject( heventSRB, DEFWAITLEN );
    }
    CloseHandle( heventSRB );

    if(buf[1]>=6)
    {
      #ifdef CDVDinfo_DEBUG
      write_debug_info("Received RPC answer from drive, this is a DVD drive\r\n");
      #endif

      cdrecTmp.info.nofUserChanges = buf[4] & 0x07;
      cdrecTmp.info.nofVendorReset = ((buf[4] & 0x38) >> 3);
      cdrecTmp.info.typeCode       = ((buf[4] & 0xC0) >> 6);
      cdrecTmp.info.regionMask     = buf[5];
      cdrecTmp.info.RPCScheme      = buf[6];
      cdrecTmp.info.RPCInfoChecked = 1;
    }

    memcpy( cdrecTmp.info.ReportKeyData, &buf[0], 20 );

    //  FILE *fp = fopen( "rpc.dat", "wb" );
    //  fwrite( buf, 1, 100, fp );
    //  fclose( fp );

    *cdrec = cdrecTmp;
  }
}


void GetDriveInfo( BYTE ha, BYTE tgt, BYTE lun, LPCDREC cdrec )
{
  HANDLE heventSRB;
  CDREC cdrecTmp;
  SRB_ExecSCSICmd s;
  BYTE buf[56];
  DWORD dwStatus;

  #ifdef CDVDinfo_DEBUG
  write_debug_info("\r\nGetDriveInfo Started");
  #endif

  if ( cdrec )
  {
    cdrecTmp = *cdrec;

    heventSRB = CreateEvent( NULL, TRUE, FALSE, NULL );

    memset( &cdrecTmp.info, 0, sizeof(CDINFO) );
    memset( &s, 0, sizeof( s ) );
    memset( buf, 0, 56 );
    s.SRB_Cmd        = SC_EXEC_SCSI_CMD;
    s.SRB_HaID       = ha;
    s.SRB_Target     = tgt;
    s.SRB_Lun        = lun;
    s.SRB_Flags      = SRB_DIR_IN | SRB_EVENT_NOTIFY;
    s.SRB_BufLen     = 56;
    s.SRB_BufPointer = buf;
    s.SRB_SenseLen   = SENSE_LEN;
    s.SRB_CDBLen     = 6;  /*INQUIRY COMMAND is 6 bytes long*/
    s.SRB_PostProc   = (LPVOID)heventSRB;
    s.CDBByte[0]     = SCSI_INQUIRY;
    s.CDBByte[4]     = 56;

  #ifdef CDVDinfo_DEBUG
  write_debug_info("\r\nGetDriveInfo.......");
  #endif

    ResetEvent( heventSRB );
    dwStatus = pfnSendASPI32Command( (LPSRB)&s );
    if ( dwStatus == SS_PENDING )
    {
      WaitForSingleObject( heventSRB, DEFWAITLEN );
    }
    CloseHandle( heventSRB );

    // FILE *fp = fopen( "inquiry.dat", "wb" );
    // fwrite( buf, 1, 100, fp );
    // fclose( fp );

    memcpy( cdrecTmp.info.vendor, &buf[8], 8 );
    memcpy( cdrecTmp.info.prodId, &buf[16], 16 );
    memcpy( cdrecTmp.info.rev, &buf[32], 4 );
    memcpy( cdrecTmp.info.vendSpec, &buf[36], 20 );
    memcpy( cdrecTmp.info.InquiryData, &buf[0], 56 );
    memcpy( cdrecTmp.info.AnsiVersion, &buf[2], 1 );
    cdrecTmp.info.AnsiVersion[0] &= 0x07;

    *cdrec = cdrecTmp;

    #ifdef CDVDinfo_DEBUG
  write_debug_info("OK\r\n");
  #endif
  }
  #ifdef CDVDinfo_DEBUG
  write_debug_info("GetDriveInfo Ended");
  #endif

}

void FindDevices( LPCDLIST cd  )
{
  HANDLE hEvent;
  int NofHostAdapters, HAcounter, TargetCounter, LunCounter;

  NofHostAdapters = getNumAdapters();

  #ifdef CDVDinfo_DEBUG
  write_debug_info("Checking NofHostAdapters\r\n");
  #endif

  //printf( "Number of Host Adapters = %d\r\n", NofHostAdapters );


  SRB_GDEVBlock sd;


  for(HAcounter=0;HAcounter<NofHostAdapters;HAcounter++)
  {
    for(TargetCounter=0;TargetCounter<=7;TargetCounter++)
    {
      for(LunCounter=0; LunCounter<=7 && cd->num < cd->max; LunCounter++)
      {
        memset( &sd, 0, sizeof( sd ) );
        sd.SRB_Cmd    = SC_GET_DEV_TYPE;
        sd.SRB_HaID   = HAcounter;
        sd.SRB_Target = TargetCounter;
        sd.SRB_Lun    = LunCounter;
        pfnSendASPI32Command( (LPSRB)&sd );

        hEvent = CreateEvent( NULL, TRUE, FALSE, NULL );

        if ( sd.SRB_Status == SS_PENDING )
        {
          WaitForSingleObject( hEvent, INFINITE );
        }

        CloseHandle( hEvent );

        if( sd.SRB_Status == SS_COMP )
        {
          if(sd.SRB_DeviceType == 0x05)   /*if CDROM Drive*/
          {
            cd->cd[cd->num].ha = sd.SRB_HaID;
            cd->cd[cd->num].tgt = sd.SRB_Target;
            cd->cd[cd->num].lun = sd.SRB_Lun;
            memset( cd->cd[cd->num].id, 0, MAXIDLEN+1 );
            GetDriveInfo( sd.SRB_HaID, sd.SRB_Target, sd.SRB_Lun, &(cd->cd[cd->num]) );
            cd->num++;
            #ifdef CDVDinfo_DEBUG
            write_debug_info("\r\nDetected a CDROM or DVD drive");
            #endif
        //    printf( "CDROM Unit found at %d:%d:%d %d\r\n", sd.SRB_HaID,
        //          sd.SRB_Target, sd.SRB_Lun, sd.SRB_DeviceType );
          }
          else
          {
            #ifdef CDVDinfo_DEBUG
            write_debug_info("\r\nDetected device, but not a CDROM or DVD drive");
            #endif
          }
        }
        else
        {
         #ifdef CDVDinfo_DEBUG
         write_debug_info(".");
         #endif

        }
      }
    }
  }
  #ifdef CDVDinfo_DEBUG
  write_debug_info("\r\nChecking NofHostAdapters Ended\r\n");
  #endif

}

int getNumAdapters( void )
{
  DWORD d;
  BYTE bHACount;
  BYTE bASPIStatus;
  char Message[500] = "";

  d = pfnGetASPI32SupportInfo();
  bASPIStatus = HIBYTE(LOWORD(d));
  bHACount    = LOBYTE(LOWORD(d));

  if ( bASPIStatus != SS_COMP || bASPIStatus == SS_NO_ADAPTERS || bHACount == 0 )
  {

    #ifdef CDVDinfo_DEBUG
    write_debug_info("ERROR something is wrong with the ASPI driver (1)\n\r");
    #endif

    strcat(Message, "ERROR something is wrong with the ASPI driver!   ReInstall ASPI-layer\n\r");
    strcat(Message, "For WIN9x/NT download ASPI driver from www.adaptec.com\n\r");
    strcat(Message, "For WIN2000/XP download wnaspi32.dll from \n\r");
    strcat(Message, "http://www.cdvdinfo.subnet.dk/wnaspi32.dll\n\r");
    strcat(Message, "and copy the file to same directory as cdvdinfo.exe\n\r");
    Application->MessageBox(Message, "ERROR", MB_OK);
  }
  return (int)bHACount;
}

int loadASPI( void )
{
   hDll = LoadLibrary( "WNASPI32.DLL" );
  if ( !hDll )
  {
    #ifdef CDVDinfo_DEBUG
    write_debug_info("Error loading wnaspi32.dll\n\r");
    #endif

   char Message[500] = "";
    strcat(Message, "Error loading wnaspi32.dll!   ReInstall ASPI-layer\n\r");
    strcat(Message, "For WIN9x/NT download ASPI driver from www.adaptec.com\n\r");
    strcat(Message, "For WIN2000/XP download wnaspi32.dll from \n\r");
    strcat(Message, " http://www.cdvdinfo.subnet.dk/wnaspi32.dll\n\r");
    strcat(Message, " and copy the file to same directory as cdvdinfo.exe\n\r");
    Application->MessageBox(Message, "ERROR", MB_OK);
    return FALSE;
  }

  pfnGetASPI32SupportInfo =
    (DWORD(*)(void))GetProcAddress( hDll, "GetASPI32SupportInfo" );
  pfnSendASPI32Command =
    (DWORD(*)(LPSRB))GetProcAddress( hDll, "SendASPI32Command" );

  if ( !pfnGetASPI32SupportInfo || !pfnSendASPI32Command)
  {
    #ifdef CDVDinfo_DEBUG
    write_debug_info("Error WNASPI32.DLL is not working");
    #endif

   char Message[500] = "";
    strcat(Message, "Error WNASPI32.DLL is not working!   ReInstall ASPI-layer\n\r");
    strcat(Message, "For WIN9x/NT download ASPI driver from www.adaptec.com\n\r");
    strcat(Message, "For WIN2000/XP download wnaspi32.dll from \n\r");
    strcat(Message, " http://www.cdvdinfo.subnet.dk/wnaspi32.dll\n\r");
    strcat(Message, " and copy the file to same directory as cdvdinfo.exe\n\r");
    Application->MessageBox(Message, "ERROR", MB_OK);
    return FALSE;
  }
  return TRUE;
}

#define _GEN_CDPARMS 0
int readCDParameters( LPCDREC cdrec /* HCDROM hCD, BOOL bChangeMask*/ )
{
  HANDLE h;
  SRB_ExecSCSICmd s;
  DWORD d,calc;
  BYTE b[256];
  int lenData;
  BYTE *p;
  BYTE *pMax = b + 256;
  LPSENSEMASK psm;
  CDREC cdrecTmp;

#if _GEN_CDPARMS
  FILE *fp;
#endif

  #ifdef CDVDinfo_DEBUG
  write_debug_info("readCDParameters Start\r\n");
  #endif

  if ( cdrec )
  {
    cdrecTmp  =  *cdrec;
    cdrecTmp.smRead = FALSE;
    psm = &cdrecTmp.sm;
    memset( psm, 0, sizeof( SENSEMASK ) );


    h = CreateEvent( NULL, TRUE, FALSE, NULL );
    memset( &s, 0, sizeof( s ) );
    memset( b, 0xFF, 256 );
    s.SRB_Cmd      = SC_EXEC_SCSI_CMD;
    s.SRB_HaID     = cdrecTmp.ha;
    s.SRB_Target   = cdrecTmp.tgt;
    s.SRB_Lun      = cdrecTmp.lun;
    s.SRB_Flags    = SRB_DIR_IN | SRB_EVENT_NOTIFY;
    s.SRB_BufLen   = 256;
    s.SRB_BufPointer = b;
    s.SRB_CDBLen   = 12;
    s.SRB_PostProc = (LPVOID)h;
    s.CDBByte[0]   = 0x5A;
    s.CDBByte[2]   = 0x3F;
    s.CDBByte[7]   = 0x01;
    s.CDBByte[8]   = 0x00;

    /* do we want just a mask of changable items? */
   //? if ( bChangeMask )
   //   s.CDBByte[2] |= 0x40;

    ResetEvent( h );
    d = pfnSendASPI32Command( (LPSRB)&s );
    if ( d == SS_PENDING )
      {
        WaitForSingleObject( h, 500 );
      }
    CloseHandle( h );

    if ( s.SRB_Status != SS_COMP )
      {
        #ifdef CDVDinfo_DEBUG
        write_debug_info("readCDParameters failed\r\n");
        #endif

         return FALSE;
      }

  #if _GEN_CDPARMS
    fp = fopen( "cdparms.dat", "wb" );
    if ( fp )
      {
        fwrite( b, 1, 256, fp );
        fclose( fp );
      }
  #endif

    lenData = ((unsigned int)b[0] << 8) + b[1];

    /* set to first sense mask, and then walk through the masks */
    p = b + 8;
    while( (p < &(b[2+lenData])) && (p < pMax) )
      {
        BYTE which;

        which = p[0] & 0x3F;
        switch( which )
          {
          case READERRREC:
            psm->rerAvail = TRUE;
            memcpy( psm->rer, p, p[1]+2 );
            break;
          case CDRPARMS:
            psm->cpmAvail = TRUE;
            memcpy( psm->cpm, p, p[1]+2 );
            break;
          case CDRAUDIOCTL:
            psm->cacmAvail = TRUE;
            memcpy( psm->cacm, p, p[1]+2 );
            break;
          case CDRCAPS:
            #ifdef CDVDinfo_DEBUG
            write_debug_info("readCDParameters CAPS received\r\n");
            #endif

            psm->ccsmAvail = TRUE;
            memcpy( psm->ccsm, p, p[1]+2 );
            if(psm->ccsm[2] & 0x01) cdrecTmp.info.cdRReadSupport = TRUE;
            if(psm->ccsm[2] & 0x02) cdrecTmp.info.cdRwReadSupport = TRUE;
            if(psm->ccsm[2] & 0x04) cdrecTmp.info.cdMetod2ReadSupport = TRUE;
            if(psm->ccsm[2] & 0x08) cdrecTmp.info.dvdRomReadSupport = TRUE;
            if(psm->ccsm[2] & 0x10) cdrecTmp.info.dvdRReadSupport = TRUE;
            if(psm->ccsm[2] & 0x20) cdrecTmp.info.dvdRamReadSupport = TRUE;
            if(psm->ccsm[3] & 0x01) cdrecTmp.info.cdRWriteSupport = TRUE;
            if(psm->ccsm[3] & 0x02) cdrecTmp.info.cdRwWriteSupport = TRUE;
            if(psm->ccsm[3] & 0x10) cdrecTmp.info.dvdRWriteSupport = TRUE;
            if(psm->ccsm[3] & 0x20) cdrecTmp.info.dvdRamWriteSupport  = TRUE;

            if( cdrecTmp.info.dvdRomReadSupport ||
                cdrecTmp.info.dvdRReadSupport   ||
                cdrecTmp.info.dvdRamReadSupport ||
                cdrecTmp.info.dvdRWriteSupport  ||
                cdrecTmp.info.dvdRamWriteSupport )
              cdrecTmp.info.dvdDrive = TRUE;
            if( cdrecTmp.info.cdRReadSupport       ||
                cdrecTmp.info.cdRwReadSupport      ||
                cdrecTmp.info.cdMetod2ReadSupport  ||
                cdrecTmp.info.cdRWriteSupport      ||
                cdrecTmp.info.cdRwWriteSupport )
              cdrecTmp.info.cdDrive = TRUE;
            if( cdrecTmp.info.cdRReadSupport       ||
                cdrecTmp.info.cdRwReadSupport      ||
                cdrecTmp.info.cdMetod2ReadSupport)
              cdrecTmp.info.cdRRead = TRUE;
            if( cdrecTmp.info.cdRWriteSupport      ||
                cdrecTmp.info.cdRwWriteSupport )
              cdrecTmp.info.cdRWrite = TRUE;

            calc = ((DWORD)psm->ccsm[8] << 8) + (DWORD)psm->ccsm[9];
            cdrecTmp.info.maxSpeedReadCd =  (long)calc / 175 ;
            calc = ((DWORD)psm->ccsm[18] << 8) + (DWORD)psm->ccsm[19];
            cdrecTmp.info.maxSpeedWriteCd = (long)calc / 175 ;
            break;
          }
        p += (p[1] + 2);
      }

    cdrecTmp.smRead = TRUE;
    *cdrec = cdrecTmp;
    return TRUE;
  }
  return TRUE;
}

#ifdef CDVDinfo_DEBUG
void start_debug()
{
  debug_file = fopen( "debug.dat", "w" );
  write_debug_info("Debug started\n\r");
  fclose( debug_file );
}

void write_debug_info(char *debug_string)
{
  debug_file = fopen( "debug.dat", "a" );
  if ( debug_file  )
  {
    fwrite( debug_string, 1, strlen(debug_string), debug_file );
    fclose( debug_file );
  }
}
#endif

