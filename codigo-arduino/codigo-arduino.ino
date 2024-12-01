#include <Adafruit_NeoPixel.h>

#define PIN 4
#define NUMPIXELS 16

Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

bool isOn = true; // Estado actual de las luces
String lastCommand = "COLOR:255,255,255"; // Último comando activo, por defecto blanco
bool isRainbowActive = false; // Indica si el efecto Rainbow está activo

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Apaga las luces inicialmente
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    if (input.startsWith("COLOR:")) {
      isOn = true; // Encender si se envía un nuevo color
      isRainbowActive = false; // Detener Rainbow si se selecciona un color
      lastCommand = input; // Guardar el último comando
      int r = input.substring(6, 9).toInt();
      int g = input.substring(10, 13).toInt();
      int b = input.substring(14, 17).toInt();
      setColor(r, g, b);
    } else if (input == "RAINBOW") {
      isOn = true; // Encender si se activa el efecto Rainbow
      isRainbowActive = true; // Activar Rainbow
      lastCommand = input; // Guardar el último comando
    } else if (input == "TOGGLE") {
      toggleLights(); // Alternar luces
    }
  }

  if (isRainbowActive && isOn) {
    rainbowEffect(10); // Mantener el efecto Rainbow activo
  }

  if (!isOn) {
    strip.clear();
    strip.show();
  }
}

void setColor(int r, int g, int b) {
  isRainbowActive = false; // Detener Rainbow si se selecciona un color
  for (int i = 0; i < NUMPIXELS; i++) {
    strip.setPixelColor(i, strip.Color(r, g, b));
  }
  strip.show();
}

void toggleLights() {
  isOn = !isOn;
  if (isOn) {
    // Restaurar el último comando activo
    if (lastCommand.startsWith("COLOR:")) {
      int r = lastCommand.substring(6, 9).toInt();
      int g = lastCommand.substring(10, 13).toInt();
      int b = lastCommand.substring(14, 17).toInt();
      setColor(r, g, b);
    } else if (lastCommand == "RAINBOW") {
      isRainbowActive = true; // Reactivar Rainbow
    }
  } else {
    strip.clear();
    strip.show();
  }
}

void rainbowEffect(int delayMs) {
  static long firstPixelHue = 0; // Variable persistente para el arcoíris
  for (int i = 0; i < strip.numPixels(); i++) {
    int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
    strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
  }
  strip.show();
  delay(delayMs);
  firstPixelHue += 256; // Avanza el arcoíris
  if (firstPixelHue >= 65536) {
    firstPixelHue -= 65536; // Reinicia el ciclo del arcoíris
  }
}
