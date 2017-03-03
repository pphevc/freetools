# Defining the output file
OUTPUT := HeatMap.out


# Compiler flags  
CC := gcc -std=c99 -c


# Linker flags
LINKER := gcc

# Defining all the source files   
SOURCES :=  ../../code/src/HeatMap.c \
            ../../code/src/Heatmap_ArgParser.c \
            ../../code/src/Heatmap_bufferManager.c \
            ../../code/src/Heatmap_performOverlay.c

# Deriving object file list   
OBJS := ${SOURCES:%.c=%.o}


# Defining all the include directory paths 
INCLUDES := -I ../../code/inc


# Compiling the C source files to get the corresponding object files
%.o:%.c
	$(CC) $(INCLUDES) -o $@ $<

# Rules to build the target.
$(OUTPUT): $(OBJS)
	$(LINKER) $(OBJS) -lm -o $(OUTPUT)


# Defining remove and force remove flag for target clean 
RM := rm
RM_FLAGS := -f
clean:
	$(RM) $(RM_FLAGS) $(OBJS) $(OUTPUT)






