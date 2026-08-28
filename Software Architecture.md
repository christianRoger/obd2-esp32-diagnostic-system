# Software Architecture

## Overview

The software architecture is based on a modular embedded firmware running on the **ESP32**.

The system combines automotive communication, diagnostic processing, local data management, graphical user interface and Web-based control within a single embedded platform.

The firmware was designed to separate the main functional layers, making the system easier to maintain, debug and extend.

---

## Software Architecture

```text
                         ESP32 FIRMWARE
                               │
              ┌────────────────┼────────────────┐
              │                │                │
              ▼                ▼                ▼
        CAN / OBD-II       User Interface     Web Server
        Communication       TFT Touchscreen      Wi-Fi
              │                │                │
              ▼                ▼                ▼
        Diagnostic         Local UI          Web API
        Processing         Management         / Pages
              │                │                │
              └────────────────┼────────────────┘
                               │
                               ▼
                       Data Management
                               │
                    ┌──────────┴──────────┐
                    │                     │
                    ▼                     ▼
                 microSD              RAM Index
                    │                     │
                    ├── Vehicle DB        │
                    ├── DTC Database      │
                    ├── CSV Files         │
                    └── Reports           │
```

---

## Firmware Core

The ESP32 acts as the central processing unit of the entire system.

The firmware is responsible for coordinating communication between the vehicle, diagnostic modules, local interface, storage system and Web Interface.

Main firmware responsibilities include:

* System initialization
* Hardware initialization
* CAN controller configuration
* OBD-II communication
* Diagnostic request handling
* CAN frame processing
* DTC decoding
* Vehicle database management
* TFT interface management
* Touchscreen input handling
* microSD file management
* Web Server operation
* Wi-Fi configuration
* Persistent configuration
* OTA firmware updates
* Simulation mode
* Error handling and system diagnostics

---

## CAN and OBD-II Communication

The automotive communication layer uses the **TWAI CAN controller integrated into the ESP32** together with the **SN65HVD230 physical transceiver**.

The firmware manages both transmission and reception of CAN frames.

The diagnostic communication layer is responsible for:

* Building OBD-II requests
* Transmitting diagnostic messages
* Receiving ECU responses
* Filtering diagnostic CAN identifiers
* Parsing response frames
* Extracting PID data
* Decoding diagnostic parameters
* Processing DTC responses

The system can communicate directly with the vehicle without requiring an external **ELM327** interface.

---

## OBD-II Diagnostic Processing

The firmware implements the logic required to communicate with compatible OBD-II systems.

Diagnostic requests are transmitted through the CAN interface and the received responses are parsed by the firmware.

Supported diagnostic parameters include, depending on vehicle support:

* Engine RPM
* Vehicle speed
* Engine coolant temperature
* Throttle position
* Engine load
* Intake manifold pressure
* Intake air temperature
* Ignition timing
* Battery voltage
* Additional powertrain parameters

The architecture allows additional PIDs to be added without redesigning the main application structure.

---

## ISO-TP Communication

The diagnostic communication layer also supports **ISO-TP (ISO 15765-2)** concepts for handling diagnostic messages that exceed the payload capacity of a single CAN frame.

The firmware can process multi-frame diagnostic communication using the appropriate message sequence and payload reconstruction.

This architecture provides a foundation for extending the system toward more advanced automotive diagnostic services.

---

## DTC Processing

The DTC processing layer is responsible for interpreting diagnostic trouble codes received from the vehicle.

The firmware converts the raw diagnostic data into standardized DTC representations and associates the codes with the local diagnostic database.

The resulting information can be displayed through both the TFT interface and the Web Interface.

The local DTC database contains more than **9,400 diagnostic codes**, allowing the system to provide code descriptions without requiring an Internet connection.

---

## Vehicle Database

Vehicle information is stored locally on the **microSD card using CSV files**.

The database architecture is designed to handle a large number of vehicle records while minimizing RAM usage.

The firmware uses:

* CSV-based data storage
* In-memory indexing
* On-demand data loading
* Record filtering
* Vehicle selection
* Parameter lookup

The architecture allows the vehicle database to be expanded without requiring changes to the core firmware logic.

---

## Data Management

The microSD subsystem provides persistent local storage for the application.

The firmware manages multiple types of data, including:

```text
microSD
  │
  ├── Vehicle Database
  │
  ├── DTC Database
  │
  ├── CSV Data
  │
  ├── Configuration
  │
  ├── Diagnostic Reports
  │
  └── System Resources
```

