//On my machine, the associated port on the Max patch
//was port e.

#define MIDI_ON 144
#define MIDI_OFF 128
#define MIDI_CHANNEL 0
#define MIDI_PROGRAM 192

#define DRUM_CHANNEL 9
#define BASS_CHANNEL 1
#define SYNTH_CHANNEL 2

#define KICK  36    // kick drum note number
#define HAT 28      // closed hi-hat note number
#define BASS 39     // bass program number
#define SYNTH 88    // synth program number

int status = 0;
int counter = 0;

char bassNote1 = 0;
char bassNote2 = 0;
char drumNote = 0;
char synthNote = 0;

void setup()
{
  Serial.begin( 115200 );  // set the MIDI baud rate
  
  Serial.print( MIDI_PROGRAM + BASS_CHANNEL );  // Do MIDI program change for bass voice
  Serial.print( ' ' );
  Serial.println( BASS );
  
  Serial.print( MIDI_PROGRAM + SYNTH_CHANNEL );  // Do MIDI program change for snyth voice
  Serial.print( ' ' );
  Serial.println( SYNTH );
}

void loop()
{
  
//____________________This is the Drum Beat______________________
  if ( counter % 4 == 0 )
  {
    drumNote = KICK;
    midi2Max( MIDI_ON + DRUM_CHANNEL, drumNote, 64 );
  }
  if ( counter % 4 == 0 && counter != 0 && counter % 8 != 0) 
  {
    drumNote = HAT;
    midi2Max( MIDI_ON + DRUM_CHANNEL, drumNote, 64 );
  }
  
  //____________________This is the Bass Line______________________
  
  //NOTE: There will be a hanging bass note when the max patch is 'paused
  //Gary said this was okay, as it was just a buggy phenomenon that happens
  //not an integral part to the assignment.
  
  if ( counter == 0 )
  {   
    midi2Max( MIDI_OFF + BASS_CHANNEL, bassNote1, 64 );
    midi2Max( MIDI_OFF + BASS_CHANNEL, bassNote2, 64 );
    
    bassNote1 = 38;
    bassNote2 = 41;
   
    midi2Max( MIDI_ON + BASS_CHANNEL, bassNote1, 64 );
    midi2Max( MIDI_ON + BASS_CHANNEL, bassNote2, 64 );
  }
  if ( counter == 16 )
  { 
    midi2Max( MIDI_OFF + SYNTH_CHANNEL, synthNote, 64 );
    
    midi2Max( MIDI_OFF + BASS_CHANNEL, bassNote1, 64 );
    midi2Max( MIDI_OFF + BASS_CHANNEL, bassNote2, 64 );   
    
    bassNote1 = 31;
    bassNote2 = 43;
    
    midi2Max( MIDI_ON + BASS_CHANNEL, bassNote1, 64 );
    midi2Max( MIDI_ON + BASS_CHANNEL, bassNote2, 64 );     
  }
  if ( counter == 32 )
  {  
    midi2Max( MIDI_OFF + BASS_CHANNEL, bassNote1, 64 );
    midi2Max( MIDI_OFF + BASS_CHANNEL, bassNote2, 64 );  
    
    bassNote1 = 45;
    bassNote2 = 48;
    
    midi2Max( MIDI_ON + BASS_CHANNEL, bassNote1, 64 );
    midi2Max( MIDI_ON + BASS_CHANNEL, bassNote2, 64 );     
  }
  if ( counter == 48 )
  { 
    midi2Max( MIDI_OFF + SYNTH_CHANNEL, synthNote, 64 );
    
    midi2Max( MIDI_OFF + BASS_CHANNEL, bassNote1, 64 );
    midi2Max( MIDI_OFF + BASS_CHANNEL, bassNote2, 64 );
    
    bassNote1 = 41;
    bassNote2 = 45;
    
    midi2Max( MIDI_ON + BASS_CHANNEL, bassNote1, 64 );
    midi2Max( MIDI_ON + BASS_CHANNEL, bassNote2, 64 );     
  } 
  
  //____________________This is the Melody______________________
  if ( counter == 1 || counter == 3 || counter == 7 || counter == 9)
  {
    midi2Max( MIDI_OFF + SYNTH_CHANNEL, synthNote, 64 );
    
    synthNote = 77;
    
    midi2Max( MIDI_ON + SYNTH_CHANNEL, synthNote, 64);    
  }
  if ( counter == 2 || counter == 33 || counter == 35 || counter == 39 || counter == 41 )
  {
    midi2Max( MIDI_OFF + SYNTH_CHANNEL, synthNote, 64 );
    
    synthNote = 76;
    
    midi2Max( MIDI_ON + SYNTH_CHANNEL, synthNote, 64);  
  }
  if ( counter == 4 || counter == 34)
  {
    midi2Max( MIDI_OFF + SYNTH_CHANNEL, synthNote, 64 );
    
    synthNote = 74;
    
    midi2Max( MIDI_ON + SYNTH_CHANNEL, synthNote, 64);  
  }
  if ( counter == 8 || counter == 36)
  {
    midi2Max( MIDI_OFF + SYNTH_CHANNEL, synthNote, 64 );
    
    synthNote = 72;
    
    midi2Max( MIDI_ON + SYNTH_CHANNEL, synthNote, 64);  
  }
  if ( counter == 10 || counter == 40)
  {
    midi2Max( MIDI_OFF + SYNTH_CHANNEL, synthNote, 64 );
    
    synthNote = 71;
    
    midi2Max( MIDI_ON + SYNTH_CHANNEL, synthNote, 64);  
  }
  if ( counter == 42 ) 
  {
    midi2Max( MIDI_OFF + SYNTH_CHANNEL, synthNote, 64 );
    
    synthNote = 69;
    
    midi2Max( MIDI_ON + SYNTH_CHANNEL, synthNote, 64); 
  }

  //____________________Increment the Counter______________________
  counter++;
  if ( counter > 63 ) counter = 0;

  //____________________Delay 150 Milliseconds______________________
  delay( 150 );  
}



// Send a 3 ``byte'' MIDI message (without checking values)
void midi2Max( int cmd, int data1, int data2 )
{
  Serial.print( cmd );
  Serial.print(' ');
  Serial.print( data1 );
  Serial.print(' ');
  Serial.print( data2 );
  Serial.println();
}
