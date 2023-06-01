// Wifi Nên cắm ở cổng bên trái của máy tính (cổng bên trái và phía trên gần với màn hình) thì nó mới nhận 
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
ESP8266WebServer server(80);            
// Đối với wifi khi setup cổng thì cần thêm A với D ví dụ A0, D4 

// Đối với wifi khi setup cổng thì cần thêm A với D ví dụ A0, D4 
// Cảm biến dò Line 
// int SensorLine = D3; // D0 nối với chân số D3 của wifi (1 là đen , 0 là trắng) , VCC nối 3V3 của wifi, GND nối GND của wifi
int SensorLine = A0; // A0 Chân đọc giá trị của cảm biến dò line (1024 là đen , 0 là trắng)
// Đổi chân ở đây thì đổi ở dưới handleReadSerial nữa 
int LineSensorValue = 0;          
// + A0 
//     + Đen là 1 
//     + Trắng là 0 
// + D0 
//     + Đen là 1024 
//     + Trắng là 0 

// ĐỘNG CƠ BƯỚC 
int Pin1 = D5;  // D5
int Pin2 = D6;  // D6
int Pin3 = D7;  // D7
int Pin4 = D8;  // D8 

int motorspeed = 0; // Tốc độ của motorsa
boolean direction = false;// false=ngược chiều kim đồng hồ, true=cùng chiều kim đồng hồ

void step_1()
{
  digitalWrite(Pin1, LOW);  
  digitalWrite(Pin2, LOW); 
  digitalWrite(Pin3, LOW); 
  digitalWrite(Pin4, HIGH); 
  delay(motorspeed);
}

void step_2()
{
  digitalWrite(Pin1, LOW);  
  digitalWrite(Pin2, LOW); 
  digitalWrite(Pin3, HIGH); 
  digitalWrite(Pin4, HIGH); 
  delay(motorspeed);
   
}

void step_3()
{
  digitalWrite(Pin1, LOW);  
  digitalWrite(Pin2, LOW); 
  digitalWrite(Pin3, HIGH); 
  digitalWrite(Pin4, LOW); 
  delay(motorspeed); 
}

void step_4()
{
  digitalWrite(Pin1, LOW);  
  digitalWrite(Pin2, HIGH); 
  digitalWrite(Pin3, HIGH); 
  digitalWrite(Pin4, LOW); 
  delay(motorspeed);
}

void step_5()
{
  digitalWrite(Pin1, LOW);  
  digitalWrite(Pin2, HIGH); 
  digitalWrite(Pin3, LOW); 
  digitalWrite(Pin4, LOW); 
  delay(motorspeed);
}

void step_6()
{
  digitalWrite(Pin1, HIGH);  
  digitalWrite(Pin2, HIGH); 
  digitalWrite(Pin3, LOW); 
  digitalWrite(Pin4, LOW); 
  delay(motorspeed);
}

void step_7()
{
  digitalWrite(Pin1, HIGH);  
  digitalWrite(Pin2, LOW); 
  digitalWrite(Pin3, LOW); 
  digitalWrite(Pin4, HIGH); 
  delay(motorspeed);
}

void step_8()
{
  digitalWrite(Pin1, HIGH);  
  digitalWrite(Pin2, LOW); 
  digitalWrite(Pin3, LOW); 
  digitalWrite(Pin4, HIGH); 
  delay(motorspeed);
}

void counter_clockwise_rotating()   //Xoay động cơ ngược chiều kim đồng hồ
{
  step_8();
  step_7();
  step_6();
  step_5();
  step_4();
  step_3();
  step_2();
  step_1();
}

void clockwise_rotating() //Xoay động cơ cùng chiều kim đồng hồ
{
  step_1();
  step_2();
  step_3();
  step_4();
  step_5();
  step_6();
  step_7();
  step_8();
}

void speed_changing(int value)  //Thay đổi tốc độ của động cơ 
{
  motorspeed = value/120 + 1;
}

void direction_changing()   //Thay đổi hướng quay của động cơ 
{
  if (direction == true){
    direction = false;    
  }
  else{
    direction = true;    
  }
}
// ĐỘNG CƠ BƯỚC 



