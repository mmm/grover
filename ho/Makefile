all: stepper

include ../Makedefs

OBJS = rk4.o myvalarray.o\
       main.o derivs.o init.o cf.o


# targets
stepper: $(OBJS)
	@echo "--- stepper ---"
	$(CXX) $(CFLAGS) $(LFLAGS) -o stepper $^ $(LIBS)

clean:
	@echo "cleaning up.."
	rm -f stepper

clobber: clean
	rm -f *.o *~ $(COMMON)/*.o $(COMMON)/*~

depend:
	@echo "Updating dependancies..."
	makedepend -m -Y. -- $(CFLAGS) -- *.C *.h $(COMMON)/*.h $(COMMON)/*.C

# DO NOT DELETE
