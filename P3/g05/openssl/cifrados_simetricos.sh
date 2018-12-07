#!/bin/bash

if [ "$#" -eq  "1" ] && [ $1 == "remove" ]
	then

	rm -f in_aes.txt in_aria.txt in_blowfish.txt in_camellia.txt in_cast5.txt in_rc2.txt in_seed.txt in_6.txt in_sm4.txt 
	rm -f out_aes.txt out_aria.txt out_blowfish.txt out_camellia.txt out_cast5.txt out_rc2.txt out_seed.txt out_sm4.txt out_7.txt


else

	printf "Probando cifrados simetricos\n\n"

	printf "AES\n"
	openssl enc -e -aes-128-ecb -K FFFFFFFFFFFFFFFF0000000000000000 -in in.txt -out out_aes.txt
	openssl enc -d -aes-128-ecb -K FFFFFFFFFFFFFFFF0000000000000000 -out in_aes.txt -in out_aes.txt

	printf "Aria\n"
	openssl enc -e -aria-128-ecb -K FFFFFFFFFFFFFFFF0000000000000000 -in in.txt -out out_aria.txt
	openssl enc -d -aria-128-ecb -K FFFFFFFFFFFFFFFF0000000000000000 -out in_aria.txt -in out_aria.txt

	printf "Blowfish\n"
	openssl enc -e -bf-ecb -K FFFFFFFFFFFFFFFF0000000000000000 -in in.txt -out out_blowfish.txt
	openssl enc -d -bf-ecb -K FFFFFFFFFFFFFFFF0000000000000000 -out in_blowfish.txt -in out_blowfish.txt

	printf "Camellia\n"
	openssl enc -e -camellia-128-ecb -K FFFFFFFFFFFFFFFF0000000000000000 -in in.txt -out out_camellia.txt
	openssl enc -d -camellia-128-ecb -K FFFFFFFFFFFFFFFF0000000000000000 -out in_camellia.txt -in out_camellia.txt

	printf "Cast5\n"
	openssl enc -e -cast5-ecb -K FFFFFFFFFFFFFFFF0000000000000000 -in in.txt -out out_cast5.txt
	openssl enc -d -cast5-ecb -K FFFFFFFFFFFFFFFF0000000000000000 -out in_cast5.txt -in out_cast5.txt

	printf "RC2\n"
	openssl enc -e -rc2-ecb -K FFFFFFFFFFFFFFFF0000000000000000 -in in.txt -out out_rc2.txt
	openssl enc -d -rc2-ecb -K FFFFFFFFFFFFFFFF0000000000000000 -out in_rc2.txt -in out_rc2.txt

	printf "Seed\n"
	openssl enc -e -seed-ecb -K FFFFFFFFFFFFFFFF0000000000000000 -in in.txt -out out_seed.txt
	openssl enc -d -seed-ecb -K FFFFFFFFFFFFFFFF0000000000000000 -out in_seed.txt -in out_seed.txt

	printf "SM4\n"
	openssl enc -e -sm4-ecb -K FFFFFFFFFFFFFFFF0000000000000000 -in in.txt -out out_sm4.txt
	openssl enc -d -sm4-ecb -K FFFFFFFFFFFFFFFF0000000000000000 -out in_sm4.txt -in out_sm4.txt
	
	fi
