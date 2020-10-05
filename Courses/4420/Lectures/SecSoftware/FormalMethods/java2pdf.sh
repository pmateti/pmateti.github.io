#!/bin/bash

java2pdf() {
    a2ps --pro=color --line-numbers=1 --columns=1 -B -R $1 -o $1.ps
    ps2pdf $1.ps 
    rm $1.ps
}
