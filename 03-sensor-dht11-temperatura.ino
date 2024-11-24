#include <DHT.h>

#define DHTTYPE DHT11
#define DHTPIN 9

DHT dht(DHTPIN, DHTTYPE);

void setup(){
  Serial.begin(9600);
  dht.begin();
}

void loop(){
  delay(2000);
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if(isnan(humidity) || isnan(temperature)){
    Serial.print("Error en el sensor");
    return;
  }
  Serial.print("Humedad: ");
  Serial.print(humidity);
  Serial.print("% Temperatura: ");
  Serial.print(temperature);
  Serial.println("°C");
  delay(1000);
}
