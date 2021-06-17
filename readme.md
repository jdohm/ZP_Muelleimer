# Mülleimer Projekt der Zukunftspiloten aus dem Bergischen Land
![GIF blaue Mülltonne](/pictures/blaue_tonne.gif "Abbildung vom Lötvorgang")
## Zur Hardware:

| Anzahl | Bezeichnung                  |
|:------:|-------------                 |
| 1      | Wemos D1 Mini ESP8266 Board  |
| 6 LED* | WS2812b LED-Streifen         |
| 1      | USB-Kabel Ladekabel          |
| 1      | USB-Netzteil                 |
| ~20g   | (klares) Filament            |

*wir nutzen ca 10 cm LED-Streifen (vom Typ WS2812b, mit 60 LED/Metern, also 6 LED pro Streifen. Dieser lässt sich mit 5 V unseres Boards betreiben. In der mitte geknickt passt er gut in unseren Mülleimer und zeigt so 3 LED zu jeder Seite.)


## Zum Hardware Aufbau

### Aufbau des Mülleimers
Der Mülleimer besteht aus einem 3D-Druck.
Hierzu gibt es zwei Varianten, die "simple" für Einsteiger und die "advanced" für Fortgeschrittene. 

1. Zur Erstellung des unteren 3D-Modells könnt ihr der Anleitung im Ordner 3D-Parts/bottom_simple oder 3D-Parts/bottom_advanced folgen. In beiden Ordnern befinden sich auch Beispielhaft fertige Datein. Das Ergebnis muss als *.stl exportiert werden, damit dieses später weiterverarbeitet werden kann. Speichert euch auch die Datei ab, falls ihr diese später noch einmal ändern wollt. *Hinweis* Das Modell darf innen gefüllt sein, da wir das später beim Drucken ändern.

2. Jetzt benötigen wir noch einen Deckel für unsere Tonne. Dazu findet sich ebenfalls unter 3D-Parts eine einfache Anleitung. Gerne könnt ihr natürlich auch euren eigenen Deckel kreieren. Achtet nur darauf das er auf unsere Tonne passt, und das wir den Deckel nicht im *Vasemode* Drucken. Deswegen sollten wir ihn nicht gefüllt konstruieren.

3. 3D-Drucken

    Bei dem Druck der Tonne und des Deckels brauchen wir unterschiedliche Einstellungen. Fangen wir mit der Tonne an. 
    Um eine möglichst durchscheinende Tonne zu bekommen nutzen wir nur eine Außenwand. Hier nutzen wir den *Vase mode* bei Cura heißt die Einstellung hierfür *spiralize outer contour*. Dazu nutzen wir bei einer Standard 0.4mm Düse eine *line width* von 0.48mm um unsere Tonne etwas stabiler zu gestalten. Es bietet sich an 3 *bottom layer* und eine *layer height* von 0.2-0.3mm einzustellen.

    Der einfache Deckel kann mit den Standardeinstellungen deines Druckers gedruckt werden. Eine *line width* von 0.48mm ist dabei Hilfreich aber nicht notwendig.

