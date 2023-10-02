.PHONY = clean
.PHONY = all

JARFALGS=cvfm
CP=-cp Pokemon.jar
CPext = -cp out:Pokemon.jar
JAVA_MOVES_FILES = $(wildcard src/added/moves/*.java)
JAVA_POKEMON_FILES = $(wildcard src/added/pokemon/*.java)
JAVA_BATTLEGROUND_FILE = $(wildcard src/added/Battleground.java)


clean:
	rm -rf out
	rm -rf Manifest.MF

all: 
	$(JAVA_MOVES_FILES)
	$(JAVA_POKEMON_FILES)
	$(JAVA_BATTLEGROUND_FILE)

Manifest.MF: 
	echo "Manifest-Version: 1.0" > $@
	echo "Main-Class: added.Battleground" >> $@
	echo "Class-Path: Pokemon.jar" >> $@



out/added/moves: 
	javac -d out $(CP)  $(JAVA_MOVES_FILES)

out/added/pokemon: out/added/moves
	javac -d out $(CPext)  $(JAVA_POKEMON_FILES)


out/added/Battleground:  out/added/pokemon 
	javac $(CPext) -d out $(JAVA_BATTLEGROUND_FILE)



project.jar: out/added/Battleground Manifest.MF
	jar $(JARFALGS) $@ Manifest.MF out/added/*


# javac -d out -cp Pokemon.jar  added/moves/*.java 

# javac -cp out:Pokemon.jar -d out added/pokemon/*.java
# javac -cp out:Pokemon.jar -d out added/Battleground.java

# jar cvfm project.jar Manifest.MF out/added/* 


