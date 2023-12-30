#include <TridentTD_LineNotify.h>
#define SSID        "YourNetworkName" //ชื่อwifi    
#define PASSWORD    "YourPassword" //รหัสwifi
#define LINE_TOKEN  "YourLine_Token" //linetoken
#define analogPin 2 //ประกาศตัวแปร ให้ analogPin แทนขา D4
int val = 0;
bool notificationSent = false;
void setup() {
  Serial.begin(115200); Serial.println(); //baud 115200
  Serial.println(LINE.getVersion());

  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n",  SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(400);
  }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());

  // กำหนด Line Token
  LINE.setToken(LINE_TOKEN);
}

void loop() {
  val = analogRead(analogPin);  //อ่านค่าสัญญาณ analog ขา D4
  Serial.print("val = "); // แสดงข้อความใน serial Monitor "val = "
  Serial.println(val); // พิมพ์ค่าของตัวแปร val
  if (val < 900 && !notificationSent) { 
    LINE.notify("อุณหภูมิ เกินกำหนด");//ข้อความที่ต้องการให้แจ้งเข้าline
    notificationSent = true;
    delay(100);
    
  }
  else{
    delay(100);
    if(val > 900 && notificationSent){
      notificationSent = false;
    }
  }
}