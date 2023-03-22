#include <ESP8266WiFi.h>                                              // Подключение библиотеки для платы ESP 8266
#include <WiFiClientSecure.h>                                         // Подключение библиотеки для связи по Wi-Fi
#include <UniversalTelegramBot.h>                                     // Подключение библиотеки для Telegram бота
#include <ArduinoJson.h>                                              // Подключение общей библиотеки

const char* ssid = "TP-Link_DCE2";                                    // Название Wi-Fi сети
const char* password = "45999765";                                    // Пароль Wi-Fi сети

#define BOTtoken "5815968028:AAHWJsje93mm82uz0oCOIsXKxHyRRRzTAxk"     // Токен моего бота Telegram
#define CHAT_ID "5185783673"                                          // Мой ID
WiFiClientSecure client;                                              // Создаём объект клиента класса WiFiClientSecure
UniversalTelegramBot bot(BOTtoken, client);                           // Инициализация Telegram бота

void setup() {                                                        // Основной цикл
  Serial.begin(9600);                                                 // Инициализация передачи данных в монитор последовательного порта
  client.setInsecure();
  pinMode(A0, INPUT_PULLUP);                                          // Внутренняя подтяжка сенсора INPUT_PULLUP

  Serial.print("Соединение с Wifi: ");                                // Вывод фразы в монитор порта
  Serial.println(ssid);                                               // Вывод названия сети в монитор порта
  WiFi.mode(WIFI_STA);                                                // Установка нужного режима соединения
  WiFi.begin(ssid, password);                                         // Подключение к сети Wi-Fi

  while (WiFi.status() != WL_CONNECTED) {                             // Пока соединение установлено
    Serial.print(".");                                                // Вывод времени в монитор порта
    delay(500);                                                       // Пауза 0,5 секунды
  }

  Serial.println("");                                                 // Вывод пустой строки в монитор порта
  Serial.println("WiFi соединение установлено");                      // Вывод фразы в монитор порта
  Serial.print("IP адрес: ");                                         // Вывод фразы в монитор порта
  Serial.println(WiFi.localIP());                                     // Вывод IP Wi-Fi сети в монитор порта
  bot.sendMessage(CHAT_ID, "Бот уровня воды стартовал", "");          // Отправка сообщения о начале работы в Telegram
}

void loop() {                                                         // Повторяющийся цикл
  int sensorValue = analogRead(A0);                                   // Получение значения уровня жидкости с датчика
  Serial.println(sensorValue);                                        // Вывод фразы в монитор порта
  if (sensorValue < 250) {                                            // Если значение уровня жидкости меньше 250
    bot.sendMessage(CHAT_ID, "Низкий уровень воды!", "");             // Отправка сообщения о низком уровне воды в Telegram
    Serial.println("Низкий уровень воды!");                           // Вывод фразы в монитор порта
  }
  delay(1800000);                                                     // Пауза 30 минут
}
