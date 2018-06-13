# launchpad-traffic-lights

# Einrichten der Arduino IDE um Kompilat erstellen zu können
- Bibliotheken *EPS8266HTTPClient* und *ESP8266WiFi* zur IDE hinzugefügen
- *esp8266* im Boardverhalter hinzufügen
- in der IDE unter Werkzeuge folgende Einstellungen einstellen: 
  Board: "NodeMCU 1.0 (ESP-12E Modul)", CPU-Frequenz: "80MHz",    
  Flash Size: "4M (3M SPIFFS)", Upload Speed: "115200"

# Hochladen des Kompilats
- USB-Serial-Wandler an RX, TX und GND anschließen
- Jumper von Pin 1&2 (rot) auf 2&3 (gelb) umstecken
- MCU resetten
- Upload über Arduino IDE starten
- Jumper von Pin 2&3 (gelb) auf 1&2 (rot) umstecken
- MCU resetten
!(.Modul.jpg "Jumper Position")

# Verbindung zwischen MCU und Ampel
- TBD