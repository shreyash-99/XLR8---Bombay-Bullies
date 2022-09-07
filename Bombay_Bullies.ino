//Including the following libraries is a must to use the IoT functions and features of esp32
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "analogWrite.h"


const char* ssid = "Bombay Bullies"; // This will show up when you turn on your mobile WIFI
const char* password = "marvel22
";  // change to more unique password

AsyncWebServer server(80); // These will start the webserver // If you don't know much, Ignore this line

// These pins are the Enable pins of the L293D motor driver which connects to esp32 gpio pins to implement the PWM function
int enable1_2 = 5; // choose the GPIO pin of esp32;
int enable3_4 = 33; // choose the GPIO pin of esp32; 

// These pins are the input pins of l293d on the left side
int inp1 = 21; // Choose your GPIO pin of esp32 for the input 1
int inp2 = 19; // Choose your GPIO pin of esp32 for the input 2


// These pins are the input pins of l293d on the right side
int inp3 = 4; // Choose your GPIO pin of esp32 for the input 3
int inp4 = 22; // Choose your GPIO pin of esp32 for the input 4 


int led = 2; // until now you must know what is the inbuilt led pin number of esp32. 

  
void setup(){

  // Fill in the blanks
  
  pinMode(enable1_2, OUTPUT);
  pinMode(enable3_4, OUTPUT);



  // The inputs
  pinMode(inp1, OUTPUT);
  pinMode(inp2, OUTPUT);
  pinMode(inp3, OUTPUT);
  pinMode(inp4, OUTPUT);


  pinMode(led, OUTPUT);


// We use the following function to run the bot at variable speed.
  analogWrite(enable1_2, 255); // analog write "255" corresponds to digital write "1"
  analogWrite(enable3_4, 255);
  

  WiFi.softAP(ssid, password);  // This sets your esp32's name as per above mentioned

  IPAddress IP = WiFi.softAPIP();


// A bit of WEB DEV stuff 
  server.on("/control", HTTP_GET, [](AsyncWebServerRequest *request){
    
    if(request->hasArg("up")){
      // You have to develop the logic that, when the Button "up" on the webpage is pressed, Then the esp32 executes the following commands
      // Refer to the this for the webpage photo
      digitalWrite(inp1, HIGH);
      digitalWrite(inp2, LOW);
      digitalWrite(inp3, HIGH);
      digitalWrite(inp4, LOW);

      digitalWrite(led, HIGH);
    }

    if(request->hasArg("down")){
      digitalWrite(inp1, LOW);
      digitalWrite(inp2, HIGH);
      digitalWrite(inp3, LOW);
      digitalWrite(inp4, HIGH);
      
    }

    if(request->hasArg("left")){
      digitalWrite(inp1, HIGH);
      digitalWrite(inp2, LOW);
      digitalWrite(inp3, LOW);
      digitalWrite(inp4, HIGH);
    }
    
    if(request->hasArg("right")){
      digitalWrite(inp1, LOW);
      digitalWrite(inp2, HIGH);
      digitalWrite(inp3, HIGH);
      digitalWrite(inp4, LOW);
    }
    

    if(request->hasArg("slow")){ 
// if '255' is the equivalent to digital '1', and '0' is eqvivalent to digial '0', We vary the pwm values to vary the speed of the motor
      analogWrite(enable1_2, 120);   
      analogWrite(enable3_4, 120);  
    }

    if(request->hasArg("fast")){
      analogWrite(enable1_2, 255 );
      analogWrite(enable3_4, 255);  
    }
    
    request->send_P(200, "text/plain", "");  
  });
  

  server.begin();
}
 
void loop(){
  

}
