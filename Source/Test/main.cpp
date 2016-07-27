#include <QtCore>

#include "gameboy.h"

void messageHandler( QtMsgType type, const QMessageLogContext &context, const QString &msg );
QString messageFormat();

int main( int argc, char *argv[] ) {
    QCoreApplication app( argc, argv );

    qSetMessagePattern( messageFormat() );
    qInstallMessageHandler( messageHandler );

    // Set app metadata
    {
        QCoreApplication::setApplicationName( "Game Boy Emulator" );
        QCoreApplication::setApplicationVersion( "0.0" );
        QCoreApplication::setOrganizationName( "athairus" );
        QCoreApplication::setOrganizationDomain( "athair.us" );
    }

    // Options
    QString romPath;

    // Handle arguments
    {
        QCommandLineParser parser;
        parser.addPositionalArgument( "rom", "ROM file", "ROM" );
        parser.addVersionOption();
        parser.addHelpOption();
        parser.setApplicationDescription( "Game Boy Emulator by athairus" );
        parser.process( app );

        if( !parser.positionalArguments().isEmpty() ) {
            romPath = parser.positionalArguments()[ 0 ];
        } else {
            qCritical() << "No ROM file specified!";
            parser.showHelp();
        }
    }

    // Load game into memory
    QFile rom( romPath );

    if( !rom.exists() ) {
        qCritical() << "Given path does not point to a ROM file:" << rom.errorString();
        return 1;
    }

    if( !rom.open( QIODevice::ReadOnly ) ) {
        qCritical() << "Unable to open file:" << rom.errorString();
        return 1;
    }

    QByteArray romData = rom.readAll();
    uint8_t *romBuffer = reinterpret_cast<uint8_t *>( romData.data() );

    // Set up Game Boy
    //GameBoy gameboy( romBuffer, static_cast<size_t>( romData.size() ) );

    // Run it a few times
    for( int i = 0; i < 60000; i++ ) {
        //gameboy.clock();
    }

    return 0;
}

void messageHandler( QtMsgType type, const QMessageLogContext &context, const QString &msg ) {
    // Change this QString to reflect the message you want to get a stack trace for
    if( QString( msg ).contains( QStringLiteral( "No file name specified" ) ) ) {

        // Put a breakpoint over this line...
        int breakPointOnThisLine( 0 );

        // ...not this one
        Q_UNUSED( breakPointOnThisLine );
    }

    // Adapted from Qt 5.6.0 source
    QString logMessage = qFormatLogMessage( type, context, msg );

    // print nothing if message pattern didn't apply / was empty.
    // (still print empty lines, e.g. because message itself was empty)
    if( logMessage.isNull() ) {
        return;
    }

    if( msg.isEmpty() ) {
        fprintf( stdout, "\n" );
    } else {
        fprintf( stdout, "%s\n", logMessage.toLocal8Bit().constData() );
    }

    fflush( stdout );
}

QString messageFormat() {
    return QStringLiteral(
            "%{if-debug}D %{endif}"
            "%{if-info}I %{endif}"
            "%{if-warning}W %{endif}"
            "%{if-critical}C %{endif}"
            "%{if-fatal}F %{endif}"
            "%{time hh:mm:ss:zzz} %{function}():%{line}:\t%{message}"
            //"%{if-debug}\n               [%{file}:%{line} %{function}()]"/*\n%{backtrace depth=20 separator=\"\n\"}*/"%{endif}"
            //"%{if-info}\n               [%{file}:%{line} %{function}()]"/*\n%{backtrace depth=20 separator=\"\n\"}*/"%{endif}"
            "%{if-warning}\n               [%{file}:%{line} %{function}()]"/*\n%{backtrace depth=20 separator=\"\n\"}*/"%{endif}"
            "%{if-critical}\n               [%{file}:%{line} %{function}()]"/*\n%{backtrace depth=20 separator=\"\n\"}*/"%{endif}"
            "%{if-fatal}\n               [%{file}:%{line} %{function}()]"/*\n%{backtrace depth=20 separator=\"\n\"}*/"%{endif}"
            );
}
