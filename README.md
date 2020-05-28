# SDL_Engine | 08.2019, 5 Monate

Was habe ich gelernt:
- C++
- Als Team arbeiten (Progammierer und Artist)
- Als Team programmieren, Versionierung
- Benutzung externer Liberies
- Tieferes Verständins einer Game Engine

Bei dieser Abgabe wurde uns C++ unterrichtet. Als praktische Umsetzung wurde im Unterricht die Grundlage diese Engine erstellt.
Als Gruppe müssen wir dann mit dieser Engine ein Spiel erstellen.
Wir hatten zusätzlich auch Game Desinge Unterricht, wo es darum ging, wie man ein Spiel erstellt, dass auch Spaß macht und an eine Zielgruppe gerichtet ist.

Meine Gruppe bestand aus 2 Programmierern und 3 Artist. Wir hatten viele Ideen, welche man in das Spiel hineinbringen könnte, doch aus zeitlichen Gründen mussten wir vieles kürzen und sind auch zum Schluß auf viele Probleme gestoßen, weshalb wir auch keine funktionierende Gameloop haben.

In diesem Projekt war es meine Aufgabe die Ameisen an Wänden und Deken laufen zu lassen. Da die Collisionsberechnung in diesem Spiel über Rects lief, wo dann ein Bild hinein geladen wird, und diese AABB sind, entschloss ich diese als Trigger zu nutzen, statt der Implementierung von eigenen Triggern oder Raycasts. Da die schon im Unterricht gemachte Rect alle Funktionen hatten wie auch ein Trigger.
Ich erstellte ein kleines Rect an allen vier Seiten des Spielers. Diese Rects sollten erkennen wo der Boden für den Spieler ist. Bei Collision mit einer Wand ändert sich die Ausrichtung des Spielers abhängig davon wurde das Bild als auch die Steuerung geändert.
Des Weiteren fügte ich neben diese vier Rects, an beiden Seiten weitere Rects ein. Denn sollte der Spieler um eine Kante herum laufen wollen, könnte man mit den beiden seitlichen Rects die Richtung der Kante bestimmen.
Nicht benötigte Rects wurden deaktiviert (Nicht auf Collision überprüft) aus Performance-Zwecken (grau).
 
