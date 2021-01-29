
# These are variables. We usually define CC, CCLINK, CFLAGS, OBJS, EXEC and RM
CXX = g++
# Read variable CXX using $(CC)
CXXFLAGS = -g -Wall -Wextra -L.
RM = clean
LINKFLAF = -fPIC -shared

LIB_OBJS = string.cpp field.cpp port.cpp ip.cpp
MAIN_OBGS = main.cpp

EXECXX = firewall.exe
EXECXX_LIB = firewall
SUPP_LIB = input


all::${EXECXX}

$(EXECXX_LIB):
	$(CXX) ${CXXFLAGS} ${LINKFLAF} ${LIB_OBJS} -o lib${EXECXX_LIB}.so
${EXECXX}: ${EXECXX_LIB}
	$(CXX) ${CXXFLAGS} ${MAIN_OBGS} -o ${EXECXX} -l${EXECXX_LIB} -l${SUPP_LIB}

# We usually have a "clean" rule to delete any automatically generated files
$(RM):
	rm -rf *.o ${EXECXX} ${EXECXX_LIB}
	
