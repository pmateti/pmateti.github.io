markdo() {
    basenm=${1%.txt}
    markdown $basenm.txt -o ${basnm}-md.html;
    pandoc -s -S -t slidy ${basenm}.txt -o ${basenm}-slidy.html;
}

mdClean() {
  mv *.html ../TBD
}

# temp fix until I learn org mode better

fixOrgHTML() {
    sed -i -e '/<\/style>/i\@media screen \{BODY \{margin: 12\%;\}\}' \
	-e '/<p class=\"date\">/d' \
	-e '/<p class=\"creator\">/d' \
	-e 's/Author: pmateti/Lecture Notes of Prabhaker Mateti/' \
	-e '/<a href="http:\/\/validator.w3.org\//d' \
	design.html
}



