/*
   Ron D Bentley, Stafford, UK
   Feb 2021

   Reading Multiple Button Switches, using simple polling
   ''''''''''''''''''''''''''''''''''''''''''''''''''''''

   This example and code is in the public domain and may be used without restriction and
   without warranty.

   This sketch will reliably read any number of button switches by polling each of
   them in turn.  Once a button switch is pressed the main code loop will switch
   to user provided code to handle the purpose of the button press.  This is controlled
   via a switch control struct(ure) and associated main loop switch-case code.

   Note that this sketch is only designed for processing multiple BUTTON switches.  However,
   the switch definition and control struct(ure) ('struct switch_control') is designed to
   support of other types of switch also, eg toggle switches.  For purposes of this example
   sketch parts of this control struct(ure) are not used.  These aspects will be picked up
   in other sketch examples.

   The sketch layout is straight forward and process code for each button can be added
   where indicated within the main loop, under the respective switch-case section for a
   button switch.

   Configurability:
   1. Number of button switches - the implementation is such that each button switch is
      allocated to a digital pin.  The sketch will therefore support as many button
      switches as a microcontroller can provide digital inputs.
      This example sketch is configured, 'out-of-the-box' (OOTB)for six button switches,
      but more may be added by:

      a. changing the macro definition '#define num_switches' to be the number of buttons
         switches to be connected
      b. for each button switch, deciding its circuit type and allocating it to a digital pin
      c. in the 'Switch to Pin Macro Definition List' adding new button switch macro
         definitions, one for each additional button switch,
         for example: '#define button_switch_?  <pin number>'
      d. in the 'Switch Control Sruct(ure) Declaration' adding further preset data to the
         'switches' data struct(ure), for example: '...,button_switch_?, circuit_?,...', etc.

   For a fuller appreciation of button switch fundementals see the tutorial 'Understanding
   and Using Button Switches':
   https://create.arduino.cc/projecthub/ronbentley1/understanding-and-using-button-switches-2ffe6c?ref=platform&ref_id=424_trending___&offset=2
*/
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// These declarations are specifically for defining and controlling the attached  switches
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#define circuit_C1           INPUT   // switch circuit requires an external pull down 10k ohm resistor
#define circuit_C2    INPUT_PULLUP   // switch type reqires no other components beyond the button switch

#define debounce             10      // number of millisecs to wait for a switch to settle once activated
#define switched           true      // signifies switch has been pressed/switch cycle complete

#define button_switch        1       // differentiates switch type
#define toggle_switch        2       // toggle switches are NOT used in this example sketch - future use

#define num_switches         6       // number of button switches connected

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// %       Switch to Pin Macro Definition List         %
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// associate button swithes each with a digital pin.
// add further definitions here if adding more switches
// note that digital pins allocated are arbitary, any
// available pin will do, or remove any not required.
#define button_switch_1      2
#define button_switch_2      3
#define button_switch_3      4
#define button_switch_4      5
#define button_switch_5      6
#define button_switch_6      7

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// %                   Switch Control Sruct(ure) Declaration                 %
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// now set up the configuration data for each individual
// switch to be used by the switch read function and to
// generally define the nature of the switch.
struct switch_control {
  int  switch_type;               // type of switch connected.NOT used in this sketch example - future use
  int  switch_pin;                // digital input pin assigned to the switch
  int  circuit_type;              // the type of circuit wired to the switch
  bool switch_on;                 // the value relating to what "on" means, set up in the setup() function
  bool switch_pending;            // records if switch in transition or not
  long unsigned int elapse_timer; // records debounce timer count when associated switch is in transition
  bool switch_status;             // current state of switch.NOT used in this sketch example - future use
} switches[num_switches] = {
  button_switch, button_switch_1, circuit_C2, LOW, false, 0, !switched,
  button_switch, button_switch_2, circuit_C2, LOW, false, 0, !switched,
  button_switch, button_switch_3, circuit_C2, LOW, false, 0, !switched,
  button_switch, button_switch_4, circuit_C2, LOW, false, 0, !switched,
  button_switch, button_switch_5, circuit_C2, LOW, false, 0, !switched,
  button_switch, button_switch_6, circuit_C2, LOW, false, 0, !switched
};
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void setup() {
  // initialise digital input switch pins
  for (int sw = 0; sw < num_switches; sw++) {
    // define the switch circuit type - circuit_type is:
    // circuit_C1 (INPUT) or circuit_C2 (INPUT_PULLUP)
    pinMode(switches[sw].switch_pin, switches[sw].circuit_type);
    // establish 'meaning' for switch on/off depending on circuit type
    if (switches[sw].circuit_type == circuit_C2) {
      // switch is NOT configured with a pull down switch resistor
      switches[sw].switch_on   = LOW;    // switch pin goes LOW when switch pressed, ie on
    } else {
      // circuit_type_C1, so switch IS configured with a pull down switch resistor
      switches[sw].switch_on   = HIGH;   // switch pin goes HIGH when switch pressed, ie on
    }
  }
  Serial.begin(115200); // dont forget to set your serial monitor speed to whatever is set here
}

void loop() {
  // poll each connected switch in turn and, if switched, process its associated purpose
  for (int sw = 0; sw < num_switches; sw++) {
    if (read_switch(sw) == switched) {
      // this switch (sw) has been pressed, so process via a case switch
      Serial.print("\nbutton switch ");
      Serial.print(sw + 1);
      Serial.print(" on digital pin ");
      byte button_pin = switches[sw].switch_pin;
      Serial.println(button_pin);
      // move to switch's associated code section
      switch (button_pin)
      {
        case button_switch_1:
          Serial.println("case statement 1 entered");
          break;
        case button_switch_2:
          Serial.println("case statement 2 entered"); break;
        case button_switch_3:
          Serial.println("case statement 3 entered");
          break;
        case button_switch_4:
          Serial.println("case statement 4 entered");
          break;
        case button_switch_5:
          Serial.println("case statement 5 entered");
          break;
        case button_switch_6:
          Serial.println("case statement 6 entered");
          break;
        default:
          // spurious switch index!  Should never arise as this is controlled
          // by the for loop within defined upper bound
          break;
      }
      Serial.flush();  // flush out the output buffer
    }
  }
  // pollng of the switches now complete until next cycle, so do other things here as required...



}

//
// generic button switch read function.
// reading is controlled by:
//   a. the function parameter which indicates which switch
//      is to be polled, and
//   b. the switch control struct(ure), referenced by a).
//
// note that this function works in a nonexclusive way
// and incorporates debounce code
//
bool read_switch(int sw) {
  int switch_pin_reading;
  switch_pin_reading = digitalRead(switches[sw].switch_pin);
  if (switch_pin_reading == switches[sw].switch_on) {
    // switch is pressed (ON), so start/restart debounce process
    switches[sw].switch_pending = true;
    switches[sw].elapse_timer = millis();    // start elapse timing
    return !switched;                        // now waiting for debounce to conclude
  }
  if (switches[sw].switch_pending && switch_pin_reading == !switches[sw].switch_on) {
    // switch was pressed, now released (OFF), so check if debounce time elapsed
    if (millis() - switches[sw].elapse_timer > debounce) {
      // dounce time elapsed, so switch press cycle complete
      switches[sw].switch_pending = false;
      return switched;
    }
  }
  return !switched;
}