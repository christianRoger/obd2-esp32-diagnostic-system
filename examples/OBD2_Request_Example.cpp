```cpp
/*
 * OBD-II Request Example
 * ESP32 TWAI / CAN Bus
 *
 * Demonstrates:
 * - OBD-II Mode 01 requests
 * - PID request construction
 * - CAN frame transmission
 * - Functional addressing using 0x7DF
 *
 * This is a simplified example for educational and
 * portfolio purposes.
 */

#include <Arduino.h>
#include "driver/twai.h"

// -----------------------------------------------------------------------------
// CAN Configuration
// -----------------------------------------------------------------------------

constexpr gpio_num_t CAN_TX_PIN = GPIO_NUM_27;
constexpr gpio_num_t CAN_RX_PIN = GPIO_NUM_35;

constexpr uint32_t OBD_REQUEST_ID = 0x7DF;

// -----------------------------------------------------------------------------
// OBD-II PIDs - Service 01
// -----------------------------------------------------------------------------

constexpr uint8_t PID_ENGINE_RPM     = 0x0C;
constexpr uint8_t PID_VEHICLE_SPEED  = 0x0D;
constexpr uint8_t PID_COOLANT_TEMP   = 0x05;

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

    return true;
}

// -----------------------------------------------------------------------------
// OBD-II Request
// -----------------------------------------------------------------------------

bool sendOBDRequest(uint8_t pid)
{
    twai_message_t message = {};

    // OBD-II functional request address
    message.identifier = OBD_REQUEST_ID;
    message.extd = 0;

    // Standard CAN data frame
    message.data_length_code = 8;

    /*
     * ISO 15765-4 / OBD-II request format:
     *
     * Byte 0 = Number of additional bytes
     * Byte 1 = Service / Mode
     * Byte 2 = PID
     */

    message.data[0] = 0x02;
    message.data[1] = 0x01;
    message.data[2] = pid;

    // Remaining bytes are padding.
    for (uint8_t i = 3; i < 8; i++)
    {
        message.data[i] = 0x00;
    }

    return twai_transmit(
        &message,
        pdMS_TO_TICKS(100)
    ) == ESP_OK;
}

// -----------------------------------------------------------------------------
// Arduino Setup
// -----------------------------------------------------------------------------

void setup()
{
    Serial.begin(115200);

    delay(1000);

    Serial.println();
    Serial.println("==============================");
    Serial.println("ESP32 OBD-II Request Example");
    Serial.println("==============================");

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
    /*
     * The following examples demonstrate how different
     * OBD-II PIDs can be requested through the CAN bus.
     */

    if (sendOBDRequest(PID_ENGINE_RPM))
    {
        Serial.println("RPM request sent");
    }
    else
    {
        Serial.println("RPM request failed");
    }

    delay(1000);

    if (sendOBDRequest(PID_VEHICLE_SPEED))
    {
        Serial.println("Vehicle speed request sent");
    }
    else
    {
        Serial.println("Vehicle speed request failed");
    }

    delay(1000);

    if (sendOBDRequest(PID_COOLANT_TEMP))
    {
        Serial.println("Coolant temperature request sent");
    }
    else
    {
        Serial.println("Coolant temperature request failed");
    }

    delay(2000);
}
```
