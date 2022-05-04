    #include <LiquidCrystal_I2C.h>

    #include <Wire.h>


       //------------------------------------------------

        //This program includes an excerpt of a song played
        //by the buzzer at the start of the program, which 
        //was modified from the original version created by the
        //Github user xitanggg, the following is the link to his code
        //https://github.com/xitanggg/-Pirates-of-the-Caribbean-Theme-Song/blob/master/Pirates_of_the_Caribbean_-_Theme_Song.ino





       //------------------------------------------------





    
    //initialize the liquid crystal library
    //the first parameter is the I2C address
    //the second parameter is how many rows are on your screen
    //the third parameter is how many columns are on your screen
    LiquidCrystal_I2C lcd(0x27, 16, 2);
    const int buzzer = 3;
    const int ledR = 2;
    // Change to 0.5 for a slower version of the song, 1.25 for a faster version
    const float songSpeed = 1.0;
    int freq = 262;
    bool up = true;
    // Defining frequency of each music note
    #define NOTE_C4 262
    #define NOTE_D4 294
    #define NOTE_E4 330
    #define NOTE_F4 349
    #define NOTE_G4 392
    #define NOTE_A4 440
    #define NOTE_B4 494
    #define NOTE_C5 523
    #define NOTE_D5 587
    #define NOTE_E5 659
    #define NOTE_F5 698
    #define NOTE_G5 784
    #define NOTE_A5 880
    #define NOTE_B5 988
    
    // Music notes of the song, 0 is a rest/pulse
    int notes[] = {
        NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
        NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
        NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
        NOTE_A4, NOTE_G4, NOTE_A4, 0,
    
        NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
        NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
        NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
        NOTE_A4, NOTE_G4, NOTE_A4, 0,
    
        NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
        NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0,
        NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
        NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,
    
        NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
        NOTE_D5, NOTE_E5, NOTE_A4, 0,
        NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
        NOTE_C5, NOTE_A4, NOTE_B4, 0
    };
    
    // Durations (in ms) of each music note of the song
    // Quarter Note is 250 ms when songSpeed = 1.0
    int durations[] = {
        125, 125, 250, 125, 125,
        125, 125, 250, 125, 125,
        125, 125, 250, 125, 125,
        125, 125, 375, 125,
    
        125, 125, 250, 125, 125,
        125, 125, 250, 125, 125,
        125, 125, 250, 125, 125,
        125, 125, 375, 125,
    
        125, 125, 250, 125, 125,
        125, 125, 250, 125, 125,
        125, 125, 250, 125, 125,
        125, 125, 125, 250, 125,
    
        125, 125, 250, 125, 125,
        250, 125, 250, 125,
        125, 125, 250, 125, 125,
        125, 125, 375, 375
    };

    int sensorPin = A0; //the analog pin the TMP36's Vout (sense) pin is connected to
                       //the resolution is 10 mV / degree centigrade with a
                       //500 mV offset to allow for negative temperatures
     
    /*
     * setup() - this function runs once when you turn your Arduino on
     * We initialize the serial connection with the computer
     */
     String x = "Initiating Startup";
    void setup()
    {
      Serial.begin(9600);  //Start the serial connection with the computer
                           //to view the result open the serial monitor 
     lcd.init();
     lcd.backlight();
    lcd.setCursor(0,0);
  // tell the screen to write “hello, from” on the top row
  lcd.print("Hello Fadi");
  // tell the screen to write on the bottom row
  lcd.setCursor(0,1);
  // tell the screen to write “Arduino_uno_guy” on the bottom row
  // you can change whats in the quotes to be what you want it to be!
     const int totalNotes = sizeof(notes) / sizeof(int);
     pinMode(ledR, OUTPUT);
    // Loop through each note
    for (int i = 0; i < totalNotes; i++)
    {
      if(i<27){
        lcd.print(x[i]);
      }
      const int currentNote = notes[i];
      float wait = durations[i] / songSpeed;
      // Play tone if currentNote is not 0 frequency, otherwise pause (noTone)
      if (currentNote != 0)
      {
        tone(buzzer, notes[i], wait); // tone(pin, frequency, duration)
      }
      else
      {
        noTone(buzzer);
      }
      // delay is used to wait for tone to finish playing before moving to next loop
      delay(wait);
    }
    lcd.clear();
    }

    void Alarm(){
        if(freq<988 && up){
        freq += 30;
      }else if(freq>988 && up){
        up = false;
      }else if(!up && freq>350){
        freq -= 30;
      }else if(freq<350){
        up = true;
      }
      if(freq>700){
        digitalWrite(ledR, HIGH);
      }else{
        digitalWrite(ledR, LOW);
      }
      tone(buzzer,freq);
      
        
    }
     
    void loop() // run over and over again
    {
     //getting the voltage reading from the temperature sensor
     int reading = analogRead(sensorPin);  
     
     // converting that reading to voltage, for 3.3v arduino use 3.3
     float voltage = reading * 5.0;
     voltage /= 1024.0; 
     
     // print out the voltage
     Serial.print(voltage); Serial.print(" volts || ");
     
     // now print out the temperature
     float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree with 500 mV offset
                                                   //to degrees ((voltage - 500mV) times 100)
     float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
     Serial.print(temperatureF); Serial.println(" degrees F");
     Serial.print(temperatureC); Serial.print(" degrees C || ");
     lcd.setCursor(0,0);
     lcd.print("Celsius:   ");
     lcd.print(temperatureC);
     lcd.setCursor(0,1);
     lcd.print("Fahrenheit:");
     lcd.print(temperatureF);
  lcd.setCursor(0,1);
     if(temperatureC>24 || temperatureC < 18){
         Alarm();
     }else{
      noTone(buzzer);
      digitalWrite(ledR, LOW);
     }
     
     delay(50);
    }
