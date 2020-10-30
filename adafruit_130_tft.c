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

#include "adafruit_130_tft.h"
#include <freertos/task.h>
#include <esp_system.h>
#include <esp_log.h>


#define ADAFRUIT_130_TFT_OFFSET_X 3
#define ADAFRUIT_130_TFT_OFFSET_Y 2


static const char * ADAFRUIT_130_TFT_TAG = "adafruit_130_tft";


void adafruit_130_tft_init(st7789_device_handle_t device)
{
    esp_err_t ret;
    st7789_backlight(device, ST7789_CFG_BCKL_OFF);
    st7789_init(device, NULL);
    st7789_hwreset(device);
    ret = st7789_swreset(device);
    ESP_ERROR_CHECK(ret);
    ret = st7789_slpout(device);
    ESP_ERROR_CHECK(ret);
    ret = st7789_frmctr1(
        device,
        1,
        44,
        45
    );
    ESP_ERROR_CHECK(ret);
    ret = st7789_frmctr2(
        device,
        1,
        44,
        45
    );
    ESP_ERROR_CHECK(ret);
    ret = st7789_frmctr3(
        device,
        1,
        44,
        45
    );
    ESP_ERROR_CHECK(ret);
    ret = st7789_invctr(
        device,
        (
            ST7789_CFG_INV_LINE_NORM |
            ST7789_CFG_INV_LINE_IDLE |
            ST7789_CFG_INV_LINE_PART
        )
    );
    ESP_ERROR_CHECK(ret);
    ret = st7789_pwctr1(
        device,
        ST7789_CFG_GVDD_460,
        ST7789_CFG_AVDD_500,
        ST7789_CFG_GVCL_NEG_460,
        ST7789_CFG_PWR_MODE_AUTO
    );
    ESP_ERROR_CHECK(ret);
    ret = st7789_pwctr2(
        device,
        ST7789_CFG_V25_240,
        ST7789_CFG_VGH_3_X_AVDD,
        ST7789_CFG_VGL_NEG_100
    );
    ESP_ERROR_CHECK(ret);
    ret = st7789_pwctr3(
        device,
        ST7789_CFG_OPAMP_I_MED_LOW,
        ST7789_CFG_OPAMP_I_SMALL,
        st7789_dca(
            ST7789_CFG_BCLK_DIV_10,
            ST7789_CFG_BCLK_DIV_10,
            ST7789_CFG_BCLK_DIV_10,
            ST7789_CFG_BCLK_DIV_10,
            ST7789_CFG_BCLK_DIV_10
        )
    );
    ESP_ERROR_CHECK(ret);
    ret = st7789_pwctr4(
        device,
        ST7789_CFG_OPAMP_I_MED_LOW,
        ST7789_CFG_OPAMP_I_SMALL,
        st7789_dca(
            ST7789_CFG_BCLK_DIV_20,
            ST7789_CFG_BCLK_DIV_10,
            ST7789_CFG_BCLK_DIV_20,
            ST7789_CFG_BCLK_DIV_20,
            ST7789_CFG_BCLK_DIV_20
        )
    );
    ESP_ERROR_CHECK(ret);
    ret = st7789_pwctr5(
        device,
        ST7789_CFG_OPAMP_I_MED_LOW,
        ST7789_CFG_OPAMP_I_SMALL,
        st7789_dca(
            ST7789_CFG_BCLK_DIV_20,
            ST7789_CFG_BCLK_DIV_40,
            ST7789_CFG_BCLK_DIV_20,
            ST7789_CFG_BCLK_DIV_40,
            ST7789_CFG_BCLK_DIV_20
        )
    );
    ESP_ERROR_CHECK(ret);
    ret = st7789_vmctr1(device, ST7789_CFG_VCOM_NEG_0775);
    ESP_ERROR_CHECK(ret);
    ret = st7789_madctl(
        device,
        (
          ST7789_CFG_MIRROR_X |
          ST7789_CFG_MIRROR_Y |
          ST7789_CFG_EXCHANGE_XY |
          // ST7789_CFG_REFRESH_RTL
          // ST7789_CFG_REFRESH_BTT
          ST7789_CFG_BGR
        )
    );
    ESP_ERROR_CHECK(ret);
    ret = st7789_invoff(device);
    ESP_ERROR_CHECK(ret);
    ret = st7789_colmod(device, ST7789_CFG_16_BIT_COLOR);
    ESP_ERROR_CHECK(ret);
    ret = st7789_caset(
        device,
        ADAFRUIT_130_TFT_OFFSET_X,
        127 + ADAFRUIT_130_TFT_OFFSET_X
    );
    ESP_ERROR_CHECK(ret);
    ret = st7789_raset(
        device,
        ADAFRUIT_130_TFT_OFFSET_Y,
        127 + ADAFRUIT_130_TFT_OFFSET_Y
    );
    ESP_ERROR_CHECK(ret);
    uint8_t pos_polarity[16] = {
      0x02, 0x1C, 0x07, 0x12,
      0x37, 0x32, 0x29, 0x2D,
      0x29, 0x25, 0x2B, 0x39,
      0x00, 0x01, 0x03, 0x10,
    };
    ret = st7789_gmctrp1(device, pos_polarity);
    ESP_ERROR_CHECK(ret);
    uint8_t neg_polarity[16] = {
      0x02, 0x1C, 0x07, 0x12,
      0x37, 0x32, 0x29, 0x2D,
      0x29, 0x25, 0x2B, 0x39,
      0x00, 0x01, 0x03, 0x10,
    };
    ret = st7789_gmctrn1(device, neg_polarity);
    ESP_ERROR_CHECK(ret);
    ret = st7789_noron(device);
    ESP_ERROR_CHECK(ret);
    ret = st7789_dispon(device);
    ESP_ERROR_CHECK(ret);
    st7789_backlight(device, ST7789_CFG_BCKL_ON);
}


