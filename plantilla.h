#ifndef _PLANTILLA_H
#define _PLANTILLA_H

#define COMILLAS '"'
#define LINEA1 "<?xml version=%c1.0%c encoding=%cUTF-8%c?>\n<kml xmlns=%chttp://www.opengis.net/kml/2.2%c> <Document>\n<name>Ruta</name>\n<description>Ruta marcada</description> <Style id=%cyellowLineGreenPoly%c>\n<Point>\n<coordinates>"
#define LINEA2 "</coordinates>\n</Point>\n<LineStyle>\n<color>7f00ffff</color>\n<width>4</width>\n</LineStyle>\n<PolyStyle>\n<color>7f00ff00</color>\n</PolyStyle>\n</Style> <Placemark>\n<name>Relieve absoluto</name>\n<description>Pared verde transparente con contornos amarillos</description>\n<styleUrl>#yellowLineGreenPoly</styleUrl>\n<LineString>\n<extrude>1</extrude>\n<tessellate>1</tessellate>\n<altitudeMode>absoluto</altitudeMode>\n<coordinates> "
#define LINEA3 "</coordinates>\n</LineString> </Placemark>\n</Document> </kml>"

#define msjMenu1  "Sin Conexion"
#define msjMenu2  "A: Seguimiento | C: Menu"
#define msjMenu3  "B: Consultar  | C:Reiniciar"
#define msjMenu4  "Lon: "
#define msjMenu5  "Lat: "
#define msjMenu6  "USB no conectada"
#define msjMenu7  "Presione C"
#define msjMenu8  "CONECTE USB"

bool imprimir_plantilla1(void);
bool imprimir_plantilla2(void);
bool imprimir_plantilla3(void);

#endif