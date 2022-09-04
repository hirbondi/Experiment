int pirPin = 2;   		// PIR sensor digital input pin
bool pirVal = LOW;     	// PIR sensor value
bool pirState = LOW;	// PIR sensor state (flag)

int gasPin = A0;		// Gas sensor analog input pin
int gasVal = 0;			// Gas sensor value
int gasThr = 500; 		// Gas sensor threshold value (configurable)

int lampPin = 4;      	// Lamp/ led digital output pin
int lampOffTime = 0;	// Lamp/ led off time counter
int lampOffVar = 15;	// Lamp/ led off time var (configurable)
bool lampTimer = LOW;	// Lamp/ led off time flag
bool lampState = LOW;	// Lamp/ led state (flag)

int fanPin = 7;			// Exhaust fan digital output pin (this is indicator only for the exhaust fan switch)
bool fanState = LOW;	// Exhaust fan state (flag)

int interval = 1;		// Loop interval in second (configurable)

String cmd = "";		// Command line read data
String dt[3];			// Parsed command line

bool streams = LOW;		// Stream data flag

void setup() {
  pinMode(pirPin, INPUT);	// declare PIR sensor as input
  pinMode(gasPin, INPUT);	// declare Gas sensor as input
  pinMode(lampPin, OUTPUT);	// declare Lamp/ led as output
  pinMode(fanPin, OUTPUT);	// declare Exhaust fan as output (switch)
 
  Serial.begin(9600);
  
  // setup module microSD
}
 
void loop(){
  pirVal = digitalRead(pirPin); // read PIR sensor value
  gasVal = analogRead(gasPin);	// read Gas sensor value
  
  /* PIR Sensor Checker */
  checkPIRDetection(pirVal);
  
  /* Lamp Checker */
  checkLamp();
  
  /* Exhaust Fan Checker */
  checkExhaustFan(gasVal);
  
  /* Print all conditions */
  showAllStatus();
  
  /* Command Line Checker */
  commandLineInterface();
 
  delay(interval*1000);
}



/* Methods */
void checkPIRDetection(int pirVal){
  if (pirVal == HIGH) {         // check if the PIR is HIGH
    if (pirState == LOW) {		// check if last PIR state is LOW to make toggle
      Serial.println("Motion detected!");
      pirState = HIGH;
      lampState = HIGH;
      fanState = HIGH;
      lampTimer = LOW;					 // deactivate lamp off timer
      digitalWrite(lampPin, lampState);  // turn lamp ON
      digitalWrite(fanPin, fanState);    // turn exhaust fan ON
    }
  } 
  
  else {						// check if the PIR is LOW
    if (pirState == HIGH){		// check if last PIR state is HIGH to make toggle
      Serial.println("No motion!");
      pirState = LOW;
      lampTimer = HIGH;			// activate lamp off timer
      lampOffTime = lampOffVar; // refresh off timer
    }
  }
}

void checkLamp(){
  if (lampTimer == HIGH){		// check if lamp off timer is activated
    if (lampOffTime > 0){		// check if the counter still running
    	lampOffTime -= interval;// decrease counter
    }
  else {
      	lampState = LOW;
      	lampTimer = LOW;		// deactivate lamp off timer
    	digitalWrite(lampPin, lampState); // turn lamp OFF
    }
  }
}

void checkExhaustFan(int gasVal){
  if (lampState == LOW && gasVal < gasThr){	// check if lamp is already LOW and gas is below threshold
    if (fanState == HIGH){					// check if last fan state is HIGH to make toggle
    	fanState = LOW;
      	digitalWrite(fanPin, fanState);  // turn off exhaust fan
    }
  }
}

void showAllStatus(){
  if (streams==LOW){
    return;
  }
  Serial.print("Lamp status : ");
  Serial.print(lampState);
  Serial.print(" ; ");
  Serial.print("Exh fan status : ");
  Serial.println(fanState);
  
  Serial.print("PIR val : ");
  Serial.print(pirVal);
  Serial.print(" ; ");
  Serial.print("Gas val : ");
  Serial.print(gasVal);
  Serial.print(" ; ");
  Serial.print("Lamp OFF Counter : ");
  Serial.println(lampOffTime);
  Serial.println("");
}

void commandLineInterface(){
  if(Serial.available()>0)
  {
  	cmd = Serial.readString();			// read command line
  	if (cmd == "/help" || cmd == "/?")	// check if command is 'help' or '?'
  	{
      	Serial.println("########## Command Line Informations ##########\n");
      	Serial.println("Show realtime data  : /stream 1\n"); // command for showing realtime data
      	Serial.println("Hide realtime data  : /stream 0\n"); // command for hiding realtime data
    	Serial.println("Input Config Format : /gasThr,lampOffVar,interval"); // give info for input format
    	Serial.println("Example : /500,15,1\n");
        Serial.println("################################################\n");
  	}
    else if (cmd == "/stream 1")
    {
    	streams = HIGH;
  	}
    else if (cmd == "/stream 0")
    {
    	streams = LOW;
  	}
  	else
    {
      	int c=0; // comma counter
  		int i=0; // command data length
      	int j=0; // command data parse index
  		dt[j]="";// refresh command data parse value
      
  		for(i=1;i<cmd.length();i++)
      	{
            if ((cmd[i] == '\n') || (cmd[i] == ',')) // check for special char for parsing
            {
                j++;		// increment index
                dt[j]=""; 	// refresh parsed command data at index j
               	
              	if (cmd[i] == ','){ // count comma char
               		c+=1;
               	}
            }
            else
            {
                dt[j] = dt[j] + cmd[i]; // store the numeric value
            }
      	}
      
    	if (c == 2){	// check if the comma amount are 2 to make sure data is valid (3 params input)
  			Serial.println("Input config success!");
  			// store input data to existing variable
      		gasThr = dt[0].toInt();
  			lampOffVar = dt[1].toInt();
  			interval = dt[2].toInt();
      		// print info
  			Serial.print("Gas Threshold : ");
  			Serial.print(gasThr);
  			Serial.print("\n");
  			Serial.print("Lamp Off Var : ");
  			Serial.print(lampOffVar);
  			Serial.print("\n");
  			Serial.print("Loop interval : ");
  			Serial.print(interval);
  			Serial.println("\n");
 		}
    	else
    	{
      		Serial.println("Data is not valid!\n");
    	}
  	}
    
  }
}