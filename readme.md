# Mülleimer Projekt der Zukunftspiloten aus dem Bergischen Land

## Zur Hardware:

| Anzahl | Bezeichnung                  |
|:------:|-------------                 |
| 1      | Wemos D1 Mini ESP8266 Board  |
| 6 LED* | WS2812b LED-Streifen         |
| 1      | USB-Kabel Ladekabel          |
| 1      | USB-Netzteil                 |
| ~20g   | (klares) Filament            |

*wir nutzen ca 10 cm LED-Streifen (vom Typ WS2812b, mit 60 LED/Metern, also 6 LED pro Streifen. Dieser lässt sich mit 5 V unseres Boards betreiben. In der mitte geknickt passt er gut in unseren Mülleimer und zeigt so 3 LED zu jeder Seite.)


## Zur Programmierung:

1.   Installation des ESP8266 Moduls für Arduino https://github.com/esp8266/Arduino hier haben wir die "Installing with Boards Manager" Option gewählt. Nicht vergessend anschließend als Board den Wemos D1 R2&Mini auswählen

2.  Installation der ESP8266Wifi Bibliothek: https://github.com/ekstrand/ESP8266wifi Hier gibt es auch eine (englische) Anleitung zur Installation.


3. Zur Steuerung der LED-Streifen fehlt uns jetzt noch eine passende Bibliothek dazu, hier installieren wir die folgende: [github.com Neopixel](https://github.com/adafruit/Adafruit_NeoPixel) Bibliothek. Auch hier gibt es eine (englische) Anleitung. Unter "first method" gibt es keine einfache und schnelle Installationsanleitung.

## Zum Hardware Aufbau

Unter: [carontepass.files.wordpress.com](https://carontepass.files.wordpress.com/2016/03/wemos-d1-mini.jpg?w=1200) finden wir einen Bild mit dem Pinout des wemos D1 mini 

### Aufbau des Mülleimers
Der Mülleimer besteht aus einem 3D-Druck.
Hierzu gibt es zwei Varianten, die "simple" für Einsteiger und die "advanced" für Fortgeschrittene. 

1. Zur Erstellung des unteren 3D-Modells könnt ihr der Anleitung im Ordner simple/advanced folgen. In beiden Ordnern befinden sich auch Beispielhaft fertige Datein. Das Ergebnis muss als *.stl exportiert werden, damit dieses später weiterverarbeitet werden kann. Speichert euch auch die Datei ab, falls ihr diese später noch einmal ändern wollt. *Hinweis* Das Modell darf innen gefüllt sein, da wir das später beim Drucken ändern.

2. Jetzt benötigen wir noch einen Deckel für unsere Tonne. 

3. 3D-Drucken

4. Anlöten der LED-Streifen

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