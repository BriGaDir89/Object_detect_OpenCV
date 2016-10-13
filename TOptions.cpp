//---------------------------------------------------------------------------

#pragma hdrstop

#include "TOptions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#include "TOptions.h"
//---------------------------------------------------------------------------
// конструктор, установка дефолтных настроек
TOptions :: TOptions()
{
	if( !LoadFromFile() ) // если загрузка настроек из файла не удалась
	{
    	Count = 0;
	}
}
//---------------------------------------------------------------------------
// загрузка настроек из файла
bool TOptions :: LoadFromFile ( void )
{
	if( FileExists( ExtractFilePath(Application->ExeName) + "Options.ini" ) )
	{
		TIniFile *Ini = new TIniFile( ExtractFilePath(Application->ExeName) + "Options.ini" );
		try {
            // [PLUGINS]
            Count = Ini->ReadInteger( "PLUGINS", "Count", 0 );
            if( Count > 0 )
            {
              	Name 	   = new AnsiString[ Count ];
                Inf 	   = new AnsiString[ Count ];
                FileIcon   = new AnsiString[ Count ];
                FileSource = new AnsiString[ Count ];
                Method     = new int       [ Count ];
                for( int i = 0; i < Count; i ++ )
                {
                	Name[ i ] 		= Ini->ReadString( "PLUGINS",
                    					"Name" + IntToStr( i + 1 ), "Ошибка" );
                    Inf[ i ] 		= Ini->ReadString( "PLUGINS",
                    					"Inf" + IntToStr( i + 1 ), "Ошибка" );
                    FileIcon[ i ] 	= Ini->ReadString( "PLUGINS",
                    					"FileIcon" + IntToStr( i + 1 ), "Error" );
                    FileSource[ i ] = Ini->ReadString( "PLUGINS",
                    					"FileSource" + IntToStr( i + 1 ), "Error" );
                    Method[ i ]     = Ini->ReadInteger( "PLUGINS",
                    					"Method" + IntToStr( i + 1 ), -1 );
                }
            }
		} __finally { delete Ini; }
		return true;
	}
	else
	{
		return false;
	}
}
//---------------------------------------------------------------------------
