/**
 * ESP-IDF library for the Adafruit 1.30" TFT LCD
 *
 * This library is released under the MIT License.
 *
 * Copyright (c) 2020 Michael Volk
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * The entirety of this notice (above and below) shall be included in all copies
 * or substantial portions of the Software.
 *
 * This library draws heavily on configuration examples in the
 * [Adafruit-ST7735-Library](Adafruit-ST7735-Library). The license and copyright
 * for that work is reproduced below and must be included in all copies or
 * substantial portions of the Software.
 *
 * This is a library for several Adafruit displays based on ST77* drivers.
 * Works with the Adafruit 1.8" TFT Breakout w/SD card
 *   ----> http://www.adafruit.com/products/358
 * The 1.8" TFT shield
 *   ----> https://www.adafruit.com/product/802
 * The 1.44" TFT breakout
 *   ----> https://www.adafruit.com/product/2088
 * as well as Adafruit raw 1.8" TFT display
 *   ----> http://www.adafruit.com/products/618
 * Check out the links above for our tutorials and wiring diagrams.
 * These displays use SPI to communicate, 4 or 5 pins are required to
 * interface (RST is optional).
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 * Written by Limor Fried/Ladyada for Adafruit Industries.
 * MIT license, all text above must be included in any redistribution
 */

#ifndef ADAFRUIT_130_TFT_H
#define ADAFRUIT_130_TFT_H

#include <freertos/FreeRTOS.h>
#include <driver/spi_master.h>
#include <esp_err.h>
#include <tft.h>
#include <st7789.h>


#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Initialize the display
 *
 * Uses memory allocated dynamically on the
 * heap.
 *
 * Adds the display to the SPI bus,
 * completes initialization of the device
 * descriptor, configures the panel and
 * resets the panel.
 *
 * See st7789_init(...) for further details.
 *
 * @param params configuration parameters
 */
tft_handle_t adafruit_130_tft_init(
   const st7789_params_t *params
);


/**
 * @brief Initialize the display
 *
 * Uses memory allocated by the caller.
 *
 * Adds the display to the SPI bus,
 * completes initialization of the device
 * descriptor, configures the panel and
 * resets the panel.
 *
 * See st7789_init_static(...) for further
 * details.
 *
 * @param params configuration parameters
 * @param tft memory that will be initialized with
 *        the tft_t
 * @param device memory that will be initialized
 *        with the st7789_device_t
 */
void adafruit_130_tft_init_static(
    const st7789_params_t *params,
    tft_handle_t tft,
    st7789_device_handle_t device
);


#ifdef __cplusplus
}
#endif

#endif // ADAFRUIT_130_TFT_H
