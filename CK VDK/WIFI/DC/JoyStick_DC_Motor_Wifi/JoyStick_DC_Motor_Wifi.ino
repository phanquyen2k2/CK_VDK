// ĐỘNG CƠ DC 
// OUT1 và OUT2 nối với động cơ DC 
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

// Joystick 
int Joystick_x = A0; // chân x của joystick      (chân A0) (A0 nối với A0 của wifi, VCC nối 3V3 của wifi, GND nối GND của wifi)   
// int Joystick_y = A3; // chân y của joystick   (chân A3) // Không dùng chân A3 vì không có 
int Joystick_sw = D3; // chân sw của joystick     (nối với chân D3 của wifi)                 
// Joystick_sw Để bình thường là 1 , bấm xuống là 0 
// Không dùng Joystick_y vẫn chạy bình thường , nó chỉ là không đọc giá trị y thôi                   

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
                
                "<label>Value Joystick</label><br>"
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
  
  // Joystick
  pinMode(Joystick_x, INPUT); // A0 Setup chân cho x  
  pinMode(Joystick_sw, INPUT); // D0 Setup chân cho sw 
  setupRoutes();
  server.begin();  // Bắt đầu web server
}

// Gửi giá trị đọc được từ cảm biến lên web 
void handleReadSerial() {
  int x,y,sw; //khai báo các biến 
  x=analogRead(Joystick_x); //đọc giá trị từ chân Analog x // A0 
  // y=analogRead(Joystick_y); //đọc giá trị từ chân Analog y
  sw=digitalRead(Joystick_sw); //đọc tín hiệu từ chân digital sw // D3
  server.send(200, "text/plain", "x : " + String(x) + " , sw : " + String(sw) + "\n");

  Serial.print(x);
  Serial.print("\t");
  Serial.print(y);
  Serial.print("\t");
  Serial.print(sw);
  Serial.print("\n");
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
