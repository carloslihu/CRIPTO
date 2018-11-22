# First convert the Tux to PPM with Gimp
# Then take the header apart
head -n 3 Tux.ppm > header.txt  
tail -n +4 Tux.ppm > body.bin 
# Then encrypt with ECB (experiment with some different keys)
#./desCBC -C -i body.bin -o body.ecb.bin
./desCBC -C -i body.bin -o body.cbc.bin
# And finally put the result together and convert to some better format with Gimp
#cat header.txt body.ecb.bin > Tux.ecb.ppm
cat header.txt body.cbc.bin > Tux.cbc.ppm

rm -f *.bin header.txt

