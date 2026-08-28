# Sistema di Diagnostica OBD-II – ESP32

## Panoramica

**Sistema portatile di diagnostica elettronica automotive sviluppato su piattaforma ESP32**, progettato per interfacciarsi direttamente con il veicolo tramite **CAN Bus / OBD-II**.

Il progetto integra hardware, firmware, comunicazione CAN, gestione di database, interfaccia touchscreen e Web Interface in un'unica piattaforma embedded.

L'obiettivo è realizzare uno strumento in grado di acquisire e visualizzare i principali parametri diagnostici del veicolo, leggere e decodificare i codici di errore e fornire strumenti di analisi e monitoraggio del bus CAN.

---

## Caratteristiche principali

* Diagnostica automotive tramite OBD-II
* Comunicazione CAN Bus tramite controller TWAI dell'ESP32
* Lettura dei parametri diagnostici del veicolo
* Lettura e decodifica dei codici DTC
* Possibilità di cancellazione dei codici di errore
* Database dei veicoli memorizzato su microSD
* Database con oltre **9.400 codici diagnostici**
* Display TFT a colori con touchscreen resistivo
* Dashboard per la visualizzazione dei parametri in tempo reale
* CAN Bus Monitor
* Funzione di analisi e rilevamento dei frame presenti sulla rete CAN
* Interfaccia Web per configurazione e monitoraggio
* Gestione dei dati tramite file CSV
* Generazione e archiviazione di report diagnostici
* Aggiornamento firmware tramite OTA
* Modalità di simulazione per sviluppo e test dell'interfaccia

---

## Architettura del sistema

Il sistema è stato progettato con un'architettura modulare che integra diversi livelli hardware e software.

```text
                     VEICOLO
                        │
                        │ CAN / OBD-II
                        ▼
                ┌─────────────────┐
                │   CAN Bus       │
                │   Transceiver   │
                └────────┬────────┘
                         │
                         ▼
                ┌─────────────────┐
                │      ESP32      │
                │  TWAI / FW      │
                └───────┬─────────┘
                        │
          ┌─────────────┼─────────────┐
          │             │             │
          ▼             ▼             ▼
       TFT Touch      microSD       Wi-Fi
          │             │             │
          ▼             ▼             ▼
      Interface      Database      Web Interface
      locale        veicoli/DTC     Dashboard
```

---

## Diagnostica OBD-II

La comunicazione con il veicolo viene effettuata direttamente tramite il controller **TWAI integrato nell'ESP32**, senza utilizzare un adattatore ELM327 come intermediario.

Il firmware gestisce la comunicazione CAN e l'elaborazione delle risposte diagnostiche.

### Parametri monitorati

Tra i principali parametri gestiti dal sistema:

* Regime motore (RPM)
* Velocità del veicolo
* Temperatura del motore
* Posizione acceleratore
* Carico motore
* Pressione MAP
* Temperatura aria aspirata
* Anticipo di accensione
* Tensione batteria
* Parametri specifici del powertrain

Il sistema supporta inoltre la gestione di comunicazioni diagnostiche multi-frame tramite **ISO-TP**.

---

## Gestione dei codici DTC

Il sistema è progettato per leggere e interpretare i **Diagnostic Trouble Codes (DTC)**.

I codici vengono associati alle relative informazioni presenti nel database e possono essere visualizzati direttamente sull'interfaccia del dispositivo.

Il database diagnostico contiene oltre **9.400 codici di errore**, permettendo una consultazione locale senza dipendere da una connessione Internet.

---

## Database dei veicoli

Le informazioni relative ai veicoli sono gestite tramite file **CSV memorizzati sulla scheda microSD**.

Il database contiene informazioni relative a:

* Marca
* Modello
* Anno
* Motorizzazione
* Potenza
* Combustibile
* Informazioni di identificazione
* Parametri del powertrain

L'architettura utilizza un sistema di indicizzazione in memoria e caricamento dei dati su richiesta, permettendo di gestire un database di grandi dimensioni anche con le risorse limitate di un microcontrollore.

---

## Interfaccia TFT Touchscreen

Il dispositivo dispone di un'interfaccia grafica locale tramite **display TFT touchscreen**.

Le principali schermate comprendono:

* Dashboard
* Selezione del veicolo
* Diagnostica / DTC
* Impostazioni
* CAN Monitor
* Wi-Fi

L'interfaccia permette di utilizzare il sistema direttamente dal dispositivo senza la necessità di un computer esterno.

---

## Interfaccia Web

