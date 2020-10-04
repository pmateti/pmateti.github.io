
mkslides() {
    targetfnm=${1%.html}Slides.html
    cp $1 $targetfnm
    sed -e 's/(default|simple).css/night.css/' -i $targetfnm 
    sed insert after <body>     <a href="../../Top/"> CEG 7370 Distributed Computing</a> | <a href=./actorsAkkaScalaSlides.html> Slides</a> | <a href=./actorsAkkaScalaOnePage.html> OnePage</a> <div class="reveal"> <div class="slides">
}


<span class="section-number-2">

mkslides scalaPractical.html

del <section  class="outline-text-2" id="text-2">
<span class="section-number-3">
<section  class="outline-text-3" id="text-3-1">
<section  class="outline-text-3" id="text-4-1">
<section  class="org-src-container">
<section  class="outline-text-3" id="text-4-2">

