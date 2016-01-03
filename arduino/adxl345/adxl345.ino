

ADXL345 adxl; //variable adxl is an instance of the ADXL345 library

void setupAdxl345()
{
  adxl.powerOn();

  //set activity/ inactivity thresholds (0-255)
  adxl.setActivityThreshold(75); //62.5mg per increment
  adxl.setInactivityThreshold(75); //62.5mg per increment
  adxl.setTimeInactivity(10); // how many seconds of no activity is inactive?
 
  //look of activity movement on this axes - 1 == on; 0 == off 
  adxl.setActivityX(1);
  adxl.setActivityY(1);
  adxl.setActivityZ(1);
 
  //look of inactivity movement on this axes - 1 == on; 0 == off
  adxl.setInactivityX(1);
  adxl.setInactivityY(1);
  adxl.setInactivityZ(1);
 
  //look of tap movement on this axes - 1 == on; 0 == off
  adxl.setTapDetectionOnX(0);
  adxl.setTapDetectionOnY(0);
  adxl.setTapDetectionOnZ(1);
 
  //set values for what is a tap, and what is a double tap (0-255)
  adxl.setTapThreshold(50); //62.5mg per increment
  adxl.setTapDuration(15); //625us per increment
  adxl.setDoubleTapLatency(80); //1.25ms per increment
  adxl.setDoubleTapWindow(200); //1.25ms per increment
 
  //set values for what is considered freefall (0-255)
  adxl.setFreeFallThreshold(7); //(5 - 9) recommended - 62.5mg per increment
  adxl.setFreeFallDuration(45); //(20 - 70) recommended - 5ms per increment
 
  //setting all interrupts to take place on int pin 1
  //I had issues with int pin 2, was unable to reset it
  adxl.setInterruptMapping( ADXL345_INT_SINGLE_TAP_BIT,   ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_DOUBLE_TAP_BIT,   ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_FREE_FALL_BIT,    ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_ACTIVITY_BIT,     ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_INACTIVITY_BIT,   ADXL345_INT1_PIN );
 
  //register interrupt actions - 1 == on; 0 == off  
  adxl.setInterrupt( ADXL345_INT_SINGLE_TAP_BIT, 1);
  adxl.setInterrupt( ADXL345_INT_DOUBLE_TAP_BIT, 1);
  adxl.setInterrupt( ADXL345_INT_FREE_FALL_BIT,  1);
  adxl.setInterrupt( ADXL345_INT_ACTIVITY_BIT,   1);
  adxl.setInterrupt( ADXL345_INT_INACTIVITY_BIT, 1);
}

void adxl345()
{
  //Boring accelerometer stuff   
  int x,y,z;  
  adxl.readXYZ(&x, &y, &z); //read the accelerometer values and store them in variables  x,y,z
  // Output x,y,z values 
  Serial.print("values of X , Y , Z: ");
  Serial.print(x);
  Serial.print(" , ");
  Serial.print(y);
  Serial.print(" , ");
  Serial.println(z);
  
  double xyz[3];
  double ax,ay,az;
  adxl.getAcceleration(xyz);
  ax = xyz[0];
  ay = xyz[1];
  az = xyz[2];
  Serial.print("X=");
  Serial.print(ax);
        Serial.println(" g");
  Serial.print("Y=");
  Serial.print(ay);
        Serial.println(" g");
  Serial.print("Z=");
  Serial.println(az);
        Serial.println(" g");
  Serial.println("**********************");
  
/*

  //Fun Stuff!    
  //read interrupts source and look for triggerd actions
  
  //getInterruptSource clears all triggered actions after returning value
  //so do not call again until you need to recheck for triggered actions
   byte interrupts = adxl.getInterruptSource();
  
  // freefall
  if(adxl.triggered(interrupts, ADXL345_FREE_FALL)){
    Serial.println("freefall");
    //add code here to do when freefall is sensed
  } 
  
  //inactivity
  if(adxl.triggered(interrupts, ADXL345_INACTIVITY)){
    Serial.println("inactivity");
     //add code here to do when inactivity is sensed
  }
  
  //activity
  if(adxl.triggered(interrupts, ADXL345_ACTIVITY)){
    Serial.println("activity"); 
     //add code here to do when activity is sensed
  }
  
  //double tap
  if(adxl.triggered(interrupts, ADXL345_DOUBLE_TAP)){
    Serial.println("double tap");
     //add code here to do when a 2X tap is sensed
  }
  
  //tap
  if(adxl.triggered(interrupts, ADXL345_SINGLE_TAP)){
    Serial.println("tap");
     //add code here to do when a tap is sensed
  } */
}

void setupDht22()
{

    Serial.println("DHT TEST PROGRAM ");
    Serial.print("LIBRARY VERSION: ");
    Serial.println(DHT_LIB_VERSION);
    Serial.println();
    Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)\tTime (us)");
}

void dht22()
{
    // READ DATA
        Serial.print("DHT22, \t");

        uint32_t start = micros();
        int chk = DHT.read22(DHT22_PIN);
        uint32_t stop = micros();

        switch (chk)
        {
        case DHTLIB_OK:
            Serial.print("OK,\t");
            break;
        case DHTLIB_ERROR_CHECKSUM:
            Serial.print("Checksum error,\t");
            break;
        case DHTLIB_ERROR_TIMEOUT:
            Serial.print("Time out error,\t");
            break;
        default:
            Serial.print("Unknown error,\t");
            break;
        }

        // DISPLAY DATA
        Serial.print(DHT.humidity, 1);
        Serial.print(",\t");
        Serial.print(DHT.temperature, 1);
        Serial.print(",\t");
        Serial.print(stop - start);
        Serial.println();

        
}

void setup()
{
    Serial.begin(115200);

    setupDht22();
    setupAdxl345();
}

void loop()
{
    dht22();
    
    adxl345();
    delay(500);   

    adxl345();
    delay(500);   

    adxl345();
    delay(500);   

    adxl345();
    delay(500);   

}
//
// END OF FILE
//
