# PixelPaper

Upload any picture in a web page and see it appear on a 2.13" e-paper display.
The image stays on the screen with no power.

## How it works

1. **Web uploader** (`uploader.html`): resizes the picture, applies Floyd-Steinberg dithering, and packs it into 1-bit black and red bitmaps.
2. **USB link:** the browser sends the data to the Arduino using the Web Serial API.
3. **Arduino** (`receiver.ino`): reads the bitmap and draws it on the Waveshare e-paper panel over SPI.

## Hardware

- Arduino UNO R4 Minima
- Waveshare 2.13" e-paper display module
- Jumper wires

| Display | Arduino |
|---|---|
| VCC | 3.3V |
| GND | GND |
| DIN | D11 |
| CLK | D13 |
| CS | D10 |
| DC | D9 |
| RST | D8 |
| BUSY | D7 |

## Setup

1. In Arduino IDE, install the **GxEPD2** library (Library Manager).
2. Open `receiver.ino`, select Arduino UNO R4 Minima, and upload.
3. In the edit block at the top of the sketch, choose the panel class that matches your display (`GxEPD2_213_Z98c` or `GxEPD2_213c`).
4. Close the Arduino Serial Monitor (it blocks the USB port).
5. Open `uploader.html` in **Chrome or Edge** on a computer.
6. Click Connect Arduino, pick a picture, then click **Send to display**.

The panel takes about 15 seconds to refresh.

## Notes

- Web Serial works only in Chrome and Edge on desktop.
- If the picture looks sheared or distorted, the size selected on the website does not match the panel. The status line reports the panel size after the first send.
- Different Waveshare 2.13" versions need different driver classes. If the screen stays blank, try the other class.

## Tech

C++ (Arduino), JavaScript, Web Serial API, SPI, GxEPD2, image dithering.
