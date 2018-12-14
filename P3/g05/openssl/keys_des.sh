#!/bin/bash

cd claves_des

if [ "$#" -eq  "1" ] && [ $1 == "remove" ]
	then

	rm -f in_1.txt in_2.txt in_3.txt in_4.txt in_5.txt in_6.txt in_7.txt in_8.txt in_9.txt in_10.txt
	rm -f out_1.txt out_2.txt out_3.txt out_4.txt out_5.txt out_6.txt out_7.txt out_8.txt out_9.txt out_10.txt
	cd ..

#Claves debiles DES
# 0x0101010101010101
# 0xFEFEFEFEFEFEFEFE
# 0xE0E0E0E0F1F1F1F1
# 0x1F1F1F1F0E0E0E0E

else

	echo "Probando claves debiles DES"

	openssl enc -e -des-ecb -K 0101010101010101 -in in.txt -out out_1.txt
	openssl enc -e -des-ecb -K 0101010101010101 -out in_1.txt -in out_1.txt

	openssl enc -e -des-ecb -K FEFEFEFEFEFEFEFE -in in.txt -out out_2.txt
	openssl enc -e -des-ecb -K FEFEFEFEFEFEFEFE -out in_2.txt -in out_2.txt

	openssl enc -e -des-ecb -K E0E0E0E0F1F1F1F1 -in in.txt -out out_3.txt
	openssl enc -e -des-ecb -K E0E0E0E0F1F1F1F1 -out in_3.txt -in out_3.txt

	openssl enc -e -des-ecb -K 1F1F1F1F0E0E0E0E -in in.txt -out out_4.txt
	openssl enc -e -des-ecb -K 1F1F1F1F0E0E0E0E -out in_4.txt -in out_4.txt


	#Claves semidebiles DES
	# 0x011F011F010E010E and 0x1F011F010E010E01
	# 0x01E001E001F101F1 and 0xE001E001F101F101
	# 0x01FE01FE01FE01FE and 0xFE01FE01FE01FE01
	# 0x1FE01FE00EF10EF1 and 0xE01FE01FF10EF10E
	# 0x1FFE1FFE0EFE0EFE and 0xFE1FFE1FFE0EFE0E
	# 0xE0FEE0FEF1FEF1FE and 0xFEE0FEE0FEF1FEF1

	echo "Probando claves semidebiles DES"

	openssl enc -e -des-ecb -K 011F011F010E010E -in in.txt -out out_5.txt
	openssl enc -e -des-ecb -K 1F011F010E010E01 -out in_5.txt -in out_5.txt

	openssl enc -e -des-ecb -K 01E001E001F101F1 -in in.txt -out out_6.txt
	openssl enc -e -des-ecb -K E001E001F101F101 -out in_6.txt -in out_6.txt

	openssl enc -e -des-ecb -K 01FE01FE01FE01FE -in in.txt -out out_7.txt
	openssl enc -e -des-ecb -K FE01FE01FE01FE01 -out in_7.txt -in out_7.txt

	openssl enc -e -des-ecb -K 1FE01FE00EF10EF1 -in in.txt -out out_8.txt
	openssl enc -e -des-ecb -K E01FE01FF10EF10E -out in_8.txt -in out_8.txt

	openssl enc -e -des-ecb -K 1FFE1FFE0EFE0EFE -in in.txt -out out_9.txt
	openssl enc -e -des-ecb -K FE1FFE1FFE0EFE0E -out in_9.txt -in out_9.txt

	openssl enc -e -des-ecb -K E0FEE0FEF1FEF1FE -in in.txt -out out_10.txt
	openssl enc -e -des-ecb -K FEE0FEE0FEF1FEF1 -out in_10.txt -in out_10.txt

	cd ..

	fi