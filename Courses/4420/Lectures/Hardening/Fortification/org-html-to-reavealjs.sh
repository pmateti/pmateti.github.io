
# for now, written for Fortification

RVLJS=~/RevealJS

# why does org mode change the link?
fix-org-link() {
    sed -i $1 \
        -e 's:<a href="./buf-ovf.html">buf-ovf.org</a>:<a href="./buf-ovf.org">buf-ovf.org</a>:'
}

org-html-to-revealjs() {
    cp $1 /tmp/
    sed -i /tmp/$1 -e '1,/id="preamble"/ d' \
        -e 's/<div /<section /' -e 's:</div>:</section>:' \
        -e 's:<section class="outline-text-2":<sectionX :' \
        -e 's:<section class="outline-text-3":<sectionX :' \
        -e ':</body>:,:</html>:d'

    sed -i /tmp/$1 -e '1i<section "id=preamble">' 
    sed -i /tmp/$1 -e '/<h1 class="title">/a<h3 style="color: darkblue">Prabhaker Mateti<h3>\n<h2>Wright State University</h2>\n<tt>www.cs.wright.edu/~pmateti</tt>\n</section>' 
    sed -i /tmp/$1 -e 's/<section id="text-table-of-contents">//'

    fix-org-link /tmp/$1

    fnm=./${1%.html}-slides.html
    cat $RVLJS/prelude.html  /tmp/$1 $RVLJS/postlude.html > $fnm
    ls -l $1 $fnm
}

# echo '<a href="./buf-ovf.html">buf-ovf.org</a> dot-org'
# sed is written up in mutiple line because seq of -e were not working
# need to read more on sed
# TBD -e 's:</section>N</section>:</section>:'
