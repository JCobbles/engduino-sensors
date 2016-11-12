import processing.serial.*;

final String URL_DEV = "http://localhost:3000/update/%s,%s";
final String URL_PROD = "http://lightandtemperature.azurewebsites.net/update/%s,%s";

Serial serial;
String message; 
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
    message = serial.readStringUntil('\n');
    if (message != null) {
      String[] data = message.split(",");
      sendDataToWebsite(data);
      updateLocalGraph(data);
    }
  } 
}

void sendDataToWebsite(String[] data) {
  loadStrings(String.format(URL_PROD, data[0], data[1]));
}

void updateLocalGraph(String[] data) {
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