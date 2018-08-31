##########################################################
#
#
#  copyright zhht.ltd
#
#
##########################################################


ifndef GXX  
    GXX := g++  
endif  
  
ifndef CXXFLAGS  
    CXXFLAGS := -g  
endif  
  
INCLUDE := -Itcp -Idaemon
  
CxxSources := $(shell find -iname *.cpp )  
  
Objs := $(CxxSources:.cpp=.o)  
  
execfile:$(Objs)  
	echo "CXXSources:" $(CxxSources)  
	echo "Objs:" $(Objs)  
	$(GXX)  -o $@ $(CXXFLAGS)  $(Objs)  
  
-include $(CxxSources:.cpp=.d)  
  
%.d : %.cpp  
	rm -f $@; \
	$(GXX) -MM $(INCLUDE) $< > $@.$$$$; \sed -e 's,^.*:,$*.o $@:,g' -e 's,$$,; $(GXX) -c $(CXXFLAGS) $(INCLUDE) $<,g'  < $@.$$$$ > $@; \  
	rm -f $@.$$$$  
  
.PHONY : clean  
  
clean:  
	echo $(CxxSources)  
	rm execfile $(CxxSources:.cpp=.d) $(CxxSources:.cpp=.o) 
