# ESP8266-MultiMeter
A MultiMeter built using an ESP8266 (d1 mini lite)<br>
To explain the circuit very simple: there are positive / negative inputs connected to `D0`, `D1`, `D2`, `D5`, `D6`, `D7`, `D8` Those will be posted to the database and then shown in a grafana board<br>

It uses [MySQL](https://www.mysql.com/) as a database, [eclipse mosquitto](https://mosquitto.org/) as MQTT broker, [GoLang](https://go.dev/) to send data recieved from MQTT to the database and [PlatformIO](https://platformio.org/) / Embedded C++ for the [ESP8266 D1-Mini-Lite](https://www.amazon.com/dp/B08HH96RJY) (you can use whatever ESP you want, i dont know if it will work tho)


### How to use
Its simple: 
1. Install docker: [here is a guide on how to do that](https://docs.docker.com/engine/install/)
2. Run `make` in the root directory of the project, this will install all images needed and run everything you need automatically
3. Create `config.h` file in `ESP/src` folder using the [sample file](./ESP/src/config.h.sample), this will contain all data that the ESP needs to connect to your "`docker server`"
4. Wire your ESP up
    - connect `D3` and `D4` to LED's (`+`) and connect the `-` of the LED's to the ESP's `GND` pin
    - connect `D0`, `D1`, `D2`, `D5`, `D6`, `D7` and `D8` to cables, those will be the inputs that are going to be measured
5. upload the contents of the [`ESP`](./ESP/) folder to an ESP (8266 D1 Mini) using PlatformIO
6. Thats it, it should now work fine and run without any problems


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

<img src="grafana.png" width="1200">

### Why?
My MultiMeter broke <!-- and I had nothing to do -->

<br><br>

I think this kinda explains how it works
<img src="drawing.png" width="600" href="drawing.png">

<!-- <img src="esp.png" width="600" href="esp.png"> -->
