//---------------------------------------------------------------------------
#ifndef OtherH
#define OtherH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Dialogs.hpp>
#include <IniFiles.hpp>
//---------------------------------------------------------------------------
#define _STLP_NO_CSTD_FUNCTION_IMPORTS
#define _FM_NO_REMAP
#include "opencv2/opencv.hpp"
//---------------------------------------------------------------------------
#define WIDTHBYTES(bits) ((((bits) + 31) / 32) * 4)
//---------------------------------------------------------------------------
// IplImage to HBITMAP
HBITMAP CreateRGBBitmap( IplImage* _Grab )
{
   	char *App;
   	IplImage *_Grab3 = 0, *_Grabf = 0;

	LPBITMAPINFO lpbi = new BITMAPINFO;

   	lpbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
   	lpbi->bmiHeader.biWidth = _Grab->width;
   	lpbi->bmiHeader.biHeight =_Grab->height;
   	lpbi->bmiHeader.biPlanes = 1;
   	lpbi->bmiHeader.biBitCount = 24;
   	lpbi->bmiHeader.biCompression = BI_RGB;
   	lpbi->bmiHeader.biSizeImage = WIDTHBYTES((DWORD)_Grab->width * 8) * _Grab->height;
   	lpbi->bmiHeader.biXPelsPerMeter = 0;
   	lpbi->bmiHeader.biYPelsPerMeter = 0;
   	lpbi->bmiHeader.biClrUsed = 0;
   	lpbi->bmiHeader.biClrImportant = 0;

	void* pBits;
   	HBITMAP hBitmap = CreateDIBSection( 	NULL, lpbi, DIB_RGB_COLORS,
   										(void **)&pBits, NULL, 0 );
   	delete lpbi;

   	if( hBitmap )
		App = (char*)pBits;

   	// Если глубина изображения не IPL_DEPTH_8U (однобайтовое целое), конвертируем
   	if( _Grab->depth != IPL_DEPTH_8U )
   	{
		_Grabf = cvCloneImage( _Grab );
      	if( _Grab )
        	cvReleaseImage( &_Grab );
		_Grab = cvCreateImage( cvSize( _Grabf->width, _Grabf->height ), IPL_DEPTH_8U, _Grabf->nChannels );
		cvConvert(_Grabf,_Grab);
		if( _Grabf )
         cvReleaseImage( &_Grabf );
	}

   	// Если изображение содержит один канал, создаем трехканальное изображение
   	// Серое или бинарное
   	if( _Grab->nChannels == 1 )
   	{
		_Grab3 = cvCreateImage( cvSize(_Grab->width,_Grab->height),IPL_DEPTH_8U,3);
      	cvMerge(_Grab,_Grab,_Grab,NULL,_Grab3);
   	}

   	// Если входное изображение трехканальное, просто копируем указатель на него
   	// Цветное
   	if( _Grab->nChannels == 3 )
   	{
		_Grab3 = _Grab;
   	}

   	// Получаем указатель на данные
   	unsigned char* data;
   	cvGetRawData( _Grab3, (uchar**)&data );

   	// Копируем данные
   	if( _Grab3 )
   	{
		for( int i = 0; i < _Grab->height; i ++ )
      	{
        	memcpy( App  + _Grab3->widthStep * (_Grab3->height - i - 1 ),
            		data + _Grab3->widthStep * i,
                    _Grab3->width * 3 );
      	}
	}

	// Очищаем память если создавали изображение, а не копировали указатель
   	if( _Grab->nChannels == 1 )
    	cvReleaseImage( &_Grab3 );

	return hBitmap;
}
//---------------------------------------------------------------------------
// Вывести IplImage на форму
// _Grab - что вывести
// HANDLE - куда выывести
void APIDrawIpl( IplImage* _Grab, void *HANDLE )
{
	HDC hMemDC,hDC;
   	hDC = GetDC( (HWND__*)HANDLE );
   	hMemDC = CreateCompatibleDC( hDC );
   	HBITMAP Bitmap = CreateRGBBitmap( _Grab );
   	SelectObject( hMemDC, Bitmap );
   	BitBlt( hDC, 0, 0, _Grab->width, _Grab->height, hMemDC, 0, 0, SRCCOPY );

   	DeleteObject( Bitmap );
   	DeleteDC( hMemDC );
   	DeleteDC( hDC );
}
//---------------------------------------------------------------------------
// расчитывает коэффициэнт отличия размеров карда
int FindKResizeFrame( int hIn, int wIn, int hOut, int wOut )
{
    int k = hIn / hOut;
   	if( ( wIn / wOut ) > k )
   	{
    	k = wIn / wOut;
   	}
    return k;
}
//---------------------------------------------------------------------------
// загрузка момента из файла
// FindMoment - моменты искомого контура
// RangeFind - диапазон в который должен попаждать результат сравнения моментов
// return true - всё хорошеё
// return false - ошибка загрузки
bool LoadMoments( AnsiString NameFile, double FindRange[], double FindMoment[]  )
{
	if( FileExists( NameFile) )
	{
		TIniFile *Ini = new TIniFile( NameFile );
		try {
            for( int i = 0; i < 9; i ++ )
            {
                if( i < 2 )
                    FindRange[ i ] = Ini->ReadFloat( "MOMENT",
                                          "FindRange" + IntToStr( i ), 0 );
                else
                {
                    FindMoment[ i - 2 ] = Ini->ReadFloat( "MOMENT",
                                          "FindMoment" + IntToStr( i - 2 ), -3 );
                }
            }
		} __finally { delete Ini; }
		return true;
	}
	else
		return false;
}
//---------------------------------------------------------------------------
//  сравнение контуров
// contour - момент которого надо сравнить с известным моментом
// mb - известный момент
double cvMatchShapesMy( const void* contour, double mb[] )
{
    CvMoments moments;
    CvHuMoments huMoments;
    double ma[7];
    int sma, smb;
    double eps = 1.e-5;
    double mmm;
    double result = 0;

    cvMoments( contour, &moments );
    cvGetHuMoments( &moments, &huMoments );

    ma[0] = huMoments.hu1;
    ma[1] = huMoments.hu2;
    ma[2] = huMoments.hu3;
    ma[3] = huMoments.hu4;
    ma[4] = huMoments.hu5;
    ma[5] = huMoments.hu6;
    ma[6] = huMoments.hu7;


	for( int i = 0; i < 7; i++ )
    {
		double ama = fabs( ma[i] );
        double amb = fabs( mb[i] );

        if( ma[i] > 0 ) sma = 1;
        else if( ma[i] < 0 ) sma = -1;
        	 else sma = 0;
        if( mb[i] > 0 ) smb = 1;
        else if( mb[i] < 0 ) smb = -1;
        	 else smb = 0;

        if( ama > eps && amb > eps )
		{
			ama = sma * log10( ama );
            amb = smb * log10( amb );
            mmm = fabs( (ama - amb) / ama );
                        if( result < mmm ) result = mmm;
        }
    }

    return result;
}
//---------------------------------------------------------------------------
// поиск объекта, Haar
// Frame - исходное изображение
// Cascade - обученный каскад
void FindObjectHaar( IplImage* Frame, CvHaarClassifierCascade *Cascade, TColor ColorFrame, int SizeLine  )
{
	CvMemStorage *MemStorage = cvCreateMemStorage( 0 );
	// поиск объекта
	CvSeq *faces = cvHaarDetectObjects( Frame, Cascade, MemStorage, 1.1, 6,
        							 		CV_HAAR_DO_CANNY_PRUNING,
                                     		cvSize( 0, 0 ) );

    // выделение объекта
    for( int i = 0; i < (faces ? faces->total:0); i ++ )
    {
    	CvRect* r = (CvRect*)cvGetSeqElem( faces, i );
        CvPoint pt1 = { r->x, r->y };
        CvPoint pt2 = { r->x + r->width, r->y + r->height };
        cvRectangle( 	Frame, pt1, pt2,
            				CV_RGB( (int)GetRValue( ColorFrame ),
                            		(int)GetGValue( ColorFrame ),
                                    (int)GetBValue( ColorFrame ) ),
                            SizeLine, 8, 0 );
    }
    cvReleaseMemStorage( &MemStorage );
}
//---------------------------------------------------------------------------
void FindObjectContur(  IplImage *Frame, double FindMoment[], double FindRange[],
						TColor ColorFrame, int SizeLine )
{
    IplImage *FrameGray = cvCreateImage( cvSize(Frame->width, Frame->height ), IPL_DEPTH_8U, 1 );
  	cvCvtColor(Frame, FrameGray, CV_RGB2GRAY);
  	cvSmooth(FrameGray, FrameGray, CV_GAUSSIAN, 5, 5 );

  	// преобразуем в двоичное
  	IplImage *FrameBin = cvCreateImage( cvSize(Frame->width, Frame->height ), IPL_DEPTH_8U, 1 );
  	cvInRangeS(FrameGray, cvScalar(120), cvScalar(230), FrameBin);

  	// находим контуры
  	CvSeq* Contours = NULL;
  	CvMemStorage *StorageFc = cvCreateMemStorage(0);
  	cvFindContours( FrameBin, StorageFc, &Contours, sizeof( CvContour ),
  					CV_RETR_LIST,CV_CHAIN_APPROX_SIMPLE, cvPoint( 0, 0 ) );

	for( CvSeq *seq0 = Contours; seq0 != 0; seq0 = seq0->h_next )
  	{
  		if( cvContourPerimeter(seq0) < 80.0 ) continue;
  		if( cvContourPerimeter(seq0) > 2000.0 ) continue;
        double Match0 = cvMatchShapesMy( seq0, FindMoment ); // сравнить контуры
        if( ( Match0 >= FindRange[ 0 ] ) && ( Match0 <= FindRange[ 1 ] ) )
        {
            CvPoint2D32f Point;
            float Rad = 0;
            cvMinEnclosingCircle( seq0, &Point, &Rad );
            CvPoint Point1, Point2;
            Point1.x = Point.x - Rad;
            Point1.y = Point.y - Rad;
            Point2.x = Point.x + Rad;
            Point2.y = Point.y + Rad;
            cvRectangle( 	Frame, Point1, Point2,
            				CV_RGB( (int)GetRValue( ColorFrame ),
                                    (int)GetGValue( ColorFrame ),
                                    (int)GetBValue( ColorFrame ) ),
                            SizeLine, 8, 0 );

        }
    }
	cvReleaseImage( &FrameGray );
	cvReleaseImage( &FrameBin );
    cvReleaseMemStorage( &StorageFc );
}
//---------------------------------------------------------------------------
// поиск объекта, Хаф
void FindObjectHough( IplImage* Frame, TColor ColorFrame, int SizeLine )
{
    IplImage *FrameGray = cvCreateImage( cvSize(Frame->width, Frame->height ), IPL_DEPTH_8U, 1 );
    cvCvtColor(Frame, FrameGray, CV_RGB2GRAY);

    CvMemStorage* storage = cvCreateMemStorage(0);
    cvSmooth(FrameGray, FrameGray, CV_GAUSSIAN, 5, 5 );
    // поиск кругов
    CvSeq* Contours = cvHoughCircles(
                FrameGray,
                storage,
                CV_HOUGH_GRADIENT,
                1,
                FrameGray->width/5
                );
    // пробегаемся по кругам и рисуем их на оригинальном изображении
   	for( int i = 0; i < Contours->total; i ++ )
    {
       	float* p = (float*) cvGetSeqElem( Contours, i );
        CvPoint pt = cvPoint( cvRound( p[0] ), cvRound( p[1] ) );
        float Rad = 0;
        //cvCircle( Frame, pt, cvRound( p[2] ), CV_RGB(0xff,0,0) );

        CvPoint Point1, Point2;
        Point1.x = pt.x - p[2]*1.2;
        Point1.y = pt.y - p[2]*1.2;
        Point2.x = pt.x + p[2]*1.2;
        Point2.y = pt.y + p[2]*1.2;
        cvRectangle( 	Frame, Point1, Point2,
            				CV_RGB( (int)GetRValue( ColorFrame ),
                                    (int)GetGValue( ColorFrame ),
                                    (int)GetBValue( ColorFrame ) ),
                            SizeLine, 8, 0 );

    }

    cvReleaseMemStorage( &storage );
    cvReleaseImage( &FrameGray );
}
//---------------------------------------------------------------------------
#endif

