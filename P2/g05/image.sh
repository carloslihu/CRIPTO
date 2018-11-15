#!/bin/bash
#copia primeros 8 bytes
dd if=mario.png of=header.bin ibs=8 count=1
#copia fichero sin cabecera
dd if=mario.png of=mario2.bin ibs=8 skip=1

#cat header.bin >> cmario.png
#cat mario3.bin >> cmario.png


