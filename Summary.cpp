//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Summary.h"
#include "Aspi.h"
#include "Stdlib.h"
#include "Stdio.h"
#include "String.h"
#include "CDVDMain.h"
#include "pngimage.hpp"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSumInfo *SumInfo;
//---------------------------------------------------------------------------
__fastcall TSumInfo::TSumInfo(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TSumInfo::FormCreate(TObject *Sender)
{
        char forfile[100];
        char rpc[10];
        char firma[8];
        char kater_model[16];
        char DISCInfoVer[15];        
        int i;
        TStringList *slInfo = new TStringList();
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
                }
                SumText->Lines->Add(slInfo->Text);
                slInfo->Text="";
                dev = dev->next;
        }
}
//---------------------------------------------------------------------------
void __fastcall TSumInfo::ClipboardClick(TObject *Sender)
{
    SumText->SelectAll();
    SumText->CopyToClipboard();    
}
//---------------------------------------------------------------------------

void __fastcall TSumInfo::SumTextKeyPress(TObject *Sender, char &Key)
{
    if (Key == 'g' || Key == 'G')
    {
        Key = 0;

        const char* sPOST_FileExt = ".png";
        const char* sPOST_Filter  = "Portable Network Graphic (*.png)|*.png";

        Main_Form->SaveDialog->DefaultExt = sPOST_FileExt;
        Main_Form->SaveDialog->Filter = sPOST_Filter;
        Main_Form->SaveDialog->Title = "Save the summary info screenshot into file";
        Main_Form->SaveDialog->FileName="";
        
        HDC DC = GetWindowDC(SumInfo->Handle);
        Graphics::TBitmap *bmp = new Graphics::TBitmap;
        TPNGObject *PNG = new TPNGObject;

        bmp->Height = SumInfo->Height;
        bmp->Width = SumInfo->Width;

        Main_Form->ComboBox->SetFocus();

        BitBlt(bmp->Canvas->Handle, 0, 0, bmp->Width, bmp->Height, DC, 0, 0, SRCCOPY);

        PNG->Assign(bmp);

        if (Main_Form->SaveDialog->Execute())
        {
            if (FileExists(Main_Form->SaveDialog->FileName))
            {
                if (!DeleteFile(Main_Form->SaveDialog->FileName))
                {
                    Application->MessageBox("Unable to save to file. Maybe file is write protected?", "Error", MB_OK | MB_ICONSTOP);
                    Abort();
                }
            }

            PNG->SaveToFile(Main_Form->SaveDialog->FileName);
        }
        Main_Form->SaveDialog->FileName="";        

        // bmp->SaveToFile("_DISCInfo.bmp");

        ReleaseDC(0, DC);
        delete bmp;
        delete PNG;
    }
}
//---------------------------------------------------------------------------

