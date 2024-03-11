#pragma once

#define SSID0 "AAB-DEV"
#define SSID1 "ALCANSWIFI"
#define SSID2 "WECLIXWIFI"
#define SSID3 "Automacao"
#define SSID4 "Weclix"
#define PASSWORD0 "AAB_DEV1"
#define PASSWORD1 "meunomeInteiroTudojunto"
#define PASSWORD2 "meunomeInteiroTudojunto"
#define PASSWORD3 "meunomeinteirotudojunto"
#define PASSWORD4 "meunomeinteirotudojunto"

#define MQTT_URI "20.127.210.50"
#define MQTT_PORT 1883
#define MQTT_QOS 2
#define MQTT_RETAIN false

#define CLIENT_ID (char *)"clientID"
#define MQTT_CLIENT_USER "pcd_meteor"
#define MQTT_CLIENT_PASS "pcd_meteor@123"

#define MQTT_TOPIC (char *)"pcd-meteor"
#define MQTT_TOPIC_TO_SITE (char *)"pcd-meteor/site"

#define MQTT_SUBTOPIC_COMMAND (char *)"/command"
#define MQTT_SUBTOPIC_STATUS (char *)"/status"
#define MQTT_SUBTOPIC_BATTERY (char *)"/battery"
#define MQTT_SUBTOPIC_INFO (char *)"/info"
#define MQTT_SUBTOPIC_EVENT (char *)"/event"

#define MQTT_SUBTOPIC_TEMPERATURE (char *)"/temp"
#define MQTT_SUBTOPIC_HUMIDITY (char *)"/humidity"
#define MQTT_SUBTOPIC_PRESSURE (char *)"/pressure"
#define MQTT_SUBTOPIC_DEWPOINT (char *)"/dewpoint"
#define MQTT_SUBTOPIC_BATTERY_LEVEL (char *)"/level"
#define MQTT_SUBTOPIC_BATTERY_CRITICAL (char *)"/critical"
#define MQTT_SUBTOPIC_BATTERY_VOLTAGE (char *)"/voltage"
#define MQTT_SUBTOPIC_BATTERY_CHARGING (char *)"/charging"
#define MQTT_SUBTOPIC_BATTERY_CHARGED (char *)"/charged"
#define MQTT_SUBTOPIC_INFO_MANUFACTORY (char *)"/manufactory"
#define MQTT_SUBTOPIC_INFO_FIRMWARE_VERSION (char *)"/fwVer"
#define MQTT_SUBTOPIC_INFO_MODEL (char *)"/model"
#define MQTT_SUBTOPIC_INFO_MAC_ADDRESS (char *)"/MACaddr"
#define MQTT_SUBTOPIC_INFO_CLIENTID (char *)"/clientID"
