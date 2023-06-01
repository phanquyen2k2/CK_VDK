// Động cơ DC 
// OUT1 và OUT2 nối với động cơ DC 
// COM6 (wifi cắm ở cổng bên trái - trên) nạp code . COM3 (Arduino cắm ở cổng bên phải) nguồn . 
// Dùng nguồn của Arduino chứ không dùng nguồn của wifi 
// 12V Nối với 5V Arduino , GND nối với GND Arduino (Ở chỗ 3 ô)(5V để trống chỉ dùng 12V thôi)
#define IN1 D6 // D6 (chân số) 
#define IN2 D5 // D5 (chân số)
#define MAX_SPEED 255  //từ 0-255
#define MIN_SPEED 0                

void Lui(int speed) {
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);  
  digitalWrite(IN1, LOW);                      
  analogWrite(IN2, speed);
}
void Dung() {// Hàm dừng motor
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}
void Tien(int speed) {
  speed = constrain(speed, MIN_SPEED, MAX_SPEED); //đảm báo giá trị nằm trong một khoảng từ 0 - MAX_SPEED 
  analogWrite(IN1, speed); 
  digitalWrite(IN2, LOW);
}
void NhanhDan(){
  for (int i = 0 ; i <= 255 ; i++){
    analogWrite(IN1 , i);
    digitalWrite(IN2 , LOW);
    delay(50);
  }
}
void ChamDan(){
  for (int i = 255; i >= 0 ; i--){
    analogWrite(IN1 , i);
    digitalWrite(IN2 , LOW);
    delay(50);
  }
}

// Wifi Nên cắm ở cổng bên trái của máy tính (cổng bên trái và phía trên gần với màn hình) thì nó mới nhận 
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
ESP8266WebServer server(80);            
// Đối với wifi khi setup cổng thì cần thêm A với D ví dụ A0, D4 

// Cảm biến siêu âm 
const int trig = D8;  // D8 chân trig của HC-SR04
const int echo = D7;  // D7 chân echo của HC-SR04                   
// LƯU Ý : Đối với siêu âm không dùng nguồn của Wifi . GND và VCC của siêu âm cắm vào nguồn của Arduino 
// Khi cắm cả wifi và arduino vào máy thì nhớ chọn cổng cho đúng để nạp code . Cắm arduino vào trước xem là COM nào sau đó cắm tiếp wifi vào xem là com nào 
// Nên cắm wifi ở cổng trái bên trên (gần màn hình) . Còn arduino cắm vào cổng bên phải . 
// NẠP CODE VÀO COM6 , còn COM3 Arduino là dùng làm nguồn 
// ĐỐI VỚI BÀI NÀY THÌ CẢ ĐỘNG CƠ DC và siêu âm điều dùng nguồn ngoài 

void setup() {
  Serial.begin(9600); 
  delay(1000);
  WiFi.begin("OPPO Reno", "vanmanh999"); //SSID && Pasword
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
                "var optionInput = document.getElementById('option');"
                "var xhttp2 =  new XMLHttpRequest();"
                "var option = optionInput.value;"
                "xhttp2.open('POST', 'sendValue', true);"
                "xhttp2.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');"
                "xhttp2.send('option=' + option);"
                "}"
                "</script>"
                "</head>"
                "<body>"
                
                "<label>Value Sensor</label><br>"
                "<input type='text' id='serialMonitor'>"
                "<br><br>"
                "<label>option (1 = Tien ,  2 = Lui , 3 = Nhanh Dan , 4 = Cham Dan): </label>"
                "<input type='text' name='option' id = 'option'>"
                "<input type='button' value='Send' onclick = sendValue()>"
                "</body>"
                
                "</html>");
  });


//  
//                "<label>Value Gas Sensor</label><br>"
//                "<textarea id='serialMonitor' style='font-family: monospace; width: 100%; height: 300px; white-space: pre; '></textarea>"
//                "<label>option (1 = Tien ,  2 = Lui , 3 = Nhanh Dan , 4 = Cham Dan): </label>"
//                "<input type='text' name='option' id = 'option'>"
//                "<input type='button' value='Send' onclick = sendValue()>"
  
  // ĐỘNG CƠ DC  
  pinMode(IN1, OUTPUT);  // (Đối với chân số thì cần khai báo) 
  pinMode(IN2, OUTPUT);  // (Đối với chân số thì cần khai báo)
  pinMode(trig, OUTPUT);    // D8
  pinMode(echo,INPUT);      // D7 
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

// Nhận giá trị độ từ web để điều khiển servo 
int option = 0;
void handleSendValue() {
  if (server.hasArg("option")) {
    option = server.arg("option").toInt();
  }
}

void setupRoutes() {
  server.on("/readSerial", handleReadSerial);
  server.on("/sendValue", handleSendValue);
}

// Nhập 1 xong đến 2 xong đến 3 rồi đến 4 để test , cuối cùng nhập 0 để dừng 
void loop() {
  // Xử lý các yêu cầu từ client
  server.handleClient();
  delay(500);  // Đợi để hệ thống xử lý các yêu cầu khác
  Serial.print("option : ");
  Serial.println(option);
  if (option == 1){ 
    Tien(200); // 200 truyền vào là tốc độ 
  }
  else if(option == 2){
    Lui(200); 
  }
  else if(option == 3){
    NhanhDan(); 
  }
  else if(option == 4){
    ChamDan();
  }
  else {
    Dung();
  }
  delay(200);
}
