# DHT22 Wi-Fi Data Logger with AI Insights

## Overview
This project is an ESP32-C3-Mini-based system that reads temperature and humidity data from a DHT22 sensor, calculates statistical insights, and sends the data to an AI service for further analysis. The system connects to Wi-Fi, logs the readings over time, and uses OpenAI's API to generate insights based on temperature and humidity trends.

## Features
- Reads temperature and humidity from a **DHT22 sensor**.
- Stores the last **10 readings** for statistical analysis.
- Calculates **average, minimum, maximum**, and **heat index**.
- Sends the data to an **AI service** for insights and recommendations.
- Uses **Wi-Fi connectivity** to transmit data.
- Outputs results via **serial monitor**.

## Hardware Requirements
- **ESP32 or Arduino-compatible board with Wi-Fi**
- **DHT22 (AM2302) Temperature & Humidity Sensor**
- **Jumper wires**
-  **Breadboard**
-  **Type C data cable**

## Software Requirements
- **Arduino IDE** (Latest Version)
- **DHT Library** ([Adafruit DHT Library](https://github.com/adafruit/DHT-sensor-library))
- **ArduinoJson Library**
- **WiFi Library**
- **HTTPClient Library**

## Circuit Diagram
```
DHT22        ESP32
VCC  ---->   3.3V
GND  ---->   GND
DATA ---->   GPIO 6 (DHTPIN)
```

## Installation & Setup
### 1. Install Arduino Libraries
Ensure you have the following libraries installed in the Arduino IDE:
- **DHT Sensor Library**
- **ArduinoJson**
- **WiFi Library**
- **HTTPClient**

### 2. Clone the Repository
```sh
$ git clone https://github.com/your-repo/dht22-wifi-ai
$ cd dht22-wifi-ai
```

### 3. Configure Wi-Fi Credentials
Modify the following lines in the code with your Wi-Fi SSID and Password:
```cpp
const char* ssid = "Your_WiFi_Name";
const char* password = "Your_WiFi_Password";
```

### 4. Upload the Code
- Connect your ESP32 board to the computer.
- Open the Arduino IDE.
- Select the correct **Board** and **COM Port**.
- Upload the sketch.

## Code Breakdown
### 1. Read Temperature & Humidity
```cpp
float temperature = dht.readTemperature();
float humidity = dht.readHumidity();
```
### 2. Store Readings and Compute Statistics
- Stores last **10 readings**
- Computes **average, min, max, and heat index**
```cpp
float tempAvg = tempSum / 10;
float heatIndex = calculateHeatIndex(tempAvg, humidityAvg);
```
### 3. Send Data to AI Service
- Creates a JSON payload
- Sends request via HTTP POST
```cpp
http.begin("https://api.openai.com/v1/chat/completions");
http.addHeader("Authorization", "Bearer YOUR_API_KEY");
http.POST(requestBody);
```
> ⚠ **Note**: Replace `YOUR_API_KEY` with your OpenAI API key.

## Expected Output
```
Connecting to WiFi...
Connected to WiFi
Temperature: 24.5°C, Humidity: 60%
Average Temp: 24.2°C, Min: 23.5°C, Max: 25.0°C
Heat Index: 25.3°C
Response from AI: "The temperature trend is stable. Consider checking for sudden drops."
```

## Potential Improvements
- **Secure API keys** using **environment variables**.
- **Send data to a cloud database** for historical tracking.
- **Add MQTT integration** for real-time updates.
- **Use a display** (OLED/LED) for local feedback.


## Contributing
Contributions are welcome! Fork the repo, make changes, and submit a PR.

## Contact
For any questions, contact **Timothy Mwala** at [mwalatimo@gmail.com](mailto:mwalatimo.com).

---
**Happy Coding! 🚀**

