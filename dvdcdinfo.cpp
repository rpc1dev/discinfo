//---------------------------------------------------------------------------
#include <stdio.h>
#include "dvdcdinfo.h"
#include "aspi_w32.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1 *Form1;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}

//---------------------------------------------------------------------------



char CDbuf[25];
CDLIST CdList;
int cdlistIdx;  // index of currently selected drive


extern CDINFO cd;
void __fastcall TForm1::FormCreate(TObject *Sender)
{
   AnsiString calc;

   CdList.max = MAXCDLIST;

   #ifdef CDVDinfo_DEBUG
    write_debug_info("Form Create\n\r");
   #endif

   #ifdef CDVDinfo_DEBUG
    write_debug_info("Read CDVDinfo\n\r");
   #endif

   Position = poScreenCenter;

   FindDevices( &CdList );

   for(cdlistIdx = 0; cdlistIdx < CdList.num && CdList.num > 0 && CdList.num < CdList.max; cdlistIdx++ )
   {
     memcpy( CDbuf, CdList.cd[cdlistIdx].info.vendor, 8 );
     memcpy( CDbuf+8, CdList.cd[cdlistIdx].info.prodId, 16 );
     ComboBox1->Items->Add( CDbuf );
    // GetProfileInfo(  &CdList.cd[cdlistIdx]);
     GetRPCInfo(  &CdList.cd[cdlistIdx] );
     readCDParameters( &CdList.cd[cdlistIdx] );
   }

   #ifdef CDVDinfo_DEBUG
    write_debug_info("Read CDVDinfo finished\n\r");
   #endif

   cdlistIdx = 0;
   ComboBox1->ItemIndex= 0;

   Label2->Caption = "";
   Label4->Caption = "";
   Label10->Caption = "";
   Label11->Caption = "";
   Label12->Caption = "";
   Label13->Caption = "";
   Label14->Caption = "";

   if(CdList.num) /* if a drive exist */
   {
   #ifdef CDVDinfo_DEBUG
    write_debug_info("Drive exist\n\r");
   #endif

     Label2->Caption = CdList.cd[ComboBox1->ItemIndex].info.rev;
     Label4->Caption = CdList.cd[ComboBox1->ItemIndex].info.vendSpec;


     if(CdList.cd[ComboBox1->ItemIndex].info.RPCInfoChecked)
     {
       switch(CdList.cd[ComboBox1->ItemIndex].info.RPCScheme)
       {
         case 0x00:
           Label10->Caption = "No";
           break;
         case 0x01:
           Label10->Caption = "Yes";
           break;
         default:
           Label10->Caption = "unknown";
           break;
       }

       switch(CdList.cd[ComboBox1->ItemIndex].info.typeCode)
       {
         case 0x3:
           Label11->Caption = "Permanent";
           break;
         default:
           Label11->Caption = "Not permanent";
           break;
       }

       Label12->Caption = IntToStr(CdList.cd[ComboBox1->ItemIndex].info.nofUserChanges);
       Label13->Caption = IntToStr(CdList.cd[ComboBox1->ItemIndex].info.nofVendorReset);

       switch(CdList.cd[ComboBox1->ItemIndex].info.regionMask)
       {
         case 0xFF:
           Label14->Caption = "none";
           break;
         case 0xFE:
           Label14->Caption = "1";
           break;
         case 0xFD:
           Label14->Caption = "2";
           break;
         case 0xFB:
           Label14->Caption = "3";
           break;
         case 0xF7:
           Label14->Caption = "4";
           break;
         case 0xEF:
           Label14->Caption = "5";
           break;
         case 0xDF:
           Label14->Caption = "6";
           break;
         case 0xBF:
           Label14->Caption = "7";
           break;
         case 0x7F:
           Label14->Caption = "8";
           break;
         default:
           Label14->Caption = "unknown";
           break;
       }

       Label5->Visible = TRUE;
       Label6->Visible = TRUE;
       Label7->Visible = TRUE;
       Label8->Visible = TRUE;
       Label9->Visible = TRUE;
       Label10->Visible = TRUE;
       Label11->Visible = TRUE;
       Label12->Visible = TRUE;
       Label13->Visible = TRUE;
       Label14->Visible = TRUE;

     }
     else
     {
       if(  CdList.cd[ComboBox1->ItemIndex].info.cdDrive &&
           !CdList.cd[ComboBox1->ItemIndex].info.dvdDrive   )
       {
         Label9->Visible = FALSE;
         Label10->Visible = FALSE;
       }
       else
       {
         Label10->Caption = "No lock Detected";
         Label9->Visible = TRUE;
       }

       Label5->Visible = FALSE;
       Label6->Visible = FALSE;
       Label7->Visible = FALSE;
       Label8->Visible = FALSE;
       Label11->Visible = FALSE;
       Label12->Visible = FALSE;
       Label13->Visible = FALSE;
       Label14->Visible = FALSE;
     }
     StaticText1->Visible = FALSE;
     StaticText2->Visible = FALSE;
     Label15->Visible = FALSE;
     Label16->Visible = FALSE;
     if(CdList.cd[ComboBox1->ItemIndex].sm.ccsmAvail)
     {
       if( CdList.cd[ComboBox1->ItemIndex].info.cdRRead )
       {
         if(CdList.cd[ComboBox1->ItemIndex].info.maxSpeedReadCd < 100)
         {
           calc = IntToStr(CdList.cd[ComboBox1->ItemIndex].info.maxSpeedReadCd);
           Label15->Caption = calc;
           Label15->Visible = TRUE;
           StaticText1->Visible = TRUE;
         }
       }
       if( CdList.cd[ComboBox1->ItemIndex].info.cdRWrite < 100)
       {
         if(CdList.cd[ComboBox1->ItemIndex].info.maxSpeedWriteCd)
         {
           calc = IntToStr(CdList.cd[ComboBox1->ItemIndex].info.maxSpeedWriteCd);
           Label16->Caption = calc;
           Label16->Visible = TRUE;
           StaticText2->Visible = TRUE;
         }
       }
     }
   }
}


