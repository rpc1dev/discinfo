#include <vcl.h>
#pragma hdrstop

#include "Aspi.h"
#include "Stdlib.h"
#include "Stdio.h"
#include "String.h"
#include "About.h"
#include "Extra.h"
#include "Searchf.h"
#include "Summary.h"
#include "Device.h"
#include "pngimage.hpp"
#include "CDVDMain.h"

// #define DISCInfo_DEBUG

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VersionInfoComponent"
#pragma resource "*.dfm"
TMain_Form *Main_Form;

#ifdef DISCInfo_DEBUG
    FILE *debug_file;
#endif

//---------------------------------------------------------------------------
__fastcall TMain_Form::TMain_Form(TComponent* Owner)
        : TForm(Owner)
{
        Main_Form->Caption=Application->Title;

        int iOSVer = getOsVersion();
        
        ASPI1->Enabled=false;
        SPTI1->Enabled=false;
        ASPI1->Checked=false;
        SPTI1->Checked=false;

        if (!InitASPI())
        {
            ASPI1->Enabled=true;

            #ifdef DISCInfo_DEBUG
                write_log("Found ASPI drivers");
            #endif
        }
        if (iOSVer>=2)
        {
            SPTI1->Enabled=true;
            SPTI1->Checked=true;
            #ifdef DISCInfo_DEBUG
                write_log("Operating system is NT or later");
                write_log("SPTI selected");
            #endif
            if (Device::makeDeviceList() || !deviceCount)
          	{
                // If still not found anything then try ASPI if avaible
                if (!deviceCount)
              	{
                    if (ASPI1->Enabled!=true)
                    {
                        #ifdef DISCInfo_DEBUG
                            write_log("No drives found via SPTI and no ASPI found to try it. Program exit");
                        #endif
                        Application->MessageBox ("Can not locate any drives in this computer.\nPossible reason is that you don't have administration rights.\nRelogon with username that has administration rights.\nYou can also try to install ASPI drivers. ASPI can work on non admin user accounts.\nProgram will now exit!", "Program error", MB_OK | MB_ICONSTOP);
                        Close();
                    }
                    else
                    {
                        SPTI1->Enabled=false;
                        SPTI1->Checked=false;
                        ASPI1->Checked=true;
                        #ifdef DISCInfo_DEBUG
                            write_log("SPTI failed to find devices. Trying ASPI");
                        #endif
                        if (Device::makeDeviceList() || !deviceCount)
                        {
                            #ifdef DISCInfo_DEBUG
                                write_log("Still nothing found. Trying to look for all devices");
                            #endif
                            // If there are no CD/DVD devices then enable the lookup for other devices
                            Displayotherdevices1->Checked=true;
                            if (Device::makeDeviceList() || !deviceCount)
                            {
                                #ifdef DISCInfo_DEBUG
                                    write_log("Still nothing found. Program exit");
                                #endif
                                Application->MessageBox ("Unable to populate the device list with ASPI driver.\nReinstall the ASPI driver with version 4.60.\nProgram will now exit!", "Program error", MB_OK | MB_ICONSTOP);
                                Close();
                            }
                        }
                    }
                }
           	}
        } else
        {
            ASPI1->Enabled=true;
            ASPI1->Checked=true;
            #ifdef DISCInfo_DEBUG
               write_log("Operating system is Windows 95 or newer (Win32)");
               write_log("ASPI selected");
            #endif
            if (InitASPI())
          	{
                #ifdef DISCInfo_DEBUG
                   write_log("ASPI not or improperly installed. Program exit.");
                #endif
          		Application->MessageBox ("ASPI driver not or improperly installed.\n It's advised to install ASPI driver version 4.60.", "ASPI error", MB_OK | MB_ICONSTOP);
           		Close();
           	}
            if (Device::makeDeviceList())
          	{
                #ifdef DISCInfo_DEBUG
                   write_log("Unable to populate devices");
                #endif
          		Application->MessageBox ("Unable to populate the device list. Program will now exit!", "Program error", MB_OK | MB_ICONSTOP);
           		Close();
           	}
            if (!deviceCount)
          	{
                #ifdef DISCInfo_DEBUG
                   write_log("No devices found. Trying to show all devices");
                #endif
                // If there are no CD/DVD devices then enable the lookup for other devices
                Displayotherdevices1->Checked=true;
                if (Device::makeDeviceList())
              	{
                    #ifdef DISCInfo_DEBUG
                       write_log("Unable to populate devices. Program exit");
                    #endif
              		Application->MessageBox ("Unable to populate the device list. Program will now exit!", "Program error", MB_OK | MB_ICONSTOP);
               		Close();
               	}
                // If still not found anything then display notice and exit
                if (!deviceCount)
              	{
                    #ifdef DISCInfo_DEBUG
                       write_log("No devices found. Program exit");
                    #endif                
              		Application->MessageBox ("Can not locate any drives in this computer. Program will now exit!", "Program error", MB_OK | MB_ICONSTOP);
               		Close();
                }
           	}
        }
        ComboBoxChange(Main_Form);
}

