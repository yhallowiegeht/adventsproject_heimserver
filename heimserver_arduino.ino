#include "SenseBoxMCU.h"
#include "Adafruit_BME680.h"

WiFiServer server(80);

Bee* b = new Bee();

Adafruit_BME680 bme;


void setup() {
  b->connectToWifi("Mehmet Scholl du Hurensohn","Wirhaben1neues");
delay(1000);
  server.begin();
  bme.begin(0x76);
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(0,0);
}

void loop() {

bme.performReading();
WiFiClient client = server.available();
  if (client && client.available()) {
    String request_string = listenClient(client);
    Request request;
    if (parseRequestSafe(request_string, request)) {
    if (request.method == "GET" && request.uri == "/heimserver.html") {
      client.println(buildSuccessfulResponse(request, buildHTML(buildTag("<link rel='stylesheet' type='text/css' href='https://dl.dropbox.com/s/a8x5o6k4hajcowp/style.css'>",""), buildTag("div",
       buildTag("p",
       "Besinnliche Weihnachtszeit!") +buildTag("table",
       buildTag("tr",
       buildTag("th",
       "Sensor") +buildTag("th",
       "Wert")) +buildTag("tr",
       buildTag("td",
       "Temperatur") +buildTag("td",
       String(bme.temperature) + String(" &#176C"))) +buildTag("tr",
       buildTag("td",
       "Luftdruck") +buildTag("td",
       String(bme.pressure / 100) + String(" HPa"))) +buildTag("tr",
       buildTag("td",
       "Luftfeuchtigkeit") +buildTag("td",
       String(bme.humidity) + String(" %")))) +buildTag("img src='https://raw.githubusercontent.com/yhallowiegeht/adventsproject_heimserver/master/senseBox_weihnachten.png'","")))));
    }
    }
    delay(1);
    client.stop();
    delay(1);
  }

}
