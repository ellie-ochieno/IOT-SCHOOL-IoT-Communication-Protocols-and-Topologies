# Angaza Elimu Smarthome - RGBLEDControl Library

The **RGBLEDControl** library, developed by the Angaza Elimu IoT Team, is designed for detecting motion using a PIR (Passive Infrared) sensor and sending updates to a specified server via HTTP POST requests. The library works with the ESP32 microcontroller and provides secure communication using SSL certificates, making it ideal for IoT smart home security systems.

## Features
 - **Motion Detection:** Detects motion using a PIR (Passive Infrared) sensor.
 - **WiFi Connectivity:** Connects to a specified WiFi network.
 - **Secure Communication:** Uses SSL certificates to secure HTTP requests.
 - **RGB LED Control:** Configures an RGB LED to visually indicate motion detection status.
 - **HTTP POST Requests:** Sends motion status (motion detected or no motion) to a server using HTTP POST.


## Installation

 Follow these steps to install the **RGBLEDControl** library in your Arduino IDE:

### Step 1: Clone the Repository
    Clone the `iot-smarthome.v2-firmware` repository from GitHub:
    ```bash
    git clone https://github.com/Angaza-Elimu/iot-smarthome.v2-firmware.git
    ```
    - With this approach, the whole repository files will be available on your local machine.

### Step 2: Download the Library

 - Download the zipped file of the **RGBLEDControl** library from the repository.

### Step 3: Install the Library in Arduino IDE

 1. Open Arduino IDE.
 2. Navigate to `Sketch` -> `Include Library` -> `Add .ZIP Library...`
 3. Select the downloaded `RGBLEDControl.zip` file.
 4. The library will now be available in your Arduino IDE.

 Alternatively, you can manually copy the unzipped folder into the `libraries` directory in your Arduino IDE installation.

## Usage

 Access Example Files
    - After the sensor library is installed, a basic `.ino` example file will be available for testing and getting started.
    - To access the example file:
      - Go to `File` -> `Examples` -> `Installed_Library_Name`
      - Open the example `.ino` file.
    - Load the example sketch, modify the necessary parameters:
       - Sensor `pins` under `pin_configuration.h` file,
       - `WiFi credentials` and `API Key` under `secrets.h` file, and upload it to your ESP32 board.

    - Alternatively, you can navigate directly to the `examples` folder in each sensor library directory within the GitHub repository.

 ### NOTE
   - Every `.ino` file has a `cert.h` file attached.
     - This holds server certificate for secure connection - `DO NOT` edit it

 ### Additional Notes

   - **WiFi Configuration**: Ensure that you have configured the correct `ssid` and `password` values in your firmware for WiFi connectivity.
   - **Secure Communication**: This firmware supports secure HTTP communication. Make sure NOT to tamper with the provided root certificate for secure connections when required.
   - **Platform connection**: For successful platform connection, ensure to provide a valid project `API Key`(generated after new project creation).


### Sensor Connection

  - Configure the sensor and other control modules connection from the `pin_configuration.h` file


     ---

   **Parameters:**
     - **server_url:** The URL to which smoke data is posted.
     - **root_cacert:** The root certificate for secure communication (HTTPS).
     - **api_key:** The API key for authenticating with the server.
     - **onboardLedPin:** Pin connected to the onboard LED for status indication.
     - **redPin, greenPin, bluePin:** RGBLED connection pins.


## Key Class Methods

  1. `RGBLEDControl()`
      - Constructor that initializes the library with the necessary parameters.
      ```cpp
      RGBLEDControl(const char* ssid, const char* password, const char* serverUrl, const char* rootCert, const String& apiKey, int pirPin, int onboardLedPin, int redPin, int greenPin, int bluePin);
      ```
  2. `begin()`
      - Initializes WiFi, sets up the PIR sensor pin, and configures the RGB LED pins. This function also connects to the server securely using SSL certificates.
      ```cpp
      void begin();
      ```

  3. `monitorPIRSensor()`
      - Continuously monitors the PIR sensor for motion. If motion is detected, it sends an HTTP POST request to the server and controls the RGB LED accordingly.
      ```cpp
      void monitorPIRSensor();
      ```

  4. `httpPOSTRequest()`
      - Sends a POST request to the server with motion status data.
      ```cpp
      String httpPOSTRequest(const String& data);
      ```

  4. `printWiFiStatus()`
      - Prints the current WiFi connection status, including the device's IP address.
      ```cpp
      void printWiFiStatus();
      ```

  ---

  Feel free to open an issue or submit a pull request to enhance or report problems with the **RGBLEDControl** library.

  Happy Coding! 😊
