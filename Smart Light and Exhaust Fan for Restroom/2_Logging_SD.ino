#include <SD.h>
#include <SPI.h>

/* Variables from data acquisition */
bool pirVal = HIGH;     	// PIR sensor value
int gasVal = 487;			    // Gas sensor value
int lampOffTime = 9;	    // Lamp/ led off time counter
bool lampState = HIGH;	  // Lamp/ led state (flag)
bool fanState = HIGH;	    // Exhaust fan state (flag)

/* Variables for microSD module */
int pinCS = 10;               // chipSelect pin in arduino uno
String fileName = "log.txt";  // log data file name

File LogData;             // create file object

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  // SD Card Initialization
  pinMode(pinCS, OUTPUT); // declare microSD module as output
  if (SD.begin())
  {
    Serial.println("SD card is ready.");
  } else
  {
    Serial.println("SD card is failed");
    return;
  }
  
}

void loop() {
  // Write data to microSD
  writeData(fileName);

  // Command line check
  commandLineInterface();

  delay(1000);

}

void writeData(String fileName){
  LogData = SD.open(fileName, FILE_WRITE);
  if (LogData) {
    Serial.println("Writing data . . .\n");

    LogData.print("Lamp status : ");
    LogData.print(lampState);
    LogData.print(" ; ");
    LogData.print("Exh fan status : ");
    LogData.print(fanState);
    LogData.print(" ; ");

    LogData.print("PIR val : ");
    LogData.print(pirVal);
    LogData.print(" ; ");
    LogData.print("Gas val : ");
    LogData.print(gasVal);
    LogData.print(" ; ");
    LogData.print("Lamp OFF Counter : ");
    LogData.print(lampOffTime);
    LogData.print("\n");

    LogData.close(); // close the file
  }
  else {
    Serial.println("error opening file .txt");
  }
}

void readData(String fileName){
  LogData = SD.open(fileName);
  if (LogData) {
    Serial.println("Reading data . . .");
    while (LogData.available()) {
      Serial.write(LogData.read());
   }
    LogData.close();
  }
  else {
    Serial.println("error opening test.txt");
  }
  Serial.println("\n");
}

void commandLineInterface(){
  if(Serial.available()>0)
  {
    String cmd = "";
    String txt[20];
  	cmd = Serial.readString();// read command line
  	if (cmd == "/readSD\n")	// command for reading microSD data
  	{
    	readData(fileName);
  	}
  }
}