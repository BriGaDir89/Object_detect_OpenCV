//---------------------------------------------------------------------------
#ifndef TOptionsH
#define TOptionsH
//---------------------------------------------------------------------------
#include <IniFiles.hpp>
#include <StdCtrls.hpp>
#include <Vcl.Dialogs.hpp>
//---------------------------------------------------------------------------
enum {
	METHOD_HOUGH  = 0,
    METHOD_CONTUR = 1,
    METHOD_HAAR   = 2
};
//---------------------------------------------------------------------------
class TOptions {
	private:
    	bool LoadFromFile ( void );	// загрузка настроек
        int Count;	// кол-во плагинов/каскадов
        AnsiString *Name; 			// имя для вывода
        AnsiString *Inf;    		// краткая инфа, до 26 символов
		AnsiString *FileIcon;		// имя фала иконки
		AnsiString *FileSource;		// имя файла каскада или моментов
        int        *Method;			// метод поиска объекта

	public:
		TOptions( );
        int GetCount( void ) { return Count; };
        AnsiString GetName ( int Index ) {
             if( Index >= Count || Index < 0 )
             	return "Error";
             else
             	return Name[ Index ];
        };
        AnsiString GetInf( int Index )
        {
        	if( Index >= Count || Index < 0 )
            	return "Error";
        	else
            	return Inf[ Index ];
        };
        AnsiString GetFileIcon( int Index ) {
             if( Index >= Count || Index < 0 )
             	return "Error";
             else
             	return FileIcon[ Index ];
        };
        AnsiString GetFileSource( int Index ) {
        	if( Index >= Count || Index < 0 )
            	return "Error";
            else
            	return FileSource[ Index ];
        };
        int GetMethod( int Index ) {
        	if( Index >= Count || Index < 0 )
            	return -1;
            else
            	return Method[ Index ];
        };
};
//-------------------------------------------------------------------------
#endif