uint16_t adafruit_130_tft_rgb565(
    uint8_t red,
    uint8_t green,
    uint8_t blue)
{
  return st7789_rgb565(red, green, blue);
}


esp_err_t adafruit_130_tft_paint(
    st7789_device_handle_t device,
    uint16_t * buffer,
    uint8_t x0,
    uint8_t y0,
    uint8_t x1,
    uint8_t y1)
{
    if (x0 > x1) {
      ESP_LOGE(
        ADAFRUIT_130_TFT_TAG,
        "adafruit_130_tft_paint(...) requires x0 <= x1"
      );
      return ESP_ERR_INVALID_ARG;
    }
    if (x0 > 127 || x1 > 127) {
      ESP_LOGE(
        ADAFRUIT_130_TFT_TAG,
        "adafruit_130_tft_paint(...) requires x0 and x1 < 128"
      );
      return ESP_ERR_INVALID_ARG;
    }
    if (y0 > y1) {
      ESP_LOGE(
        ADAFRUIT_130_TFT_TAG,
        "adafruit_130_tft_paint(...) requires y0 <= y1"
      );

    }
    if (y0 > 127 || y1 > 127) {
      ESP_LOGE(
        ADAFRUIT_130_TFT_TAG,
        "adafruit_130_tft_paint(...) requires y0 and y1 < 128"
      );
      return ESP_ERR_INVALID_ARG;
    }
    return st7789_paint(
        device,
        (void *) buffer,
        x0 + ADAFRUIT_130_TFT_OFFSET_X,
        x1 + ADAFRUIT_130_TFT_OFFSET_X,
        y0 + ADAFRUIT_130_TFT_OFFSET_Y,
        y1 + ADAFRUIT_130_TFT_OFFSET_Y
    );
}

esp_err_t adafruit_130_tft_pixel(
    st7789_device_handle_t device,
    uint16_t * buffer,
    uint8_t x,
    uint8_t y)
{
    if (x > 127 || y > 127) {
      ESP_LOGE(
        ADAFRUIT_130_TFT_TAG,
        "adafruit_130_tft_pixel(...) requires x < 128 and y < 128"
      );
      return ESP_ERR_INVALID_ARG;
    }
    esp_err_t ret;
    uint8_t xo = x + ADAFRUIT_130_TFT_OFFSET_X;
    uint8_t yo = y + ADAFRUIT_130_TFT_OFFSET_Y;
    ret = st7789_caset(device, xo, xo);
    if (ret != ESP_OK) {
      ESP_LOGE(
        ADAFRUIT_130_TFT_TAG,
        "adafruit_130_tft_pixel(...) failed on st7789_caset: %s",
        esp_err_to_name(ret)
      );
    } else {
      ret = st7789_raset(device, yo, yo);
      if (ret != ESP_OK) {
        ESP_LOGE(
          ADAFRUIT_130_TFT_TAG,
          "adafruit_130_tft_pixel(...) failed on st7789_raset: %s",
          esp_err_to_name(ret)
        );
      } else {
        ret = st7789_ramwr(device, buffer, 1);
        if (ret != ESP_OK) {
          ESP_LOGE(
            ADAFRUIT_130_TFT_TAG,
            "adafruit_130_tft_pixel(...) failed on st7789_ramwr: %s",
            esp_err_to_name(ret)
          );
        }
      }
    }

    return ret;
}
