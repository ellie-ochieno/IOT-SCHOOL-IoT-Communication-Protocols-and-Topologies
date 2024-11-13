# AE-ALX-IoT-School
## Angaza Elimu - ALX IoT School Training

### Session 16: Data Science and ML for IoT - Part 1

This guide provides a comprehensive setup for IoT beginner students to gather, monitor, and analyze data using ThingSpeak, ESP32, and Google Colab. In this session, you will learn to create a ThingSpeak channel, connect an ESP32 microcontroller, and analyze collected data using Google Colab.

---

### Table of Contents
1. [Setting up a ThingSpeak Account and Creating a New Channel](#1-setting-up-a-thingspeak-account-and-creating-a-new-channel)
2. [Connecting ThingSpeak to ESP32 and Sending DHT22 Data to ThingSpeak](#2-connecting-thingspeak-to-esp32-and-sending-dht22-data-to-thingspeak)
3. [Setting up Google Colab](#3-setting-up-google-colab)
4. [Connecting ThingSpeak to Google Colab](#4-connecting-thingspeak-to-google-colab)
5. [Practical Activity Code Repository](#5-practical-activity-code-repository)

---

### 1. Setting up a ThingSpeak Account and Creating a New Channel
ThingSpeak is an IoT analytics platform that allows us to collect, visualize, and analyze live data streams. We'll start by creating a new channel in ThingSpeak.

- **Step 1**: Create a ThingSpeak account (if you don’t have one) and log in.
- **Step 2**: Create a new channel for collecting data from the DHT22 sensor.
  - **Note**: For the DHT22 sensor, we’ll only require **two fields**:
    - **Field1** for **temperature**
    - **Field2** for **humidity**
  - **Important**: Maintain the field names exactly as **temperature** and **humidity** since the provided Python scripts use these specific names as filter keywords when reading from the ThingSpeak API. If you want to use different field names, make sure to update the Python scripts accordingly.

- **Video Guide**: Follow along with this YouTube tutorial to create your ThingSpeak channel: [ThingSpeak Channel Setup](https://youtu.be/8fcQuMRSNBw).

---

### 2. Connecting ThingSpeak to ESP32 and Sending DHT22 Data to ThingSpeak
To connect the ESP32 and send data from the DHT22 sensor to ThingSpeak, we’ll use the **data_collect.ino** Arduino file located in the `data_collect` folder available in the repository. This file configures the ThingSpeak connection details and collects data from the DHT22 sensor.

- **API Key**: Only the **ThingSpeak Write API Key** is required for sending data to ThingSpeak.
- **WiFi Credentials**: Ensure to provide the correct **WiFi SSID** and **PASSWORD** for the ESP32 to connect to your network. These details, along with the ThingSpeak connection credentials, are stored in the `secrets.h` file.
- **ThingSpeak URL**: Keep the **THINGSPEAK_URL** as is to maintain proper connectivity.

- **Video Guide**: Watch this YouTube video for a step-by-step guide on connecting ThingSpeak to ESP32 and sending DHT22 data: [ESP32 ThingSpeak Setup](https://youtu.be/f4ps1oCYeKk).

---

### 3. Setting up Google Colab
Google Colab is a free platform for running Python code in the cloud, ideal for data science and machine learning tasks. We’ll use it to analyze data collected in ThingSpeak.

- **Step 1**: Open Google Colab (you’ll need a Google account).
- **Step 2**: Download all Python files provided in the repository and upload them to your Google Colab environment for analysis.
  - These files help you connect to ThingSpeak, retrieve data, and perform basic data visualization and anomaly detection.

- **Video Guide**: Follow this introductory YouTube video on getting started with Google Colab: [Google Colab Basics](https://youtu.be/RLYoEyIHL6A).

---

### 4. Connecting ThingSpeak to Google Colab
After setting up ThingSpeak and Google Colab, we need to connect them so that we can fetch data from ThingSpeak directly into Colab for analysis.

- **Step 1**: Under the ThingSpeak channel you created, locate your **Channel ID** and **Read API Key**.
- **Step 2**: In the Python scripts, enter your Channel ID and API Key where prompted to establish a connection with ThingSpeak.
  - This connection will enable real-time data retrieval for further analysis in Google Colab, including data visualization and anomaly detection.

---

### 5. Practical Activity Code Repository
To access the practical code for this session, refer to the following GitHub repository:
- [AE-ALX-IoT-School GitHub Repository](https://github.com/ellie-ochieno/AE-ALX-IoT-School)

This repository contains all necessary files, including:
  - **data_collect/data_collect.ino**: For collecting data from DHT22 and sending it to ThingSpeak.
  - **data_collect/secrets.h**: For configuring WiFi and ThingSpeak credentials.
  - **Python scripts**: For retrieving, analyzing, and visualizing data in Google Colab.

---

Following this guide will help you set up a complete IoT data pipeline, from data collection to visualization and anomaly detection, giving you a hands-on introduction to data science applications in IoT.
