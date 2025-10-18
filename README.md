# Smart Air Quality Sensor

An ESP8266-based smart air quality monitoring system that measures temperature, humidity, and CO2 levels, displays the data on RGB LED matrices, and publishes to Home Assistant via MQTT.

## Features

- **Temperature & Humidity Monitoring**: Using AM2302 DHT22 sensor
- **CO2 Measurement**: Using Sensirion SCD40 sensor (ppm)
- **Visual Display**: 3x 8x8 RGB LED matrices (NeoPixel) for real-time data visualization
- **Home Assistant Integration**: MQTT protocol for seamless integration
- **Low Power**: USB-C powered (5V)
- **WiFi Connectivity**: ESP8266 microcontroller

## Hardware Requirements

### Components
- **Microcontroller**: ESP8266 (NodeMCU, Wemos D1 Mini, or similar Wi-Fi capable MCUs)
- **Temperature/Humidity Sensor**: AM2302 DHT22
- **CO2 Sensor**: Sensirion SCD40
- **Display**: 4 pcs WS2812B 8x8 RGB LED matrices
- **Power**: USB-C connector with 5V power supply

### Pin Connections

#### ESP8266 Pin Assignments
```
DHT22 Data Pin     -> GPIO2  (D4 on NodeMCU)
SCD40 SDA          -> GPIO4  (D2 on NodeMCU)
SCD40 SCL          -> GPIO5  (D1 on NodeMCU)
LED Matrix Data    -> GPIO14 (D5 on NodeMCU)
```

#### DHT22 Wiring
```
VCC  -> 3.3V or 5V voltage source
GND  -> GND
DATA -> GPIO2 (with 10kΩ pull-up resistor to VCC)
```

#### SCD40 Wiring
```
VDD  -> 3.3V voltage source
GND  -> GND
SDA  -> GPIO4
SCL  -> GPIO5
```

#### LED Matrix Wiring
```
VCC  -> 5V
GND  -> GND
DIN  -> GPIO14
```

***Note**: Chain the three 8x8 matrices together by connecting DOUT of one matrix to DIN of the next.*

## Software Requirements

- [PlatformIO](https://platformio.org/) or [Arduino IDE](https://www.arduino.cc/en/software)

### Required Libraries
- DHT sensor library (Adafruit)
- Adafruit Unified Sensor
- SparkFun SCD4x Arduino Library
- Adafruit NeoPixel
- Adafruit NeoMatrix
- Adafruit GFX Library
- PubSubClient (MQTT)

## Installation

### Using PlatformIO

1. **Clone the repository**:
   ```bash
   git clone https://github.com/mikoa001/smart-air-sensor.git
   cd smart-air-sensor
   ```

2. **Configure your settings**:
   ```bash
   cp src/config.h.example src/config.h
   ```

3. **Edit `src/config.h`** with your WiFi and MQTT credentials:
   ```cpp
   #define WIFI_SSID "your_wifi_ssid"
   #define WIFI_PASSWORD "your_wifi_password"
   #define MQTT_SERVER "192.168.1.100"
   #define MQTT_USER "mqtt_user"
   #define MQTT_PASSWORD "mqtt_password"
   ```

4. **Build and upload**:
   ```bash
   pio run --target upload
   ```

5. **Monitor serial output**:
   ```bash
   pio device monitor
   ```

### Using Arduino IDE

1. **Install ESP8266 board support**:
   - File → Preferences → Additional Board Manager URLs
   - Add: `http://arduino.esp8266.com/stable/package_esp8266com_index.json`
   - Tools → Board → Board Manager → Search "ESP8266 Boards" and install

2. **Install required libraries**:
   - Sketch → Include Library → Manage Libraries
   - Install all libraries listed in the Software Requirements section

3. **Open the project**:
   - Rename `src/main.cpp` to `smart-air-sensor.ino`
   - Open in Arduino IDE

4. **Configure settings** as described above

5. **Select your board**:
   - Tools → Board → ESP8266 Boards → Generic ESP8266 Module

6. **Upload the sketch**

## Configuration

### MQTT Topics

The sensor publishes to the following MQTT topics (configurable in `config.h`):

- `home/sensor/temperature` - Temperature in Celsius
- `home/sensor/humidity` - Relative humidity in percentage
- `home/sensor/co2` - CO2 concentration in ppm
- `home/sensor/status` - Sensor online status

### Update Intervals

Default intervals (configurable in `config.h`):
- Sensor reading & MQTT publish: 30 seconds
- Display rotation: 2 seconds (cycles through temp, humidity, CO2)

### LED Matrix Display

The display cycles through three modes:
1. **Temperature**: Orange color
2. **Humidity**: Blue color
3. **CO2 Level**: 
   - Green: < 1000 ppm (Good)
   - Yellow: 1000-2000 ppm (Warning)
   - Red: > 2000 ppm (Poor)

## Home Assistant Integration

Add the following to your Home Assistant `configuration.yaml`:

```yaml
mqtt:
  sensor:
    - name: "Air Quality Temperature"
      state_topic: "home/sensor/temperature"
      unit_of_measurement: "°C"
      device_class: temperature
      
    - name: "Air Quality Humidity"
      state_topic: "home/sensor/humidity"
      unit_of_measurement: "%"
      device_class: humidity
      
    - name: "Air Quality CO2"
      state_topic: "home/sensor/co2"
      unit_of_measurement: "ppm"
      icon: mdi:molecule-co2
```

Restart Home Assistant after adding the configuration.

## Serial Monitor Output

Example output:
```
Smart Air Quality Sensor Starting...
LED Matrix initialized
DHT22 initialized
I2C initialized
SCD40 initialized
Connecting to WiFi...
WiFi connected
IP address: 192.168.1.50
Attempting MQTT connection...connected
Temperature: 22.5°C, Humidity: 45.2%
CO2: 678 ppm
Published temperature: 22.5
Published humidity: 45.2
Published CO2: 678
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request and I will reveiw it within 1-2 weeks.
