# Bill of Materials (BOM)

Complete list of components needed to build the Smart Air Quality Sensor.

## Electronic Components

| Qty | Component | Specifications | Notes | Est. Price (USD) |
|-----|-----------|---------------|-------|------------------|
| 1 | ESP8266 Development Board | NodeMCU v3 or Wemos D1 Mini | ESP-12E/F module recommended | $3-8 |
| 1 | DHT22 (AM2302) | Temperature & Humidity Sensor | Digital output, 3.3-5V | $5-10 |
| 1 | SCD40 | CO2 Sensor | I2C interface, 3.3V | $40-50 |
| 3 | WS2812B LED Matrix | 8x8 RGB LED Matrix | NeoPixel compatible, 5V | $15-25 (for 3) |
| 1 | USB-C Breakout Board | 5V Power | Or USB-C cable with exposed wires | $2-5 |
| 1 | 10kΩ Resistor | 1/4W | Pull-up for DHT22 data line | $0.10 |
| 2 | 4.7kΩ Resistor (optional) | 1/4W | I2C pull-ups if needed | $0.10 each |
| 1 | 100µF Capacitor (optional) | Electrolytic, 16V+ | Power filtering for LED matrices | $0.25 |
| 1 | 470Ω Resistor (optional) | 1/4W | Data line protection for LEDs | $0.10 |

**Total Electronic Components: ~$65-95**

## Wiring & Connectivity

| Qty | Item | Specifications | Notes | Est. Price (USD) |
|-----|------|---------------|-------|------------------|
| 1 | Breadboard | 830 tie-points | Half-size acceptable | $3-5 |
| 20 | Jumper Wires | Male-to-male | Various lengths, 22 AWG | $2-5 (set) |
| 10 | Jumper Wires | Male-to-female | Various lengths, 22 AWG | $2-5 (set) |
| 1 | USB Cable | USB-A to Micro-USB or USB-C | For programming ESP8266 | $2-5 |

**Total Wiring: ~$9-20**

## Power Supply

| Qty | Item | Specifications | Notes | Est. Price (USD) |
|-----|------|---------------|-------|------------------|
| 1 | USB Power Adapter | 5V, 2A minimum | USB-C output preferred | $5-10 |
| 1 | USB-C Cable | Power delivery | 1-2 meters length | $3-8 |

**Total Power: ~$8-18**

## Enclosure (Optional)

| Qty | Item | Specifications | Notes | Est. Price (USD) |
|-----|------|---------------|-------|------------------|
| 1 | Project Box | ~120x90x50mm | Must have ventilation | $5-15 |
| 4 | M3 Screws | 10-15mm length | For mounting components | $1-2 (set) |
| 4 | M3 Standoffs | 10mm height | Component spacing | $2-4 (set) |

**Total Enclosure: ~$8-21**

## Tools Required

| Item | Purpose | Notes |
|------|---------|-------|
| Soldering Iron | Header pins, connections | 30-60W recommended |
| Solder | Electrical connections | Lead-free or 60/40 |
| Wire Strippers | Preparing jumper wires | Optional |
| Multimeter | Voltage/continuity testing | Highly recommended |
| Small Screwdriver Set | Assembly | Phillips and flathead |
| Wire Cutters | Trimming components | Flush cutters preferred |
| Hot Glue Gun (optional) | Strain relief | Alternative: zip ties |

## Recommended Suppliers

### USA
- **Adafruit**: High-quality sensors and LED matrices
- **SparkFun**: SCD40, sensors, development boards
- **Amazon**: General components, quick delivery
- **Digi-Key**: Professional components, wide selection
- **Mouser**: Professional components

### Europe
- **Pimoroni**: UK-based, Adafruit distributor
- **BerryBase**: Germany, Raspberry Pi accessories
- **Mouser**: International shipping
- **AliExpress**: Budget option (longer shipping)

### Asia
- **AliExpress**: Budget-friendly, direct from manufacturers
- **Banggood**: Electronics hobbyist supplies
- **Taobao**: China domestic (via agent)

## Cost Summary

| Category | Estimated Cost (USD) |
|----------|---------------------|
| Electronic Components | $65-95 |
| Wiring & Connectivity | $9-20 |
| Power Supply | $8-18 |
| Enclosure (Optional) | $8-21 |
| **Total (without enclosure)** | **$82-133** |
| **Total (with enclosure)** | **$90-154** |

## Component Selection Notes

### ESP8266 Board Choice
- **NodeMCU v3**: Larger, breadboard-friendly, built-in USB
- **Wemos D1 Mini**: Compact, requires separate USB cable
- **Generic ESP-12E/F**: Cheapest, requires FTDI programmer

### DHT22 Variations
- DHT22 and AM2302 are the same sensor
- Some come pre-mounted on PCB with pull-up resistor
- Loose sensor requires separate pull-up resistor

### LED Matrix Options
- Individual WS2812B 8x8 matrices
- Pre-assembled 3-panel matrix (easier assembly)
- Flexible NeoPixel strips (alternative display)

### SCD40 vs SCD41
- SCD40: Standard version, used in this project
- SCD41: Slightly better accuracy, compatible with code

## Alternatives & Substitutions

### Lower Cost Options
- **ESP8266 Generic**: Save $2-5 vs name brand
- **DHT11**: Save $3-5 (lower accuracy)
- **Smaller Display**: 2 matrices instead of 3 (save $5-8)

### Higher Performance Options
- **ESP32**: More memory, Bluetooth ($8-12)
- **SCD41**: Better CO2 accuracy (+$5-10)
- **Enclosed LED Matrices**: Professional appearance (+$10-20)

## Purchasing Recommendations

1. **Buy extra resistors** - Cheap and useful for other projects
2. **Get a starter kit** - May include breadboard, wires, resistors
3. **Check bundle deals** - LED matrices often sold in sets
4. **Verify compatibility** - Ensure 5V/3.3V levels match
5. **Read reviews** - Especially for sensors (quality varies)

## Inventory Checklist

Before starting assembly, verify you have:
- [ ] ESP8266 development board
- [ ] DHT22 temperature/humidity sensor
- [ ] SCD40 CO2 sensor
- [ ] 3x 8x8 RGB LED matrices
- [ ] 10kΩ resistor for DHT22
- [ ] Breadboard
- [ ] Jumper wires (male-to-male and male-to-female)
- [ ] USB-C power supply (5V, 2A+)
- [ ] USB cable for programming
- [ ] Soldering equipment (if needed)
- [ ] Multimeter for testing

## Notes

- Prices are approximate and vary by supplier and location
- Shipping costs not included
- Tools excluded from cost estimate (one-time purchase)
- Consider buying from single supplier to save on shipping
- Watch for sales and bundle deals
- Quality of components affects reliability
