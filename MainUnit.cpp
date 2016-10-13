//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonStartStopClick(TObject *Sender)
{
	if( ButtonStartStop->Caption == "Запустить" )
    {
		VideoThread = new TVideoThread( false, Options,
        								ListBox->ItemIndex,
                                        ColorBoxColor->Selected,
                                        ComboBoxSize->ItemIndex + 1 );
        ButtonStartStop->Caption = "Остановить";
    }
    else
    {
    	VideoThread->Terminate();
        ButtonStartStop->Caption = "Запустить";
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ListBoxDrawItem(TWinControl *Control, int Index, TRect &Rect,
          TOwnerDrawState State)
{
    ListBox->Canvas->Font->Color   = clBlack;
    ListBox->Canvas->Brush->Color  = clWhite;
    ListBox->Canvas->FillRect( Rect );
    ListBox->Canvas->Brush->Color = (TColor)RGB( 255, 255, 255 );
    ListBox->Canvas->Pen->Color  = (TColor)RGB( 0, 0, 0 );
    ListBox->Canvas->RoundRect( Rect.Left + 3,  Rect.Top + 3,
            				 	Rect.Right - 2, Rect.Bottom - 2, 8, 8);
	ListBox->Canvas->RoundRect( Rect.Left + 3, Rect.Top + 3,
            					Rect.Right - 3, Rect.Bottom - 3, 5, 5);
	if( State.Contains( odSelected ) )
  	{
        ListBox->Canvas->Brush->Color = (TColor)RGB( 225, 225, 225 );
        ListBox->Canvas->RoundRect( Rect.Left + 3, Rect.Top + 3,
                					Rect.Right - 3, Rect.Bottom - 3, 5, 5);
        ListBox->Canvas->Font->Color = clBlue;
        if( State.Contains( odFocused ) )
        	DrawFocusRect( ListBox->Canvas->Handle, &Rect );
    }

    ImageList->Draw( 	ListBox->Canvas, Rect.Left + 7,
            			Rect.top + (ListBox->ItemHeight - ListBox->Height)%2+7,
                        Index, true) ;

    ListBox->Canvas->TextOut( 	Rect.Left + 40 + 10, Rect.Top + 10,
								Options.GetName( Index ) );
    ListBox->Canvas->TextOut(	Rect.Left + 40 + 10, Rect.Top + 24,
                            	Options.GetInf(  Index ) );
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormClose(TObject *Sender, TCloseAction &Action)
{
    if( ButtonStartStop->Caption == "Остановить" )
	{
        VideoThread->Terminate();
        VideoThread->WaitFor();
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ListBoxClick(TObject *Sender)
{
	if( ButtonStartStop->Caption == "Остановить" )
    {
		VideoThread->ReloadOptions( ListBox->ItemIndex );
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormCreate(TObject *Sender)
{
	for( int i = 0; i < Options.GetCount(); i ++ )
    {
		ListBox->Items->Add("");
		Graphics::TBitmap * bmpPicture = NULL;

		bmpPicture = new Graphics::TBitmap;
		bmpPicture->LoadFromFile( Options.GetFileIcon( i ) );
		ImageList->Add(bmpPicture, bmpPicture);
    }
    ListBox->ItemIndex = 0;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ColorBoxColorChange(TObject *Sender)
{
	if( ButtonStartStop->Caption == "Остановить" )
    {
    	VideoThread->ReloadColorFrame( ColorBoxColor->Selected );
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ComboBoxSizeChange(TObject *Sender)
{
	if( ButtonStartStop->Caption == "Остановить" )
    {
    	VideoThread->ReloadSizeLine( ComboBoxSize->ItemIndex + 1 );
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::NAboutClick(TObject *Sender)
{
	FormAbout->ShowModal();
}
//---------------------------------------------------------------------------

