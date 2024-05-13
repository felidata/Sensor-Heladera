
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL2NESuNIUT"
#define BLYNK_TEMPLATE_NAME "Temperature and Humidity Sensor"
#define BLYNK_AUTH_TOKEN "fcL9hLLEruvFR7jbwlCb6-Wqvndr9QKc"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT.h>

#define DHTPIN 4         // Pin de conexión del sensor DHT
#define DHTTYPE DHT22    // Tipo de sensor DHT (DHT22)
#define ONE_WIRE_BUS 5       // Pin de conexión del bus OneWire para el sensor DS18B20

char auth[] = BLYNK_AUTH_TOKEN;  // Reemplaza con el token de autorización de tu proyecto en Blynk
char ssid[] = "Nestorcasa";               // Nombre de tu red WiFi
char pass[] = "kx4edfegqc";        // Contraseña de tu red WiFi

DHT dht(DHTPIN, DHTTYPE);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  dht.begin();
  sensors.begin();
}

void loop() {
  /*Blynk.run();
  */
  delay(2000);  // Espera 2 segundos entre lecturas

  // Lectura de la temperatura en grados Celsius
  float tempC_dht = dht.readTemperature();
  // Lectura de la humedad relativa
  float humedad_dht = dht.readHumidity();

  // Lectura de la temperatura con el sensor DS18B20
  sensors.requestTemperatures();
  float tempC_ds18b20 = sensors.getTempCByIndex(0);

  // Comprueba si las lecturas fueron exitosas
  if (isnan(tempC_dht) || isnan(humedad_dht)/* || tempC_ds18b20 == DEVICE_DISCONNECTED_C*/) {
    Serial.println("Error al leer los sensores");
    return;
  }
  
  // Envía los datos a la aplicación Blynk
  Blynk.virtualWrite(V0, tempC_dht);     // Virtual Pin V0 para temperatura (DHT22)
  Blynk.virtualWrite(V1, humedad_dht);   // Virtual Pin V1 para humedad (DHT22)
  Blynk.virtualWrite(V2, tempC_ds18b20);   // Virtual Pin V7 para temperatura del DS18B20

  Serial.print("Temperatura: ");
  Serial.print(tempC_dht);
  Serial.print(" °C\t");
  Serial.print("Humedad: ");
  Serial.print(humedad_dht);
  Serial.println(" %");

  Serial.print("Temperatura (DS18B20): ");
  Serial.print(tempC_ds18b20);
  Serial.println(" °C");
}
