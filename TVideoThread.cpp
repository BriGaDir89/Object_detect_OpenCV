//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "TVideoThread.h"
#include "MainUnit.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TVideoThread::TVideoThread(	bool CreateSuspended, TOptions _Options,
										int _IndexPl, TColor _ColorFrame,
                                        int _SizeLine ) : TThread( CreateSuspended )
{

	ColorFrame = _ColorFrame;
    SizeLine = _SizeLine;
	Options  = _Options;
    IndexPl  = _IndexPl;
    NewIndexPl = IndexPl;
	Priority = tpNormal;  // приоритет
    fReloadCascade = false;
    fInit = true;
}
//---------------------------------------------------------------------------
void __fastcall TVideoThread::_InputFrame( void )
{
	APIDrawIpl( FrameInput, FormMain->VideoFrame->Handle );
}
//---------------------------------------------------------------------------
void TVideoThread::InputFrame( IplImage* _Grab )
{
	FrameInput = cvCloneImage( _Grab );
	Synchronize( &_InputFrame );
    cvReleaseImage( &FrameInput );
    FrameInput = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TVideoThread::ReloadOptions( int _Index )
{
	NewIndexPl = _Index;
    fInit = true;
}
//---------------------------------------------------------------------------
void __fastcall TVideoThread::Execute()
{
    IplImage *Frame = NULL;

    CvHaarClassifierCascade *Cascade = NULL;

    double FindMoment[ 7 ];
    double FindRange [ 2 ];

	// включение камеры
    CvCapture *Capture = NULL;
   	Capture = cvCreateCameraCapture( CV_CAP_ANY );
    if( !Capture )
    {
    	String text = "¬идео камера в вашей системе не обнаружена.";
    	Application->MessageBox( text.c_str(), FormMain->Caption.c_str(), MB_OK );
    }

   	assert( Capture );

    bool fError = true;

    while( true )
    {
    	if( fInit )
        {
            IndexPl = NewIndexPl;
            switch( Options.GetMethod( IndexPl ) )
            {
                case METHOD_HOUGH: {;} break;
                case METHOD_CONTUR: {
                    fError = LoadMoments(
                    	Options.GetFileSource( IndexPl ), FindRange, FindMoment );
                } break;
                case METHOD_HAAR: {
                    // записать в файл каскада  type_id="opencv-haar-classifier"
                    cvReleaseHaarClassifierCascade( &Cascade );
                    Cascade = ( CvHaarClassifierCascade* ) cvLoad(
                                        Options.GetFileSource( IndexPl ).c_str(),
                                        NULL, NULL, NULL );
                    if( Cascade == NULL )
                    	fError = false;
                } break;
                default: {
                	ShowMessage("Ќеверный метод. ѕроверьте файл натроек программы.");
                };
            }
            fInit = false;
        }

        // запись кадра
        Frame = cvQueryFrame( Capture );

        switch( Options.GetMethod( IndexPl ) )
        {
        	case METHOD_HOUGH: {
            	FindObjectHough( Frame, ColorFrame, SizeLine );
            } break;
            case METHOD_CONTUR: {
            	FindObjectContur( Frame,  FindMoment, FindRange, ColorFrame, SizeLine );
            } break;
            case METHOD_HAAR: {
				FindObjectHaar( Frame, Cascade, ColorFrame, SizeLine );
            } break;
        }


        // расчет отличи€ размера кадра от размера формы дл€ вывода
        float k = FindKResizeFrame( Frame->height, 		Frame->width,
                                    FormMain->VideoFrame->Height,
                                    FormMain->VideoFrame->Width );

        // выделение пам€ти под кадр дл€ вывода
        IplImage *FrameCopy = cvCreateImage(
                                    cvSize( Frame->width / k, Frame->height / k ),
                                    IPL_DEPTH_8U, Frame->nChannels );
        // изменить размер кадра до размеров формы дл€ вывода
        cvResize( Frame, FrameCopy, CV_INTER_LINEAR );

        // вывод кадра на форму
       	InputFrame( Frame );

        cvReleaseImage( &FrameCopy );

        if( Terminated ) {  break; }// прекратить извне поток
    }

    cvReleaseHaarClassifierCascade( &Cascade );
    cvReleaseImage( &Frame );
    cvReleaseCapture( &Capture );
}
//---------------------------------------------------------------------------

