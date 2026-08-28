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
 *
 * This is a simplified example extracted from the concepts
 * used in the OBD-II diagnostic platform.
 */

#include <Arduino.h>
#include "driver/twai.h"

// Example GPIO configuration
constexpr gpio_num_t CAN_TX_PIN = GPIO_NUM_27;
constexpr gpio_num_t CAN_RX_PIN = GPIO_NUM_35;

void setupCAN()
{
    // Configure the TWAI general settings
    twai_general_config_t general_config =
        TWAI_GENERAL_CONFIG_DEFAULT(
            CAN_TX_PIN,
            CAN_RX_PIN,
            TWAI_MODE_NORMAL
        );

    // Configure CAN timing
    twai_timing_config_t timing_config =
        TWAI_TIMING_CONFIG_500KBITS();

    // Accept all CAN messages in this example
    twai_filter_config_t filter_config =
        TWAI_FILTER_CONFIG_ACCEPT_ALL();

    // Install the TWAI driver
    if (twai_driver_install(
            &general_config,
            &timing_config,
            &filter_config) != ESP_OK)
    {
        Serial.println("Error installing TWAI driver");
        return;
    }

    // Start the CAN controller
    if (twai_start() != ESP_OK)
    {
        Serial.println("Error starting TWAI controller");
        return;
    }

    Serial.println("TWAI CAN controller started");
}

void sendCANFrame()
{
    twai_message_t message = {};

    // Standard 11-bit CAN identifier
    message.identifier = 0x123;
    message.extd = 0;

    // CAN data frame
    message.data_length_code = 8;

    message.data[0] = 0x01;
    message.data[1] = 0x02;
    message.data[2] = 0x03;
    message.data[3] = 0x04;
    message.data[4] = 0x05;
    message.data[5] = 0x06;
    message.data[6] = 0x07;
    message.data[7] = 0x08;

    esp_err_t result =
        twai_transmit(&message, pdMS_TO_TICKS(100));

    if (result == ESP_OK)
    {
        Serial.println("CAN frame transmitted");
    }
    else
    {
        Serial.println("CAN transmission failed");
    }
}

void receiveCANFrame()
{
    twai_message_t message;

    // Check for a received frame
    if (twai_receive(
            &message,
            pdMS_TO_TICKS(10)) == ESP_OK)
    {
        Serial.print("CAN ID: 0x");
        Serial.println(message.identifier, HEX);

        Serial.print("DLC: ");
        Serial.println(message.data_length_code);

        Serial.print("DATA: ");

        for (uint8_t i = 0;
             i < message.data_length_code;
             i++)
        {
            if (message.data[i] < 0x10)
                Serial.print("0");

            Serial.print(message.data[i], HEX);
            Serial.print(" ");
        }

        Serial.println();

        if (message.extd)
        {
            Serial.println("Frame type: Extended (29-bit)");
        }
        else
        {
            Serial.println("Frame type: Standard (11-bit)");
        }
    }
}

void setup()
{
    Serial.begin(115200);

    delay(1000);

    Serial.println();
    Serial.println("ESP32 CAN Communication Example");

    setupCAN();
}

void loop()
{
    // Example transmission
    sendCANFrame();

    // Check for received CAN frames
    receiveCANFrame();

    delay(1000);
}
```

