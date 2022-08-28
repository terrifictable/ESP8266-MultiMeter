package main

import (
	"fmt"
	"time"

	mqtt "github.com/eclipse/paho.mqtt.golang"
	_ "github.com/go-sql-driver/mysql"
	"database/sql"
)



var connected bool = false
var database *sql.DB




// ============ MQTT ==============

func messagePubHandler(client mqtt.Client, msg mqtt.Message) {
	fmt.Println(fmt.Sprintf("Received message: %s from topic: %s\n", msg.Payload(), msg.Topic()))
	querrySQL(database, "INSERT INTO Input(pin, voltage) VALUES(\"D1\", 1.5)")
}

func connectHandler(client mqtt.Client) {
	connected = true
	fmt.Println("MQTT Connected")
}

func connectLostHandler(client mqtt.Client, err error) {
	connected = false
	fmt.Println(fmt.Sprintf("Connect lost: %v", err))
}

func messageReceiveHandler(client mqtt.Client, msg mqtt.Message) {
	fmt.Printf("Topic '#/%s' logged...\n", msg.Topic())
	querrySQL(database, "INSERT INTO Input(pin, voltage) VALUES(\"D1\", 1.5)")
}




func connectMQTT(broker string, port int) mqtt.Client {
	opts := mqtt.NewClientOptions()
	opts.AddBroker(fmt.Sprintf("tcp://%s:%d", broker, port))
	opts.SetClientID("/")
	opts.SetUsername("mqtt")
	opts.SetPassword("mqtt")
	// opts.SetDefaultPublishHandler(messagePubHandler)
	opts.OnConnect = connectHandler
	opts.OnConnectionLost = connectLostHandler
	client := mqtt.NewClient(opts)
	if token := client.Connect(); token.Wait() && token.Error() != nil {
		panic(token.Error())
	}
	return client
}

func subscribeTopic(client mqtt.Client, topic string, handler mqtt.MessageHandler) {
	if token := client.Subscribe(topic, 0, handler); token.Wait() && token.Error() != nil {
		panic(token.Error())
	}
}

// ============ MQTT ==============


// ============ MYSQL ==============

func connectDB(driverName string, dataSourceName string) *sql.DB {
	db, err := sql.Open(driverName, dataSourceName)
	if err != nil {
		panic(err)
	}
	db.SetMaxOpenConns(10)
	db.SetMaxIdleConns(5)
	fmt.Println("DB Connected")
	return db
}

func querrySQL(db *sql.DB, sql string) {
	for i := 0; i < 100; i++ {
		go func(I int) {
			rows, err := db.Query(sql)
			if err != nil {
				panic(err)
			}
			_ = rows.Close()
			fmt.Println(I)
		}(i)
	}
}

// ============ MYSQL ==============



func main() {

	fmt.Println("Starting...")

	broker 	:= "mosquitto"
	port 	:= 8883

	client := connectMQTT(broker, port)
	time.Sleep(2 * time.Second)

	database = connectDB("mysql", "root:mysql-pass@tcp(database:3306)/VoltsInput")
	time.Sleep(2 * time.Second)

	subscribeTopic(client, "#", messagePubHandler)

	if connected {
		for {
			time.Sleep(time.Second)
		}
	}

	fmt.Println("Exiting...")

}
