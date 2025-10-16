# Wiring Diagram

## Complete Circuit Schematic

```
                           USB-C (5V Power)
                                 │
                    ┌────────────┴────────────┐
                    │                         │
                   5V                        GND
                    │                         │
         ┌──────────┼─────────────────────────┼────────────────┐
         │          │                         │                │
         │      ┌───┴────┐                    │                │
         │      │ ESP8266│                    │                │
         │      │NodeMCU │                    │                │
         │      │        │                    │                │
         │      │  3.3V  ├────┬───────────────┼────┐           │
         │      │        │    │               │    │           │
         │      │  GND   ├────┼───────────────┼────┼───────────┤
         │      │        │    │               │    │           │
         │      │  D4 (2)├───┐│               │    │           │
         │      │        │   ││               │    │           │
         │      │  D2 (4)├──┐││               │    │           │
         │      │        │  │││               │    │           │
         │      │  D1 (5)├─┐│││               │    │           │
         │      │        │ ││││               │    │           │
         │      │ D5 (14)├┐││││               │    │           │
         │      └────────┘│││││               │    │           │
         │                │││││               │    │           │
         │                │││││               │    │           │
         │         ┌──────┘││││               │    │           │
         │         │  LED Matrix Data         │    │           │
         │         │       ││││               │    │           │
         │    ┌────┴────┐  ││││               │    │           │
         │    │LED Mat 1│  ││││               │    │           │
         ├────┤  VCC    │  ││││               │    │           │
         │    │  GND    ├──┼┼┼┼───────────────┘    │           │
         │    │  DIN    │◄─┘│││                    │           │
         │    │  DOUT   ├──┐│││                    │           │
         │    └─────────┘  ││││                    │           │
         │                 ││││                    │           │
         │    ┌─────────┐  ││││                    │           │
         │    │LED Mat 2│  ││││                    │           │
         ├────┤  VCC    │  ││││                    │           │
         │    │  GND    ├──┼┼┼┼────────────────────┘           │
         │    │  DIN    │◄─┘│││                                │
         │    │  DOUT   ├──┐│││                                │
         │    └─────────┘  ││││                                │
         │                 ││││                                │
         │    ┌─────────┐  ││││                                │
         │    │LED Mat 3│  ││││                                │
         ├────┤  VCC    │  ││││                                │
         │    │  GND    ├──┼┼┼┼────────────────────────────────┘
         │    │  DIN    │◄─┘│││
         │    │  DOUT   │   │││  (not connected)
         │    └─────────┘   │││
         │                  │││
         │    ┌──────────┐  │││
         │    │  DHT22   │  │││
         ├────┤  VCC     │  │││
         │    │  GND     ├──┼┼┼────────────────────────────────┐
         │    │  DATA    │◄─┘││                                │
         │    └──────────┘   ││                                │
         │         │          ││                                │
         │      10kΩ Pull-up  ││                                │
         │                    ││                                │
         │    ┌──────────┐    ││                                │
         │    │  SCD40   │    ││                                │
         ├────┤  VDD     │    ││                                │
         │    │  GND     ├────┼┼────────────────────────────────┘
         │    │  SDA     │◄───┘│
         │    │  SCL     │◄────┘
         │    └──────────┘
         │
        GND (Common Ground)
```

## Pin Connection Table

### ESP8266 (NodeMCU) Connections

| Pin Label | GPIO | Connected To          | Notes                    |
|-----------|------|-----------------------|--------------------------|
| 3.3V      | -    | DHT22 VCC, SCD40 VDD  | 3.3V output              |
| 5V (VIN)  | -    | LED Matrices VCC      | From USB-C 5V            |
| GND       | -    | All component GNDs    | Common ground            |
| D4        | 2    | DHT22 DATA            | With 10kΩ pull-up        |
| D2        | 4    | SCD40 SDA             | I2C Data                 |
| D1        | 5    | SCD40 SCL             | I2C Clock                |
| D5        | 14   | First LED Matrix DIN  | NeoPixel data            |

### Component Connections

#### DHT22 (AM2302)
```
Pin 1 (VCC)  -> ESP8266 3.3V or 5V
Pin 2 (DATA) -> ESP8266 D4 (GPIO2) + 10kΩ resistor to VCC
Pin 3 (NC)   -> Not connected
Pin 4 (GND)  -> Common GND
```

#### SCD40 (I2C)
```
VDD -> ESP8266 3.3V
GND -> Common GND
SDA -> ESP8266 D2 (GPIO4)
SCL -> ESP8266 D1 (GPIO5)
SEL -> GND (for I2C mode, if pin exists)
```

#### LED Matrices (WS2812B 8x8)
```
Matrix 1:
  VCC  -> 5V power rail
  GND  -> Common GND
  DIN  -> ESP8266 D5 (GPIO14)
  DOUT -> Matrix 2 DIN

Matrix 2:
  VCC  -> 5V power rail
  GND  -> Common GND
  DIN  -> Matrix 1 DOUT
  DOUT -> Matrix 3 DIN

Matrix 3:
  VCC  -> 5V power rail
  GND  -> Common GND
  DIN  -> Matrix 2 DOUT
  DOUT -> Not connected
```

## Power Distribution

```
USB-C 5V Input
    ├── ESP8266 VIN (5V)
    ├── LED Matrix 1 VCC
    ├── LED Matrix 2 VCC
    └── LED Matrix 3 VCC

ESP8266 3.3V Regulator
    ├── DHT22 VCC
    └── SCD40 VDD

Common Ground (GND)
    ├── ESP8266 GND
    ├── DHT22 GND
    ├── SCD40 GND
    ├── LED Matrix 1 GND
    ├── LED Matrix 2 GND
    └── LED Matrix 3 GND
```

## Notes

1. **Pull-up Resistor**: The 10kΩ resistor between DHT22 DATA and VCC is required
2. **I2C Pull-ups**: ESP8266 has internal pull-ups, but external 4.7kΩ may improve reliability
3. **Power Supply**: Minimum 2A recommended for stable operation
4. **Decoupling Capacitors**: Consider adding 100µF capacitor across LED matrix power pins
5. **Data Line**: Keep LED matrix data line as short as possible for signal integrity
6. **Grounding**: Ensure all grounds are connected to a common ground point
