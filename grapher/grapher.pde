import processing.serial.*;

Serial serial;
String val; 
int xPosition = 1;
void setup() {
  size(400, 300);
  background(0);
  String portName = Serial.list()[0]; // the Engduino is on the first port
  serial = new Serial(this, portName, 9600);
}

void draw() {
  stroke(127, 34, 255);
  
  if (serial.available() > 0) {  
    val = serial.readStringUntil('\n');
    if (val == null) {
      return;
    }
    String[] data = val.split(",");
    println(data[0]);
    line(xPosition, height, xPosition, height - Integer.parseInt(data[0]));
    if (xPosition >= width) { 
      // we are at the end of the screen, so wipe the screen continue from there
      xPosition = 0;
      background(0);
    } else {
      // increment the horizontal position:
      xPosition++;
    }
  } 
}