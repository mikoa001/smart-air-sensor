# PlatformIO Setup Guide

This guide helps you set up PlatformIO for building and uploading the Smart Air Quality Sensor firmware.

## What is PlatformIO?

PlatformIO is a cross-platform build system and library manager for embedded development. It's easier to use than Arduino IDE and handles dependencies automatically.

## Installation

### Method 1: Using pip (Recommended)

```bash
# Install Python 3.7 or later first
python3 --version

# Install PlatformIO
pip install platformio

# Verify installation
pio --version
```

### Method 2: VSCode Extension

1. Install [Visual Studio Code](https://code.visualstudio.com/)
2. Install PlatformIO IDE extension from VSCode marketplace
3. Restart VSCode

## Project Setup

### 1. Open Project

```bash
# Clone repository
git clone https://github.com/mikoa001/smart-air-sensor.git
cd smart-air-sensor
```

### 2. Configure Settings

```bash
# Copy example configuration
cp src/config.h.example src/config.h

# Edit with your credentials
nano src/config.h
# or use your preferred editor
```

### 3. Install Dependencies

PlatformIO will automatically download required libraries on first build:

```bash
pio lib install
```

## Building

### Compile the Project

```bash
# Build for ESP8266
pio run

# Clean build (if needed)
pio run --target clean
pio run
```

Expected output:
```
Processing esp12e (platform: espressif8266; board: esp12e; framework: arduino)
...
Building .pio/build/esp12e/firmware.bin
...
========================= [SUCCESS] Took X.XX seconds =========================
```

## Uploading

### 1. Connect ESP8266

- Connect ESP8266 to computer via USB cable
- Wait for drivers to install (first time)

### 2. Upload Firmware

```bash
# Auto-detect port and upload
pio run --target upload

# Specify port manually (if needed)
pio run --target upload --upload-port /dev/ttyUSB0    # Linux
pio run --target upload --upload-port COM3            # Windows
```

### 3. Monitor Serial Output

```bash
# Start serial monitor (115200 baud)
pio device monitor

# Or combine upload and monitor
pio run --target upload && pio device monitor
```

## Common PlatformIO Commands

| Command | Description |
|---------|-------------|
| `pio run` | Build project |
| `pio run -t upload` | Upload firmware |
| `pio device monitor` | Serial monitor |
| `pio device list` | List connected devices |
| `pio lib install` | Install dependencies |
| `pio lib update` | Update libraries |
| `pio run -t clean` | Clean build files |
| `pio update` | Update PlatformIO |

## VSCode Integration

### Open Project in VSCode

```bash
# Open project folder
code .
```

### PlatformIO Toolbar

Look for PlatformIO icon in VSCode sidebar:
- ✓ Build
- → Upload  
- 🔌 Serial Monitor
- 🗑️ Clean

### Keyboard Shortcuts

- **Build**: Ctrl+Alt+B (Cmd+Alt+B on Mac)
- **Upload**: Ctrl+Alt+U (Cmd+Alt+U on Mac)

## Configuration Options

### Change Upload Speed

Edit `platformio.ini`:
```ini
[env:esp12e]
upload_speed = 115200  # Slower, more reliable
# or
upload_speed = 921600  # Faster (default)
```

### Change Serial Monitor Speed

```ini
[env:esp12e]
monitor_speed = 115200
```

### Add Build Flags

```ini
[env:esp12e]
build_flags = 
    -D MQTT_MAX_PACKET_SIZE=512
    -D DEBUG=1
```

## Troubleshooting

### Port Not Found

**Windows**:
- Install USB drivers (CH340 or CP2102)
- Check Device Manager for COM port

**Linux**:
- Add user to dialout group: `sudo usermod -a -G dialout $USER`
- Logout/login for changes to take effect
- Check port: `ls /dev/ttyUSB*`

**Mac**:
- Install drivers if needed
- Check port: `ls /dev/cu.*`

### Upload Fails

1. **Check cable**: Use data cable (not charge-only)
2. **Try different port**: Front vs back USB ports
3. **Lower upload speed**: Edit platformio.ini
4. **Press FLASH button**: Some boards need manual reset

### Library Issues

```bash
# Clear library cache
rm -rf .pio/libdeps

# Reinstall
pio lib install
```

### Build Errors

```bash
# Update PlatformIO
pip install --upgrade platformio

# Update platform
pio platform update espressif8266

# Clean build
pio run -t clean
```

## Advanced Configuration

### Multiple Environments

Edit `platformio.ini` to support different boards:

```ini
[env:nodemcu]
platform = espressif8266
board = nodemcuv2
framework = arduino

[env:d1_mini]
platform = espressif8266
board = d1_mini
framework = arduino
```

Build specific environment:
```bash
pio run -e nodemcu
pio run -e d1_mini
```

### Custom Library Versions

```ini
lib_deps = 
    adafruit/DHT sensor library@1.4.4
    sparkfun/SparkFun SCD4x Arduino Library@~1.1.0
```

### Debugging

Enable serial debugging:
```ini
build_flags = 
    -D DEBUG_ESP_PORT=Serial
    -D DEBUG_ESP_CORE
```

## IDE Comparison

| Feature | PlatformIO | Arduino IDE |
|---------|-----------|-------------|
| Library Management | Automatic | Manual |
| Multi-board Support | Excellent | Basic |
| Build Speed | Fast (incremental) | Slower |
| Code Completion | Yes (IntelliSense) | Limited |
| Debugging | Yes | No |
| Learning Curve | Moderate | Easy |

## Resources

- [PlatformIO Documentation](https://docs.platformio.org/)
- [ESP8266 Arduino Core](https://github.com/esp8266/Arduino)
- [PlatformIO Forum](https://community.platformio.org/)

## Next Steps

After successful upload:
1. Open serial monitor (115200 baud)
2. Watch for WiFi connection
3. Verify sensor readings
4. Check MQTT publishing
5. Observe LED display

For more help, see [TROUBLESHOOTING.md](TROUBLESHOOTING.md).
