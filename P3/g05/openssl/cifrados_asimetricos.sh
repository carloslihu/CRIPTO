#!/bin/bash

cd asimetricos

if [ "$#" -eq  "1" ] && [ $1 == "remove" ]
	then

	rm -f in_rsa.txt  
	rm -f out_rsa.txt

	cd ..

else

	printf "Probando cifrados simetricos\n\n"

	printf "RSA\n\n"

	# Generar clave privada
	openssl genrsa -out privada.key 4096

	# extraer una clave pública a partir de la clave privada:
	openssl rsa -in privada.key -pubout -out publica.key

	# Ahora, teniendo un archivo datos.raw que queremos cifrar, hacemos:
	openssl rsautl -pubin -encrypt -in in.txt -out out_rsa.txt -inkey publica.key

	# Y cuando necesitemos descifrarlo:
	openssl rsautl -decrypt -inkey privada.key -in out_rsa.txt -out in_rsa.txt


	cd ..
	
	fi




