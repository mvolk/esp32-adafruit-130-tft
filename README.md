# Adafruit 1.30" TFT Prototyping Library for ESP32 & ESP-IDF

This library supports quick-start interfacing support
with an Adafruit 1.30" 240x240 pixel TFT LCD screen via
SPI on an Espressif ESP32 system using the ESP-IDF
development platform.

A breakout board with the TFT hardware is available from
[Adafruit](https://www.adafruit.com/product/4313).

## For Prototyping

This library does not emphasize performance, memory
efficiency, testing or configurability.

This library is particularly useful for getting up
and running rapidly with the 1.30" TFT using ESP-IDF,
and as a jumping-off point for learning how to
configure and utilize this peice of hardware.

This library is licensed under the permissive MIT
license. You are encouraged to fork it, modify it,
and mould it to fit your needs. It aspires only to
be your starting point.

## Supported Ecosystem

This library aims to support the following... and only the following:

* **Microcontroller:** Espressif [ESP32 modules](https://www.espressif.com/en/products/modules/esp32)
* **TFT Controller:** Sitronix [ST7789V](https://www.newhavendisplay.com/appnotes/datasheets/LCDs/ST7789V.pdf)
* **Interface:** SPI 4-wire sans MISO, with an
  additional line for data/command signaling, and
  optionally with lines for hardware reset and backlight control
* **Display Panel:** [Adafruit 1.30" TFT LCD](https://www.adafruit.com/product/4313)
* **Development Platform:** [ESP-IDF v4.1+](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/index.html),
  Espressif's freeRTOS-based platform for ESP32 development

## Dependencies

This library depends on the following components:
* [esp32-tft](https://github.com/mvolk/esp32-tft)
* [esp32-st7789](https://github.com/mvolk/esp32-st7789)

Installation of these components is your responsibility.

## Boundaries

* **SPI Bus:** this library relies on the
  [esp32-st7789](https://github.com/mvolk/esp32-st7789)
  library to interface with the driver IC over SPI. This
  library does not itself directly exercise any SPI bus
  features.
* **Display Panel:** this library does not provide support
  for any display panel other than the 1.30" Adafruit TFT
* **GFX:** this library does not provide features to draw
  geometries, text, images, etc.
* **Peripherals:** this library provides no support for the
  SD card reader included in the Adafruit 1.30" TFT breakout
  board, but its use is expected to be compatible with use
  of the SD card reader on the same SPI bus via a different
  library or user code.
* **API:** This library provides an API for initializing the
  panel and `tft_t` struct. All other APIs for interacting
  with the display are provided by the
  [esp32-tft](https://github.com/mvolk/esp32-tft) library.

## Installation

Using the modern ESP-IDF with CMake, Git and the recommended
project structure (with a `components` folder), the easiest
way to install this library is to add it to the `components`
folder as a Git submodule:

```shell
cd ${YOUR_PROJECT_ROOT}/components
git submodule add https://github.com/mvolk/esp32-adafruit-130-tft.git
# If esp32-tft is not already installed:
git submodule add https://github.com/mvolk/esp32-tft.git
# If esp32-st7789 is not already installed:
git submodule add https://github.com/mvolk/esp32-st7789.git
git commit -m "Add esp32_adafruit_130_tft component and dependencies"

```

## API

There's not much to this high-level library. The
heavy lifting has been delegated to the
[esp32-st7789](https://github.com/mvolk/esp32-st7789)
library behind the scenes and to the
[esp32-tft](https://github.com/mvolk/esp32-tft) library
for application interfacing, leaving this "developer
interface" quite lean.

* `adafruit_130_tft_init(...)` initializes the panel using
  memory it allocates from the heap
* `adafruit_130_tft_init_static(...)` initializes the panel
  using memory provided by the caller

See detailed durocumentation in
[adafruit-130-tft.h](./include/adafruit-130-tft.h)

The initialization functions will provide you with an
initialized `tft_handle_t` that you can supply to the drawing
API provided by [esp32-tft](https://github.com/mvolk/esp32-tft).

## Technical Notes

* This library's convention is that the origin (0, 0) is
  at the bottom left of the screen. The physical location
  of this corner in the default (upright) orientation is
  closest to the "lite" pin with the x-axis extending towards
  the ribbon cable opposite the header pins.

* This library is a thin wrapper around the
  [esp32-st7789](https://github.com/mvolk/esp32-st7789)
  library. There are a number of important technical
  notes in that library's README that are well worth
  reading.

## Support

Technical support is not available.

## Contributing

### Bug Reports

Please feel free to report bugs by
[opening a new issue via Github](https://github.com/mvolk/esp32-adafruit-130-tft/issues/new).

Please do not use Github issues to request technical support.

### Pull Requests

Pull requests that further the goals of this library are welcome.

The [issues list](https://github.com/mvolk/esp32-adafruit_130_tft/issues)
is a good place to look for ideas if you would like to contribute but
don't have a specific contribution in mind.

If you would like to extend support to additional panels, MCUs or
development platforms, please consider forking this library.

## Credits

This library is not quite a derivative of the
[Adafruit-ST7735-Library](https://github.com/adafruit/Adafruit-ST7735-Library)
for the Arduino platform, but it draws so heavily on the configuration
examples provided in that library that the Adafruit license and copyright
are reproduced as part of this library's licensing.

Espressif's [ESP-IDF Programming Guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/index.html)
was invaluable.

A Sitronix [ST7789V datasheet](https://www.newhavendisplay.com/appnotes/datasheets/LCDs/ST7789V.pdf)
and TFT breakout board sourced from [Adafruit](https://www.adafruit.com/)
made this library possible.

## License & Copyright

See [LICENSE.txt](./LICENSE.txt) for license details.

## Liability Notice

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
