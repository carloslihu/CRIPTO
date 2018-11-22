#!/bin/bash
#copia primeros 8 bytes
#dd if=mario.png of=header.bin ibs=8 count=1
#copia fichero sin cabecera
#dd if=mario.png of=mario2.bin ibs=8 skip=1

#escribo cabecera en imagen cifrada
#cat header.bin > cmario.png

#en mario3.bin guardamos imagen cifrada sin cabecera
#cat mario3.bin >> cmario.png

# First convert the Tux to PPM with Gimp
# Then take the header apart
head -n 4 Tux.ppm > header.txt  
tail -n +5 Tux.ppm > body.bin 
# Then encrypt with ECB (experiment with some different keys)
./desCBC -C -i body.bin -o body.ecb.bin
# And finally put the result together and convert to some better format with Gimp
cat header.txt body.ecb.bin > Tux.ecb.ppm
 
