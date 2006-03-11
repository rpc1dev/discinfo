//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Searchf.h"
#include "Aspi.h"
#include "Device.h"
#include "Stdlib.h"
#include "Stdio.h"
#include "String.h"
#include "CDVDMain.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSearch_Box *Search_Box;
//---------------------------------------------------------------------------
__fastcall TSearch_Box::TSearch_Box(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TSearch_Box::FormCreate(TObject *Sender)
{
        int i=0;
        char vendor[8];
        char model[8];
        char tempvar[20];
        char tempvar2[20];
        char firmware[4];
        char title[40];
        char *spacer;
        char *spacer2;
        Device* dev = devices;

        int pos = deviceCount-Main_Form->ComboBox->ItemIndex-1;

        for (i=0; i < pos; i++)
        {
                dev = dev->next;
        }

        //sprintf(dev->vendor_name,"PLEXTOR CD-R   PX-W3434");
        //sprintf(dev->vendor_name,"HL-DT-STDVD-ROM GDR8160B");
        //sprintf(dev->vendor_name,"YAMAHA  CRW8424E   ");
        //sprintf(dev->vendor_name,"SONY    DVD RW DRU-500A");
        //sprintf(dev->vendor_name,"PIONEER DVD-RW  DVR-104");
        
        if (!isalnum(dev->firmware_version[0]))
        {
            sprintf(firmware,"%s","????");
        } else
        {
            sprintf(firmware,"%s",Trim(AnsiString(dev->firmware_version)));
        }
        sprintf(title,"%s [%s]",Trim(AnsiString(dev->vendor_name)),firmware);
        TheName->Caption=Trim(AnsiString(title));

        memcpy(vendor, dev->vendor_name, 8);
        vendor[8] = 0;
        VendorBox->Caption=Trim(AnsiString(vendor));

        sprintf(tempvar2,"%s",Trim(AnsiString(dev->vendor_name+8)));
        spacer=strstr(tempvar2," ");
        if (spacer!=NULL)
        {
            spacer++;
            sprintf(tempvar,"%s",TrimRight(AnsiString(spacer)));
            
            spacer2=strstr(tempvar," ");
            if (spacer2!=NULL)
            {
                spacer2++;
                sprintf(tempvar,"%s",spacer2);
            }
        }
        if (spacer==NULL)
        {
            ModelBox->Caption=Trim(AnsiString(dev->vendor_name+8));

        } else
        {
            ModelBox->Caption=Trim(AnsiString(tempvar));
        }
}
//---------------------------------------------------------------------------

void __fastcall TSearch_Box::CloseBtnClick(TObject *Sender)
{
    TSearch_Box::Close();
}
//---------------------------------------------------------------------------

void __fastcall TSearch_Box::SrchButtonClick(TObject *Sender)
{
        char search[500];
        if (VendorBox->Checked && ModelBox->Checked)
        {
            sprintf(search,"http://forum.rpc1.org/dl_result.php?kaj=1&isces=%s %s",VendorBox->Caption,ModelBox->Caption);
        }
        if (VendorBox->Checked && !ModelBox->Checked)
        {
            sprintf(search,"http://forum.rpc1.org/dl_result.php?kaj=1&isces=%s",VendorBox->Caption);
        }
        if (!VendorBox->Checked && ModelBox->Checked)
        {
            sprintf(search,"http://forum.rpc1.org/dl_result.php?kaj=1&isces=%s",ModelBox->Caption);
        }
        if (!VendorBox->Checked && !ModelBox->Checked)
        {
      		Application->MessageBox ("You have to check at least one option.", "Error", MB_OK | MB_ICONSTOP);
            return;
        }
        ShellExecute(Application->Handle,"open",search,"","",0);
}
//---------------------------------------------------------------------------
void __fastcall TSearch_Box::VendorBoxKeyPress(TObject *Sender, char &Key)
{
    if (Key == 'x' || Key == 'X' || Key == VK_ESCAPE)
    {
        TSearch_Box::Close();
    }
}
//---------------------------------------------------------------------------

void __fastcall TSearch_Box::ModelBoxKeyPress(TObject *Sender, char &Key)
{
    if (Key == 'x' || Key == 'X' || Key == VK_ESCAPE)
    {
        TSearch_Box::Close();
    }
}
//---------------------------------------------------------------------------

void __fastcall TSearch_Box::SrchButtonKeyPress(TObject *Sender, char &Key)
{
    if (Key == 'x' || Key == 'X' || Key == VK_ESCAPE)
    {
        TSearch_Box::Close();
    }
}
//---------------------------------------------------------------------------

void __fastcall TSearch_Box::CloseBtnKeyPress(TObject *Sender, char &Key)
{
    if (Key == 'x' || Key == 'X' || Key == VK_ESCAPE)
    {
        TSearch_Box::Close();
    }
}
//---------------------------------------------------------------------------

