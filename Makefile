# Definitions de macros
OUT = projet
CXX = g++
CXXFLAGS = -Wall -std=c++17 
LINKING = `pkg-config --cflags gtkmm-4.0`
LDLIBS = `pkg-config --libs gtkmm-4.0`
CXXFILES = projet.cc lifeform.cc message.cc shape.cc simulation.cc gui.cc graphic.cc
OFILES = projet.o lifeform.o message.o shape.o simulation.o gui.o graphic.o

# Definition de la premiere regle
all: $(OUT)

projet.o: projet.cc simulation.h lifeform.h shape.h gui.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)
lifeform.o: lifeform.cc message.h lifeform.h shape.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)
message.o: message.cc message.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)
shape.o: shape.cc shape.h graphic.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)
simulation.o: simulation.cc simulation.h lifeform.h shape.h message.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)
gui.o: gui.cc gui.h simulation.h lifeform.h shape.h graphic.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)
graphic.o: graphic.cc graphic.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)


$(OUT): $(OFILES)
	$(CXX) $(CXXFLAGS) $(LINKING) $(OFILES) -o $@ $(LDLIBS)

depend:
	@echo " *** MISE A JOUR DES DEPENDANCES ***"
	@(sed '/^# DO NOT DELETE THIS LINE/q' Makefile && \
	  $(CXX) -MM $(CXXFLAGS) $(CXXFILES) | \
	  egrep -v "/usr/include" \
	 ) >Makefile.new
	@mv Makefile.new Makefile


clean:
	@echo "Cleaning compilation files"
	@rm *.o $(OUT) *.cc~ *.h~

#
# -- Regles de dependances generees automatiquement
#
# DO NOT DELETE THIS LINE
