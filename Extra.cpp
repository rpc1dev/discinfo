//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Extra.h"
#include "Device.h"
#include "Stdlib.h"
#include "Stdio.h"
#include "String.h"
#include "CDVDMain.h"
#include "pngimage.hpp"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TExtra_Box *Extra_Box;
//---------------------------------------------------------------------------
__fastcall TExtra_Box::TExtra_Box(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TExtra_Box::FormCreate(TObject *Sender)
{
        int i=0;
        char title[40];
        char firmware[4];

        Device* dev = devices;

        int pos = deviceCount-Main_Form->ComboBox->ItemIndex-1;

        for (i=0; i < pos; i++)
        {
                dev = dev->next;
        }

        // Hints
        SNText->Hint="Drives serial number if avaible";
        Label31->Hint="Drives physichal interface";
        Label30->Hint="Loading mechanism type";
        LevelText->Hint="The Number of Volume Levels Supported is the number of discrete volume levels supported by the drive";
        BufferText->Hint="The Buffer Size is the number of bytes of buffer dedicated to the data stream returned to the Initiator";

        Label18->Hint="When Audio Play is checked, the drive shall be capable of analog Audio Play";
        Label19->Hint="When Composite is checked, the drive shall be capable of delivering a composite\n Audio and Video data stream from an independent digital port";
        Label20->Hint="When Digital Port (1) is checked, the drive shall support digital output (IEC958) on port 1";
        Label21->Hint="When Digital Port (2) is checked, the drive shall support digital output (IEC958) on port 2";
        Label26->Hint="When UPC is checked, the drive shall support reading Media Catalog Number\n (also known as Uniform Product Code) via the READ SUB-CHANNEL command";
        Label28->Hint="When BUF is checked, the drive shall support buffer under-run free recording on CD-R/RW media";
        Label24->Hint="When Multi Session is checked, the drive shall support reading multiple session CD discs";
        Label22->Hint="When Mode 2 Form 1 is checked, the drive shall support reading CD sectors in Mode 2 Form 1 format";
        Label23->Hint="When Mode 2 Form 2 is checked, the drive shall support reading CD sectors in Mode 2 Form 2 format";
        Label25->Hint="When ISRC is checked, the drive shall support reading\n International Standard Recording Code Information via the READ SUB-CHANNEL command";
        Label27->Hint="When Read Bar Code is checked, the drive shall support reading the disc bar code\n and returning the information via the READ DISC INFORMATION command";
        Label29->Hint="When Mt. Rainier is checked it indicates that the drive is capable of reading\n and possibly writing a disc with the MRW format";

        Label1->Hint="Indicates if the drive can read CDR media";
        Label2->Hint="Indicates if the drive can read CDRW media";
        Label3->Hint="Indicates if the drive shall support the reading fixed packet tracks\n on CD-R/RW media where the Addressing type is Method 2";
        Label5->Hint="Indicates if the drive can read DVD-ROM media";
        Label7->Hint="Indicates if the drive can read DVD-R media";
        Label13->Hint="Indicates if the drive can read DVD-RW media";
        Label6->Hint="Indicates if the drive can read DVD-RAM media";
        Label14->Hint="Indicates if the drive can read DVD+R media";
        Label15->Hint="Indicates if the drive can read DVD+RW media";

        Label8->Hint="Indicates if the drive can write CDR media";
        Label9->Hint="Indicates if the drive can write CDRW media";
        Label12->Hint="Indicates if the drive shall support the test writing";
        Label10->Hint="Indicates if the drive can write DVD-R media";
        Label4->Hint="Indicates if the drive can write DVD-RW media";
        Label11->Hint="Indicates if the drive can write DVD-RAM media";
        Label16->Hint="Indicates if the drive can write DVD+R media";
        Label17->Hint="Indicates if the drive can write DVD+RW media";

        r_cdr->Checked=false;
        r_cdrw->Checked=false;
        r_m2->Checked=false;
        r_dvdrom->Checked=false;
        r_dvdr->Checked=false;
        w_cdr->Checked=false;
        w_cdrw->Checked=false;
        w_dvdr->Checked=false;
        w_dvdram->Checked=false;

        if (!isalnum(dev->firmware_version[0]))
        {
            sprintf(firmware,"%s","????");
        } else
        {
            sprintf(firmware,"%s",Trim(AnsiString(dev->firmware_version)));
        }
        sprintf(title,"%s [%s]",Trim(AnsiString(dev->vendor_name)),firmware);
        l_name->Caption=Trim(AnsiString(title));

        if(dev->audioplay)
                AudioPlay->Checked=true;

        if(dev->composite)
                Composite->Checked=true;

        if(dev->digport1)
                Digiport1->Checked=true;

        if(dev->digport2)
                Digiport2->Checked=true;

        if(dev->UPC)
                upcread->Checked=true;

        if(dev->buffunder)
                BufferUnder->Checked=true;

        if(dev->multisession)
                Multisession->Checked=true;

        if(dev->mode1form)
                Mode2F1->Checked=true;

        if(dev->mode2form)
                Mode2F2->Checked=true;

        if(dev->ISRC)
                isrc->Checked=true;

        if(dev->barcode)
                BarCode->Checked=true;

        if(dev->mtrainier)
                mtrainier->Checked=true;

        if(dev->cdRRead)
                r_cdr->Checked=true;

        if(dev->cdRWRead)
                r_cdrw->Checked=true;

        if(dev->cdMethod2Read)
                r_m2->Checked=true;

        if(dev->dvdRomRead)
                r_dvdrom->Checked=true;

        if(dev->dvdRRead)
                r_dvdr->Checked=true;

        if(dev->dvdRWRead)
                r_dvdrw->Checked=true;

/*
        if(dev->dvdRRead)  // IF -R THEN ALSO -RW
                r_dvdrw->Checked=true;
*/
        if(dev->dvdRamRead)
                r_dvdram->Checked=true;

        if(dev->dvdPRRead)
                r_dvdpr->Checked=true;

        if(dev->dvdPRWRead)
                r_dvdprw->Checked=true;

        if(dev->cdRWrite)
                w_cdr->Checked=true;

        if(dev->cdRWWrite)
                w_cdrw->Checked=true;

        if(dev->testWrite)
                w_test->Checked=true;

        if(dev->dvdRWrite)
            w_dvdr->Checked=true;

        if(dev->dvdRWWrite)
            w_dvdrw->Checked=true;

        if(dev->dvdRamWrite)
                w_dvdram->Checked=true;

        if(dev->dvdPRWrite)
            w_dvdpr->Checked=true;

        if(dev->dvdPRWWrite)
            w_dvdprw->Checked=true;

        if (dev->serial[0] != 0)
                SerialNum->Caption=AnsiString(dev->serial).SubString(0,12);

        if (dev->mechanism[0] != 0)
                Mechanism->Caption=AnsiString(dev->mechanism).Trim();

        if(dev->levels)
                VolumeLevel->Caption=dev->levels;

        if(dev->buffersize)
                BufferSize->Caption=(AnsiString)dev->buffersize+"KB";

        switch(dev->interfacex[0])
        {
            case 0x00:
                Interface->Caption="ATAPI";
                break;
            case 0x01:
                Interface->Caption="SCSI 1";
                break;
            case 0x02:
                Interface->Caption="SCSI 2";
                break;
            case 0x03:
                Interface->Caption="SCSI 3";
                break;
            default:        // IF NOT FOUND
                Interface->Caption="Unknowned";            
                break;
       }
}
//---------------------------------------------------------------------------
void __fastcall TExtra_Box::r_cdrKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        Abort();
}
//---------------------------------------------------------------------------

