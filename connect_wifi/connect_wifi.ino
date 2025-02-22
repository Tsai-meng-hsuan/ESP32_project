#include <WiFi.h>
#include <HTTPClient.h>

// const char *ssid     = "HoChiang"; //ssid:網路名稱
// const char *password = "Ho10417115"; //pasword：網路密碼
// const char *ssid     = "mhtsai_12mini"; //ssid:網路名稱
// const char *password = "mengal25141425"; //pasword：網路密碼
const char *ssid     = "Thinktron Guest"; //ssid:網路名稱
const char *password = "#smart&green#"; //pasword：網路密碼


//建立HTTPClient實例
HTTPClient http;

void setup() {
  Serial.begin(115200); //ESP32胞率好像固定是115200
  WiFi.begin(ssid, password); //連線
  Serial.println(String("Connecting to ")+ssid);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\nIP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("WiFi status:");
  WiFi.printDiag(Serial); //顯示WiFi連線狀態資訊：工作模式、Channel、SSID、Passphrase、BSSID
  
  //打API
  String url = "https://lab-monitor-backend-fastapi.onrender.com/upload_data";
  //加入參數
  url += "?data=test123";  // 傳遞 sensor_id 參數
  
  http.begin(url);
  int httpCode = http.GET();
  if (httpCode > 0) { //检查返回的代码
    String payload = http.getString();
    Serial.println(httpCode);
    Serial.println(payload);
  }else {
    Serial.println("Error on HTTP request");
  }
  http.end(); //释放资源
}
  
void loop() {
}