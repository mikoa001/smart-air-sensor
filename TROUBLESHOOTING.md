# Troubleshooting Guide

## Common Issues and Solutions

### WiFi Connection Problems

#### Issue: Cannot connect to WiFi
**Symptoms:**
- Serial monitor shows repeated "." without connection
- No IP address displayed

**Solutions:**
1. **Verify credentials**:
   - Double-check SSID and password in `config.h`
   - Ensure no extra spaces or special characters
   
2. **Check WiFi compatibility**:
   - ESP8266 only supports 2.4GHz WiFi (NOT 5GHz)
   - Ensure 2.4GHz network is enabled on your router
   
3. **Signal strength**:
   - Move device closer to router
   - Check for interference from other devices
   
4. **Router settings**:
   - Ensure DHCP is enabled
   - Check MAC address filtering isn't blocking device
   - Try disabling AP isolation if enabled

#### Issue: WiFi keeps disconnecting
**Solutions:**
- Improve signal strength
- Update ESP8266 firmware
- Add WiFi reconnection logic (already implemented)
- Check power supply stability

### MQTT Connection Issues

#### Issue: MQTT connection fails
**Symptoms:**
- Serial shows "failed, rc=X"
- Return codes meaning:
  - rc=-4: Connection timeout
  - rc=-3: Connection lost
  - rc=-2: Connect failed
  - rc=1: Wrong protocol version
  - rc=2: Client ID rejected
  - rc=3: Server unavailable
  - rc=4: Bad username/password
  - rc=5: Not authorized

**Solutions:**
1. **For rc=4 (Authentication failure)**:
   - Verify MQTT username and password
   - Check MQTT broker allows password authentication
   
2. **For rc=-4 (Timeout)**:
   - Verify MQTT broker IP address
   - Ensure MQTT broker is running
   - Check firewall settings (port 1883)
   
3. **For rc=5 (Not authorized)**:
   - Check MQTT broker ACL settings
   - Verify user has publish permissions
   
4. **General MQTT troubleshooting**:
   ```bash
   # Test MQTT broker from command line
   mosquitto_sub -h MQTT_SERVER -p 1883 -u USER -P PASSWORD -t "#" -v
   ```

#### Issue: Messages not appearing in Home Assistant
**Solutions:**
- Verify topic names match in both config.h and Home Assistant
- Check Home Assistant MQTT integration is configured
- Use MQTT Explorer or mosquitto_sub to verify messages
- Restart Home Assistant after configuration changes

### Sensor Reading Problems

#### Issue: DHT22 returns NaN or incorrect values
**Symptoms:**
- Serial shows "Failed to read from DHT sensor!"
- Temperature or humidity shows as NaN

**Solutions:**
1. **Check wiring**:
   - Verify DATA pin connected to GPIO2
   - Ensure 10kΩ pull-up resistor is present
   - Check VCC and GND connections
   
2. **Sensor power**:
   - Use 3.3V or 5V (both work)
   - Ensure stable power supply
   
3. **Timing issues**:
   - DHT22 needs 2 seconds between readings (already handled)
   - Try power cycling the sensor
   
4. **Faulty sensor**:
   - Test with known-good sensor
   - Check sensor with multimeter (resistance between pins)

#### Issue: SCD40 not detected
**Symptoms:**
- Serial shows "SCD40 sensor not detected"

**Solutions:**
1. **Check I2C wiring**:
   - SDA to GPIO4 (D2)
   - SCL to GPIO5 (D1)
   - Pull-up resistors (4.7kΩ) may help if having issues
   
2. **Verify I2C address**:
   ```cpp
   // Test I2C scanner sketch to find devices
   Wire.begin(4, 5);
   Wire.beginTransmission(0x62); // SCD40 default address
   ```
   
3. **Power requirements**:
   - SCD40 needs 3.3V (NOT 5V)
   - Ensure stable power supply
   
4. **Sensor initialization**:
   - Allow 1-2 seconds after power-on before initialization
   - Try adding delay(2000) before scd4x.begin()

#### Issue: CO2 readings seem incorrect
**Symptoms:**
- CO2 always reads 400 ppm or fixed value
- CO2 readings unrealistic

**Solutions:**
1. **Calibration**:
   - SCD40 needs 7 days for automatic self-calibration
   - Ensure sensor gets fresh air periodically
   - Manual calibration may be needed
   
