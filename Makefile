APP = ddr-qos

# Add any other object files to this list below
APP_OBJS = *.o

all: build

build: $(APP)

$(APP): $(APP_OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $(APP_OBJS) $(LDLIBS)
clean:
	rm -f $(APP) *.o *.elf
