#!/bin/bash

# ./test_openssl.sh > test_results2.txt

while read line
do

	echo -n $line | openssl dgst -sha1
	echo -n $line | openssl sha1 -binary | openssl base64

done < test_sentences.txt 

