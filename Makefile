
# SOURCE FILES
CPPFILES = \
	main.cpp \
	job.cpp \
	applicant.cpp \
	hr.cpp \
	string_operations.cpp

OBJECTS=$(CPPFILES:.cpp=.o)

# COMPILATION SETTINGS
CC = g++-9.1.0
OPTIMISATION = -O2 -Wall
CPP_VERSION = -std=c++17
CFLAGS = -c $(OPTIMISATION) $(CPP_VERSION)

# LINKING SETTINGS
EXECUTABLE = hrsystem


# ACTIONS START HERE:
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $(EXECUTABLE)  $(OBJECTS)
	@echo -e "\033[1;32mBuilding $@...done!\n\033[0m"

%.o: %.cpp %.h
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)
