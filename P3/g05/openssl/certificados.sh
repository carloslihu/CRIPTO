#!/bin/bash


cd certificados

# First start by creating your CA key:
openssl genrsa -out ca.key 4096

# Next we need to create our CA certificate
openssl req -new -x509 -days 1826 -key ca.key -out ca.crt -subj "/C=US/ST=New York/L=Brooklyn/O=CA/CN=ca.com"

# Next we have to create a certificate for that server we want to use SSL on
openssl genrsa -out server.key 4096

# After that we need certificate request, it is here you have to fill in the domain name that you are going to use the certificate with:
openssl req -new -key server.key -out server.csr  -subj "/C=US/ST=New York/L=Brooklyn/O=Server/CN=server.com"

# Then lastly we can create our server certificate
openssl x509 -req -days 730 -in server.csr -CA ca.crt -CAkey ca.key -set_serial 01 -out server.crt


cd ..