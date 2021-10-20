### How to compile?

    	g++ -g main.cpp SingleRune.cpp WyrdRune.cpp -o rreader.bin -lsfml-graphics -lsfml-window -lsfml-system

This application is build in c++ with help of sfml libraries.

Rune Reader will help user to cast runes in all of the most popular casting systems but without any help in regards of interpretation. User will find nice looking gui built with sfml. With castings with more runes, user could experience laging(nothig to worry about; I will correct that if I find some spare time:-). There are 4 background images that are change in random maner on every program run. User could change background images simply by puting new images in background folder. If user install debian version of this app, background will be in /usr/share/rune reader/background. If user chooses to compile program himself, background folder should be in the same directory as the binary file.

This program is free software; you can redistribute it and/or modify it under the terms of the Apache License, Version 2.0. 
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the Apache License, Version 2.0 for more details.
You should have received a copy of the Apache License, Version 2.0 along with this program; if not, check apache.org for copy of Apache License, Version 2.0.
