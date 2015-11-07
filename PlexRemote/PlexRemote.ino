/*
 * Plex IR remote for Arduino Micro
 * By Sebastian Goscik - 22/09/2015
 * 
 * Please read the readme.md file for instructions on
 * how to use this sketch.
 */

#include <IRremote.h> 
#include <HID-Project.h>

/* Please change the order of these to match your IR receiver
   In necessary than can be moved to any other pins. These pins
   were selected to allow the IR sensor to rest on top of the MCU
*/
#define RECV_PIN 3 
#define GND_PIN 4
#define PWR_PIN 5


IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  Keyboard.begin();
  irrecv.enableIRIn();

  pinMode(GND_PIN, OUTPUT);
  digitalWrite(GND_PIN, LOW);
  pinMode(PWR_PIN, OUTPUT);
  digitalWrite(PWR_PIN, HIGH);
}

void loop() {
  if (irrecv.decode(&results)) {

    // Plex keyboard shortcuts can be found here:
    // https://support.plex.tv/hc/en-us/articles/201670487-Keyboard-Shortcuts
    // IR codes are from a NOW TV (roku) remote
    switch(results.value)
    {
      case 0x57436699: //Back
        Keyboard.press(KEY_ESC);
        break;
      case 0x5743C03F: //Home
        Keyboard.press(KEY_TAB);
        break;
      case 0x57439867: //Up
        Keyboard.press(KEY_UP_ARROW);
        break;
      case 0x5743CC33: //Down
        Keyboard.press(KEY_DOWN_ARROW);
        break;
      case 0x57437887: //Left
        Keyboard.press(KEY_LEFT_ARROW);
        break;
      case 0x5743B44B: //Right
        Keyboard.press(KEY_RIGHT_ARROW);
        break;
      case 0x574354AB: //OK
        Keyboard.press(KEY_RETURN);
        break;
      case 0x57432CD3: //Rewind
        Keyboard.press('r');
        break;
      case 0x574332CD: //Play/Pause
        Keyboard.press(' ');
        break;
      case 0x5743AA55: //Fast Forward
        Keyboard.press('f');
        break;
      case 0x57438679: //Wake
        System.write(SYSTEM_WAKE_UP);
        break;
      case 0x574320DF: //NOW TV - Launch plex via eventghost
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press('p');
        break;
      case 0x5743E817: //Apps - Launch steam via eventghost
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press('s');
        break;
      default:
        Serial.print("0x");
        Serial.println(results.value, HEX);
    }
    Keyboard.releaseAll();
    irrecv.resume(); // Receive the next value
  }
}
