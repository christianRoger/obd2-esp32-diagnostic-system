# Hardware & Connections

## Overview

The prototype is based on an **ESP32 DevKit** and an **SN65HVD230 CAN transceiver**, providing direct CAN Bus communication with the vehicle through the **OBD-II interface**.

The hardware architecture also integrates a **TFT touchscreen display**, **microSD storage**, and the ESP32's built-in **Wi-Fi connectivity**.

```text
                    VEHICLE
                       │
                       │ OBD-II
                       │ CAN-H / CAN-L
                       ▼
              ┌──────────────────┐
              │   SN65HVD230     │
              │   CAN Transceiver│
              └────────┬─────────┘
                       │
                       │ TX / RX
                       ▼
              ┌──────────────────┐
              │      ESP32       │
              │    TWAI / CAN    │
              └───────┬──────────┘
                      │
          ┌───────────┼───────────┐
          │           │           │
          ▼           ▼           ▼
        TFT         microSD      Wi-Fi
     Touchscreen    Storage    Web Interface
```

---

## Main Hardware

### ESP32 DevKit

The **ESP32** is the main processing unit of the system.

It is responsible for:

* CAN communication through the integrated TWAI controller
* OBD-II request and response handling
* DTC processing and decoding
* Vehicle database management
* TFT touchscreen interface
* microSD data management
* Web Server operation
* Wi-Fi connectivity
* Firmware and system control

### SN65HVD230

The **SN65HVD230** is used as the physical CAN Bus transceiver between the ESP32 and the vehicle network.

The transceiver provides the electrical interface required to connect the ESP32's CAN controller to the differential **CANH / CANL** bus.

### OBD-II Interface

The system connects to the vehicle through a standard **16-pin OBD-II connector**.

The CAN Bus connection uses the standard OBD-II CAN lines:

* **Pin 6 — CAN High**
* **Pin 14 — CAN Low**

The OBD-II interface provides access to the vehicle's diagnostic CAN network.

---

## Display

The prototype uses a **TFT color display with resistive touchscreen** as the local user interface.

The display provides access to:

* Dashboard
* Vehicle selection
* Diagnostic functions
* DTC information
* CAN Monitor
* Settings
* Wi-Fi configuration
* Simulation mode

Communication between the ESP32 and the display is performed through **SPI**.

---

## microSD Storage

A **microSD interface** is used for local data storage.

The storage system is used for:

* Vehicle database
* Diagnostic code database
* CSV files
* Configuration data
* Diagnostic reports
* Other system resources

This architecture allows the device to operate with a local database without requiring an Internet connection for basic data access.

---

## CAN Communication

The ESP32 communicates with the vehicle using its integrated **TWAI CAN controller** together with the **SN65HVD230 transceiver**.

The system supports:

* Standard CAN identifiers (11-bit)
* Extended CAN identifiers (29-bit)
* CAN frame reception
* CAN frame transmission
* OBD-II diagnostic requests
* Diagnostic response processing
* CAN Bus monitoring
* Passive CAN ID scanning

---

## Communication Architecture

```text
OBD-II Connector
       │
       │ CANH / CANL
       ▼
SN65HVD230 CAN Transceiver
       │
       │ CAN TX / CAN RX
       ▼
ESP32 TWAI Controller
       │
       ├── OBD-II Diagnostics
       ├── DTC Processing
       ├── CAN Monitor
       ├── Vehicle Database
       ├── TFT Interface
       ├── microSD Storage
       └── Wi-Fi / Web Interface
```
