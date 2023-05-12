#!/usr/bin/gnuplot -persist

set terminal pngcairo size 640,480 enhanced font "Verdana,10"

set style data histograms
set style histogram cluster
set style fill solid 2.0

set xrange [0:330]

do for [hash_fun in "const first_char strlen sum_char rotr rotl crc32"] {
     input_filename = 'hash_' . hash_fun . ".dat"
    output_filename = 'hash_' . hash_fun . ".png"

    set output output_filename

    plot input_filename using 2 title 'hash_' . hash_fun noenhanced linetype rgbcolor "royalblue"
}