4. Anlöten der LED-Streifen

    Unter: [carontepass.files.wordpress.com](https://carontepass.files.wordpress.com/2016/03/wemos-d1-mini.jpg?w=1200) finden wir einen Bild mit dem Pinout des wemos D1 mini 

    Leider entpricht die Reihenfolge des LED-Streifens nicht der unseres Microkontrollers. Aus diesem Grund müssen wir mit ein paar kurzen Leitungen nachhelfen. Auch sollten wir nicht den Pin D4 nutzen, da dieser mit der internen blauen LED Verbunden ist.
    Wie hier in der Abbildung zu sehen wird die Seite des LED-Streifens auf der **Din** steht mit der Seite des Microkontrollers verbunden auf der sich die USB-Buchse befindet.

    Verbunden wird: 

    | LED | Microkontrollers |
    |:------:|-------------  |
    | +5V | 5V |
    | Din | D2 |
    | GND | G  |

    ![Abbildung vom Lötvorgang](/assembly/soldering.jpg "Abbildung vom Lötvorgang")

    *Hinweis* In der Arduino Umgebung heißt der Pin D2 "4". Das liegt daran das der Arduino den Wemos D1 mit den Nummern des eingebauten ESP8266 anspricht, die Hersteller vom Wemos D1 die aber umbenannt haben (zum Beispiel eben 4 in D2, oder Pin 2 in D4). Auf D4/Pin2 liegt die interne LED. Diese können wir im Arduino aber auch über *LED_BUILTIN* ansprechen.

5. Zusammenbau

    Mit einem Elektronikseitenschneider wird unten knapp über dem Boden ein Loch in unsere Tonne geschnitten sodass das kleine Ende vom USB-Kabel hindurch passt.
    Anschließend wird das Kabel hindurchgeführt, und an den Wemos D1 mini angeschlossen. Vorsichtig wird das Kabel wieder soweit hinaus gezogen, dass der Microkontroller am Boden liegt und der LED Streifen nach oben zeigt.

    ![Abbildung von Mülleimer und Seitenschneider](/3D-Parts/bottom_advanced/cutting.jpg "Abbildung von Mülleimer und Seitenschneider")

    Anschließend kann der Deckel einfach aufgesetzt werden.


## Zur Programmierung:

1.   Installation des ESP8266 Moduls für Arduino https://github.com/esp8266/Arduino hier haben wir die "Installing with Boards Manager" Option gewählt. Nicht vergessend anschließend als Board den Wemos D1 R2&Mini auswählen

2.  Aus dem gleichen Set nutzen wir auch die ```ESP8266Wifi.h``` Library. Eine (englisches) Handbuch dazu findet sich hier:
[arduino-esp8266.readthedocs.io](https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html)
hier gibt es auch ein [Beispiel Wifi Cleint](https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/client-examples.html), bei dem ein Client aufgesetzt wird.

    Um die aktuelle Zeit und das Dazum zu kennen nutzen wir die Uhrzeit aus dem Internet. Dazu kann die folgende Anleitung genutzt werden: [simple-circuit.com](https://simple-circuit.com/esp8266-esp-01-internet-clock-wifi/). Hier wird erklärt wie wir eine Uhrzeit über NTP beziehen können. 
    Anschließend kann mit der Time Bibliothek die Linux-Uhrzeit in ein Datum umgerechnet werden. Die Informationen dazu finden wir hier: [github.com Time](https://github.com/PaulStoffregen/Time)

    * ICal (*.ics Datei) Version:

        Diese Version nutzt ICal Datein, einige Städte bieten diese zum Download für ihre Bürger an. Beispielsweise in Bochum oder Wuppertal.

        Um die Daten aus der Kalender Datei zu verwenden müssen wir den Kalender erst einmal auf unseren ESP bekommen. Dazu nutzen wir das ESP8266 Filesystem. Eine Anleitung dazu finden wir hier: [ESP Filesystem](http://arduino.esp8266.com/Arduino/versions/2.0.0/doc/filesystem.html) In dieser Anleitung wird auch erkärt, wie wir Daten von der Arduino Programmierumgebung (IDE) auf den ESP Laden.
        Hierbei muss darauf geachtet werden, die neuste Version zu nutzen, *nicht* die im Artikel verlinkte.

        Anschließend kann mit der [Github ICSParser](https://github.com/jdohm/ICSParser) Bibliothek der Kalender ausgelesen werden. 

    * Für andere Städte (Beispielsweise Remscheid) gestaltet sich das ganze etwas schwieriger. 
    
        Bei dem leichteren Fällen, kann die Information über http unverschlüsselt abgerufen werden. 
        Dazu haben wir bereits alle Infos im dem [Beispiel Wifi Cleint](https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/client-examples.html)

        In den schwierigeren Fällen (wie auch in Remscheid) müssen wir die Information über eine verschlüsselte https Verbindung abfragen.

        Dazu nutzen wir die Bibliothek [Github RemscheidMuellParser](https://github.com/jdohm/RemscheidMuellParser) mit welcher wir (aktuell noch nicht für die gelbe Tonne) von einem Webserver abfragen ob der Müll rausgestellt werden muss.

3. Zur Steuerung der LED-Streifen fehlt uns jetzt noch eine passende Bibliothek, hier installieren wir die [github.com Neopixel](https://github.com/adafruit/Adafruit_NeoPixel) Bibliothek. Auch hier gibt es eine (englische) Anleitung. Unter "first method" gibt es eine einfache und schnelle Installationsanleitung.
