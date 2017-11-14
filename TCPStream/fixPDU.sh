#!/bin/bash

sed -i 's/PDU \*/PDUP \*/g' SMB2_Generated.h
sed -i 's/PDU \*/PDUP \*/g' SMB2_Generated.c