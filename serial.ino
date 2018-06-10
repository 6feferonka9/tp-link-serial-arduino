String inputString = "";
boolean stringComplete = false;
String input = "";
String br1 = "Autobooting in 1 seconds";
boolean done = false;
boolean gg = true;

void setup() {
  Serial.begin(115200);
  inputString.reserve(200);
}

void loop() {
  if (stringComplete) {
    if(done == false){
      Serial.println(inputString);
    }

    if(inputString.indexOf("Autobooting in 1 seconds") >= 0){
      Serial.println(F("tpl"));
      done = true;
    }   
  
    inputString = "";
    stringComplete = false;
  }
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;

    if (inChar == '\n') {
      stringComplete = true;
    }

    if (done){
       Serial.println(Serial.readString());

       if(gg){
          if(Serial.readString().indexOf("wasp>") >= 0){
            Serial.println(F("setenv ipaddr 192.168.0.1"));
          }        
          if(Serial.readString().indexOf("ipaddr") >= 0){
            Serial.println(F("setenv serverip 192.168.0.66"));
          }     
          if(Serial.readString().indexOf("serverip") >= 0){
            Serial.println(F("tftpboot 0x80000000 openwrt.bin"));
          }             
          if(Serial.readString().indexOf("transferred") >= 0){
            Serial.println(F("erase 0x9f020000 +0x3c0000"));
          }     
          if(Serial.readString().indexOf("Erased") >= 0){
            Serial.println(F("cp.b 0x80000000 0x9f020000 3c0000"));
            gg = false;
          }    
          if(Serial.readString().indexOf("on") >= 0){
            Serial.println(F("reboot"));
            gg = false;
          }            
     
       }
                                
    }
    
  }
}





