# tool., Inc - Laser Tube Light
Do you have an old, dead, laser tube taking up space that you're not sure what to do with? They look so cool, why not turn it into a light fixture? The engineers at [tool., Inc.](https://toolinc.com/) have done just that! We converted an old 120W, 80mm diameter, 1450mm long, CO2 laser tube into a, slightly less powerful, 25W LED fixture. Using an Arduino and NeoPixels, you can go from plain white to custom RGB lighting effects in the flick of a switch. We've open sourced the project so you too can DIY the most expensive lamp in your shop!

![Banner](./Renders/Banner.png)

## Bill of Materials

### 3D Prints

|Part|File|Quantity|
|:---|:---|:---|
|Electronics Enclosure|electronics_enclosure.stl|1|
|Hanger Cable Pulley|hanger_cable_pully.stl|2|
|Strip (End)|strip_end.stl|2|
|Strip (Side)|strip_side.stl|6|

### Laser Cuts

|Part|File|Quantity|
|:---|:---|:---|
|Strip Backing|strip_back.dxf|1|
|Teardrop Hanger|teardrop_hanger.dxf|4|

### Hardware

|Part|SKU|Quantity|Link|
|:---|:---|:---|:---|
|M3 Heat Set Inserts|94459A140|26|[McMaster-Carr](https://www.mcmaster.com/94459A140/)|
|M3 x 8 mm Button Head Hex Drive Screw|92095A181|22|[McMaster-Carr](https://www.mcmaster.com/92095A181/)|
|M3 x 30 mm Button Head Hex Drive Screw|92095A187|4|[McMaster-Carr](https://www.mcmaster.com/92095A187/)|
|Binding Barrel|98002A202|2|[McMaster-Carr](https://www.mcmaster.com/98002A202/)|
|Wire Rope|3461T474|1|[McMaster-Carr](https://www.mcmaster.com/3461T474/)|
|Wire Rope Compression Sleeve|3896T61|4|[McMaster-Carr](https://www.mcmaster.com/3896T61/)|
|Foam Double Face Mounting Tape|3744A41|1|[McMaster-Carr](https://www.mcmaster.com/3744A41/)|

### Electronics

|Part|SKU|Quantity|Link|Notes|
|:---|:---|:---|:---|:---|
|Arduino Nano Every|ABX00028|1|[Arduino](https://store.arduino.cc/products/arduino-nano-every)|I'd recommend getting the version without headers to solder directly to the Arduino.|
|DC Power Supply (5V, 5A)|B078RT3ZPS|1|[Amazon](https://a.co/d/07ThTM0f)|Each NeoPixel can draw up to 60 mA. For my strip length, that's 4.26 amps!|
|DC Barrel Jack|B07CTCLKPP|1|[Amazon](https://a.co/d/05rNLqdA)||
|Toggle Switch|100SP1T1B1M1QEH|3|[DigiKey](https://www.digikey.com/en/products/detail/e-switch/100SP1T1B1M1QEH/378819)||
|NeoPixel Strip (2 m)|2540|1|[Adafruit](https://www.adafruit.com/product/2540)|To save a couple bucks, buying two 1 m strips can be cheaper.|
|Resistor (470 Ω)|CF14JT470R|1|[DigiKey](https://www.digikey.com/en/products/detail/stackpole-electronics-inc/CF14JT470R/1741440)||
|Capacitor (1,000 μF)|ECA-0JM102|1|[DigiKey](https://www.digikey.com/en/products/detail/panasonic-electronic-components/ECA-0JM102/244974)||

## Author
Jordan Tryon for tool., Inc.
