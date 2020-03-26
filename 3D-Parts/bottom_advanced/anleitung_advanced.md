# Anleitung gewellter Mülleimer

Hier ekläre ich wie mittels des freien Programms FreeCAD https://www.freecadweb.org/ ein etwas komplizierterer Mülleimer creirt werden kann.

## Vorläufig: (aktueller Stand in Video (noch nicht veröffentlicht))
Diese Datei ist aktuell nur enthalten um zu einem Späteren Zeitpunkt angepasst zu werden

**Die Datein Trashcan_bottom sind allerdings einsatzbereit!**

1. Wir öffnen ein neues Projekt in FreeCAD im der Part Design Workbench. Dort wählen wir "Körper erstellen"

2. Erstellen eines Sketches in der xy Ebene

3. Hier erstellen wir zwei kreise um den Mittelpunkt. 
Der kleinere erhält einen Radius von 20,65 mm (Dadurch passt später der wemos D1 ins innere).

4. Als nächstes legen wir einen B-Spline an. Dieser erhält 4 Punkte. Der Startpunkt liegt dabei auf dem äußeren Kreis, die zwei nächsten zwischen den Kreisen und der letzte liegt auf dem inneren Kreis.

5. Jetzt legen wir zwischen den Punkten auf dem Kreis und den Kreisen eine tangential Bedingung an (Tangente zwischen zwei Elementen erzwingen (T)).

6. Der innere Punkt wird jetzt auf die X-Achse gelegt (Punkt auf ein Objekt festlegen (Umschalt+O))

7. Der äußere Punkt soll auf 10° des Kreises eingestellt werden. Da wir nur Linien mit einer Winkelbedingung belegen können, legen wir eine Hilfslienie vom Nullpunkt bis zum äußeren Kreis an. Diese bemaßen wir mit 10°.
Als nächstes legen wir den äußeren Punkt unserer B-Spline auf diese Hilfslinie (mittels Punkt auf ein Objekt festlegen (Umschalt+O)).

8. Die zwei Kreise und die Hilfslinie dienten uns nur zur Konstruktion, diese können jetzt als Hilfslienie gesetz werden. 

9. Wir spiegeln unsere gesetzte B-Spline um die X-Achse

10. Wir schließen den Sketch und wechseln in die Draft Workbench.

11. Hier wählen wir den Sketch in der Combo-Ansicht aus. Dann wählen wir das Array Tool.

12. Der "Array Type" wird auf "polar" geändert. Dazu wird die "Number Polar" auf 18 geändert. Wenn anschließend aktualisiert wird erhalten wir bereits die Bodenplatte unseres Mülleimers!