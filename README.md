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
- **([Carenuity ESP32_C3-Mini](https://www.chipglobe.shop/en))**
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
 Request Body: {"model":"gpt-3.5-turbo","messages":[{"role":"system","content":"You are a helpful assistant."},{"role":"user","content":"Analyze the following statistical data: \n
Temperature (Avg/Min/Max): 32.97°C / 32.90°C / 33.00°C\nHumidity (Avg/Min/Max): 99.90% / 99.90% / 99.90%\nHeat Index: 30.66°C\n
Provide insights into trends, anomalies, and any recommendations."}]}
00:00:23.550 -> Response: {
  "role": "assistant",
23:57:36.627 ->         "content": "Based on the provided statistical data:\n\n1.
Temperature: The average temperature is 31.92°C, with a narrow range between the minimum (31.60°C) and maximum (32.20°C) temperatures. This suggests a relatively stable temperature range.\n\n2.
Humidity: The humidity levels are very high, with an average, minimum, and maximum of 99.90%. This indicates extremely humid conditions.\n\n3.
Heat Index: The heat index, which takes into account both temperature and humidity, is slightly lower at 29.51°C compared to the actual temperature. This suggests that despite the high humidity, the perceived temperature may be slightly lower due to the influence of relative humidity.\n\nInsights:\n- The high humidity levels coupled with relatively stable temperatures indicate a humid and warm climate.\n-
The heat index being lower than the actual temperature implies that the perceived temperature may not feel as hot due to the high humidity levels.\n\nRecommendations:\n- Stay hydrated: High humidity can make temperatures feel hotter, so it's essential to stay hydrated.\n- Use fans or air conditioning: Given the high humidity levels, using fans or air conditioning can help improve comfort levels.\n- Monitor for heat-related illnesses: Due to the high humidity, there is an increased risk of heat-related illnesses, so it's important to be aware of symptoms and take necessary precautions.\n- Consider wearing lightweight, breathable clothing: In such humid conditions, wearing light and breathable fabrics can help in staying comfortable.\n\n
Overall, the data suggests a humid and warm environment with high humidity levels. By following the recommendations mentioned above, individuals can better cope with these conditions.",
23:57:36.673 ->         "
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

