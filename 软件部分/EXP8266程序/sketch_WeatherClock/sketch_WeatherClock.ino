#include <ESP8266WiFi.h>        // 本程序使用 ESP8266WiFi库
#include <ESP8266WiFiMulti.h>   // 本程序使用ESP8266WiFiMulti库

#define MAX_SRV_CLIENTS 1  //做多多少个客户端可以连接
#define Port 8080

ESP8266WiFiMulti wifiMulti;  
WiFiServer server(Port);    //创建server 端口号是8080
WiFiClient serverClients[MAX_SRV_CLIENTS];   //定义最多多少个client可以连接本server(一般不要超过4个)
 
uint8_t Connect_Count=0;
void setup() 
{
  Serial.begin(115200);                   // 启动串口通讯
  pinMode(LED_BUILTIN, OUTPUT);           //设置内置LED引脚为输出模式以便控制LED
  wifiMulti.addAP("LC", "12345654321");   // 这三条语句通过调用函数addAP来记录3个不同的WiFi网络信息。
  //wifiMulti.addAP("WL", "19781021");    // 这3个WiFi网络名称分别是taichi-maker, taichi-maker2, taichi-maker3。
  //wifiMulti.addAP("XH030608", "18871080299"); 

  WiFi.mode(WIFI_STA);

  //Serial.println("\nConnecting ...");         // 通过串口监视器输出信息告知用户NodeMCU正在尝试连接WiFi                            
  while (wifiMulti.run() != WL_CONNECTED) 
  { 
    delay(1000);         
    //Serial.print('.');                       
  }  
  /*                                         // 一旦连接WiFI成功，wifiMulti.run()将会返回“WL_CONNECTED”。
  Serial.print("\nConnected to ");            // NodeMCU将通过串口监视器输出。
  Serial.println(WiFi.SSID());                // 连接的WiFI名称
  Serial.print("IP address:");                // 以及
  Serial.println(WiFi.localIP());             // NodeMCU的IP地址*/
  Serial.write('N');
  Serial.print(WiFi.SSID());
  Serial.write(0XA5);
  Serial.write('I');
  Serial.print(WiFi.localIP());  //启动server
  Serial.write(0XA5);
  server.begin();
  server.setNoDelay(true);//关闭小包合并包功能，不会延时发送数据
 // WifiHasConnected=1;
}
 
uint8_t Serial_DataGet,ConnectData;
uint8_t WifiHasConnected=0; //Mode: 0默认模式 1天气时钟信息更新 2图片信息传输
uint8_t i;
//'0'错误信号 '1'连接成功 '2'天气信息传输标志 '3'图片信息传输标志
void WIFIConnectState();
void Client_STA();
void Client_DataTransform();
void WIFIdataGet();
void loop(void)
{
  WIFIConnectState();
  Mode_Switch();              //接受串口数据切换模式
  Client_STA();               //检测是否有设备连入
  Client_DataTransform();     //将TCP传入数据通过串口传出
}

void WIFIConnectState()
{
  if(WiFi.status()!=WL_CONNECTED)
  {
    Serial.write('N');
    Serial.write("None");
    Serial.write(0XA5);
    Serial.write('I');
    Serial.write("None");  //启动server
    Serial.write(0XA5);
    server.stop();
    while (wifiMulti.run() != WL_CONNECTED) 
      delay(1000);         
    Serial.write('N');
    Serial.print(WiFi.SSID());
    Serial.write(0XA5);
    Serial.write('I');
    Serial.print(WiFi.localIP());  //启动server
    Serial.write(0XA5);
    server.begin();
    server.setNoDelay(true);//关闭小包合并包功能，不会延时发送数据
  }

}

uint8_t Mode=0;
void Mode_Switch()
{
  if((!Mode)&&(Serial.available()))
  {
    Serial_DataGet=Serial.read();
    switch(Serial_DataGet)
    {
      case '1':
        Mode=1;
        break;
      case '2':
        Mode=2;
        break;    
    }
  }
  else if(Mode)
  {
    digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));// 改变LED的点亮或者熄灭状态
    Mode=0;
  }
}
void Client_STA()
{
  if (server.hasClient()) 
  {  //判断是否有新的client请求进来
    for (i = 0; i < MAX_SRV_CLIENTS; i++) 
    {
      //释放旧无效或者断开的client
      if (!serverClients[i] || !serverClients[i].connected()) 
      {
        if (!serverClients[i]) 
        {
          //serverClients[i]    判断指定序号的客户端是否有效
          serverClients[i].stop();  //停止指定客户端的连接
        }
        serverClients[i] = server.available();//分配最新的client
        //Serial.print("1个新的客户端: "); 
        break; //跳出一层for循环
      }
    }
    //当达到最大连接数 无法释放无效的client，需要拒绝连接
    if (i == MAX_SRV_CLIENTS) 
    {
      WiFiClient client = server.available();
      client.stop();
      //Serial.println("连接被拒绝 ");
    }
  }
}

void Client_DataTransform()
{
  for (i = 0; i < MAX_SRV_CLIENTS; i++) 
  {
    if (serverClients[i] && serverClients[i].connected()) 
    {
      if (serverClients[i].available()) 
      {
        //serverClients[i].available()   判断指定客户端是否有可读数据
        while (serverClients[i].available())  
        Serial.write(serverClients[i].read());
      }
    }
  }
}