L'ESP32 integra inoltre un **Web Server**, permettendo di accedere al sistema tramite browser attraverso la rete Wi-Fi.

La Web Interface comprende funzioni per:

* Visualizzazione dei parametri OBD
* Selezione e gestione dei veicoli
* Consultazione dei DTC
* Monitoraggio del CAN Bus
* Configurazione del dispositivo
* Gestione del database
* Upload di immagini
* Generazione e download dei report
* Aggiornamento firmware tramite OTA

L'interfaccia Web è stata sviluppata come applicazione integrata nel firmware del dispositivo.

---

## CAN Bus Monitor

Oltre alla diagnostica OBD-II, il progetto include una modalità **CAN Bus Monitor**.

Questa funzione permette di:

* Visualizzare i frame CAN ricevuti
* Monitorare gli identificativi presenti sul bus
* Gestire frame standard ed extended
* Analizzare la frequenza di ricezione
* Effettuare una scansione passiva degli ID presenti sulla rete

La modalità Monitor è stata sviluppata come strumento di supporto per analisi e troubleshooting delle comunicazioni CAN.

---

## Hardware

Componenti principali utilizzati nel prototipo:

* ESP32 DevKit
* Transceiver CAN **SN65HVD230**
* Display TFT touchscreen
* Modulo microSD
* Interfaccia Wi-Fi integrata nell'ESP32
* Circuiti e cablaggi di interfacciamento

Il sistema è stato assemblato e testato come prototipo funzionante su banco.

---

## Software e tecnologie

### Embedded

* ESP32
* Arduino Framework
* C/C++
* Firmware embedded
* TWAI / CAN
* ISO-TP

### Hardware

* CAN Bus
* OBD-II
* SN65HVD230
* TFT Touchscreen
* microSD
* SPI

### Web

* HTML
* CSS
* JavaScript
* WebServer
* REST API

### Gestione dati

* CSV
* Database locale su microSD
* Indicizzazione in RAM
* Generazione di report HTML

---

## Funzionalità avanzate

Il progetto include diverse funzionalità sviluppate per rendere il sistema più flessibile e utilizzabile durante le fasi di sviluppo e test.

### Modalità simulazione

È presente una modalità di simulazione che permette di testare l'interfaccia e le funzioni del sistema anche senza collegamento a un veicolo reale.

### Aggiornamento OTA

Il firmware può essere aggiornato tramite la Web Interface utilizzando la funzione **Over-The-Air (OTA)**.

### Configurazione persistente

Le impostazioni del dispositivo vengono memorizzate nella memoria non volatile dell'ESP32, permettendo di conservarle tra un riavvio e l'altro.

---

## Test e validazione

Durante lo sviluppo sono state effettuate attività di:

* Test della comunicazione CAN
* Verifica della ricezione dei frame
* Test della comunicazione OBD-II
* Verifica della decodifica dei parametri
* Test di lettura dei DTC
* Test del database
* Test dell'interfaccia touchscreen
* Test della Web Interface
* Test della gestione microSD
* Debug firmware
* Verifica dell'integrazione hardware/software

Il sistema è stato sviluppato e testato progressivamente attraverso diverse revisioni del firmware e dell'interfaccia.

---

## Obiettivi del progetto

Il progetto nasce dall'interesse per l'integrazione tra **elettronica, sistemi embedded e diagnostica automotive**.

L'obiettivo è continuare a sviluppare la piattaforma aggiungendo nuove funzionalità diagnostiche, ampliando il supporto ai diversi veicoli e migliorando gli strumenti di analisi del CAN Bus.

---

## Tecnologie

**ESP32 · C/C++ · Embedded Systems · Firmware · CAN Bus · OBD-II · ISO-TP · TWAI · TFT Touchscreen · microSD · Wi-Fi · HTML · CSS · JavaScript · REST API · Automotive Electronics**

---

## 📸 Interfaccia del sistema

### Dashboard

![Dashboard principale](images/dashboard-01.jpg)

![Dashboard telemetria](images/dashboard-02.jpg)

### Selezione veicolo

![Selezione veicolo](images/dashboard-auto.jpg)

### Impostazioni

![Impostazioni](images/settings-01.jpg)

![Impostazioni avanzate](images/settings-02.jpg)

### Modalità simulazione

![Modalità simulazione](images/simulation-mode.jpg)

### CAN Monitor

![CAN Monitor](images/can-monitor-01.jpg)

![CAN Monitor - Network Scan](images/can-monitor-02.jpg)

### Report diagnostico

![Report diagnostico](images/diagnostic-report.jpg)