//---------------------------------------------------------------------------
void __fastcall TForm1::EditCompo(TObject *Sender)
{
   AnsiString calc;

   #ifdef CDVDinfo_DEBUG
    write_debug_info("CHANGE COMBO\n\r");
   #endif

   if(CdList.num) /* if a drive exist */
   {

     Label2->Caption = CdList.cd[ComboBox1->ItemIndex].info.rev;
     Label4->Caption = CdList.cd[ComboBox1->ItemIndex].info.vendSpec;

     GetRPCInfo(  &CdList.cd[ComboBox1->ItemIndex] );
    //  GetProfileInfo(  &CdList.cd[ComboBox1->ItemIndex]);

     if(CdList.cd[ComboBox1->ItemIndex].info.RPCInfoChecked)
     {
       switch(CdList.cd[ComboBox1->ItemIndex].info.RPCScheme)
       {
         case 0x00:
           Label10->Caption = "No";
           break;
         case 0x01:
           Label10->Caption = "Yes";
           break;
         default:
           Label10->Caption = "unknown";
           break;
       }

       switch(CdList.cd[ComboBox1->ItemIndex].info.typeCode)
       {
         case 0x3:
           Label11->Caption = "Permanent";
           break;
         default:
           Label11->Caption = "Not permanent";
           break;
       }

       Label12->Caption = IntToStr(CdList.cd[ComboBox1->ItemIndex].info.nofUserChanges);
       Label13->Caption = IntToStr(CdList.cd[ComboBox1->ItemIndex].info.nofVendorReset);

       switch(CdList.cd[ComboBox1->ItemIndex].info.regionMask)
       {
         case 0xFF:
           Label14->Caption = "none";
           break;
         case 0xFE:
           Label14->Caption = "1";
           break;
         case 0xFD:
           Label14->Caption = "2";
           break;
         case 0xFB:
           Label14->Caption = "3";
           break;
         case 0xF7:
           Label14->Caption = "4";
           break;
         case 0xEF:
           Label14->Caption = "5";
           break;
         case 0xDF:
           Label14->Caption = "6";
           break;
         case 0xBF:
           Label14->Caption = "7";
           break;
         case 0x7F:
           Label14->Caption = "8";
           break;
         default:
           Label14->Caption = "unknown";
           break;
       }
       Label5->Visible = TRUE;
       Label6->Visible = TRUE;
       Label7->Visible = TRUE;
       Label8->Visible = TRUE;
       Label9->Visible = TRUE;
       Label10->Visible = TRUE;
       Label11->Visible = TRUE;
       Label12->Visible = TRUE;
       Label13->Visible = TRUE;
       Label14->Visible = TRUE;
     }
     else
     {
       if(  CdList.cd[ComboBox1->ItemIndex].info.cdDrive &&
           !CdList.cd[ComboBox1->ItemIndex].info.dvdDrive   )
       {
         Label9->Visible = FALSE;
         Label10->Visible = FALSE;
       }
       else
       {
         Label10->Caption = "No lock Detected";
         Label9->Visible = TRUE;
       }

       Label5->Visible = FALSE;
       Label6->Visible = FALSE;
       Label7->Visible = FALSE;
       Label8->Visible = FALSE;
       Label11->Visible = FALSE;
       Label12->Visible = FALSE;
       Label13->Visible = FALSE;
       Label14->Visible = FALSE;
     }
     StaticText1->Visible = FALSE;
     StaticText2->Visible = FALSE;
     Label15->Visible = FALSE;
     Label16->Visible = FALSE;
     if(CdList.cd[ComboBox1->ItemIndex].sm.ccsmAvail)
     {
       if( CdList.cd[ComboBox1->ItemIndex].info.cdRRead )
       {
         if(CdList.cd[ComboBox1->ItemIndex].info.maxSpeedReadCd < 100)
         {
           calc = IntToStr(CdList.cd[ComboBox1->ItemIndex].info.maxSpeedReadCd);
           Label15->Caption = calc;
           Label15->Visible = TRUE;
           StaticText1->Visible = TRUE;
         }
       }
       if( CdList.cd[ComboBox1->ItemIndex].info.cdRWrite < 100 )
       {
         if(CdList.cd[ComboBox1->ItemIndex].info.maxSpeedWriteCd)
         {
           calc = IntToStr(CdList.cd[ComboBox1->ItemIndex].info.maxSpeedWriteCd);
           Label16->Caption = calc;
           Label16->Visible = TRUE;
           StaticText2->Visible = TRUE;
         }
       }
     }

   }
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#define VENDOR  "\nDRIVE VENDOR          : "
#define PROID   "\nDRIVE PROID           : "
#define REV     "\nDRIVE REVISION        : "
#define VENSPEC "\nVENDOR SPECIFIC       : "
#define INTERFA "\nINTERFACE             : "
#define ATAPI   "ATAPI"
#define SCSI1   "SCSI 1"
#define SCSI2   "SCSI 2"
#define SCSI3   "SCSI 3"

#define CDRREAD "\nCDR  READ SUPPORT     : "
#define CRWREAD "\nCDRW READ SUPPORT     : "
#define CD2READ "\nCDRM2 READ SUPPORT    : "
#define CDRWRIT "\nCDR  WRITE SUPPORT    : "
#define CRWWRIT "\nCDRW WRITE SUPPORT    : "
#define DROREAD "\nDVD-ROM READ SUPPORT  : "
#define DRRREAD "\nDVD-R   READ SUPPORT  : "
#define DRAREAD "\nDVD-RAM READ SUPPORT  : "
#define DRRWRIT "\nDVD-R   WRITE SUPPORT : "
#define DRAWRIT "\nDVD-RAM WRITE SUPPORT : "
#define MAXSPED "\nMAX CDR READ SPEED    : "
#define MAXWRIT "\nMAX CDR WRITE SPEED   : "

#define RPCSTA  "\nSETTING STATUS        : "
#define RPCSCH  "\nRPC2 SCHEME           : "
#define USRCHA  "\nUSER CHANGES          : "
#define MANCHA  "\nMANUFACTOR RESET      : "
#define REGCOD  "\nREGION CODE           : "

#define NO      "NO"
#define YES     "YES"


void __fastcall TForm1::RunSaveDialog(TObject *Sender)
{
   int iFileHandle;
   char buf[20];
   FILE *fp;
   int driveCounter;
   AnsiString calc;

   if(SaveDialog1->Execute())
   {
     if (FileExists(SaveDialog1->FileName))
     {
       if (!DeleteFile(SaveDialog1->FileName))
       {
         Application->MessageBox("FILE exist, is it write protected?", "ERROR", MB_OK);
       }
     }

     iFileHandle =  FileCreate(SaveDialog1->FileName);

     if(iFileHandle > 0)
     {
       for(driveCounter = 0; driveCounter < CdList.num && driveCounter < CdList.max; driveCounter++)
       {
         FileWrite(iFileHandle, VENDOR, sizeof(VENDOR)-1);
         FileWrite(iFileHandle, (char*)&(CdList.cd[driveCounter].info.vendor), sizeof
            (CdList.cd[driveCounter].info.vendor) -1);

         FileWrite(iFileHandle, PROID, sizeof(PROID)-1);
         FileWrite(iFileHandle, (char*)&(CdList.cd[driveCounter].info.prodId), sizeof
            (CdList.cd[driveCounter].info.prodId) -1);

         FileWrite(iFileHandle, REV, sizeof(REV)-1);
         FileWrite(iFileHandle, (char*)&(CdList.cd[driveCounter].info.rev), sizeof
            (CdList.cd[driveCounter].info.rev) -1);

         FileWrite(iFileHandle, VENSPEC, sizeof(VENSPEC)-1);
         FileWrite(iFileHandle, (char*)&(CdList.cd[driveCounter].info.vendSpec), sizeof
            (CdList.cd[driveCounter].info.vendSpec) -1);

         FileWrite(iFileHandle, INTERFA, sizeof(INTERFA)-1);
         switch(CdList.cd[driveCounter].info.AnsiVersion[0])
         {
           case 0x00:
             FileWrite(iFileHandle, ATAPI, sizeof(ATAPI)-1);
             break;
           case 0x01:
             FileWrite(iFileHandle, SCSI1, sizeof(SCSI1)-1);
             break;
           case 0x02:
             FileWrite(iFileHandle, SCSI2, sizeof(SCSI2)-1);
             break;
           case 0x03:
             FileWrite(iFileHandle, SCSI3, sizeof(SCSI3)-1);
             break;
         }

         if(CdList.cd[driveCounter].info.RPCInfoChecked)
         {
           FileWrite(iFileHandle, RPCSCH, sizeof(RPCSCH)-1);
           switch(CdList.cd[driveCounter].info.RPCScheme)
           {
            case 0x00:
              FileWrite(iFileHandle, "NO       ", sizeof("NO       ")-1);
              break;
            case 0x01:
              FileWrite(iFileHandle, "YES      ", sizeof("YES      ")-1);
              break;
            default:
              FileWrite(iFileHandle, "UNKNOWN  ", sizeof("UNKNOWN  ")-1);
              break;
           }
           //FileWrite(iFileHandle, &CdList.cd[driveCounter].info.RPCScheme, sizeof(CdList.cd[driveCounter].info.RPCScheme));

           FileWrite(iFileHandle, RPCSTA, sizeof(RPCSTA)-1);
           switch(CdList.cd[driveCounter].info.typeCode)
           {
             case 0x3:
               FileWrite(iFileHandle, "PERMANENT  ", sizeof("PERMANENT  ")-1);
               break;
             default:
               FileWrite(iFileHandle, "NOT PERMANENT  ", sizeof("NOT PERMANENT  ")-1);
               break;
           }
           //FileWrite(iFileHandle, &CdList.cd[driveCounter].info.typeCode, sizeof(CdList.cd[driveCounter].info.typeCode));

           FileWrite(iFileHandle, USRCHA, sizeof(USRCHA)-1);
           CdList.cd[driveCounter].info.nofUserChanges += 0x30;
           FileWrite(iFileHandle, &CdList.cd[driveCounter].info.nofUserChanges, sizeof(CdList.cd[driveCounter].info.nofUserChanges));
           CdList.cd[driveCounter].info.nofUserChanges -= 0x30;

           FileWrite(iFileHandle, MANCHA, sizeof(MANCHA)-1);
           CdList.cd[driveCounter].info.nofVendorReset += 0x30;
           FileWrite(iFileHandle, &CdList.cd[driveCounter].info.nofVendorReset, sizeof(CdList.cd[driveCounter].info.nofVendorReset));
           CdList.cd[driveCounter].info.nofVendorReset -= 0x30;

           FileWrite(iFileHandle, REGCOD, sizeof(REGCOD)-1);
           if( CdList.cd[driveCounter].info.regionMask == 0xFF )
             FileWrite(iFileHandle, "NONE", sizeof("NONE")-1);
           if( !(CdList.cd[driveCounter].info.regionMask & 0x01) )
             FileWrite(iFileHandle, "1 ", sizeof("1 ")-1);
           if( !(CdList.cd[driveCounter].info.regionMask & 0x02) )
             FileWrite(iFileHandle, "2 ", sizeof("1 ")-1);
           if( !(CdList.cd[driveCounter].info.regionMask & 0x04) )
             FileWrite(iFileHandle, "3 ", sizeof("1 ")-1);
           if( !(CdList.cd[driveCounter].info.regionMask & 0x08) )
             FileWrite(iFileHandle, "4 ", sizeof("1 ")-1);
           if( !(CdList.cd[driveCounter].info.regionMask & 0x10) )
             FileWrite(iFileHandle, "5 ", sizeof("1 ")-1);
           if( !(CdList.cd[driveCounter].info.regionMask & 0x20) )
             FileWrite(iFileHandle, "6 ", sizeof("1 ")-1);
           if( !(CdList.cd[driveCounter].info.regionMask & 0x40) )
             FileWrite(iFileHandle, "7 ", sizeof("1 ")-1);
           if( !(CdList.cd[driveCounter].info.regionMask & 0x80) )
             FileWrite(iFileHandle, "8 ", sizeof("1 ")-1);
          /*
           switch(CdList.cd[driveCounter].info.regionMask)
           {
             case 0xFF:
               FileWrite(iFileHandle, "NONE", sizeof(5));
               break;
             case 0xFE:
               FileWrite(iFileHandle, "1", sizeof("1")-1));
               break;
             case 0xFD:
               FileWrite(iFileHandle, "2", sizeof("2")-1));
               break;
             case 0xFB:
               FileWrite(iFileHandle, "3", sizeof("2")-1));
               break;
             case 0xF7:
               FileWrite(iFileHandle, "4", sizeof("2")-1));
               break;
             case 0xEF:
               FileWrite(iFileHandle, "5", sizeof("2")-1));
               break;
             case 0xDF:
               FileWrite(iFileHandle, "6", sizeof("2")-1));
               break;
             case 0xBF:
               FileWrite(iFileHandle, "7", sizeof("2")-1));
               break;
             case 0x7F:
               FileWrite(iFileHandle, "8", sizeof("2")-1));
               break;
             default:
               FileWrite(iFileHandle, "UNKNOWN", sizeof("2"-1));
               break;
           } */

         }
         else
         {
            if(  CdList.cd[ComboBox1->ItemIndex].info.cdDrive &&
                !CdList.cd[ComboBox1->ItemIndex].info.dvdDrive   )
            {

            }
            else
            {
              FileWrite(iFileHandle, RPCSCH, sizeof(RPCSCH)-1);
              FileWrite(iFileHandle, "NO       ", sizeof("NO       ")-1);
            }
         }

         if(CdList.cd[driveCounter].sm.ccsmAvail)
         {
           FileWrite(iFileHandle, CDRREAD, sizeof(CDRREAD)-1);
           if(CdList.cd[driveCounter].info.cdRReadSupport)
             FileWrite(iFileHandle, YES, sizeof(YES)-1);
           else
             FileWrite(iFileHandle, NO, sizeof(NO)-1);

           FileWrite(iFileHandle, CRWREAD, sizeof(CRWREAD)-1);
           if(CdList.cd[driveCounter].info.cdRwReadSupport)
             FileWrite(iFileHandle, YES, sizeof(YES)-1);
           else
             FileWrite(iFileHandle, NO, sizeof(NO)-1);

           FileWrite(iFileHandle, CD2READ, sizeof(CD2READ)-1);
           if(CdList.cd[driveCounter].info.cdMetod2ReadSupport)
             FileWrite(iFileHandle, YES, sizeof(YES)-1);
           else
             FileWrite(iFileHandle, NO, sizeof(NO)-1);

           FileWrite(iFileHandle, CDRWRIT, sizeof(CDRWRIT)-1);
           if(CdList.cd[driveCounter].info.cdRWriteSupport)
             FileWrite(iFileHandle, YES, sizeof(YES)-1);
           else
             FileWrite(iFileHandle, NO, sizeof(NO)-1);

           FileWrite(iFileHandle, CRWWRIT, sizeof(CRWWRIT)-1);
           if(CdList.cd[driveCounter].info.cdRwWriteSupport)
             FileWrite(iFileHandle, YES, sizeof(YES)-1);
           else
             FileWrite(iFileHandle, NO, sizeof(NO)-1);

           FileWrite(iFileHandle, DROREAD, sizeof(DROREAD)-1);
           if(CdList.cd[driveCounter].info.dvdRomReadSupport)
             FileWrite(iFileHandle, YES, sizeof(YES)-1);
           else
             FileWrite(iFileHandle, NO, sizeof(NO)-1);

           FileWrite(iFileHandle, DRRREAD, sizeof(DRRREAD)-1);
           if(CdList.cd[driveCounter].info.dvdRReadSupport)
             FileWrite(iFileHandle, YES, sizeof(YES)-1);
           else
             FileWrite(iFileHandle, NO, sizeof(NO)-1);

           FileWrite(iFileHandle, DRAREAD, sizeof(DRAREAD)-1);
           if(CdList.cd[driveCounter].info.dvdRamReadSupport)
             FileWrite(iFileHandle, YES, sizeof(YES)-1);
           else
             FileWrite(iFileHandle, NO, sizeof(NO)-1);

           FileWrite(iFileHandle, DRRWRIT, sizeof(DRRWRIT)-1);
           if(CdList.cd[driveCounter].info.dvdRWriteSupport)
             FileWrite(iFileHandle, YES, sizeof(YES)-1);
           else
             FileWrite(iFileHandle, NO, sizeof(NO)-1);

           FileWrite(iFileHandle, DRAWRIT, sizeof(DRAWRIT)-1);
           if(CdList.cd[driveCounter].info.dvdRamWriteSupport)
             FileWrite(iFileHandle, YES, sizeof(YES)-1);
           else
             FileWrite(iFileHandle, NO, sizeof(NO)-1);

           if(  (CdList.cd[driveCounter].info.cdRReadSupport  ||
                 CdList.cd[driveCounter].info.cdRwReadSupport ||
                 CdList.cd[driveCounter].info.cdMetod2ReadSupport) &&
                (CdList.cd[driveCounter].info.maxSpeedReadCd))
           {
             FileWrite(iFileHandle, MAXSPED, sizeof(MAXSPED)-1);
             buf[0] = (CdList.cd[driveCounter].info.maxSpeedReadCd / 10) + 0x30;
             if(buf[0]!=0x30)
               FileWrite(iFileHandle, &buf, 1);
             buf[0] = (CdList.cd[driveCounter].info.maxSpeedReadCd % 10) + 0x30;
             FileWrite(iFileHandle, &buf, 1);
           }

           if(  (CdList.cd[driveCounter].info.cdRWriteSupport ||
                 CdList.cd[driveCounter].info.cdRwWriteSupport) &&
                (CdList.cd[driveCounter].info.maxSpeedWriteCd))
           {
             FileWrite(iFileHandle, MAXWRIT, sizeof(MAXWRIT)-1);
             if( CdList.cd[driveCounter].info.maxSpeedWriteCd < 100)
             {
               buf[0] = (CdList.cd[driveCounter].info.maxSpeedWriteCd / 10 ) + 0x30;
               if(buf[0]!= 0x30)
                 FileWrite(iFileHandle, &buf, 1);
               buf[0] = (CdList.cd[driveCounter].info.maxSpeedWriteCd % 10) + 0x30;
               FileWrite(iFileHandle, &buf, 1);
             }
           }
         }
         if(CdList.cd[driveCounter].info.RPCInfoChecked)
         {
           FileWrite(iFileHandle, "\nKEY BINARY DATA :\n", sizeof("\nKEY BINARY DATA:\n"));
           FileWrite(iFileHandle, &CdList.cd[driveCounter].info.ReportKeyData, 20);
         }
      /*   FileWrite(iFileHandle, "\n", 1);
         FileWrite(iFileHandle, "\nDRIVE BINARY DATA :\n", sizeof("\nDRIVE BINARY DATA:\n"));
         FileWrite(iFileHandle, &CdList.cd[driveCounter].info.InquiryData, 20);
         FileWrite(iFileHandle, "\n", 1);
         FileWrite(iFileHandle, &CdList.cd[driveCounter].info.InquiryData[20], 20);
         FileWrite(iFileHandle, "\n", 1);
         FileWrite(iFileHandle, &CdList.cd[driveCounter].info.InquiryData[40], 16);
         FileWrite(iFileHandle, "\n", 1); */
         FileWrite(iFileHandle, "\n", 1);
       }
       FileClose(iFileHandle);
     }
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::eXit1Click(TObject *Sender)
{
   #ifdef CDVDinfo_DEBUG
    write_debug_info("Exit Normal \n\r");
   #endif

  exit(0);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::About1Click(TObject *Sender)
{

 char Caption[] = "About";
 char Message[1000] = "";

 // Yeah, I know this is the lame way to set the MessageBox text... :-)


strcat(Message, "Before testing your DVD-drive insert a DVD. Some DVD-\n\r");
strcat(Message, "drives will not give correct region information without\n\r");
strcat(Message, "the DVD disc inserted.\n\r");
strcat(Message, "\n\r");
strcat(Message, "Save CD/DVD-drive information using File->Save Info.\n\r");
strcat(Message, "Send the file to this address: cdvdinfo@e-mail.dk\n\r");
strcat(Message, "We will use this information to build a large database\n\r");
strcat(Message, "to document which DVD-drives and Firmware that is region\n\r");
strcat(Message, "locked. Also to document features of CD/DVD-drives.\n\r");
strcat(Message, "Take a look in the file, more informations are available!\n\r");
strcat(Message, "\n\r");
strcat(Message, "Check the homepage at: www.cdvdinfo.subnet.dk/\n\r");
strcat(Message, "\n\r");
strcat(Message, "This software is made by Klaus Jensen, Denmark\n\r");
strcat(Message, "With help from SiGMA");

Position = poScreenCenter;
// Value of 64 informs the MessageBox to show the "Information" icon.
// The user shouldn't be able to return focus to the main window until
// the message box is closed.

Application->MessageBox(Message, Caption, 64);

//delete[] Message;
}

//---------------------------------------------------------------------------

