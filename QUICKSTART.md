# Quick Start Guide

## Prerequisites

1. **Hardware**:
   - ESP8266 development board (NodeMCU or Wemos D1 Mini)
   - AM2302 DHT22 sensor
   - SCD40 CO2 sensor
   - 3x WS2812B 8x8 LED matrices
   - USB-C cable and power supply (5V, 2A minimum)
   - Jumper wires and breadboard
   - 10kΩ resistor

2. **Software**:
   - [PlatformIO](https://platformio.org/install) or [Arduino IDE](https://www.arduino.cc/en/software)
   - MQTT Broker (e.g., Mosquitto)
   - Home Assistant (optional, for integration)

## Installation Steps

### Step 1: Clone Repository
```bash
git clone https://github.com/mikoa001/smart-air-sensor.git
cd smart-air-sensor
```

### Step 2: Assemble Hardware
Follow the detailed instructions in [WIRING.md](WIRING.md) to connect all components.

### Step 3: Configure Software
```bash
# Copy the example configuration
cp src/config.h.example src/config.h

# Edit configuration with your credentials
nano src/config.h  # or use your preferred editor
```

Update the following values in `src/config.h`:
- `WIFI_SSID` - Your WiFi network name
- `WIFI_PASSWORD` - Your WiFi password
- `MQTT_SERVER` - Your MQTT broker IP address
- `MQTT_USER` - Your MQTT username
- `MQTT_PASSWORD` - Your MQTT password

### Step 4: Build and Upload

#### Using PlatformIO (Recommended)
```bash
# Install PlatformIO if not already installed
pip install platformio

# Build the project
pio run

# Upload to ESP8266 (connect via USB first)
pio run --target upload

# Monitor serial output
pio device monitor
```

#### Using Arduino IDE
1. Open Arduino IDE
2. Install ESP8266 board support:
   - File → Preferences
   - Additional Board Manager URLs: `http://arduino.esp8266.com/stable/package_esp8266com_index.json`
   - Tools → Board → Board Manager → Search "ESP8266" → Install
3. Install required libraries (see README.md)
4. Rename `src/main.cpp` to `smart-air-sensor.ino`
5. Open the file in Arduino IDE
6. Select your board: Tools → Board → ESP8266 Boards → NodeMCU 1.0 (or your board)
7. Select your port: Tools → Port → (your USB port)
8. Click Upload

### Step 5: Configure Home Assistant (Optional)

1. Copy the MQTT sensor configuration from `homeassistant_config.yaml`
2. Add to your Home Assistant `configuration.yaml`
3. Restart Home Assistant
4. Add dashboard cards as shown in the configuration file

## First Run

1. **Power on the device** via USB-C
2. **Check serial monitor** (115200 baud) for connection status
3. **Verify WiFi connection** - Should see IP address in serial output
4. **Verify MQTT connection** - Should see "connected" message
5. **Check sensors** - Should see temperature, humidity, and CO2 readings
6. **Observe LED display** - Should cycle through temp, humidity, and CO2

## Expected Serial Output

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

## LED Display Behavior

The display cycles every 2 seconds:
1. **Temperature** in orange
2. **Humidity** in blue
3. **CO2 level** in green (good), yellow (warning), or red (poor)

## Troubleshooting

See [TROUBLESHOOTING.md](TROUBLESHOOTING.md) for common issues and solutions.

## Next Steps

- Mount in enclosure
- Position for optimal air circulation
- Create Home Assistant automations
- Set up alerts for poor air quality
- Monitor historical data

## Support

For issues or questions:
1. Check [TROUBLESHOOTING.md](TROUBLESHOOTING.md)
2. Review [README.md](README.md) for detailed documentation
3. Open an issue on GitHub
