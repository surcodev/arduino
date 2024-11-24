#include <DHT.h>

// Pines y tipo del sensor DHT
#define DHTPIN 6       // Pin donde está conectado el sensor DHT
#define DHTTYPE DHT11  // Tipo de sensor DHT (puede ser DHT11, DHT22, etc.)

float humedad;
float temperatura;
float indice;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  humedad = dht.readHumidity();
  temperatura = dht.readTemperature(); // Por defecto, la temperatura estará en Celsius.
                                       // Para Fahrenheit, coloca "true" como argumento.

  if (isnan(humedad) || isnan(temperatura)) {
    Serial.println("Error de lectura del sensor");
    return;
  }

  indice = dht.computeHeatIndex(temperatura, humedad, false); // 'false' para Celsius.

  Serial.print("Humedad: ");
  Serial.print(humedad);
  Serial.print("% Temperatura: ");
  Serial.print(temperatura);
  Serial.println("°C");
}
