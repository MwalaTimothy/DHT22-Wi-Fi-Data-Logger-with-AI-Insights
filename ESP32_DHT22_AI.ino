#include <DHT.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define DHTPIN 6          // Pin where the DHT22 is connected
#define DHTTYPE DHT22     // DHT 22 (AM2302)
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "YOUR SSID";
const char* password = "YOUR SSID PASSWORD";

// Arrays to store the last 10 readings
float temperatureReadings[10];
float humidityReadings[10];
int readingIndex = 0;

void setup() {
  Serial.begin(115200);
  dht.begin();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  // Read data from DHT22
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Check if any reads failed and exit early (to try again).
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Store the readings in the arrays
  temperatureReadings[readingIndex] = temperature;
  humidityReadings[readingIndex] = humidity;
  readingIndex++;

  // After 10 readings, calculate statistics and heat index
  if (readingIndex >= 10) {
    calculateAndSendStatistics();
    readingIndex = 0; // Reset the index
  }

  // Delay before the next reading
  delay(5000); // Adjust the delay as needed
}

void calculateAndSendStatistics() {
  // Calculate average, min, max, and mode for temperature and humidity
  float tempSum = 0, humiditySum = 0;
  float tempMin = temperatureReadings[0], tempMax = temperatureReadings[0];
  float humidityMin = humidityReadings[0], humidityMax = humidityReadings[0];

  for (int i = 0; i < 10; i++) {
    tempSum += temperatureReadings[i];
    humiditySum += humidityReadings[i];

    if (temperatureReadings[i] < tempMin) tempMin = temperatureReadings[i];
    if (temperatureReadings[i] > tempMax) tempMax = temperatureReadings[i];
    if (humidityReadings[i] < humidityMin) humidityMin = humidityReadings[i];
    if (humidityReadings[i] > humidityMax) humidityMax = humidityReadings[i];
  }

  float tempAvg = tempSum / 10;
  float humidityAvg = humiditySum / 10;

  // Calculate heat index
  float heatIndex = calculateHeatIndex(tempAvg, humidityAvg);

  // Create a JSON document to store the statistical data
  StaticJsonDocument<500> doc;
  doc["temperature_avg"] = tempAvg;
  doc["temperature_min"] = tempMin;
  doc["temperature_max"] = tempMax;
  doc["humidity_avg"] = humidityAvg;
  doc["humidity_min"] = humidityMin;
  doc["humidity_max"] = humidityMax;
  doc["heat_index"] = heatIndex;

  // Convert the JSON document to a string
  String payload;
  serializeJson(doc, payload);

  // Create the prompt for the AI service
  String prompt = "Analyze the following statistical data: \n";
  prompt += "Temperature (Avg/Min/Max): " + String(tempAvg, 2) + "°C / " + String(tempMin, 2) + "°C / " + String(tempMax, 2) + "°C\n";
  prompt += "Humidity (Avg/Min/Max): " + String(humidityAvg, 2) + "% / " + String(humidityMin, 2) + "% / " + String(humidityMax, 2) + "%\n";
  prompt += "Heat Index: " + String(heatIndex, 2) + "°C\n";
  prompt += "Provide insights into trends, anomalies, and any recommendations.";

  // Send the prompt to the AI service
  sendToAI(prompt);
}

float calculateHeatIndex(float temperature, float humidity) {
  // Heat index formula (simplified)
  float heatIndex = 0.5 * (temperature + 61.0 + ((temperature - 68.0) * 1.2) + (humidity * 0.094));
  return heatIndex;
}

void sendToAI(String prompt) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("https://api.openai.com/v1/chat/completions");
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization", "Bearer Your API kEY);  // Replace with your API key
    // Create JSON payload for chat completions endpoint
    StaticJsonDocument<400> doc;
    doc["model"] = "gpt-3.5-turbo";

    // Add the messages array
    JsonArray messages = doc.createNestedArray("messages");

    // System message
    JsonObject systemMessage = messages.createNestedObject();
    systemMessage["role"] = "system";
    systemMessage["content"] = "You are a helpful assistant.";

    // User prompt
    JsonObject userMessage = messages.createNestedObject();
    userMessage["role"] = "user";
    userMessage["content"] = prompt;

    String requestBody;
    serializeJson(doc, requestBody);

    // Debug the request body
    Serial.println("Request Body: " + requestBody);

    int httpResponseCode = http.POST(requestBody);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Response: " + response);
    } else {
      Serial.println("Error on sending POST: " + String(httpResponseCode));
    }

    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }
}
