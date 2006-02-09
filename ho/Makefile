all: stepper

include ../Makedefs

OBJS = rk4.o \
       main.o derivs.o init.o cf.o


# targets
stepper: $(OBJS)
	@echo "--- stepper ---"
	$(CXX) $(CFLAGS) $(LFLAGS) -o stepper $^ $(LIBS)

clean:
	@echo "cleaning up.."
	rm -f stepper core stepper.exe

clobber: clean
	rm -f *.o *~ $(COMMON)/*.o $(COMMON)/*~ *.out

depend:
	@echo "Updating dependancies..."
	makedepend -m -Y. -- $(CFLAGS) -- *.C *.h $(COMMON)/*.C $(COMMON)/*.h

# DO NOT DELETE

