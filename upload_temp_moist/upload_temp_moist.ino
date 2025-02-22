#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"
#define DHTPIN 25 //for ESP32
#define DHTTYPE DHT11

// const char *ssid     = "HoChiang"; //ssid:網路名稱
// const char *password = "Ho10417115"; //pasword：網路密碼
// const char *ssid     = "mhtsai_12mini"; //ssid:網路名稱
// const char *password = "mengal25141425"; //pasword：網路密碼
const char *ssid     = "Thinktron Guest"; //ssid:網路名稱
const char *password = "#smart&green#"; //pasword：網路密碼


String sql_str = "INSERT INTO public.temperature_moisture_monitor("
                  "time, temperature, moisture)"
                  "VALUES (%s, %s, %s);";


//建立HTTPClient實例
HTTPClient http;
//建立溫溼度感測器實例
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200); //ESP32胞率好像固定是115200
  dht.begin();  //初始化DHT
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
}
  
void loop() {
  float h = dht.readHumidity();     //取得濕度
  float t = dht.readTemperature();  //取得溫度C
  h = 45.2;
  t = 25.3;
  // 将湿度和温度转换为字符串
  String humidityStr = String(h, 2);   // 保留 2 位小数
  String temperatureStr = String(t, 2); // 保留 2 位小数
  //打API
  String url = "https://surface_tunnel_1.mhtsai.org/get_sensor_data";
  //加入參數，ESP32的GET方式好像只能傳單一參數，只好在感測器端以STR回傳，進行後續字串處理
  url += "?data=";  // 傳遞 sensor_id 參數
  url += "temperature:" + temperatureStr;
  url += ",moisture:" + humidityStr;

  Serial.println(url);
  http.begin(url);
  
  int httpCode = http.GET();
  if (httpCode > 0) { //检查返回的代码
    String payload = http.getString();
    Serial.println(httpCode);
    Serial.println(payload);
  }else {
    Serial.println(httpCode);
    Serial.println("Error on HTTP request");
  }
  http.end(); //释放资源
  delay(15*60*1000);
  // delay(5*1000);
}


// void sendGETRequest() {
//   // 创建一个 HTTPClient 对象
//   HTTPClient http;

//   // 构建带查询字符串的 URL（例如：`api?param1=value1&param2=value2`）
//   String url = String(serverUrl) + "?param1=value1&param2=value2";

//   // 启动请求
//   http.begin(url);  // 请求的 URL

//   // 发送 GET 请求
//   int httpCode = http.GET();

//   // 检查请求结果
//   if (httpCode > 0) {
//     Serial.printf("GET request successful, code: %d\n", httpCode);
//     String payload = http.getString();  // 获取响应内容
//     Serial.println("Response: ");
//     Serial.println(payload);  // 打印响应内容
//   } else {
//     Serial.printf("GET request failed, code: %d\n", httpCode);
//   }

//   // 结束请求
//   http.end();
// }


// void sendPOSTRequest() {
//   // 创建一个 HTTPClient 对象
//   HTTPClient http;

//   // 构建 POST 请求的 URL（例如：`http://example.com/api`）
//   String url = serverUrl;

//   // 创建 POST 请求的内容，可以是 JSON 格式或表单数据格式
//   String jsonData = "{\"param1\":\"value1\", \"param2\":\"value2\"}";  // 发送的 JSON 数据

//   // 启动请求
//   http.begin(url);  // 请求的 URL

//   // 设置请求头部，告诉服务器请求体是 JSON 格式
//   http.addHeader("Content-Type", "application/json");

//   // 发送 POST 请求并附带数据
//   int httpCode = http.POST(jsonData);

//   // 检查请求结果
//   if (httpCode > 0) {
//     Serial.printf("POST request successful, code: %d\n", httpCode);
//     String payload = http.getString();  // 获取响应内容
//     Serial.println("Response: ");
//     Serial.println(payload);  // 打印响应内容
//   } else {
//     Serial.printf("POST request failed, code: %d\n", httpCode);
//   }

//   // 结束请求
//   http.end();
// }