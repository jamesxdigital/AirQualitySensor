# Arduino ESP32 Air Quality Sensor

Air Quality Sensor with information dashboard and mobile notification functionality.

Made with an Arduino ESP32, [IFTTT](http://ifttt.com), [io.adafruit](http://io.adafruit.com) and multiple sensors wires, and resistors.

by [jamesmilton.me](http://jamesmilton.me)

# Contents

- [Why?](#why)
- [Design](#design)
  - [Components](#components)
  - [Information](#information)
  - [Schematics](#schematics)
- [Capabilities](#capabilities)
  - [Internal](#internal)
  - [External](#external)
- [Operation](#operation)
  - [Dashboard](#dashboard)
  - [Notifications](#notifications)

# Why?

Air pollution is responsible for 7 million premature deaths around the world each year. When breathed in, pollutants can be absorbed in the blood and travel throughout the body and can damage the heart and other vital organs.

So on that dark note... how do we get better air?!

Air pollution sensors can help individuals control their environments through increased awareness of what's in the air around them. With this awareness, individuals can change their day-to-day life in order to increase the quality of life and overall health of individuals.

# Design

## Components

<img src="images/airqualityraw.jpg" width="80%">

1. #### Arduino ESP32

   Low-power system on a chip (SoC) series with Wi-Fi & dual-mode Bluetooth capabilities. Enginereered for IoT devices.

2. #### MQ-135 Air Quality Hazardous Gas Detection Sensor

This analog sensor can detect a variation of gasses, dependant on the resistance set, which configurable from the dial on the rear of the sensor.

3. #### GP2Y1010AU0F Optical Dust Sensor

Designed to sense dust particles. An infrared emitting diode and a phototransistor are diagonally arranged into this device, to allow it to detect the reflected light of dust in air. Effective in detecting very fine particles found in smoke.

4. #### DC-DC Boost Module

This module provides a stable 5 V from a single Lithium Ion Polymer Battery. (2.5V - 5V) 600 mA TO USB 5 V.

5. #### Lithium Ion Polymer Battery

Thin, light and powerful. The output of the battery ranges from 4.2V when completely charged to 3.7V. This battery has a capacity of 1200mAh for a total of about 4.5 watt-hours.

6. #### Breadboard

A simple terminal array board. Solderless breadboard does not require soldering, it is reusable.

## Information

- Data from the gas sensor is read from A4 analog pin.

- Data from the dust sensor is read from A3 analog pin.

- When the Lithium Ion Polymer Battery battery is connected to the ESP32 and no USB power is available, the USB pin does not provide power.

  - The battery voltage is available at the BAT pin which is 4.2V and reduces to 3.3V when battery exhausts.

  - As the sensors connected need 5V, a DC-DC booster is required to needed to boost the battery voltage to 5V.

  - [DC-DC Boost Module](#dc-dc-boost-module) does this for us.

## Schematics

<img src="images/airqualitybreadboard.png" width="80%">

<img src="images/airqualityschematic.png" width="80%">

# Capabilities

## Internal

Simple pseudocode description of code process:

```java
...
WAKE

Setup analog pin allocation

setup()
  Search for WiFi network
    Connect to WiFi

  Connect to io.adafruit via MQTT
    Connect to io.adafruit dust and gas feeds

  Obtain analog reading from dust sensor from pin A3
    Publish reading to io.adafruit dust sensor feed

  Obtain analog reading from gas sensor from pin A4
    Publish reading to io.adafruit gas sensor feed

  Start sleep activation

loop() //empty as all functioning happens in setup() then goes back to sleep

SLEEP for x minutes
...
```

## External

When the gas and dust sensor data is sent to io.adafruit, the data is stored in individual gas and dust 'feeds'. The data in the feeds can be visualised in a variation of ways on the io.adafruit [dashboard](#dashboard).

Additonally, the data from the feeds can be read by IFTTT (IF This Then That). I created two 'applets' which moniter both gas and dust feeds in io.adafruit.

The first applet sends me a [notification](#notifications) to my phone if the dust sensor reads a value larger than 100.

The second applet sends me a [notification](#notifications) to my phone if the gas sensor reads a value larger than 1200.

<table width="70%" border="0">
  <tr>
    <td colspan="2"><img src="images/airqualityifttt.png" width="100%"></td>
  </tr>
  <tr>
    <td><img src="images/airqualityiftttdust.png"></td>
    <td><img src="images/airqualityiftttgas.png"></td>
  </tr>
</table>

# Operation

## Dashboard

<table width="100%" border="0">
  <tr>
    <td><img src="images/airqualityiodust.png"></td>
  </tr>
  <tr>
    <td>
      On this dashboard, we have two data feeds (gas and dust) - each presented in three different ways:
      <ul>
        <li>Data flow</li>
        <li>Plotted line graph</li>
        <li>Live gauge</li>
      </ul>
      <p>At a stable level, the gas sensor reads around 700. The increase on the most recent value is from deodorant sprayed near the sensor. The dust sensor's stable level is 0. The increase on the most recent value is from a thin object inserted between infrared sensors, imitating dust.</p>
    </td>
  </tr>
</table>

## Notifications

<table width="100%" border="0">
  <tr>
    <td><img src="images/airqualityiphonedust.png"></td>
    <td><img src="images/airqualityiphonegas.png"></td>
  </tr>
  <tr>
    <td>Notification from IFTTT when a high reading of dust is detected.</td>
    <td>Notification from IFTTT when a high reading of gas is detected.</td>
  </tr>
</table>
