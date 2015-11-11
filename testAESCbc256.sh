#!/bin/bash

openssl aes-256-cbc -d -K $(echo -n '01234567890123456789012345678901'  | od -A n -t x1 -w32 | sed 's/ //g')  -iv '' -in /tmp/output
