rsyncFromTo() { 
    [ -z $2 ] && echo source-dir dest-dir args requred && return 0
    time nice rsync -acxz -v -K --links --safe-links \
	--copy-unsafe-links --hard-links --update \
	'--exclude=**/.*' '--exclude=**/Desktop' $1 $2
}

namesUSBD="MATETI16GB"

bk7140TBD() {
    course=7140
    dirs="2013-Fall Exams Private Lectures Projects Top"

    dst=/media/MATETI16GB/pmateti/Courses/${course}
    [ ! -d ${dst} ] && echo "${dst} does not exist" && return 0

    src=/var/HomeLocal/pmateti/Courses/${course}
    for dnm in ${dirs}
    do
	echo rsyncFromTo ${src}/${dnm} ${dst}
	rsyncFromTo ${src}/${dnm} ${dst}
    done
}

bk71404350() {
time cp -frauvp /home/pmateti/Courses/7140/ /home/pmateti/Courses/4350/ \
     /media/pmateti/MATETI16USB/pmateti/Courses/
time cp -frauvp /home/pmateti/Courses/7140/ /home/pmateti/Courses/4350/ \
     /media/pmateti/MATETI32USB/pmateti/Courses/
}