//---------------------------------------------------------------------------
void __fastcall TMain_Form::Exit1Click(TObject *Sender)
{
        #ifdef DISCInfo_DEBUG
            write_log("Program exit");
        #endif
        Close();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
int getOsVersion()
{
  OSVERSIONINFO os;
  
  ZeroMemory( &os, sizeof(os) );
  os.dwOSVersionInfoSize = sizeof(os);
  GetVersionEx( &os );
  
  if ( os.dwPlatformId == VER_PLATFORM_WIN32_NT )
  {
    if ( os.dwMajorVersion == 3 && os.dwMinorVersion >= 50 )
      return OS_WINNT35;
    else if ( os.dwMajorVersion == 4 )
      return OS_WINNT4;
    else if ( os.dwMajorVersion == 5 )
      return OS_WIN2K;
  }
  else if ( os.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS )
  {
    if ( os.dwMinorVersion == 0 )
      return OS_WIN95;
    else
      return OS_WIN98;
  }

  return OS_UNKNOWN;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TMain_Form::SaveData1Click(TObject *Sender)
{
        TStringList *slInfo = new TStringList();
        char forfile[100];
        char rpc[10];
        char firma[8];
        char kater_model[16];
        char DISCInfoVer[15];        
        int i;
        bool first_time=true;
        Device* dev = devices;

        // Retrieve the File Version
        DWORD h;
        DWORD Size=GetFileVersionInfoSize(Application->ExeName.c_str(), &h);
        if(Size==0)
            sprintf(DISCInfoVer,"Unknowned");
        char *buf;
        char *ValueBuf;
        buf=(char*)GlobalAlloc(GMEM_FIXED, Size);
        if(GetFileVersionInfo(Application->ExeName.c_str(),
                          h,
                          Size,
                          buf)!=0)
        {
            UINT Len;
            VerQueryValue(buf, "\\VarFileInfo\\Translation", &(void*)ValueBuf, &Len);
            if(Len>=4)
            {
                AnsiString CharSet=IntToHex((int)MAKELONG(*(int*)(ValueBuf+2), *(int*)ValueBuf), 8);
                /*
                if(VerQueryValue(buf,
                        AnsiString("\\StringFileInfo\\"+CharSet+"\\ProductName").c_str(),
                        &(void*)ValueBuf,
                        &Len)!=0)
                        ShowMessage(ValueBuf);
                if(VerQueryValue(buf,
                        AnsiString("\\StringFileInfo\\"+CharSet+"\\LegalCopyright").c_str(),
                        &(void*)ValueBuf,
                        &Len)!=0)
                        ShowMessage(ValueBuf);
                if(VerQueryValue(buf,
                        AnsiString("\\StringFileInfo\\"+CharSet+"\\CompanyName").c_str(),
                        &(void*)ValueBuf,
                        &Len)!=0)
                        ShowMessage(ValueBuf);
                 */
                if(VerQueryValue(buf,
                        AnsiString("\\StringFileInfo\\"+CharSet+"\\FileVersion").c_str(),
                        &(void*)ValueBuf,
                        &Len)!=0)
                        sprintf(DISCInfoVer,"%s",ValueBuf);
           }
        } else
            sprintf(DISCInfoVer,"Unknowned");
        GlobalFree(buf);

        for (i=0;i<deviceCount;i++)
        {
                if (dev->type==DTYPE_WORM || dev->type==DTYPE_CROM)
                {
                        if (i!=0 && deviceCount>1 && !first_time)
                        {
                                slInfo->Add("<- ->");
                        }
                        memcpy(firma,dev->vendor_name,8);
                        firma[8]=0;
                        memcpy(kater_model,&dev->vendor_name[8],16);
                        firma[16]=0;

                        sprintf(forfile,"DISCINFO VERSION   : %s",DISCInfoVer);
                        slInfo->Add(forfile);

                        sprintf(forfile,"VENDOR             : %s",firma);
                        slInfo->Add(forfile);
                        sprintf(forfile,"MODEL              : %s",kater_model);
                        slInfo->Add(forfile);
                        sprintf(forfile,"REVISION           : %s",dev->firmware_version);
                        slInfo->Add(forfile);

                        if (dev->extra_info[0]!=0)
                        {
                            sprintf(forfile,"VENDOR SPECIFIC    : %s",dev->extra_info);
                            slInfo->Add(forfile);
                        }

                        if (dev->mechanism[0]!=0)
                        {
                            sprintf(forfile,"LOADING MECHANISM  : %s",AnsiString(dev->mechanism).Trim());
                            slInfo->Add(forfile);
                        }
                        if (dev->serial[0]!=0)
                        {
                            sprintf(forfile,"SERIAL NUMBER      : %s",AnsiString(dev->serial).SubString(0,12));
                            slInfo->Add(forfile);
                        }
                        if (dev->levels > 0)
                        {
                               sprintf(forfile,"NUMBER VOL. LEVELS : %i",dev->levels);
                               slInfo->Add(forfile);
                        }
                        if (dev->buffersize > 0)
                        {
                               sprintf(forfile,"BUFFER SIZE        : %iKB",dev->buffersize);
                               slInfo->Add(forfile);
                        }
                        if (dev->if_toshiba)
                        {
                                sprintf(forfile,"TOSHIBA CODE       : %s",dev->fw_code);
                                slInfo->Add(forfile);
                                sprintf(forfile,"TOSHIBA MODEL      : %s",dev->tosh_model);
                                slInfo->Add(forfile);
                        }
                        switch(dev->interfacex[0])
                        {
                                case 0x00:
                                        sprintf(forfile,"INTERFACE          : %s","ATAPI");
                                        slInfo->Add(forfile);
                                        break;
                                case 0x01:
                                        sprintf(forfile,"INTERFACE          : %s","SCSI 1");
                                        slInfo->Add(forfile);
                                        break;
                                case 0x02:
                                        sprintf(forfile,"INTERFACE          : %s","SCSI 2");
                                        slInfo->Add(forfile);
                                        break;
                                case 0x03:
                                        sprintf(forfile,"INTERFACE          : %s","SCSI 3");
                                        slInfo->Add(forfile);
                                        break;
                                default:        // IF NOT FOUND
                                        break;
                        }
                        if (dev->drive_status)
                        {
                                sprintf(rpc,"%s","YES");
                                rpc[3]=0;
                        } else
                        {
                                sprintf(rpc,"%s","NO");
                                rpc[2]=0;
                        }
                        sprintf(forfile,"RPC2 SCHEME        : %s",rpc);
                        slInfo->Add(forfile);
                        if (dev->drive_status)
                        {
                                sprintf(forfile,"STATUS             : %s",dev->region_status);
                                slInfo->Add(forfile);
                                sprintf(forfile,"USER CHANGES       : %i",dev->user);
                                slInfo->Add(forfile);
                                sprintf(forfile,"VENDOR CHANGES     : %i",dev->manufactor);
                                slInfo->Add(forfile);
                                sprintf(forfile,"CURRENT REGION     : %s",dev->current_region);
                                slInfo->Add(forfile);
                        }

                        if (dev->iscdDrive || dev->iscdRRead || dev->iscdRWrite || dev->isdvdDrive)
                        {
                                if (dev->audioplay)
                                        sprintf(forfile,"ANALOG AUDIO PLAY  : %s","YES");
                                else
                                        sprintf(forfile,"ANALOG AUDIO PLAY  : %s","NO");
                                slInfo->Add(forfile);

                                if (dev->composite)
                                        sprintf(forfile,"COMPOSITE OUTPUT   : %s","YES");
                                else
                                        sprintf(forfile,"COMPOSITE OUTPUT   : %s","NO");
                                slInfo->Add(forfile);

                                if (dev->digport1)
                                        sprintf(forfile,"DIGITAL PORT-PORT1 : %s","YES");
                                else
                                        sprintf(forfile,"DIGITAL PORT-PORT1 : %s","NO");
                                slInfo->Add(forfile);

                                if (dev->digport2)
                                        sprintf(forfile,"DIGITAL PORT-PORT2 : %s","YES");
                                else
                                        sprintf(forfile,"DIGITAL PORT-PORT2 : %s","NO");
                                slInfo->Add(forfile);

                                if (dev->UPC)
                                        sprintf(forfile,"READ UPC CODE      : %s","YES");
                                else
                                        sprintf(forfile,"READ UPC CODE      : %s","NO");
                                slInfo->Add(forfile);

                                if (dev->multisession)
                                        sprintf(forfile,"MULTISESSION READ  : %s","YES");
                                else
                                        sprintf(forfile,"MULTISESSION READ  : %s","NO");
                                slInfo->Add(forfile);

                                if (dev->mode1form)
                                        sprintf(forfile,"MODE 2 FORM 1      : %s","YES");
                                else
                                        sprintf(forfile,"MODE 2 FORM 1      : %s","NO");
                                slInfo->Add(forfile);

                                if (dev->mode2form)
                                        sprintf(forfile,"MODE 2 FORM 2      : %s","YES");
                                else
                                        sprintf(forfile,"MODE 2 FORM 2      : %s","NO");
                                slInfo->Add(forfile);

                                if (dev->ISRC)
                                        sprintf(forfile,"READ ISRC CODE     : %s","YES");
                                else
                                        sprintf(forfile,"READ ISRC CODE     : %s","NO");
                                slInfo->Add(forfile);

                                if (dev->barcode)
                                        sprintf(forfile,"READ BAR CODE      : %s","YES");
                                else
                                        sprintf(forfile,"READ BAD CODE      : %s","NO");
                                slInfo->Add(forfile);

                                if (dev->buffunder)
                                        sprintf(forfile,"BUFFER UNDER-RUN   : %s","YES");
                                else
                                        sprintf(forfile,"BUFFER UNDER-RUN   : %s","NO");
                                slInfo->Add(forfile);

                                if (dev->mtrainier)
                                        sprintf(forfile,"MT. RAINIER        : %s","YES");
                                else
                                        sprintf(forfile,"MT. RAINIER        : %s","NO");
                                slInfo->Add(forfile);

                                if (dev->cdRRead)
                                        sprintf(forfile,"CAN READ CDR       : %s","YES");
                                else
                                        sprintf(forfile,"CAN READ CDR       : %s","NO");
                                slInfo->Add(forfile);

                                if (dev->cdRWRead)
                                        sprintf(forfile,"CAN READ CDRW      : %s","YES");
                                else
                                        sprintf(forfile,"CAN READ CDRW      : %s","NO");
                                slInfo->Add(forfile);

                                if (dev->cdMethod2Read)
                                        sprintf(forfile,"CAN READ CDRM2     : %s","YES");
                                else
                                        sprintf(forfile,"CAN READ CDRM2     : %s","NO");
                                slInfo->Add(forfile);

                                if (dev->cdRWrite)
                                        sprintf(forfile,"CAN WRITE CDR      : %s","YES");
                                else
                                        sprintf(forfile,"CAN WRITE CDR      : %s","NO");
                                slInfo->Add(forfile);

                                if (dev->cdRWWrite)
                                        sprintf(forfile,"CAN WRITE CDRW     : %s","YES");
                                else
                                        sprintf(forfile,"CAN WRITE CDRW     : %s","NO");
                                slInfo->Add(forfile);

                                if (dev->testWrite)
                                        sprintf(forfile,"CAN TEST WRITE     : %s","YES");
                                else
                                        sprintf(forfile,"CAN TEST WRITE     : %s","NO");
                                slInfo->Add(forfile);

                                if (dev->dvdRomRead)
                                        sprintf(forfile,"CAN READ DVD-ROM   : %s","YES");
                                else
                                        sprintf(forfile,"CAN READ DVD-ROM   : %s","NO");
                                slInfo->Add(forfile);

                                if (dev->dvdRRead)
                                        sprintf(forfile,"CAN READ DVD-R     : %s","YES");
                                else
                                        sprintf(forfile,"CAN READ DVD-R     : %s","NO");
                                slInfo->Add(forfile);

                                if (dev->dvdRWRead)
                                        sprintf(forfile,"CAN READ DVD-RW    : %s","YES");
                                else
                                        sprintf(forfile,"CAN READ DVD-RW    : %s","NO");
                                slInfo->Add(forfile);

                                if (dev->dvdRamRead)
                                        sprintf(forfile,"CAN READ DVD-RAM   : %s","YES");
                                else
                                        sprintf(forfile,"CAN READ DVD-RAM   : %s","NO");
                                slInfo->Add(forfile);

                                if (dev->dvdPRRead)
                                        sprintf(forfile,"CAN READ DVD+R     : %s","YES");
                                else
                                        sprintf(forfile,"CAN READ DVD+R     : %s","NO");
                                slInfo->Add(forfile);

                                if (dev->dvdPRWRead)
                                        sprintf(forfile,"CAN READ DVD+RW    : %s","YES");
                                else
                                        sprintf(forfile,"CAN READ DVD+RW    : %s","NO");
                                slInfo->Add(forfile);
                                
                                if (dev->dvdRWrite)
                                        sprintf(forfile,"CAN WRITE DVD-R    : %s","YES");
                                else
                                        sprintf(forfile,"CAN WRITE DVD-R    : %s","NO");
                                slInfo->Add(forfile);

                                if (dev->dvdRWWrite)
                                        sprintf(forfile,"CAN WRITE DVD-RW   : %s","YES");
                                else
                                        sprintf(forfile,"CAN WRITE DVD-RW   : %s","NO");
                                slInfo->Add(forfile);

                                if (dev->dvdRamWrite)
                                        sprintf(forfile,"CAN WRITE DVD-RAM  : %s","YES");
                                else
                                        sprintf(forfile,"CAN WRITE DVD-RAM  : %s","NO");
                                slInfo->Add(forfile);

                                if (dev->dvdPRWrite)
                                        sprintf(forfile,"CAN WRITE DVD+R    : %s","YES");
                                else
                                        sprintf(forfile,"CAN WRITE DVD+R    : %s","NO");
                                slInfo->Add(forfile);

                                if (dev->dvdPRWWrite)
                                        sprintf(forfile,"CAN WRITE DVD+RW   : %s","YES");
                                else
                                        sprintf(forfile,"CAN WRITE DVD+RW   : %s","NO");
                                slInfo->Add(forfile);

                        }

                        if (dev->read_s > 0)
                        {
                               sprintf(forfile,"MAX CDR READ SPEED : %i",dev->read_s);
                               slInfo->Add(forfile);
                        }

                        if (dev->iscdRWrite && dev->write_s > 0)
                        {
                                sprintf(forfile,"MAX CDR WRITE SPEED: %i",dev->write_s);
                                slInfo->Add(forfile);
                        }
                        first_time=false;
                }
                dev = dev->next;
        }
        
        const char* sPOST_FileExt = ".hif";
        const char* sPOST_Filter  = "CD/DVD Info File (*.hif)|*.hif";

        SaveDialog->DefaultExt = sPOST_FileExt;
        SaveDialog->Filter = sPOST_Filter;
        SaveDialog->Title = "Save the CD/DVD informations into a file";
        SaveDialog->FileName="";
        
        if (SaveDialog->Execute())
        {
                if (FileExists(SaveDialog->FileName))
                {
                        if (!DeleteFile(SaveDialog->FileName))
                        {
                                Application->MessageBox("Unable to save to file. Maybe file is write protected?", "Error", MB_OK | MB_ICONSTOP);
                                Abort();
                        }
                }
                slInfo->SaveToFile(SaveDialog->FileName);
        }
        #ifdef DISCInfo_DEBUG
            write_log("HIF file saved");
        #endif
        SaveDialog->FileName="";

        /*
        char firmax[60];
        char sumahex[8];
        int suma;
        sprintf(firmax,"%s",SaveDialog->FileName);

        FILE* fin = fopen(firmax,"rb");
        do
        {
                suma += fgetc(fin);     // sum all bytes
        } while(!feof(fin));
        fclose(fin);

        sprintf(sumahex,"CRC:%04X",suma&0xFFFF); // LAST FEW BYTES
        sumahex[8]=0;
        Application->MessageBox (sumahex, "ASPI error", MB_OK | MB_ICONSTOP);
        fin = fopen(firmax,"a+");
        fwrite(sumahex, 8, 1, fin);
        fclose(fin);
        */
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TMain_Form::About1Click(TObject*)
{
    #ifdef DISCInfo_DEBUG
       write_log("Opening About box");
    #endif
    About_Box = new TAbout_Box(Application);
    About_Box->ShowModal();
    delete About_Box;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TMain_Form::ComboBoxChange(TObject *Sender)
{
        int i=0;

        Device* dev = devices;

        ExtraInfo1->Enabled=false;
        Firmwareupdates1->Enabled=false;

        int pos = deviceCount-Main_Form->ComboBox->ItemIndex-1;

        for (i=0; i < pos; i++)
        {
                dev = dev->next;
        }
        GetDeviceData (dev);
        #ifdef DISCInfo_DEBUG
            char tmp[255];
            sprintf(tmp,"Viewing details for the drive %s",AnsiString(dev->vendor_name).Trim());
            write_log(tmp);
        #endif
        if (dev->type == DTYPE_WORM || dev->type == DTYPE_CROM)
        {
                if(dev->iscdDrive || dev->iscdRRead || dev->iscdRWrite || dev->isdvdDrive)
                {
                    Main_Form->ExtraInfo1->Enabled=true;
                    Main_Form->Firmwareupdates1->Enabled=true;
        	}
        }
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TMain_Form::ComboBoxKeyPress(TObject *Sender, char &Key)
{

        if (Key == 'x' || Key == 'X' || Key == VK_ESCAPE)
        {
                #ifdef DISCInfo_DEBUG
                    write_log("Program exit");
                #endif        
                Close();
        }
        if (Key == 'c' || Key == 'C')
        {
                Key = 0;
                #ifdef DISCInfo_DEBUG
                    write_log("Displaying Capabilities info selected");
                #endif
                ExtraInfo1->Click();
        }
        if (Key == 'a' || Key == 'A')
        {
                Key = 0;
                #ifdef DISCInfo_DEBUG
                    write_log("Displaying About box selected");
                #endif
                About1->Click();
        }
        if (Key == 'd' || Key == 'D')
        {
                Key = 0;
                #ifdef DISCInfo_DEBUG
                    write_log("Displaying other devices than CD/DVD selected");
                #endif
                Displayotherdevices1->Click();
        }
        if (Key == 's' || Key == 'S')
        {
                Key = 0;
                #ifdef DISCInfo_DEBUG
                    write_log("Save data to HIF file selected");
                #endif
                SaveData1->Click();
        }
        if (Key == 'f' || Key == 'F')
        {
                Key = 0;
                #ifdef DISCInfo_DEBUG
                    write_log("Firmware updates selected");
                #endif
                Firmwareupdates1->Click();
        }
        if (Key == 'g' || Key == 'G')
        {
                Key = 0;
                #ifdef DISCInfo_DEBUG
                    write_log("Take screenshot of main window selected");
                #endif
                versionDblClick(NULL);
        }
        if (Key == 'i' || Key == 'I')
        {
                Key = 0;
                #ifdef DISCInfo_DEBUG
                    write_log("Display summary page selected");
                #endif
                CopyToClipboard1->Click();
        }
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TMain_Form::Displayotherdevices1Click(TObject *Sender)
{
        if (Displayotherdevices1->Checked)
        {
                #ifdef DISCInfo_DEBUG
                    write_log("Disable showing of other deviced selected");
                #endif
                Displayotherdevices1->Checked=false;
                ComboBox->Clear();
                Device::makeDeviceList ();
                ComboBoxChange(Main_Form);
        } else
        {
                #ifdef DISCInfo_DEBUG
                    write_log("Enable showing of other deviced selected");
                #endif
                Displayotherdevices1->Checked=true;
                ComboBox->Clear();
                Device::makeDeviceList ();
                ComboBoxChange(Main_Form);
        }
}

//---------------------------------------------------------------------------
void __fastcall TMain_Form::ExtraInfo1Click(TObject *Sender)
{
    #ifdef DISCInfo_DEBUG
        write_log("Showing capabilities window");
    #endif
    Extra_Box = new TExtra_Box(Application);
    Extra_Box->ShowModal();
    delete Extra_Box;
}

//---------------------------------------------------------------------------
void __fastcall TMain_Form::Firmwareupdates1Click(TObject *Sender)
{
    #ifdef DISCInfo_DEBUG
        write_log("Showing firmware update window");
    #endif
    Search_Box = new TSearch_Box(Application);
    Search_Box->ShowModal();
    delete Search_Box;
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::CopyToClipboard1Click(TObject *Sender)
{
    #ifdef DISCInfo_DEBUG
        write_log("Showing summary page window");
    #endif
    SumInfo = new TSumInfo(Application);
    SumInfo->ShowModal();
    delete SumInfo;
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::SPTI1Click(TObject *Sender)
{
    if (!SPTI1->Checked)
    {
        #ifdef DISCInfo_DEBUG
            write_log("SPTI access enabled");
        #endif
        SPTI1->Checked=true;
        ASPI1->Checked=false;
        ComboBox->Clear();
        Device::makeDeviceList ();
        ComboBoxChange(Main_Form);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::ASPI1Click(TObject *Sender)
{
    if (!ASPI1->Checked)
    {
        #ifdef DISCInfo_DEBUG
            write_log("ASPI access enabled");
        #endif
        SPTI1->Checked=false;
        ASPI1->Checked=true;
        ComboBox->Clear();
        if (InitASPI() || Device::makeDeviceList () || !deviceCount)
       	{
      		Application->MessageBox ("ASPI driver not or improperly installed.\nTrying to switch back to SPTI mode.", "ASPI error", MB_OK | MB_ICONSTOP);
            SPTI1->Checked=true;
            ASPI1->Checked=false;
            if (Device::makeDeviceList () || !deviceCount)
          	{
                #ifdef DISCInfo_DEBUG
                    write_log("No devices found or I have problem with finding them");
                #endif
          		Application->MessageBox ("Can't find any drives or problem with identifying them.", "Critical error", MB_OK | MB_ICONSTOP);
           		Close();
           	}
       	}
        ComboBoxChange(Main_Form);        
    }
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::Resfresh1Click(TObject *Sender)
{
    #ifdef DISCInfo_DEBUG
        write_log("Refreshing the drive list");
    #endif
    ComboBox->Clear();
    Device::makeDeviceList ();
    ComboBoxChange(Main_Form);
}
//---------------------------------------------------------------------------

#ifdef DISCInfo_DEBUG
void start_log()
{
    char LogFileDir[MAX_PATH];
    sprintf(LogFileDir,"%s\\DISCInfo.log",GetCurrentDir());
    debug_file = fopen( LogFileDir, "w" );
    write_log("Loging started");
    fclose( debug_file );
}

void write_log(char *debug_string)
{
    char neki[255];
    char LogFileDir[MAX_PATH];
    sprintf(LogFileDir,"%s\\DISCInfo.log",GetCurrentDir());
    sprintf(neki,"%s: %s\n",TimeToStr(Time()),debug_string);
    debug_file = fopen(LogFileDir, "a" );
    if ( debug_file  )
    {
        fwrite( neki, 1, strlen(neki), debug_file );
        fclose( debug_file );
    }
}
#endif

// Get Data out of the drive
void GetDeviceData (Device *device)
{
    char type_of[50];
    char temp[2];

    switch(device->type)
    {
        case DTYPE_DASD:
            memcpy(type_of,"Hard Disk Device",50);
            break;
        case DTYPE_SEQD:
            memcpy(type_of,"Tape Device",50);
            break;
        case DTYPE_PRNT:
            memcpy(type_of,"Printer Device",50);
            break;
        case DTYPE_SCAN:
            memcpy(type_of,"Scanner Device",50);
            case DTYPE_PROC:
            memcpy(type_of,"Process Unit",50);
            break;
        case DTYPE_WORM:
            memcpy(type_of,"CD/DVD Burner Device",50);
            break;
        case DTYPE_CROM:
            memcpy(type_of,"CD-ROM Device",50);
            break;
        case DTYPE_OPTI:
            memcpy(type_of,"Optical Memory Device",50);
            break;
        case DTYPE_JUKE:
            memcpy(type_of,"Juke Box Device",50);
            break;
        default:
            memcpy(type_of,"Unknowned Device",50);
            break;
    }
    if (device->isdvdDrive && !device->iscdRWrite && device->type == DTYPE_CROM || device->type == DTYPE_WORM)
        memcpy(type_of,"DVD-ROM Device",50);

    if (device->isdvdDrive && device->iscdRWrite && device->type == DTYPE_CROM || device->type == DTYPE_WORM)
        memcpy(type_of,"COMBO (CDR/DVD) Device",50);

    if (device->iscdRWrite && !device->isdvdDrive && device->type == DTYPE_CROM || device->type == DTYPE_WORM)
        memcpy(type_of,"CDR Burner Device",50);

    if (device->iscdRWrite && !device->isdvdDrive && device->cdRWWrite && device->type == DTYPE_CROM || device->type == DTYPE_WORM)
        memcpy(type_of,"CDRW Burner Device",50);

    if (device->iscdRWrite && device->dvdRWrite && device->type == DTYPE_CROM || device->type == DTYPE_WORM)
        memcpy(type_of,"DVD Burner Device",50);

    if (!device->if_toshiba)
    {
        Main_Form->fw_code->Caption="none";    
        Main_Form->specific_d->Caption=type_of;
    } else
    {
        Main_Form->fw_code->Caption=Trim((AnsiString) device->fw_code);
        if(AnsiString(device->tosh_model).Length() == 0)
        {
             Main_Form->specific_d->Caption=AnsiString(type_of).Trim();
        } else
        {
             Main_Form->specific_d->Caption=device->tosh_model;
        }
    }

    Main_Form->date->Caption=AnsiString(device->extra_info).Trim();
    Main_Form->version->Caption=device->firmware_version;

    if (device->type == DTYPE_CROM || device->type == DTYPE_WORM)
    {
        Main_Form->read_s->Caption="Read speed:";
        Main_Form->write_s->Caption="Write speed:";
        if (device->read_s > 0)
        {
            sprintf(temp,"%ix",device->read_s);
            Main_Form->readval->Caption=temp;
        } else
            Main_Form->readval->Caption="n/a";

        if (device->write_s > 0)
        {
            sprintf(temp,"%ix",device->write_s);
            Main_Form->writeval->Caption=temp;
        } else
            Main_Form->writeval->Caption="n/a";            
    } else
    {
        Main_Form->read_s->Caption="";
        Main_Form->write_s->Caption="";
        Main_Form->readval->Caption="";
        Main_Form->writeval->Caption="";
    }

    if (!device->drive_status || !device->isdvdDrive)
    {
        Main_Form->reg_status->Caption="";
        Main_Form->permanent_status->Caption="";
        Main_Form->changes_left->Caption="";
        Main_Form->manuf_left->Caption="";
        Main_Form->region_set->Caption="";
        Main_Form->change_data->Caption="";
        Main_Form->man_data->Caption="";
        Main_Form->set_data->Caption="";

        if (device->isdvdDrive)
        {
            Main_Form->region_status->Caption="Drive region status:";
            Main_Form->status_rpc->Hint="RPC-1 :o)";
            Main_Form->status_rpc->Caption="No Lock Detected";
        } else
        {
            Main_Form->status_rpc->Caption="";
            Main_Form->region_status->Caption="";
        }

        if (device->type == DTYPE_DASD || device->type == DTYPE_PROC) // Specical case for HD
        {
            Main_Form->status_rpc->Caption="";
            Main_Form->region_status->Caption="";
        }
    } else
    {
        Main_Form->region_status->Caption="Drive region status:";
        Main_Form->reg_status->Caption="Region setting status";
        Main_Form->changes_left->Caption="User changes left:";
        Main_Form->manuf_left->Caption="Manufactor resets left:";
        Main_Form->region_set->Caption="Current region set:";

        Main_Form->status_rpc->Hint="RPC-2 :-(";
        Main_Form->status_rpc->Caption="Lock Detected";
        Main_Form->permanent_status->Caption=device->region_status;
        Main_Form->set_data->Caption=device->current_region;

        if (Trim(Main_Form->set_data->Caption) == "n/a")
        {
            Main_Form->set_data->Caption="n/a";
            Main_Form->change_data->Caption="n/a";
            Main_Form->man_data->Caption="n/a";
        } else
        {
            Main_Form->set_data->Caption=device->current_region;
            Main_Form->change_data->Caption=device->user;
            Main_Form->man_data->Caption=device->manufactor;
        }
    }
}
void __fastcall TMain_Form::versionDblClick(TObject *Sender)
{
    const char* sPOST_FileExt = ".png";
    const char* sPOST_Filter  = "Portable Network Graphic (*.png)|*.png";

    SaveDialog->DefaultExt = sPOST_FileExt;
    SaveDialog->Filter = sPOST_Filter;
    SaveDialog->Title = "Save the program screenshot into file";

    HDC DC = GetWindowDC(Main_Form->Handle);
    Graphics::TBitmap *bmp = new Graphics::TBitmap;
    TPNGObject *PNG = new TPNGObject;

    bmp->Height = Main_Form->Height;
    bmp->Width = Main_Form->Width;

    ComboBox->SetFocus();
    BitBlt(bmp->Canvas->Handle, 0, 0, bmp->Width, bmp->Height, DC, 0, 0, SRCCOPY);

    PNG->Assign(bmp);

    if (SaveDialog->Execute())
    {
        if (FileExists(SaveDialog->FileName))
        {
            if (!DeleteFile(SaveDialog->FileName))
            {
                Application->MessageBox("Unable to save to file. Maybe file is write protected?", "Error", MB_OK | MB_ICONSTOP);
                Abort();
            }
        }

        PNG->SaveToFile(SaveDialog->FileName);
    }

    #ifdef DISCInfo_DEBUG
        write_log("Screenshot of main window saved");
    #endif

    ReleaseDC(0, DC);
    delete bmp;
    delete PNG;
}
//---------------------------------------------------------------------------

#define ABOUT_BUTTON_CPP(TMain_Form, INI_FILE)
void __fastcall TMain_Form::WMNCPaint(TMessage &Msg)
{
	TForm::Dispatch(&Msg);
	TCanvas * FCanvas = new TCanvas();
	Graphics::TBitmap *Bmp = new Graphics::TBitmap;

	FCanvas->Handle = GetWindowDC(Handle);
	Bmp->LoadFromResourceName(int(HInstance), "FOTO");

	/*calc width*/
	InfoButtonRect.left = GetSystemMetrics(SM_CXSIZE) * 3 + GetSystemMetrics(SM_CXFRAME) + Bmp->Width;
	InfoButtonRect.left = Width - InfoButtonRect.left;

	/*calc last three points of rect*/
	if(BorderStyle == bsSizeable)
	{
	    InfoButtonRect.top = GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYBORDER);
	}
	else
	{
	    InfoButtonRect.top = GetSystemMetrics(SM_CYFRAME);
	}

	InfoButtonRect.right = InfoButtonRect.left + Bmp->Width;
	InfoButtonRect.bottom = InfoButtonRect.top + Bmp->Height;

	SetBkMode(FCanvas->Handle, TRANSPARENT);

	/*draw bitmap*/
	FCanvas->Draw(InfoButtonRect.left, InfoButtonRect.top, Bmp);
	// Repaint();
	/*overwrite top to catch all clicks on bitmap*/
	InfoButtonRect.top = -1;

	ReleaseDC(Handle, FCanvas->Handle);
	delete Bmp;
	delete FCanvas;

}
/*---------------------------------------------------------------------------*/
void __fastcall TMain_Form::WMNCLButtonDown(TMessage &Msg)
{
	TForm::Dispatch(&Msg);
									
	if (Msg.WParam == HTCAPTION)                               
	{                                                          
		int LSpace = GetSystemMetrics(SM_CXBORDER) + GetSystemMetrics(SM_CXFRAME);     
		int TSpace = GetSystemMetrics(SM_CXSIZE);

		POINTS MPoints = MAKEPOINTS(Msg.LParam);
		TPoint MousePoint = TPoint(MPoints.x + LSpace, (MPoints.y + TSpace + 25));
		MousePoint = ScreenToClient(MousePoint);

		if(PtInRect(InfoButtonRect, MousePoint))
		{
               versionDblClick(NULL);
		}
	}
}
/*---------------------------------------------------------------------------*/
void __fastcall TMain_Form::WMActivate(TMessage &Msg)
{
	TForm::Dispatch(&Msg);

	Perform(WM_NCPAINT, 0, 0);
}
/*---------------------------------------------------------------------------*/
void __fastcall TMain_Form::WMNCActivate(TMessage &Msg)
{
	TForm::Dispatch(&Msg);

	Perform(WM_NCPAINT, 0, 0);
}

void __fastcall TMain_Form::FormResize(TObject *Sender)
{
     Perform(WM_NCPAINT, 0, 0);
}
//---------------------------------------------------------------------------

