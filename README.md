# Book: [Ajhc](http://ajhc.metasepi.org/) Hacking Guide

## Where is the book

* In Japanese: http://files.metasepi.org/ajhc/ajhc-hg-ja.pdf

## How to build

Get your Debian wheezy PC and setup it.

    $ sudo apt-get install git omake unoconv libreoffice texlive-lang-cjk texlive-fonts-recommended ruby-full rake bundler okular
    $ git clone https://github.com/kmuto/review.git
    $ cd review
    $ sudo rake install

Then get settings for Japanese. http://uwabami.junkhub.org/log/20121202p01.html

Build me.

    $ git clone https://github.com/ajhc/ajhc-hacking-guide.git
    $ cd ajhc-hacking-guide
    $ omake
    $ okular ja/ajhc-hg.pdf

## License

This work is licensed under a [Creative Commons Attribution-ShareAlike 3.0 Unported License](http://creativecommons.org/licenses/by-sa/3.0/).
[![](http://i.creativecommons.org/l/by-sa/3.0/80x15.png)](http://creativecommons.org/licenses/by-sa/3.0/)

The code for this book reuses the trema-book's https://github.com/yasuhito/trema-book.
Thank's yasuhito!
