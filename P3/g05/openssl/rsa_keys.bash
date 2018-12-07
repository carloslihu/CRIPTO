#!/bin/bash

#Generate a public-private keypair with the genrsa context (the last number is the keylength in bits):
openssl genrsa -out keypair.pem 2048

#To extract the public part, use the rsa context:
openssl rsa -in keypair.pem -pubout -out publickey.crt

#Finally, convert the original keypair to PKCS#8 format with the pkcs8 context:
openssl pkcs8 -topk8 -inform PEM -outform PEM -nocrypt -in keypair.pem -out pkcs8.key