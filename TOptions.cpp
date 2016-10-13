//---------------------------------------------------------------------------

#pragma hdrstop

#include "TOptions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#include "TOptions.h"
//---------------------------------------------------------------------------
// �����������, ��������� ��������� ��������
TOptions :: TOptions()
{
	if( !LoadFromFile() ) // ���� �������� �������� �� ����� �� �������
	{
    	Count = 0;
	}
}
//---------------------------------------------------------------------------
// �������� �������� �� �����
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
                    					"Name" + IntToStr( i + 1 ), "������" );
                    Inf[ i ] 		= Ini->ReadString( "PLUGINS",
                    					"Inf" + IntToStr( i + 1 ), "������" );
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