void setup() {
  Serial.begin(9600); 
  delay(1000);
  WiFi.begin("OPPO Reno", "vanmanh9999"); //SSID && Pasword
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println(".");
  }
  Serial.println("IP: ");
  Serial.println(WiFi.localIP());
  server.on("/", [] {
    server.send(200, "text/html",
                "<!DOCTYPE html>"
                "<html>"
                "<head>"
                "<title>Serial Monitor</title>"
                "<script>"
                "window.onload = function() {"
                "readSerial();"
                "};"
                "function readSerial() {"
                "var serialMonitor = document.getElementById('serialMonitor');"
                "var xhttp = new XMLHttpRequest();"
                "xhttp.onreadystatechange = function() {"
                "if (this.readyState == 4 && this.status == 200) {"
                "serialMonitor.value = this.responseText;"
                "serialMonitor.scrollTop = serialMonitor.scrollHeight;"
                "setTimeout(readSerial, 500);"
                "}"
                "};"
                "xhttp.open('GET', 'readSerial', true);"
                "xhttp.send();"
                "}"
                "function sendValue(){"
                "var DirectionOfRotationInput = document.getElementById('DirectionOfRotation');"
                "var xhttp2 =  new XMLHttpRequest();"
                "var DirectionOfRotation = DirectionOfRotationInput.value;"
                "xhttp2.open('POST', 'sendValue', true);"
                "xhttp2.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');"
                "xhttp2.send('DirectionOfRotation=' + DirectionOfRotation);"
                "}"
                "</script>"
                "</head>"
                "<body>"
                
                "<label>Value Sensor</label><br>"
                "<input type='text' id='serialMonitor'>"
                "<br><br>"
                "<label>Direction Of Rotation (1 = clockwise_rotating) : </label>"
                "<input type='text' name='DirectionOfRotation' id = 'DirectionOfRotation'>"
                "<input type='button' value='Send' onclick = sendValue()>"
                "</body>"
                
                "</html>");
  });


//  
//                "<label>Value Dò line Sensor</label><br>"
//                "<textarea id='serialMonitor' style='font-family: monospace; width: 100%; height: 300px; white-space: pre; '></textarea>"
//                "<label>DirectionOfRotation : </label>"
//                "<input type='text' name='DirectionOfRotation' id = 'DirectionOfRotation'>"
//                "<input type='button' value='Send' onclick = sendValue()>"

  pinMode(Pin1, OUTPUT); // ĐỘNG CƠ BƯỚC   
  pinMode(Pin2, OUTPUT); // ĐỘNG CƠ BƯỚC   
  pinMode(Pin3, OUTPUT); // ĐỘNG CƠ BƯỚC   
  pinMode(Pin4, OUTPUT); // ĐỘNG CƠ BƯỚC  

    // Dò Line 
  pinMode(SensorLine, INPUT); // D0 hay A0 thì cũng để như thế này 
  // D0 Thêm setup nếu dùng D0 => D3 , còn nếu dùng A0 thì không cần 
  // A0 Chân analog cũng có thể setup pinMode (có mấy cái không cần setup cũng được) 
  
  setupRoutes();
  server.begin();  // Bắt đầu web server
}


// Gửi giá trị đọc được từ cảm biến lên web 
void handleReadSerial() {
  // LineSensorValue = digitalRead(SensorLine); // D0 nối với D3 wifi 
  LineSensorValue = analogRead(SensorLine); // A0 nối với A0 wifi 
  server.send(200, "text/plain", String(LineSensorValue) + "\n");
}

// Nhận giá trị độ từ web để điều khiển Động cơ bước 
int receivedValue = 0; // nhận số 
void handleSendValue() {
  if (server.hasArg("DirectionOfRotation")) {
    receivedValue = server.arg("DirectionOfRotation").toInt(); // nhận số 
  }
}

void setupRoutes() {
  server.on("/readSerial", handleReadSerial);
  server.on("/sendValue", handleSendValue);
}
void loop() {
  // Xử lý các yêu cầu từ client
  server.handleClient();
  delay(500);  // Đợi để hệ thống xử lý các yêu cầu khác
  Serial.println(receivedValue);
  speed_changing(0);
  if (receivedValue == 1){ // Nhận số 1 là cùng chiều 
    for (int i=0; i<128; i++)  {
      clockwise_rotating()   ;  // Xoay động cơ cùng chiều kim đồng hồ
    }
    delay(1000);
  }
  else{ // ngược lại nhận 0 thì ngược chiều  
    for (int i=0; i<128; i++)  {
      counter_clockwise_rotating()   ;  //Xoay động cơ ngược chiều kim đồng hồ
    }
    delay(1000);
  }  
}
