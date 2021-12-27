dir /B *.java > sources.txt
javac -cp ".;%MPJ_HOME%/lib/mpj.jar" @sources.txt
mpjrun.bat -np 2 Main
