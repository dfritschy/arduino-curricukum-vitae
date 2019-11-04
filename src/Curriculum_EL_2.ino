//
// Curriculum Vitae
//
// Art Project/Installation
// (c) 2019 Donat Fritschy
//

#define DEBUGGING   true

#define EL_WIRES        8     // Number of EL wires.
#define TIME_SLOTS      10    // Number of time slots
#define CYCLE_DELAY     5000  // delay after a cycle
#define DURATION_SKEW   3     // skew factor for duration

// H Dankbarkeit
// G Zuversicht
// F Depression
// E Zweifel
// D Resignation
// C Bangen
// B Hoffen
// A Angst

int disp[TIME_SLOTS][EL_WIRES] = {
  // Wire                                     //  Time Slot
  //   A    B    C    D    E    F    G    H
    {100,   0,   0,   0,   0,   0,   0,   0}, // 1
    {100, 100,   0,   0,   0,   0,   0,   0}, // 2
    { 80, 100, 100,   0,  20,   0,   0,   0}, // 3
    { 50, 100, 100,  50,  50,  20,  10,   0}, // 4
    { 50,  10,  50, 100,  50,  50,  30,   0}, // 5
    { 40,  20,  10, 100, 100,  10,  50,   0}, // 6
    { 30,  30,  10,  10,  80, 100,  80,   0}, // 7 
    { 20,  50,  20,  20,  20,  20, 100,   0}, // 8
    { 10,  50,  10,  10,  10,  10, 100, 100}, // 9
    {  0,   0,   0,   0,   0,   0,   0, 100}  // 10
};

int duration[TIME_SLOTS] = {
  1000, // 1
  1000, // 2
  1000, // 3
  1000, // 4
  1000, // 5
  1000, // 6
  1000, // 7
  1000, // 8
  2000, // 9
  3000  // 10
};

//
//  Utility Functions
//

// Setup Output Ports for EL Wires

void wireSetup()
{
  // The EL channels are on pins 2 through 9
  // Initialize the pins as outputs
  pinMode(2, OUTPUT);  // channel A  
  pinMode(3, OUTPUT);  // channel B   
  pinMode(4, OUTPUT);  // channel C
  pinMode(5, OUTPUT);  // channel D    
  pinMode(6, OUTPUT);  // channel E
  pinMode(7, OUTPUT);  // channel F
  pinMode(8, OUTPUT);  // channel G
  pinMode(9, OUTPUT);  // channel H
  // We also have two status LEDs, pin 10 on the Escudo, 
  // and pin 13 on the Arduino itself
  pinMode(10, OUTPUT);     
  pinMode(13, OUTPUT);    
}

// Test EL Wire setup by lighting all wires for 5 second

void testWireSetup()
{
  turnAllWiresOn();
  delay(5000);
  turnAllWiresOff();
}

// Turn single wire on

void turnWireOn( int wire)
{
  int pin = wire + 2;
  digitalWrite(pin, HIGH);    // turn the EL channel on
  Serial.print( "X " );
}

// Turn single wire off

void turnWireOff( int wire)
{
  int pin = wire + 2;
  digitalWrite(pin, LOW);    // turn the EL channel off
  Serial.print( "- " );
}

// Turn all EL Wires on

void turnAllWiresOn()
{
  int x;
  Serial.println( "Turn all wires on" );
  for (x=2; x<=9; x++)
  {
      digitalWrite(x, HIGH);    // turn the EL channel on
  }
}

// Turn all EL Wires off

void turnAllWiresOff()
{
  int x;
  Serial.println( "Turn all wires off" );
  for (x=2; x<=9; x++)
  {
      digitalWrite(x, LOW);    // turn the EL channel on
  }  
}

// Decide if wire should be turned on based on probability p

bool showWire( int p )
{
  int x;
  
  x = random(1,100);
  return x <= p;
}

// Delay Slot, i.e. time showing the combination

void delaySlot(int slot)
{
  delay(random(duration[slot], duration[slot] * DURATION_SKEW));     // wait variable time
}
 
// Delay Cycle, i.e. dark time till next start

void delayCycle()
{
  delay(CYCLE_DELAY);
}

//
//  Setup
//

void setup() {        
  Serial.begin(9600);
  Serial.println(F("Curriculum Setup Started"));

  wireSetup();
  testWireSetup();
  
  Serial.println(F("Curriculum Setup Finished"));
}

//
// Main loop
//

void loop() 
{
  int slot, wire;
  
  // Loop over time slots
  for (slot = 0; slot < TIME_SLOTS; slot++)
  {
    Serial.print(F("TimeSlot "));
    Serial.print( slot );
    Serial.print( ": " );
    
    // Loop over all eight EL channels (pins 2 through 9)
    for (wire = 0; wire < EL_WIRES; wire++)
    {
      if (showWire(disp[slot][wire])) {
        turnWireOn(wire);
      }
      else {
        turnWireOff(wire);
      }
    }
    Serial.println();
    delaySlot( slot );
  }

  // End of cycle, turn all wires off, wait for next cycle
  turnAllWiresOff();
  delayCycle();
}
