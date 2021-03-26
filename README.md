# ConnectReactNativetoEmbeddedLinux

## Description

In this app, I use a user interface to control the in-build led on a Embedded Linux device. I am using a BeagleBone Black. For the user interface, I build a mobile application using React Native for the front-end. The user can click on a button and it send a POST request using fetch to the BeagleBone. The BeagleBone is running a TCP server that is listening for income message that built on C and the filename is openServer.c
