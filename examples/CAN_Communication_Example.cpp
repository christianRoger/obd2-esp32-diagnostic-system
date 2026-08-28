```cpp
/*
 * CAN Communication Example
 * ESP32 TWAI / CAN Bus
 *
 * Demonstrates:
 * - TWAI driver configuration
 * - CAN frame transmission
 * - CAN frame reception
 * - Standard and extended CAN identifiers
 * - Basic CAN frame inspection
 *
 * This example demonstrates selected CAN communication concepts
 * used in the OBD-II diagnostic platform.
 */

#include <Arduino.h>
#include "driver/twai.h"

// -----------------------------------------------------------------------------
// CAN GPIO Configuration
// -----------------------------------------------------------------------------

constexpr gpio_num_t CAN_TX_PIN = GPIO_NUM_27;
constexpr gpio_num_t CAN_RX_PIN = GPIO_NUM_35;

constexpr uint32_t CAN_BITRATE = 500000;

// -----------------------------------------------------------------------------
// CAN Initialization
// -----------------------------------------------------------------------------

bool setupCAN()
{
    twai_general_config_t general_config =
        TWAI_GENERAL_CONFIG_DEFAULT(
            CAN_TX_PIN,
            CAN_RX_PIN,
            TWAI_MODE_NORMAL
        );

    twai_timing_config_t timing_config =
        TWAI_TIMING_CONFIG_500KBITS();

    twai_filter_config_t filter_config =
        TWAI_FILTER_CONFIG_ACCEPT_ALL();

    if (twai_driver_install(
            &general_config,
            &timing_config,
            &filter_config) != ESP_OK)
    {
        Serial.println("ERROR: Failed to install TWAI driver");
        return false;
    }

    if (twai_start() != ESP_OK)
    {
        Serial.println("ERROR: Failed to start TWAI controller");
        return false;
    }

    Serial.println("TWAI CAN controller started");
    Serial.print("CAN bitrate: ");
    Serial.print(CAN_BITRATE);
    Serial.println(" bit/s");

    return true;
}

// -----------------------------------------------------------------------------
// CAN Frame Transmission
// -----------------------------------------------------------------------------

void sendCANFrame()
{
    twai_message_t message = {};

    // Standard 11-bit CAN identifier
    message.identifier = 0x123;
    message.extd = 0;

    // Data frame with 8-byte payload
    message.data_length_code = 8;

    for (uint8_t i = 0; i < 8; i++)
    {
        message.data[i] = i + 1;
    }

    esp_err_t result =
        twai_transmit(
            &message,
            pdMS_TO_TICKS(100)
        );

    if (result == ESP_OK)
    {
        Serial.println("CAN frame transmitted");
    }
    else
    {
        Serial.println("CAN transmission failed");
    }
}

// -----------------------------------------------------------------------------
// CAN Frame Reception
// -----------------------------------------------------------------------------

void receiveCANFrame()
{
    twai_message_t message = {};

    if (twai_receive(
            &message,
            pdMS_TO_TICKS(10)) != ESP_OK)
    {
        return;
    }

    Serial.print("CAN ID: 0x");

    if (message.extd)
    {
        Serial.print(message.identifier, HEX);
        Serial.println(" (Extended 29-bit)");
    }
    else
    {
        Serial.print(message.identifier, HEX);
        Serial.println(" (Standard 11-bit)");
    }

    Serial.print("DLC: ");
    Serial.println(message.data_length_code);

    Serial.print("DATA: ");

    for (uint8_t i = 0;
         i < message.data_length_code;
         i++)
    {
        if (message.data[i] < 0x10)
        {
            Serial.print("0");
        }

        Serial.print(message.data[i], HEX);
        Serial.print(" ");
    }

    Serial.println();
}

// -----------------------------------------------------------------------------
// Arduino Setup
// -----------------------------------------------------------------------------

void setup()
{
    Serial.begin(115200);

    delay(1000);

    Serial.println();
    Serial.println("================================");
    Serial.println("ESP32 CAN Communication Example");
    Serial.println("================================");

    if (!setupCAN())
    {
        Serial.println("CAN initialization failed");
    }
}

// -----------------------------------------------------------------------------
// Arduino Main Loop
// -----------------------------------------------------------------------------

void loop()
{
    // Demonstration CAN transmission
    sendCANFrame();

    // Check for incoming CAN frames
    receiveCANFrame();

    delay(1000);
}
```
