# ESP8266-MultiMeter
A MultiMeter built using an ESP8266 (d1 mini lite)<br>
To explain the circuit very simple: there are positive / negative inputs connected to `D0`, `D1`, `D2`, `D5`, `D6`, `D7`, `D8` Those will be posted to the database and then shown in a grafana board<br>

It uses [MySQL](https://www.mysql.com/) as a database, [eclipse mosquitto](https://mosquitto.org/) as MQTT broker, [GoLang](https://go.dev/) to send data recieved from MQTT to the database and [PlatformIO](https://platformio.org/) / Embedded C++ for the [ESP8266 D1-Mini-Lite](https://www.amazon.com/dp/B08HH96RJY) (you can use whatever ESP you want, i dont know if it will work tho)

### Why?
My MultiMeter broke <!-- and I had nothing to do -->

<br><br>

I think this kinda explains how it works, not sure if you can read it tho
<img src="drawing.png" width="600" href="drawing.png">
