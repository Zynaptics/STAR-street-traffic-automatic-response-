# 🌟 STAR – Street Traffic Auto Response

**STAR (Street Traffic Auto Response)** is a smart street lighting system designed to optimize energy consumption and improve automation in urban environments. The system automatically turns ON street lights only when a vehicle is detected **at night**. If it's daytime or no car is present, the lights remain OFF.
This project is built using **Arduino UNO** and **ESP32** with **Wi-Fi connectivity**, **IR and LDR sensors**, and uses the **MQTT protocol** to publish real-time data to the cloud.


## 🔧 Technologies Used

| Component/Tool        | Description                                              |
|-----------------------|----------------------------------------------------------|
| Arduino UNO           | Controls IR sensor and LED using Assembly language       |
| ESP32                 | Reads LDR sensor and sends data over Wi-Fi via MQTT      |
| LDR Sensor            | Detects ambient light level to determine day/night       |
| IR Sensor             | Detects presence of a car                                |
| Arduino IDE           | Used to write C code for ESP32                           |
| Microchip Studio      | Used to write Assembly code for Arduino UNO              |
| MQTT (HiveMQ Broker)  | Public broker to publish LDR values                      |
| MQTT Explorer         | Desktop tool to visualize MQTT messages                  |



## ⚙️ Working of Components

### 🟦 Arduino UNO
- Connected to **IR sensor** and **LED**.
- Programmed in **Assembly** using **Microchip Studio**.
- If **car is detected** _and_ it's **night**, turn **light ON**.
- If it's **daytime** or **no car**, keep **light OFF**.

# 🟩 ESP32
- Connected to an **LDR sensor**.
- Reads analog light intensity values.
- Publishes LDR values to MQTT topic using **PubSubClient** library.
- Programmed using **Arduino IDE** in C.

### 🔆 LDR Sensor
- Determines whether it is day or night by sensing ambient light.
- Higher analog value = more light (day), lower = dark (night).

### 🔲 IR Sensor
- Detects the presence of a car using infrared reflection.
- Sends HIGH or LOW signal based on detection.

### ☁️ MQTT
- Broker: `broker.hivemq.com`
- Port: `1883` (No authentication required)
- Topic: `esp32/lrd`
- ESP32 publishes LDR values here.
- Use **MQTT Explorer** to monitor data in real-time.



## 📊 Truth Table

| Car Detected | Night (LDR Low) | Light Status |
|--------------|------------------|--------------|
| No           | No               | OFF          |
| No           | Yes              | OFF          |
| Yes          | No               | OFF          |
| Yes          | Yes              | ON           |


## 🧪 Sample MQTT Output

**Topic**: `esp32/lrd`  
**Values** (example):  
- `2595`  
- `2610`  
- `2700`

> The value increases with more ambient light and decreases as it gets darker.



## 🛠️ Setup Instructions

### Step 1: Arduino UNO (IR + LED)
- Connect IR sensor to digital input pin.
- Connect LED to output pin.
- Open `arduino_uno.asm` in Microchip Studio.
- Burn code to Arduino UNO via USB.

### Step 2: ESP32 (LDR + MQTT)
- Connect LDR sensor to analog pin (GPIO 34).
- Open `esp32_code.ino` in Arduino IDE.
- Install **PubSubClient** library.
- Set your Wi-Fi credentials.
- Upload the code to ESP32.

### Step 3: MQTT Explorer
- Download [MQTT Explorer](https://mqtt-explorer.com/).
- Connect to broker: `broker.hivemq.com`, port `1883`.
- Subscribe to topic: `esp32/lrd`
- Monitor LDR readings live.



## 🚀 Future Work

- Add Firebase/ThingSpeak for historical data storage
- Build Android app for live monitoring
- Use PIR instead of IR for accurate vehicle detection
- Use solar-powered energy-efficient lights
- Add voice or SMS alert system



## 📚 References

- [ESP32 Documentation](https://docs.espressif.com/)
- [Arduino UNO Datasheet](https://store.arduino.cc/products/arduino-uno-rev3)
- [Microchip Studio](https://www.microchip.com/en-us/tools-resources/develop/microchip-studio)
- [MQTT Explorer](https://mqtt-explorer.com/)
- [HiveMQ Public Broker](https://www.hivemq.com/public-mqtt-broker/)
- [PubSubClient Library](https://github.com/knolleary/pubsubclient)


> ⭐ If you found this project helpful, give it a star.

