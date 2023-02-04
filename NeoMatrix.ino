#include <Adafruit_NeoPixel.h>

#define LED_PIN     6

#define LED_COUNT   30

int c;
int v=0;
int msg_pos = 0;
int pos = 0;
int red = 0;
int green = 0;
int blue = 0;

Adafruit_NeoPixel matrix(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {

  Serial.begin(115200);
  Serial.println("Started.");
  
  matrix.begin();
  matrix.setBrightness(255);
  matrix.show();
}

void loop() {
  while (Serial.available()) {
    c = Serial.read();
    // handle digits
    if ((c >= '0') && (c <= '9')) {
      v = 10 * v + c - '0';
    }
    // handle delimiter
    else if (c == ',') {
      msg_pos++;
      if(v == 256) {
        msg_pos = 0;
      }
      else if(v == 257) {
        msg_pos = 0;
        matrix.setPixelColor(pos, matrix.Color(red, green, blue));
        matrix.show();
      }
      else {
        if(msg_pos==1) {
          pos=v;
        }
        if(msg_pos==2) {
          red=constrain(v, 0, 255);
        }
        if(msg_pos==3) {
          green=constrain(v, 0, 255);
        }
        if(msg_pos==4) {
          blue=constrain(v, 0, 255);
        }
      }
      Serial.println(v);
      v = 0;
    }
  }
}
