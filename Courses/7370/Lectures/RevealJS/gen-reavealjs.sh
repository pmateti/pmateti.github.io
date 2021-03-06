
# convert an html file generated by org mode into revealjs based slides
# not elegant, but works

PMWSRT=


# $1 html file generated by org; $2 RevealJS is relative to cwd, ex: '../..'
org-revealjs() {
    [ -z $2 ] && echo '$2' RevealJS dots are empty && return
    sedpat=s:./RevealJS:$2/RevealJS:
    ofnm=./${1%.html}-slides.html
    pre=$2/RevealJS/revealjs-pre.html
    post=$2/RevealJS/revealjs-post.html
    tfnm=/tmp/$1

    cp $1 /tmp/
    sed -i $tfnm -e '1,/id="content"/ d' \
        -e 's/<div /<section /' \
        -e 's:</div>:</section>:' \
        -e 's:<section class="outline-text-2":<sectionX :' \
        -e 's:<section class="outline-text-3":<sectionX :' \
        -e ':</body>:,:</html>:d'

    sed -i $tfnm -e 's/<section id="text-table-of-contents">//'
    sed -i $tfnm -e '1i<section "id=preamble">' 
    sed -i $tfnm -e 's@/h1>@/h1><h2 style="color: black"> Prabhaker Mateti<h2><h3>Wright State University</h3><a href="http://www.cs.wright.edu/~pmateti">www.cs.wright.edu/~pmateti</a><\/section>@'
    
    cat $pre $tfnm $post > $ofnm
    sed -i $ofnm -e $sedpat
    ls -l $1 $ofnm
}

# files $pre and $post contain pathnames to RevealJS files.

# sed is written up in mutiple lines because seq of -e were not
# working; need to read more on sed;

# TBD -e 's:</section>N</section>:</section>:'
# the resulting html can be cleaned up further -- but no time now
