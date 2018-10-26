//*****************************************//
//  Parker King-Fournier
//  Assignmet 6, question 3
//
// Compiler Statement: g++ ass6q3.cpp RtMidi.cpp
// Run Statement: ./a.out
//*****************************************//

#include <iostream>
#include <cstdlib>
#include <signal.h>
#include "RtMidi.h"

// Platform-dependent sleep routines.
#if defined(__WINDOWS_MM__)
  #include <windows.h>
  #define SLEEP( milliseconds ) Sleep( (DWORD) milliseconds ) 
#else // Unix variants
  #include <unistd.h>
  #define SLEEP( milliseconds ) usleep( (unsigned long) (milliseconds * 1000.0) )
#endif

bool done;
static void finish( int ignore ){ done = true; }

void usage( void ) 
{
  // Error function in case of incorrect command-line
  // argument specifications.
  std::cout << "\nusage: qmidiin <port>\n";
  std::cout << "    where port = the device to use (default = 0).\n\n";
  exit( 0 );
}

int main( int argc, char *argv[] )
{
  RtMidiIn *midiin = 0;
  std::vector<unsigned char> message;
  int nBytes, i;
  double stamp;

  // Minimal command-line check.
  if ( argc > 2 ) usage();

  // RtMidiIn constructor
  try 
  {
    midiin = new RtMidiIn();
  }
  catch ( RtMidiError &error ) 
  {
    error.printMessage();
    exit( EXIT_FAILURE );
  }

  // Check available ports vs. specified.
  unsigned int port = 0;
  unsigned int nPorts = midiin->getPortCount();
  if ( argc == 2 ) 
  {
      port = (unsigned int) atoi( argv[1] );
  }
  if ( port >= nPorts ) 
  {
    delete midiin;
    std::cout << "Invalid port specifier!\n";
    usage();
  }

  try 
  {
    midiin->openPort( port );
  }
  catch ( RtMidiError &error ) 
  {
    error.printMessage();
    goto cleanup;
  }

  // Don't ignore sysex, timing, or active sensing messages.
  midiin->ignoreTypes( false, false, false );

  // Install an interrupt handler function.
  done = false;
  (void) signal(SIGINT, finish);

  // Periodically check input queue.
  std::cout << "Reading MIDI from port ... quit with Ctrl-C.\n";
  while ( !done ) 
  {
    stamp = midiin->getMessage( &message );
    nBytes = message.size();

    if ( nBytes > 0 )
    {
        int status = (int)message[0];

         //System Real Time Messages
          if(status == 248)
          {
              std::cout << "System Real Time: Timing Tick" << std::endl;
          }
          if(status == 249)
          {
              std::cout << "System Real Time: Undefined (249)" << std::endl;
          }
          if(status == 250)
          {
              std::cout << "System Real Time: Start Song" << std::endl;
          }
          if(status == 251)
          {
              std::cout << "System Real Time: Continue Song" << std::endl;
          }
          if(status == 252)
          {
              std::cout << "System Real Time: Stop Song" << std::endl;
          }
          if(status == 253)
          {
              std::cout << "System Real Time: Undefined (253)" << std::endl;
          }
          if(status == 254)
          {
              std::cout << "System Real Time: Active Sensing" << std::endl;
          }
          if(status == 255)
          {
              std::cout << "System Real Time: System Reset" << std::endl;
          }

          //System Common Messages
          if(status == 241)
          {
              std::cout << "System Common: Time Code Qtr Frame, ";
              std::cout << "Time Code Value = " << (int)message[1] << std::endl;
          }
          if(status == 242)
          {
              std::cout << "System Common: Song Position, ";
              std::cout << "Position LSB = " << (int)message[1] << ", ";
              std::cout << "Position MSB = " << (int)message[2] << std::endl;
          }
          if(status == 243)
          {
              std::cout << "System Common: Song Select, ";
              std::cout << "Song Number = " << (int)message[1] << std::endl;
          }
          if(status == 244)
          {
              std::cout << "System Common: Undefined(244)" << std::endl;
          }
          if(status == 245)
          {
              std::cout << "System Common: Undefined(245)" << std::endl;
          }
          if(status == 246)
          {
              std::cout << "System Common: Tune Request" << std::endl;
          }
          if(status == 247)
          {
              std::cout << "System Common: End of Sysex" << std::endl;
          }

          //System Exclusive
          //Note: If system exclusive messages are used, any data bytes from the system common will be 
          //pushed into the system exclusive vector. They wil then be output in a system exclusive message 
          //when the end of Sysex message is sent. This is because System exlusive is not defined.
          if(status == 240)
          {
              std::cout << "System Exclusive: ";
              for ( i=1; i<nBytes; i++ )
              {
                   std::cout << "DataByte " << i << " = " << (int)message[i] << ", ";
              }
              std::cout << std::endl;
          }

           //Channel Messages
          if(status >127 && status <144)
          {
              std::cout << "Channel: Note Off, Channel = " << status%128<< ", " ;
              std::cout << "Note Number = " << (int)message[1] << ", ";
              std::cout << "Velocity = " << (int)message[2] << std::endl;
          }
          if(status >143 && status <160)
          {
              std::cout << "Channel: Note On, Channel = " << status%144<< ", " ;
              std::cout << "Note Number = " << (int)message[1] << ", ";
              std::cout << "Velocity = " << (int)message[2] << std::endl;
          }
          if(status >159 && status <176)
          {
              std::cout << "Channel: Aftertouch, Channel = " << status%160<< ", " ;
              std::cout << "Note Number = " << (int)message[1] << ", ";
              std::cout << "Key Pressure = " << (int)message[2] << std::endl;
          }
          if(status >175 && status <192)
          {
              std::cout << "Channel: Control Change, Channel = " << status%176<< ", " ;
              std::cout << "Control Number = " << (int)message[1] << ", ";
              std::cout << "Control Change = " << (int)message[2] << std::endl;
          }
          if(status >191 && status <208)
          {
              std::cout << "Channel: Program Change, Channel = " << status%192<< ", " ;
              std::cout << "Program Number = " << (int)message[1] << std::endl;
          }
          if(status >207 && status <208)
          {
              std::cout << "Channel: Channel Pressure, Channel = " << status%208<< ", " ;
              std::cout << "Pressure = " << (int)message[1] << std::endl;
          }
          if(status >223 && status <240)
          {
              std::cout << "Channel: Pitch Bend, Channel = " << status%224<< ", " ;
              std::cout << "Value LSB = " << (int)message[1] << ", ";
              std::cout << "Value MSB = " << (int)message[2] << std::endl;
          }
      }
    SLEEP( 10 );
  }

  // Clean up
  cleanup:
    delete midiin;
    return 0;
}




