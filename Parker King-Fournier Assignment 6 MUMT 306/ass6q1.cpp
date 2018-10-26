//*****************************************//
//  Parker King-Fournier
//  Assignmet 6, question 1
//
// Compiler Statement: g++ ass6q1.cpp RtMidi.cpp
// Run Statement: ./a.out
//*****************************************//


#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include "RtMidi.h"

//Platform-dependent sleep routines.
#if defined(__WINDOWS_MM__)
	#include <windows.h>
	#define SLEEP( milliseconds ) Sleep( (DWORD) milliseconds ) 
#else // Unix variants
	#include <unistd.h>
	#define SLEEP( milliseconds ) usleep( (unsigned long) (milliseconds * 1000.0) )
#endif

bool chooseMidiPort( RtMidiOut *rtmidi );

int main()
{
	//Change this variable to change how many times it loops
	int loops = 1; 

	RtMidiOut *midiout = new RtMidiOut();
	std::vector<unsigned char> message;

	int counter = 0;
	int measure_counter = 0;

	try 
	{
		if ( chooseMidiPort( midiout ) == false ) goto cleanup;
	}
	catch ( RtMidiError &error ) 
	{
		error.printMessage();
		goto cleanup;
	}

	//Program change: 193, 39
	//For the Bass
	message.push_back( 193 );
	message.push_back( 39 );
	midiout->sendMessage( &message );

	//Program change: 194, 88
	//For the Synth
	message.push_back( 194 );
	message.push_back( 88 );
	midiout->sendMessage( &message );


	while( measure_counter < loops )
	{
		//____________________This is the Drum Beat______________________
		if( counter % 4 == 0 )
		{
			//Kick
			message[0] = 153;
			message[1] = 36;
			message[2] = 64;
			midiout->sendMessage( &message );
		}
		if( counter % 4 == 0 && counter != 0 && counter % 8 != 0 )
		{
			//Hat
			message[0] = 153;
			message[1] = 28;
			message[2] = 64;
			midiout->sendMessage( &message );
		}

		//____________________This is the Bass Line______________________
		if( counter == 0 )
		{
			message[0] = 129;
			message[1] = 41;
			message[2] = 64;
			midiout->sendMessage( &message );

			message[0] = 129;
			message[1] = 45;
			message[2] = 64;
			midiout->sendMessage( &message );

			message[0] = 145;
			message[1] = 38;
			message[2] = 64;
			midiout->sendMessage( &message );

			message[0] = 145;
			message[1] = 41;
			message[2] = 64;
			midiout->sendMessage( &message );
		}
		if( counter == 16 )
		{
			message[0] = 130;
			message[1] = 71;
			message[2] = 64;
			midiout->sendMessage( &message );

			message[0] = 129;
			message[1] = 38;
			message[2] = 64;
			midiout->sendMessage( &message );

			message[0] = 129;
			message[1] = 41;
			message[2] = 64;
			midiout->sendMessage( &message );

			message[0] = 145;
			message[1] = 31;
			message[2] = 64;
			midiout->sendMessage( &message );

			message[0] = 145;
			message[1] = 43;
			message[2] = 64;
			midiout->sendMessage( &message );
		}
		if( counter == 32 ) 
		{ 
			message[0] = 129;
			message[1] = 31;
			message[2] = 64;
			midiout->sendMessage( &message );

			message[0] = 129;
			message[1] = 43;
			message[2] = 64;
			midiout->sendMessage( &message );

			message[0] = 145;
			message[1] = 45;
			message[2] = 64;
			midiout->sendMessage( &message );

			message[0] = 145;
			message[1] = 48;
			message[2] = 64;
			midiout->sendMessage( &message );
		}
		if( counter == 48 ) 
		{
			message[0] = 130;
			message[1] = 69;
			message[2] = 64;
			midiout->sendMessage( &message );

			message[0] = 129;
			message[1] = 45;
			message[2] = 64;
			midiout->sendMessage( &message );

			message[0] = 129;
			message[1] = 48;
			message[2] = 64;
			midiout->sendMessage( &message );

			message[0] = 145;
			message[1] = 41;
			message[2] = 64;
			midiout->sendMessage( &message );

			message[0] = 145;
			message[1] = 45;
			message[2] = 64;
			midiout->sendMessage( &message );
		}

		//____________________This is the Melody______________________
		if ( counter == 1 || counter == 3 || counter == 7 || counter == 9)
		{
			message[0] = 130;
			message[1] = 69;
			message[2] = 64;
			midiout->sendMessage( &message );

			message[0] = 146;
			message[1] = 77;
			message[2] = 64;
			midiout->sendMessage( &message );		
		}
		if ( counter == 2 || counter == 33 || counter == 35 || counter == 39 || counter == 41 )
		{
			message[0] = 130;
			message[1] = 77;
			message[2] = 64;
			midiout->sendMessage( &message );

			message[0] = 146;
			message[1] = 76;
			message[2] = 64;
			midiout->sendMessage( &message );	
		}
		if ( counter == 4 || counter == 34)
		{
			message[0] = 130;
			message[1] = 76;
			message[2] = 64;
			midiout->sendMessage( &message );

			message[0] = 146;
			message[1] = 74;
			message[2] = 64;
			midiout->sendMessage( &message );	
		}
		if ( counter == 8 || counter == 36)
		{
			message[0] = 130;
			message[1] = 74;
			message[2] = 64;
			midiout->sendMessage( &message );

			message[0] = 146;
			message[1] = 72;
			message[2] = 64;
			midiout->sendMessage( &message );	
		}
		if ( counter == 10 || counter == 40)
		{
			message[0] = 130;
			message[1] = 72;
			message[2] = 64;
			midiout->sendMessage( &message );

			message[0] = 146;
			message[1] = 71;
			message[2] = 64;
			midiout->sendMessage( &message );	
		}
		if ( counter == 42 ) 
		{
			message[0] = 130;
			message[1] = 71;
			message[2] = 64;
			midiout->sendMessage( &message );

			message[0] = 146;
			message[1] = 69;
			message[2] = 64;
			midiout->sendMessage( &message );	
		}

		//_________________Increment the counters___________
		counter++;

		if( counter > 63 )
		{
			counter = 0;
			measure_counter++;
		}
		
		//_________________delay____________
		SLEEP( 150000 );
	}

// Clean up
	cleanup:
	delete midiout;
	return 0;
}

bool chooseMidiPort( RtMidiOut *rtmidi )
{
	std::cout << "\nWould you like to open a virtual output port? [y/N] ";

	std::string keyHit;
	std::getline( std::cin, keyHit );
	if ( keyHit == "y" ) {
		rtmidi->openVirtualPort();
		return true;
	}

	std::string portName;
	unsigned int i = 0, nPorts = rtmidi->getPortCount();
	if ( nPorts == 0 ) {
		std::cout << "No output ports available!" << std::endl;
		return false;
	}

	if ( nPorts == 1 ) {
		std::cout << "\nOpening " << rtmidi->getPortName() << std::endl;
	}
	else {
		for ( i=0; i<nPorts; i++ ) {
			portName = rtmidi->getPortName(i);
			std::cout << "  Output port #" << i << ": " << portName << '\n';
		}

		do {
			std::cout << "\nChoose a port number: ";
			std::cin >> i;
		} while ( i >= nPorts );
	}

	std::cout << "\n";
	rtmidi->openPort( i );

	return true;
}