2. **Warm-up time**:
   - First readings may be inaccurate
   - Allow 5-10 minutes for sensor to stabilize
   
3. **Measurement interval**:
   - SCD40 takes 5 seconds per measurement
   - Don't read faster than every 5 seconds (code already handles this)

### LED Matrix Issues

#### Issue: LED matrix not lighting up
**Solutions:**
1. **Power supply**:
   - LED matrices need 5V and can draw significant current
   - Ensure power supply provides at least 2A
   - Try with lower brightness setting
   
2. **Wiring**:
   - Verify DIN connected to GPIO14
   - Check VCC and GND connections
   - Ensure matrices are chained correctly (DOUT → DIN)
   
3. **Library configuration**:
   - Verify MATRIX_WIDTH and MATRIX_HEIGHT in config.h
   - Check NEO_MATRIX_TOP/LEFT/ROWS/ZIGZAG settings match your hardware

#### Issue: Wrong colors or flickering
**Solutions:**
1. **Color order**:
   - Try changing NEO_GRB to NEO_RGB or NEO_GRBW in main.cpp
   - Different LED strips use different color orders
   
2. **Power stability**:
   - Add 100µF capacitor across power pins
   - Use shorter wires for data line
   - Add 220-470Ω resistor on data line
   
3. **Brightness**:
   - Lower brightness if flickering (currently set to 40)
   - `matrix.setBrightness(20);` for dimmer display

#### Issue: Display shows wrong numbers or garbled text
**Solutions:**
- Verify MATRIX_WIDTH setting (24 for 3 matrices)
- Check matrix orientation and settings
- Try different NEO_MATRIX settings

### Power Issues

#### Issue: Device keeps resetting
**Solutions:**
- Use adequate power supply (5V, 2A minimum)
- Check for loose connections
- Add bulk capacitor (470µF) on power rails
- Reduce LED brightness

#### Issue: Brown-out detector triggered
**Solutions:**
- ESP8266 needs stable 3.3V (from onboard regulator)
- Don't power ESP8266 with 5V on 3.3V pin
- Use quality USB cable
- Add capacitor near ESP8266 power pins

### Build and Upload Issues

#### Issue: PlatformIO build fails
**Solutions:**
1. **Clean build**:
   ```bash
   pio run --target clean
   pio run
   ```
   
2. **Update PlatformIO**:
   ```bash
   pip install --upgrade platformio
   ```
   
3. **Library issues**:
   ```bash
   pio lib update
   ```

#### Issue: Upload fails
**Solutions:**
- Select correct COM port
- Install USB drivers (CH340/CP2102)
- Press FLASH button during upload (some boards)
- Try lower upload speed: `upload_speed = 115200` in platformio.ini

### Serial Monitor Issues

#### Issue: Garbage characters in serial monitor
**Solutions:**
- Set baud rate to 115200
- Some ESP8266 boards output at 74880 during boot (normal)

#### Issue: No serial output
**Solutions:**
- Verify USB cable supports data (not charge-only)
- Check serial port selection
- Try different USB port
- Reset ESP8266

## Debugging Tips

### Enable Verbose Logging
Add debug output to identify issues:
```cpp
Serial.setDebugOutput(true);
```

### Test Components Individually
1. Test WiFi connection alone
2. Test sensors separately
3. Test LED matrix independently
4. Add MQTT last

### Use MQTT Tools
```bash
# Subscribe to all topics
mosquitto_sub -h MQTT_SERVER -t "#" -v

# Publish test message
mosquitto_pub -h MQTT_SERVER -t "home/sensor/test" -m "test"
```

### I2C Scanner
If SCD40 not detected, scan I2C bus:
```cpp
Wire.begin(4, 5);
for (byte i = 1; i < 127; i++) {
  Wire.beginTransmission(i);
  if (Wire.endTransmission() == 0) {
    Serial.print("Found I2C device at 0x");
    Serial.println(i, HEX);
  }
}
```

## Getting Help

If issues persist:
1. Check serial monitor output carefully
2. Document exact error messages
3. List hardware components used
4. Note any modifications made
5. Open GitHub issue with details

## Advanced Troubleshooting

### Reset to Factory Settings
1. Re-flash firmware
2. Clear EEPROM (if used)
3. Power cycle all components

### Hardware Testing
- Use multimeter to verify voltages
- Check continuity of connections
- Verify resistor values
- Test with minimal setup (one sensor at a time)
