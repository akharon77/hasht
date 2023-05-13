#!/usr/bin/gnuplot -persist

set terminal pngcairo size 640,480 noenhanced font "Verdana,10"

set style data histograms
set style histogram cluster
set style fill solid 2.0

set xrange [0:330]

assets_dir = 'assets/'

do for [hash_fun in "const first_char strlen sum_char rotr rotl crc32"] {
     input_filename  = assets_dir . 'data/hash_funs/hash_' . hash_fun . ".dat"
     output_filename = assets_dir . 'pictures/hash_' . hash_fun . ".png"

    set output output_filename

    plot input_filename using 2 title 'hash_' . hash_fun linetype rgbcolor "royalblue"
}
