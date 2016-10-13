//---------------------------------------------------------------------------

#ifndef TVideoThreadH
#define TVideoThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
#define _STLP_NO_CSTD_FUNCTION_IMPORTS
#define _FM_NO_REMAP
#include "opencv2/opencv.hpp"
//---------------------------------------------------------------------------
#include "TOptions.h"
#include "Other.h"
//---------------------------------------------------------------------------
class TVideoThread : public TThread
{
private:
	IplImage *FrameInput;
    TOptions Options;
    int IndexPl;
    int NewIndexPl;
    bool fInit;
    bool fReloadCascade;
    TColor ColorFrame;
    int SizeLine;
protected:
	void __fastcall Execute();
public:
	__fastcall TVideoThread( bool CreateSuspended, TOptions _Options,
    						 int _IndexPl, TColor _ColorFrame, int _SizeLine );
    void __fastcall _InputFrame( void );
    void  InputFrame( IplImage* _Grab );
    void ReloadColorFrame( TColor _ColorFrame ) {  ColorFrame = _ColorFrame; };
    void ReloadSizeLine( int _SizeLine ) {  SizeLine = _SizeLine; };
    void __fastcall ReloadOptions( int _Index );
};
//---------------------------------------------------------------------------
#endif

