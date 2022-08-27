package main

import (
    "fmt"
    mqtt "github.com/eclipse/paho.mqtt.golang"
    "time"
)



var connected bool = false




func messagePubHandler(client mqtt.Client, msg mqtt.Message) {
	fmt.Println(fmt.Sprintf("Received message: %s from topic: %s\n", msg.Payload(), msg.Topic()))
}

func connectHandler(client mqtt.Client) {
    connected = true
	fmt.Println("Connected")
}

func connectLostHandler(client mqtt.Client, err error) {
	fmt.Println(fmt.Sprintf("Connect lost: %v", err))
    connected = false
}



func connect(broker string, port int) {
    opts := mqtt.NewClientOptions()
    opts.AddBroker(fmt.Sprintf("tcp://%s:%d", broker, port))
    opts.SetClientID("/")
    opts.SetUsername("mqtt")
    opts.SetPassword("mqtt")
    opts.SetDefaultPublishHandler(messagePubHandler)
    opts.OnConnect = connectHandler
    opts.OnConnectionLost = connectLostHandler
    client := mqtt.NewClient(opts)
    if token := client.Connect(); token.Wait() && token.Error() != nil {
        panic(token.Error())
    }
    return client
}


func main() {

    fmt.Println("Starting...")

	broker 	    := "mosquitto"
    port 	    := 8883

    client := connect(broker, port);
    
    time.Sleep(2 * time.Second)


    if (connected) {
        for {} // infinite "`while`" loop
    }

    fmt.Println("Exiting...")

}
