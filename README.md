# ESP8266-MultiMeter
A MultiMeter built using an ESP8266 (d1 mini lite)<br>
To explain the circuit very simple: there are positive / negative inputs connected to `D0`, `D1`, `D2`, `D5`, `D6`, `D7`, `D8` Those will be posted to the database and then shown in a grafana board<br>

It uses [MySQL](https://www.mysql.com/) as a database, [eclipse mosquitto](https://mosquitto.org/) as MQTT broker, [GoLang](https://go.dev/) to send data recieved from MQTT to the database and [PlatformIO](https://platformio.org/) / Embedded C++ for the [ESP8266 D1-Mini-Lite](https://www.amazon.com/dp/B08HH96RJY) (you can use whatever ESP you want, i dont know if it will work tho)


### Bugs
Current Bugs:
 - Go will add about 200 new entries to database when recieves something trough mqtt
 - Go output is weird

### ToDos
 - Dimm LED's
 - Fix cables
 - Fix Go

### Features
 - ESP8266 programm to get voltage input data for D0-D8 pins and send them to MQTT Server
 - Mosquitto/MQTT, MySQL, Grafana, Adminer and GoBackend, all inside a single docker container / docker-compose "container"
 - GoBackend that receives data from MQTT and posts it to the MySQL Database


### Why?
My MultiMeter broke <!-- and I had nothing to do -->

<br><br>

I think this kinda explains how it works, not sure if you can read it tho
<img src="drawing.png" width="600" href="drawing.png">

<!-- <img src="esp.png" width="600" href="esp.png"> -->