The application loads only the information required for each operation, reducing memory consumption on the ESP32.

---

## TFT User Interface

The local graphical interface is implemented directly on the ESP32.

The TFT touchscreen provides an independent user interface that allows the device to operate without a computer or external application.

Main interface modules include:

* Dashboard
* Vehicle selection
* OBD-II diagnostics
* DTC display
* CAN Monitor
* Settings
* Wi-Fi configuration
* Simulation mode

Touchscreen events are processed by the firmware and mapped to the corresponding application functions.

---

## Web Server

The ESP32 also operates as an embedded **Web Server**, providing remote access to system functions through a browser.

The Web Interface communicates with the firmware through HTTP requests and application endpoints.

Main Web functions include:

* Real-time diagnostic data
* Vehicle selection
* DTC consultation
* CAN Bus monitoring
* Device configuration
* Database management
* Resource upload
* Diagnostic report generation
* OTA firmware update

The Web Interface is integrated directly into the embedded application rather than requiring an external backend server.

---

## CAN Bus Monitor

The firmware includes a dedicated CAN monitoring subsystem.

The CAN Monitor allows the user to inspect traffic present on the CAN network and provides information useful for development and troubleshooting.

Supported functions include:

* CAN frame reception
* CAN frame transmission
* Standard identifiers
* Extended identifiers
* CAN ID monitoring
* Frame frequency analysis
* Passive CAN ID scanning
* Raw frame inspection

The monitor can be used independently of the standard OBD-II diagnostic functions.

---

## Simulation Mode

A dedicated simulation mode is available for development and interface testing.

The simulation layer generates representative diagnostic data without requiring a physical vehicle connection.

This allows developers to test:

* Dashboard rendering
* DTC visualization
* Vehicle selection
* Web Interface functions
* CAN Monitor interface
* Diagnostic reports
* User interaction

Simulation mode reduces the dependency on a connected vehicle during firmware development and UI validation.

---

## Persistent Configuration

System configuration is stored in the ESP32's non-volatile memory.

This allows selected settings to persist across system restarts.

Persistent configuration can be used for parameters such as:

* Wi-Fi settings
* User preferences
* Operating modes
* Device configuration
* Application settings

---

## OTA Firmware Update

The firmware supports **Over-The-Air (OTA)** updates through the Web Interface.

This allows new firmware versions to be uploaded to the ESP32 without requiring a physical USB connection.

The OTA architecture simplifies firmware deployment during development and testing.

---

## Error Handling and Debugging

The firmware includes diagnostic and debugging mechanisms used during development.

Development activities include:

* Serial logging
* CAN communication monitoring
* Hardware diagnostics
* Communication error detection
* Database validation
* File system verification
* Interface testing
* Firmware debugging

These mechanisms help isolate hardware, communication and software-related problems during development.

---

## Modular Design

The software architecture is designed to allow individual subsystems to evolve independently.

Conceptually, the firmware is divided into the following modules:

```text
Application
│
├── System Manager
│
├── CAN / TWAI Driver
│
├── OBD-II Manager
│
├── ISO-TP Layer
│
├── DTC Manager
│
├── Vehicle Database Manager
│
├── microSD Manager
│
├── TFT / Touch UI
│
├── CAN Monitor
│
├── Web Server / API
│
├── Wi-Fi Manager
│
├── OTA Manager
│
└── Simulation Engine
```

This modular structure makes it possible to add new diagnostic functions, communication protocols and interface features while keeping the main firmware organized.

---

## Technologies

### Firmware

* C/C++
* ESP32
* Arduino Framework
* Embedded Systems
* Firmware Development

### Automotive Communication

* CAN Bus
* TWAI
* OBD-II
* ISO-TP
* Diagnostic Communication

### Data Management

* microSD
* CSV
* RAM indexing
* Local database
* HTML report generation

### User Interface

* TFT
* Resistive Touchscreen
* HTML
* CSS
* JavaScript

### Connectivity

* Wi-Fi
* HTTP
* Web Server
* REST-style API
* OTA

---

## Development Approach

The project was developed incrementally, with hardware and software functionality being added and validated through successive firmware revisions.

The development process involved integration testing between:

* ESP32 hardware
* CAN transceiver
* OBD-II interface
* TFT touchscreen
* microSD storage
* Wi-Fi subsystem
* Web Interface
* Diagnostic data processing

The architecture is intended to provide a foundation for future expansion into more advanced automotive diagnostic and CAN analysis functions.

