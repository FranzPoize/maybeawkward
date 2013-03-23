g++ -o game -g `find . -name '*.cpp'` -L /usr/local/lib/ -I /usr/local/include/ClanLib-2.3 -std=c++0x 2>&1 -lclan23App -lclan23Core -lclan23GL -lclan23Display -lpthread | prettybuild
