#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2
#define LM35_PIN A0

// Configurar la comunicación OneWire
OneWire oneWire(ONE_WIRE_BUS);

// Crear un objeto DallasTemperature
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  sensors.begin();    // Iniciar el sensor 
  sensors.setResolution(12); // Configurar resolución del DS18B20 (750 ms) 
}

void loop() {

  unsigned long startTime = millis();
  unsigned long duration = 750; // 750 ms para igualar el tiempo del DS18B20
  int count = 0;
  float tempAnalogSum = 0;

  while (millis() - startTime < duration) {
    float tempAnalog = analogRead(LM35_PIN) * (1.0 / 1023.0) * 100.0; // Conversión a °C
    tempAnalogSum += tempAnalog;
    count++;
  }
  float temperaturaAnalog = tempAnalogSum / count;

  sensors.requestTemperatures(); // Solicitar datos al sensor
  // Leer y mostrar la temperatura en Celsius
  float temperaturaDig = sensors.getTempCByIndex(0);

  Serial.print(temperaturaAnalog);
  Serial.print(",");  
  Serial.print(temperaturaDig);
  Serial.println();
}