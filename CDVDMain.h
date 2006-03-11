//---------------------------------------------------------------------------

#ifndef CDVDMainH
#define CDVDMainH

// #define DISCInfo_DEBUG

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include "Device.h"
#include "VersionInfoComponent.h"
//---------------------------------------------------------------------------
class TMain_Form : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TGroupBox *GroupBox1;
        TGroupBox *GroupBox2;
        TMainMenu *MainMenu1;
        TMenuItem *File1;
        TMenuItem *SaveData1;
        TMenuItem *Exit1;
        TMenuItem *About1;
        TLabel *fw_version;
        TLabel *fw_date;
        TLabel *specific;
        TLabel *region_status;
        TLabel *version;
        TLabel *date;
        TLabel *specific_d;
        TLabel *status_rpc;
        TLabel *reg_status;
        TLabel *permanent_status;
        TLabel *changes_left;
        TLabel *manuf_left;
        TLabel *region_set;
        TLabel *fw_code;
        TLabel *change_data;
        TLabel *man_data;
        TLabel *set_data;
        TSaveDialog *SaveDialog;
        TMenuItem *N1;
        TComboBox *ComboBox;
        TLabel *read_s;
        TLabel *write_s;
        TLabel *readval;
        TLabel *writeval;
        TMenuItem *Displayotherdevices1;
        TMenuItem *ExtraInfo1;
        TMenuItem *View1;
    TMenuItem *Firmwareupdates1;
    TMenuItem *CopyToClipboard1;
    TMenuItem *Options1;
    TMenuItem *ASPI1;
    TMenuItem *SPTI1;
    TMenuItem *Resfresh1;
    TMenuItem *N2;
        void __fastcall Exit1Click(TObject *Sender);
        void __fastcall SaveData1Click(TObject *Sender);
        void __fastcall About1Click(TObject *Sender);
        void __fastcall ComboBoxChange(TObject *Sender);
        void __fastcall ComboBoxKeyPress(TObject *Sender, char &Key);
        void __fastcall Displayotherdevices1Click(TObject *Sender);
        void __fastcall ExtraInfo1Click(TObject *Sender);
    void __fastcall Firmwareupdates1Click(TObject *Sender);
    void __fastcall CopyToClipboard1Click(TObject *Sender);
    void __fastcall SPTI1Click(TObject *Sender);
    void __fastcall ASPI1Click(TObject *Sender);
    void __fastcall Resfresh1Click(TObject *Sender);
    void __fastcall versionDblClick(TObject *Sender);
     void __fastcall FormResize(TObject *Sender);
private:	// User declarations
#define ABOUT_BUTTON_H
/*info button rect*/
TRect InfoButtonRect;
TRect HelpButtonRect;
/*os message functions*/
void __fastcall WMNCLButtonDown(TMessage &Msg);
void __fastcall WMNCPaint(TMessage &Msg);
void __fastcall WMNCActivate(TMessage &Msg);
void __fastcall WMActivate(TMessage &Msg);
/*catch os messages*/
BEGIN_MESSAGE_MAP
	VCL_MESSAGE_HANDLER(WM_NCLBUTTONDOWN, TMessage, WMNCLButtonDown)
	VCL_MESSAGE_HANDLER(WM_NCPAINT,       TMessage, WMNCPaint)
	VCL_MESSAGE_HANDLER(WM_NCACTIVATE,    TMessage, WMNCActivate)
	VCL_MESSAGE_HANDLER(WM_ACTIVATE,      TMessage, WMActivate)
END_MESSAGE_MAP(TForm)
public:		// User declarations
    __fastcall TMain_Form(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMain_Form *Main_Form;
int getOsVersion();
void GetDeviceData(Device *device);
void start_log();
void write_log(char *debug_string);
//---------------------------------------------------------------------------
#endif