void __fastcall TExtra_Box::r_cdrMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        Abort();
}
//---------------------------------------------------------------------------

void __fastcall TExtra_Box::CloseClick(TObject *Sender)
{
    TExtra_Box::Close;
}
//---------------------------------------------------------------------------


void __fastcall TExtra_Box::CloseKeyPress(TObject *Sender, char &Key)
{
    switch (Key)
    {
        case VK_SPACE:
            Key=0;
            Extra_Box->ModalResult=mrCancel;
            break;
        case VK_ESCAPE:
            Key=0;
            Extra_Box->ModalResult=mrCancel;
            break;
    }
}
//---------------------------------------------------------------------------

void __fastcall TExtra_Box::Button1Click(TObject *Sender)
{
    const char* sPOST_FileExt = ".png";
    const char* sPOST_Filter  = "Portable Network Graphic (*.png)|*.png";

    Main_Form->SaveDialog->DefaultExt = sPOST_FileExt;
    Main_Form->SaveDialog->Filter = sPOST_Filter;
    Main_Form->SaveDialog->Title = "Save the capabilities window screenshot into file";
    Main_Form->SaveDialog->FileName="";
    
    HDC DC = GetWindowDC(Extra_Box->Handle);
    Graphics::TBitmap *bmp = new Graphics::TBitmap;
    TPNGObject *PNG = new TPNGObject;

    bmp->Height = Extra_Box->Height;
    bmp->Width = Extra_Box->Width;

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
//---------------------------------------------------------------------------
