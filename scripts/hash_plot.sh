#!/usr/bin/gnuplot -persist

set terminal pngcairo size 1024,720 noenhanced font "Verdana,10"

set style data histograms
set style histogram clustered gap 10
set style fill solid 0.5

# set xrange [0:330]
set boxwidth 0.9 * 10
set xtics 1 0, 50, 330

assets_dir = 'assets/'

do for [hash_fun in "const crc32 first_char rotl rotr strlen sum_char"] {
    do for [size in "523 977"] {
         input_filename  = assets_dir . 'data/hash_funs/len/hash_' . hash_fun . '_size_' . size . ".dat"
         output_filename = assets_dir . 'pictures/hash_' . hash_fun . '_size_' . size . ".png"

        set output output_filename

        plot input_filename using 2 title 'hash_' . hash_fun linetype rgbcolor "royalblue"
    }
}
