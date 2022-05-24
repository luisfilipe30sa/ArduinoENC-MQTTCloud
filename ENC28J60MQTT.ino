#include <SPI.h> //INCLUSÃO DE BIBLIOTECA
#include <UIPEthernet.h> //INCLUSÃO DE BIBLIOTECA
#include <PubSubClient.h>


#define led  6   //pino de saida para acionamento da Lampada L1
#define led2 7   //pino de saida para acionamento da Lampada L1
#define led3 8   //pino de saida para acionamento da Lampada L1
#define led4 9   //pino de saida para acionamento da Lampada L1


// TODO: AskSensors MQTT user config
const char* username = "Test"; // my AskSensors username
const char* pubTopic = "L1"; // publish/username/apiKeyIn
// MQTT host config
const char* mqtt_server = "m13.cloudmqtt.com";
unsigned int mqtt_port = 14853;

EthernetClient askClient;
PubSubClient client(askClient);

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //ATRIBUIÇÃO DE ENDEREÇO MAC AO ENC28J60
byte ip[] = { 192,168,33,115 }; //COLOQUE UMA FAIXA DE IP DISPONÍVEL DO SEU ROTEADOR.
EthernetServer server(80); //PORTA EM QUE A CONEXÃO SERÁ FEITA
int SAIDA[] = {6, 7, 8, 9}; //PINOS DIGITAIS UTILIZADOS PELAS SAÍDAS A RELÉ


void setup(){
    pinMode(led,  OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(led4, OUTPUT);
Serial.begin(115200);
if (Ethernet.begin(mac) == 0) 
{
Ethernet.begin(mac, ip);
}
// give the Ethernet shield a second to initialize:
client.setServer(mqtt_server, mqtt_port);
client.setCallback(callback);
}

void loop(){
  
if (!client.connected())
        reconnect();
        client.loop();        
client.subscribe(pubTopic, 1);
if (!client.connected())
        reconnect();
}


void callback(char* topic, byte* payload, unsigned int length) 
{
//armazena msg recebida em uma sring
  payload[length] = '\0';
  String strMSG = String((char*)payload);
  
Serial.print("Message arrived [");
Serial.print(topic);
Serial.print("] ");
Serial.println();
  //aciona saída conforme msg recebida 
  if (strMSG == "1")
  {         //se msg "1"
     digitalWrite(led, HIGH);  //coloca saída em high para ligar a Lampada - > o módulo RELE usado tem acionamento invertido. Se necessário ajuste para o seu modulo
  }
  else if (strMSG == "0")
  {   //se msg "0"
     digitalWrite(led, LOW);   //coloca saída em low para desligar a Lampada - > o módulo RELE usado tem acionamento invertido. Se necessário ajuste para o seu modulo
  }
  else  if (strMSG == "3")
  {         //se msg "1"
     digitalWrite(led2, HIGH);  //coloca saída em high para ligar a Lampada - > o módulo RELE usado tem acionamento invertido. Se necessário ajuste para o seu modulo
  }
  else if (strMSG == "2")
  {   //se msg "0"
     digitalWrite(led2, LOW);   //coloca saída em low para desligar a Lampada - > o módulo RELE usado tem acionamento invertido. Se necessário ajuste para o seu modulo
  }  
  else if (strMSG == "5")
  {         //se msg "1"
     digitalWrite(led3, HIGH);  //coloca saída em high para ligar a Lampada - > o módulo RELE usado tem acionamento invertido. Se necessário ajuste para o seu modulo
  }
  else if (strMSG == "4")
  {   //se msg "0"
     digitalWrite(led3, LOW);   //coloca saída em low para desligar a Lampada - > o módulo RELE usado tem acionamento invertido. Se necessário ajuste para o seu modulo
  } 
   else if (strMSG == "7")
  {         //se msg "1"
     digitalWrite(led4, HIGH);  //coloca saída em high para ligar a Lampada - > o módulo RELE usado tem acionamento invertido. Se necessário ajuste para o seu modulo
  }
  else if (strMSG == "6")
  {   //se msg "0"
     digitalWrite(led4, LOW);   //coloca saída em low para desligar a Lampada - > o módulo RELE usado tem acionamento invertido. Se necessário ajuste para o seu modulo
  } 
}
void reconnect() 
{
// Loop until we're reconnected
while (!client.connected()) 
{
if (client.connect("ethClient", "iavlbrzx", "ANunaAHkWsYO")) 
{
Serial.println("-> MQTT client connected");
} 
}
}
