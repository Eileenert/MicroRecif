# Definitions de macros
CXX     = g++
CXXFLAGS = -g -Wall -std=c++11
CXXFILES = projet.cc lifeform.cc message.cc shape.cc simulation.cc gui.cc graphic.cc
OFILES = projet.o lifeform.o message.o shape.o simulation.o gui.o graphic.o

# Definition de la premiere regle

projet: $(OFILES)
	$(CXX) $(OFILES) -o projet

# Definitions de cibles particulieres

depend:
	@echo " *** MISE A JOUR DES DEPENDANCES ***"
	@(sed '/^# DO NOT DELETE THIS LINE/q' Makefile && \
	  $(CXX) -MM $(CXXFLAGS) $(CXXFILES) | \
	  egrep -v "/usr/include" \
	 ) >Makefile.new
	@mv Makefile.new Makefile

clean:
	@echo " *** EFFACE MODULES OBJET ET EXECUTABLE ***"
	@/bin/rm -f *.o *.x *.cc~ *.h~ projet

#
# -- Regles de dependances generees automatiquement
#
# DO NOT DELETE THIS LINE
projet.o: projet.cc simulation.h lifeform.h shape.h gui.h
lifeform.o: lifeform.cc message.h lifeform.h shape.h
message.o: message.cc message.h
shape.o: shape.cc shape.h graphic.h
simulation.o: simulation.cc simulation.h lifeform.h shape.h message.h
gui.o: gui.cc simulation.h lifeform.h shape.h graphic.h
graphic.o: graphic.cc
