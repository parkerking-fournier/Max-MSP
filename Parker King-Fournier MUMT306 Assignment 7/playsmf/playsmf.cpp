
// In the context of the directory that I have zipped with this,
// all you have to do to compile is write:
//  
// make
//
// to run, write:
//
// ./playsmf filepath
// 
//
// Parker King-Fournier

#include "MidiFileIn.h"
#include "RtMidi.h"
#include <signal.h>
#include <unistd.h>
#include <climits>
#include <stdio.h>

using namespace stk;

bool done = false;
static void finish(int ignore){ done = true; }

void usage(void) {
  // Error function in case of incorrect command-line
  // argument specifications.
  std::cout << "\nusage: playsmf file track <port>\n";
  std::cout << "   where file = a standard MIDI file,\n";
  std::cout << "   track = the track to play (0 = 1st track),\n";
  std::cout << "   and an optional port integer identifier can be specified\n";
  std::cout << "   (default = 0) or a value of -1 to use a virtual MIDI output port.\n\n";
  exit(0);
}

int main( int argc, char *argv[] )
{
  RtMidiOut *midiout = 0;

  if ( argc < 2 || argc > 3 ) usage();

  // Attempt to instantiate MIDI output class.
  try {
    midiout = new RtMidiOut();
  }
  catch ( RtMidiError& error ) {
    error.printMessage();
    exit(0);
  }

  // Check command-line arguments.
  int port = 0;
  if ( argc == 3 ) port = atoi( argv[2] );
  if ( port == -1 ) {
    try {
      midiout->openVirtualPort();
    }
    catch ( RtMidiError& error ) {
      error.printMessage();
      goto cleanup;
    }
    std::cout << "\nVirtual port open.\n\n";
  }
  else {
    if ( midiout->getPortCount() < 1 ) {
      std::cout << "\nThere are no MIDI output destinations available!\n\n";
      goto cleanup;
    }
    try {
      midiout->openPort( port );
    }
    catch ( RtMidiError& error ) {
      error.printMessage();
      goto cleanup;
    }
  }

  // Install an interrupt handler function.  Type "ctrl-c" to quit the
  // program.
  (void) signal(SIGINT, finish);
  
  try 
  {
    MidiFileIn midiFile( argv[1] );

    // Print a little information about the file.
    std::cout << "\nThe MIDI file (" << argv[1] << ") information:\n";
    std::cout << "  - format = " << midiFile.getFileFormat() << "\n";
    std::cout << "  - tracks = " << midiFile.getNumberOfTracks() << "\n";
    std::cout << "  - seconds / ticks = " << midiFile.getTickSeconds() << "\n";

    std::cout << "\nPress <enter> to start reading/playing ... type Ctrl-C to quit.\n";
    char input;
    std::cin.get(input);

    int nTracks = midiFile.getNumberOfTracks();
    
    std::vector< std::vector<unsigned char> > event(nTracks);
    std::vector<long> ticks(nTracks);

    
    for (int i = 0; i < nTracks; ++i)
    {
      ticks[i] = midiFile.getNextMidiEvent( &event[i], i);
    }

    int minTicks = 0;
    int minTrack = 0;

    while ( !done ) 
    {
      //Find Minimum Tick Value
      minTicks = INT_MAX;
      for (int i = 0; i < nTracks; ++i)
      {
        if(ticks[i] < minTicks && ticks[i] >= 0)
        {
          minTicks = ticks[i];
          minTrack = i;
        }
      }

      // Pause for the MIDI event delta time.
      Stk::sleep( (unsigned long) (minTicks * midiFile.getTickSeconds( minTrack ) * 1000 ) );

      //fprintf(stderr,"Msg len: %lu\n",event[minTrack].size());

      midiout->sendMessage( &event[minTrack] );

      for(int j = 0; j < nTracks; j++)
      {
        ticks[j] = ticks[j] - minTicks;
      }

      // Get a new event.
      if( minTicks == INT_MAX )
      {
        break;
      }
      else if (event[minTrack].size() == 0) 
      {
        ticks[minTrack] = -1;
      }
      else
      {
        ticks[minTrack] = midiFile.getNextMidiEvent( &event[minTrack], minTrack );
      }

    }

    // Send a "all notes off" to the synthesizer on all 16 channels.
    for( int j = 0; j < nTracks; j++)
    {
      for ( int i=0; i<16; i++ ) 
      {
        event[j].clear();
        event[j].push_back( 0xb0+i );
        event[j].push_back( 0x7b );
        event[j].push_back( 0x0 );
        midiout->sendMessage( &event[j] );
      }
    }
  }

  catch ( StkError & ) 
  {
    // You might want to do something more useful here.
    std::cout << "\nAborting program!\n";
    goto cleanup;
  }

  cleanup:
  delete midiout;

  return 0;
}
