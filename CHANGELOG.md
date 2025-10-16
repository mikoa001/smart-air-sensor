# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.0.0] - 2025-10-16

### Added
- Initial release of Smart Air Quality Sensor
- ESP8266-based microcontroller support
- DHT22 (AM2302) temperature and humidity sensor integration
- SCD40 CO2 sensor support with I2C communication
- 3x 8x8 RGB LED matrix display (WS2812B/NeoPixel)
- WiFi connectivity for ESP8266
- MQTT client for Home Assistant integration
- Automatic sensor reading every 30 seconds
- LED display rotation (temperature, humidity, CO2)
- Color-coded CO2 level display (green/yellow/red)
- USB-C power support (5V)
- Configuration file template (config.h.example)
- Comprehensive documentation:
  - README.md with full project overview
  - HARDWARE.md for assembly instructions
  - WIRING.md with detailed pin connections and circuit diagrams
  - QUICKSTART.md for rapid setup
  - TROUBLESHOOTING.md for common issues
  - BOM.md with complete parts list and pricing
- Home Assistant configuration examples
- PlatformIO configuration for easy building
- Library dependencies auto-installation

### Features
- Real-time air quality monitoring
- MQTT publishing to multiple topics
- Automatic WiFi reconnection
- Automatic MQTT reconnection
- Serial debugging output
- Configurable update intervals
- Adjustable LED brightness
- Three measurement display modes

### Documentation
- Complete hardware assembly guide
- Detailed wiring diagrams
- Pin reference tables
- Home Assistant integration guide
- MQTT configuration examples
- Troubleshooting guide with solutions
- Quick start guide
- Bill of materials with pricing

### Libraries Used
- DHT sensor library v1.4.4 (Adafruit)
- Adafruit Unified Sensor v1.1.14
- SparkFun SCD4x Arduino Library v1.1.2
- Adafruit NeoPixel v1.12.0
- Adafruit NeoMatrix v1.3.2
- Adafruit GFX Library v1.11.9
- PubSubClient v2.8 (MQTT)
- ESP8266 Arduino Core

## [Unreleased]

### Planned Features
- Web interface for configuration
- Over-the-air (OTA) updates
- Historical data logging
- Multi-sensor support
- Customizable display modes
- Temperature unit selection (C/F)
- Advanced calibration options
- Battery backup support
- Deep sleep mode for power saving

### Under Consideration
- E-ink display option
- Local data storage (SD card)
- Additional gas sensors (VOC, PM2.5)
- BLE support (ESP32 version)
- REST API endpoint
- Touch controls
- Sound alerts
- Alternative MQTT broker support

---

## Version History

- **1.0.0** (2025-10-16): Initial release with full functionality
