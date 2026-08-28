```cpp
/*
 * OBD-II Request Example
 * ESP32 TWAI / CAN Bus
 *
 * Demonstrates:
 * - OBD-II Mode 01 request
 * - PID request construction
 * - CAN frame transmission
 *
 * This is a simplified example for educational and
 * portfolio purposes.
 */

#include <Arduino.h>
#include "driver/twai.h"

constexpr gpio_num_t CAN_TX_PIN = GPIO_NUM_27;
constexpr gpio_num_t CAN_RX_PIN = GPIO_NUM_35;

// Standard OBD-II functional request ID
constexpr uint32_t OBD_REQUEST_ID = 0x7DF;

// Example PIDs
constexpr uint8_t PID_ENGINE_RPM = 0x0C;
constexpr uint8_t PID_VEHICLE_SPEED = 0x0D;
constexpr uint8_t PID_COOLANT_TEMP = 0x05;

bool sendOBDRequest(uint8_t pid)
{
    twai_message_t message = {};

    message.identifier = OBD_REQUEST_ID;
    message.extd = 0;
    message.data_length_code = 8;

    // ISO 15765-4 / OBD-II request
    message.data[0] = 0x02;  // Number of additional data bytes
    message.data[1] = 0x01;  // Service / Mode 01
    message.data[2] = pid;

    // Remaining bytes are filled with zero
    for (uint8_t i = 3; i < 8; i++)
    {
        message.data[i] = 0x00;
    }

    return twai_transmit(
        &message,
        pdMS_TO_TICKS(100)
    ) == ESP_OK;
}

void setupCAN()
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
        Serial.println("Error installing TWAI driver");
        return;
    }

    if (twai_start() != ESP_OK)
    {
        Serial.println("Error starting TWAI controller");
        return;
    }

    Serial.println("TWAI CAN controller started");
}

void setup()
{
    Serial.begin(115200);

    delay(1000);

    Serial.println();
    Serial.println("ESP32 OBD-II Request Example");

    setupCAN();
}

void loop()
{
    // Request engine RPM
    if (sendOBDRequest(PID_ENGINE_RPM))
    {
        Serial.println("OBD-II RPM request sent");
    }
    else
    {
        Serial.println("OBD-II request failed");
    }

    delay(1000);

    // Request vehicle speed
    if (sendOBDRequest(PID_VEHICLE_SPEED))
    {
        Serial.println("OBD-II speed request sent");
    }
    else
    {
        Serial.println("OBD-II request failed");
    }

    delay(1000);

    // Request coolant temperature
    if (sendOBDRequest(PID_COOLANT_TEMP))
    {
        Serial.println("OBD-II coolant temperature request sent");
    }
    else
    {
        Serial.println("OBD-II request failed");
    }

    delay(2000);
}
```

