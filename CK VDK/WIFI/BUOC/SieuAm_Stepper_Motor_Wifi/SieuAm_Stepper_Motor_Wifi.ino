// Wifi Nên cắm ở cổng bên trái của máy tính (cổng bên trái và phía trên gần với màn hình) thì nó mới nhận 
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
ESP8266WebServer server(80);            
// Đối với wifi khi setup cổng thì cần thêm A với D ví dụ A0, D4 

// Cảm biến siêu âm 
const int trig = D4;  // D4 chân trig của HC-SR04
const int echo = D3;  // D3 chân echo của HC-SR04                   
// LƯU Ý : Đối với siêu âm không dùng nguồn của Wifi . GND và VCC của siêu âm cắm vào nguồn của Arduino 
// Khi cắm cả wifi và arduino vào máy thì nhớ chọn cổng cho đúng để nạp code . Cắm arduino vào trước xem là COM nào sau đó cắm tiếp wifi vào xem là com nào 
// Nên cắm wifi ở cổng trái bên trên (gần màn hình) . Còn arduino cắm vào cổng bên phải . 
// NẠP CODE VÀO COM6 , còn COM3 Arduino là dùng làm nguồn 
// ĐỐI VỚI BÀI NÀY THÌ CẢ ĐỘNG CƠ DC và siêu âm điều dùng nguồn ngoài 

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

  // Siêu âm 
  pinMode(trig, OUTPUT);    // D4
  pinMode(echo,INPUT);      // D3 

  setupRoutes();
  server.begin();  // Bắt đầu web server
}

// Gửi giá trị đọc được từ cảm biến lên web 
void handleReadSerial() {

  unsigned long duration; // biến đo thời gian
  int distance;           // biến lưu khoảng cách
  /* Phát xung từ chân trig */
  digitalWrite(trig,0);   // tắt chân trig
  delayMicroseconds(2);
  digitalWrite(trig,1);   // phát xung từ chân trig
  delayMicroseconds(10);   // xung có độ dài 10 microSeconds
  digitalWrite(trig,0);   // tắt chân trig
  /* Tính toán thời gian,khoảng cách */
  // Đo độ rộng xung HIGH ở chân echo. Đơn vị us
  duration = pulseIn(echo,HIGH); 
  // Tính khoảng cách đến vật.
  //van toc am thanh 340m/s = 0.034cm/us
  // s = v*t
  distance = int(duration*0.034/2);
  /* In kết quả ra Serial Monitor */    
  Serial.print(distance);
  Serial.println("cm");

  server.send(200, "text/plain", String(distance) + "cm" + "\n");
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
