package main

import (
    "fmt"
    mqtt "github.com/eclipse/paho.mqtt.golang"
)

func messagePubHandler(client mqtt.Client, msg mqtt.Message) {
	fmt.Printf("Received message: %s from topic: %s\n", msg.Payload(), msg.Topic())
}

func connectHandler(client mqtt.Client) {
	fmt.Println("Connected")
}

func connectLostHandler(client mqtt.Client, err error) {
	fmt.Printf("Connect lost: %v", err)
}


func main() {

	broker 	:= "localhost"
    port 	:= 8883


    opts := mqtt.NewClientOptions()
    opts.AddBroker(fmt.Sprintf("tcp://%s:%d", broker, port))
    opts.SetClientID("/")
    // opts.SetUsername("mqtt")
    // opts.SetPassword("mqtt")
    opts.SetDefaultPublishHandler(messagePubHandler)
    opts.OnConnect = connectHandler
    opts.OnConnectionLost = connectLostHandler
    client := mqtt.NewClient(opts)
    if token := client.Connect(); token.Wait() && token.Error() != nil {
        panic(token.Error())
	}

}
