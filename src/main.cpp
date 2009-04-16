#include <QApplication>
#include "mainwindowimpl.h"
//
void printUsage( const char * progname );

int main(int argc, char ** argv)
{

	QApplication app( argc, argv );
	if ( !QGLFormat::hasOpenGL() ) 
		qFatal( "This system has no OpenGL support" ); 
		
		
		
		
	QString filename;
	
	for( int i = 1; i < argc; i ++ ) {
		if( ( QString( "-h" ) == argv[ i ] ) ||
			( QString( "--help" ) == argv[ i ] ) ) {
			printUsage( argv[0] );
			exit( 1 );
		}
		
		if( QString( argv[ i ] ).startsWith( "-" ) ) {
		qWarning( "ERROR: Invalid argument specified: %s",
		argv[ i ] );
		printUsage( argv[ 0 ] );
		exit( 1 );
        }

        filename = argv[ i ];
    }


	MainWindowImpl win;
	win.show(); 
	app.connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT( quit() ) );
	return app.exec();
}

void printUsage( const char * progname ) {
    qWarning( "Usage is:\n" );
    qWarning(
            "%s <options> <filename>\n"
            "    To start Parade with options and loading <filename>.\n",
            progname );
    qWarning(
            "%s [-h|--help]\n"
            "    Print these instructions.\n",
            progname );
}
