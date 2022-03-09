# Laboratorio de Sistemas Embebidos Avanzados
# Seguidor de Ubicación Usando GPS y Memoria Permanente

## 1 Introducción

En esta práctica de laboratorio, el objetivo principal ser ́a desarrollar un sistema embebido con la capacidad de recopilar y almacenar datos de geoposicionamiento mediante el uso de dispositivos de posicionamiento global GPS y memorias EEPROM. El resto de componentes lo integran un teclado matricial (KeyPad), un display de cristal l ́ıquido (LCD) y el sistema de desarrollo Raspberry Pi Pico. Para el desarrollo del firmware, el grupo de estudiantes podrá emplear la SDK de C/C++ además de librerías propias.

## 2 Descripción del Problema

Al grupo de estudiantes se le encarga la labor de desarrollar un sistema embebido con la capacidad de recopilar valores de geoposicionamiento mediante dispositivos GPS apropiados y almacenarlos en memoria no vol ́atil para futuras consultas. El sistema debe operar en dos modos:

- seguimiento.
- consulta.

En modo seguimiento, el sistema recopila los datos de coordenadas (latitud, longitud) que provienen desde el GPS empleando el protocolo NMEA (National Marine Electronics Asociation) y los almacena en una memoria EEPROM a través del protocolo I^2 C. En modo consulta, el sistema envía la información almacenada en la memoria no volátil a la terminal de un computador en formato KML (Keyhole Markup Language). El formato KML es empleado por Google Earth para mostrar información geográfica.

La funcionalidad del sistema es la siguiente:

a. Al iniciar el sistema, ́este debe mostrar en un LCD un menú que permita seleccionar uno de los modos de operación. Opciones adicionales como borrar los datos de la memoria pueden estar presentes.
b. En modo seguimiento, el sistema debe mostrar en el LCD el valor actual tomado desde el GPS, junto con la fecha y hora, mientras va registrando dicha información en la memoria no volátil. El grupo de estudiantes define la estrategia para almacenar los datos de geoposicionamiento. Para este modo, se recomienda que el sistema opere con baterías.
c. En modo consulta, el sistema envía la información almacenada en memoria (datos de geoposicionamiento) a un PC empleando la conexi ́on UART-USB disponible. La información debe estar en formato KML para luego ser usada por Google Earth con el fin de mostrar el camino seguido por el sistema mientras estuvo registrando información.
d. Para la operación del sistema se puede emplear un KeyPad.

Componentes y características del desarrollo:

a. Microcontrolador RP2040.
b. Dispositivo de posicionamiento global GPS. En el laboratorio est ́an disponibles varios GNSS (Global Navigation Satellite System) que incluyen GPS, referencia NEO-7 y NEO-M8.
c. Memoria EEPROM con interfaz I^2 C. Un tipo de memorias EEPROM I^2 C populares son las de referencia 24LCXX.
d. Teclado matricial 4x4 (KeyPad) para operar los menús del sistema.
e. Display de cristal líquido para la visualizaci ́on de menús, datos de geoposicionamiento, entre otros.
f. PC para tomar la información en formato KML desde el sistema embebido y mostrarla en pantalla usando Google Earth.

La Fig.1 muestra un esquema posible del sistema a diseñar.

![Esquema del sistema a diseñar](https://i.ibb.co/dB6Ps5L/Capture.jpg)
Fig.1: Esquema del sistema a diseñar

## 5 Referencias

```
a. Embedded System Design de Peter Marwedel. Kluwer Academic, Springer, 2006.
b. Programming Embedded Systems in C and C++ de Michael Barr. O’Reilly.
c. Documentaci ́on SDK para Raspberry Pi Pico
https://raspberrypi.github.io/pico-sdk-doxygen/
d. Getting Started with Pico Manual
https://datasheets.raspberrypi.org/pico/getting-started-with-pico.pdf
e. Raspberry Pi Pico Datasheet
https://datasheets.raspberrypi.com/pico/pico-datasheet.pdf
f. RP2040 Microcontroller Datasheet
https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf
g. Raspberry Pi Pico C/C++ SDK
https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-c-sdk.pdf
h. GNSS Neo-M8
https://www.u-blox.com/en/product/neo-m8-series
i. GNSS Neo-7
https://www.u-blox.com/en/product/neo-7-series
```

