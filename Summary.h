//---------------------------------------------------------------------------

#ifndef SummaryH
#define SummaryH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TSumInfo : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TGroupBox *GroupBox1;
    TMemo *SumText;
    TBitBtn *Clipboard;
    TBitBtn *Close;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall ClipboardClick(TObject *Sender);
    void __fastcall SumTextKeyPress(TObject *Sender, char &Key);
private:	// User declarations
public:		// User declarations
    __fastcall TSumInfo(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSumInfo *SumInfo;
//---------------------------------------------------------------------------
#endif
