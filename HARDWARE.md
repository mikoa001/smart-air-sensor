# Hardware Assembly Guide

## Required Components

### Main Components
- 1x ESP8266 development board (NodeMCU or Wemos D1 Mini recommended)
- 1x AM2302 DHT22 temperature and humidity sensor
- 1x Sensirion SCD40 CO2 sensor
- 3x WS2812B 8x8 RGB LED matrices
- 1x USB-C breakout board or cable

### Additional Parts
- 1x 10kΩ resistor (for DHT22 pull-up)
- Jumper wires (male-to-male and male-to-female)
- Breadboard or custom PCB
- 5V power supply (minimum 2A recommended for LED matrices)
- USB-C cable
- Enclosure (optional)

## Assembly Steps

### 1. Power Setup
1. Connect USB-C breakout to provide 5V power
2. Connect 5V to ESP8266 VIN pin
3. Connect GND to ESP8266 GND pin

### 2. DHT22 Sensor
1. Connect DHT22 VCC to ESP8266 3.3V or 5V
2. Connect DHT22 GND to ESP8266 GND
3. Connect DHT22 DATA to GPIO2 (D4)
4. Add 10kΩ pull-up resistor between DATA and VCC

### 3. SCD40 Sensor
1. Connect SCD40 VDD to ESP8266 3.3V
2. Connect SCD40 GND to ESP8266 GND
3. Connect SCD40 SDA to GPIO4 (D2)
4. Connect SCD40 SCL to GPIO5 (D1)

**Note**: The ESP8266 has internal pull-up resistors on I2C pins, but external 4.7kΩ pull-ups may improve reliability.

### 4. LED Matrices
1. Connect first matrix VCC to 5V power rail
2. Connect first matrix GND to common ground
3. Connect first matrix DIN to GPIO14 (D5)
4. Chain matrices: DOUT of matrix 1 → DIN of matrix 2
5. Chain matrices: DOUT of matrix 2 → DIN of matrix 3
6. Connect VCC and GND of all matrices

**Important**: LED matrices can draw significant current (up to 1.5A at full brightness). Use adequate power supply.

### 5. Layout Recommendations
```
┌─────────────────────────────────┐
│  [Matrix 1] [Matrix 2] [Matrix 3] │
│                                 │
│        [SCD40]    [DHT22]       │
│                                 │
│          [ESP8266]              │
│                                 │
│          [USB-C]                │
└─────────────────────────────────┘
```

## Pin Reference Table

| Component      | Pin Name | ESP8266 GPIO | NodeMCU Label |
|---------------|----------|--------------|---------------|
| DHT22         | DATA     | GPIO2        | D4            |
| SCD40         | SDA      | GPIO4        | D2            |
| SCD40         | SCL      | GPIO5        | D1            |
| LED Matrix    | DIN      | GPIO14       | D5            |

## Power Considerations

- ESP8266: ~80mA (WiFi active), ~15mA (sleep)
- DHT22: ~2.5mA
- SCD40: ~18mA (average)
- LED Matrices: Up to 1.5A (full brightness, all LEDs white)

**Total estimated**: 2A minimum recommended

## Safety Notes

1. Double-check all connections before powering on
2. Use proper voltage levels (3.3V for sensors, 5V for matrices)
3. Don't exceed current ratings
4. Add capacitors (100µF) across LED matrix power if experiencing stability issues
5. Use heat sinks if enclosing in small space

## Testing

1. Upload firmware first
2. Test each component individually:
   - Check serial monitor for WiFi connection
   - Verify DHT22 readings
   - Verify SCD40 readings
   - Test LED matrix display
3. Verify MQTT publishing to Home Assistant

## Enclosure Design

Recommended features:
- Ventilation holes for accurate sensor readings
- Window or cutout for LED matrix visibility
- Access to USB-C port
- Mounting holes for wall mounting
- Minimum internal dimensions: 100mm x 80mm x 40mm
