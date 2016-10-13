//---------------------------------------------------------------------------

#ifndef MainUnitH
#define MainUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Menus.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.StdActns.hpp>
//---------------------------------------------------------------------------
#define _STLP_NO_CSTD_FUNCTION_IMPORTS
#define _FM_NO_REMAP
#include "opencv2/opencv.hpp"
//---------------------------------------------------------------------------
#include "UnitAbout.h"
#include "TVideoThread.h"
#include "TOptions.h"
#include "Other.h"
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
	TButton *ButtonStartStop;
	TScrollBox *VideoFrame;
	TListBox *ListBox;
	TImageList *ImageList;
	TMainMenu *MainMenu;
	TMenuItem *File1;
	TLabel *Label1;
	TGroupBox *GroupBox1;
	TColorBox *ColorBoxColor;
	TComboBox *ComboBoxSize;
	TLabel *Label2;
	TLabel *Label3;
	TActionList *ActionList;
	TFileExit *FileExit;
	TMenuItem *N1;
	TMenuItem *NAbout;
	void __fastcall ButtonStartStopClick(TObject *Sender);
	void __fastcall ListBoxDrawItem(TWinControl *Control, int Index, TRect &Rect, TOwnerDrawState State);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall ListBoxClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ColorBoxColorChange(TObject *Sender);
	void __fastcall ComboBoxSizeChange(TObject *Sender);
	void __fastcall NAboutClick(TObject *Sender);

private:	// User declarations
public:		// User declarations
	TVideoThread *VideoThread;
	__fastcall TFormMain(TComponent* Owner);
	TOptions Options;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
