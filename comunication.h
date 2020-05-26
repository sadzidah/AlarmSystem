#ifndef COMUNICATION_H
#define COMUNICATION_H

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <zconf.h>
#include <string.h>
#include "mainwindow.h"
#define PORT 8090
#define ADDRESS "192.168.43.253"
#define BUFFER_LENGTH 4096
#define WRITE_BUFFER_LENGTH 64

    int getBufferLength(char[]);
    void receive(char, MainWindow*);
    void sendHeader(char);
    void sendData(char, QString, QString, QString);


#endif // COMUNICATION_H
