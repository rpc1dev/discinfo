//---------------------------------------------------------------------------

#ifndef SearchH
#define SearchH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TSearch_Box : public TForm
{
__published:	// IDE-managed Components
        TPanel *MainPanel;
        TPanel *DriveName;
        TLabel *TheName;
        TGroupBox *GroupOkno;
        TBitBtn *SrchButton;
        TPanel *TextPanel;
    TLabel *Label1;
        TCheckBox *VendorBox;
    TCheckBox *ModelBox;
        TBitBtn *CloseBtn;
    TLabel *Label2;
    TLabel *Label3;
        void __fastcall FormCreate(TObject *Sender);
    void __fastcall CloseBtnClick(TObject *Sender);
    void __fastcall SrchButtonClick(TObject *Sender);
    void __fastcall VendorBoxKeyPress(TObject *Sender, char &Key);
    void __fastcall ModelBoxKeyPress(TObject *Sender, char &Key);
    void __fastcall SrchButtonKeyPress(TObject *Sender, char &Key);
    void __fastcall CloseBtnKeyPress(TObject *Sender, char &Key);
private:	// User declarations
public:		// User declarations
    __fastcall TSearch_Box(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSearch_Box *Search_Box;
//---------------------------------------------------------------------------
#endif
