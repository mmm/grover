all: stepper

include ../Makedefs

OBJS = fwrap.o Bures.o Matrices.o exceptions.o\
       main.o


# targets
stepper: $(OBJS)
	@echo "--- stepper ---"
	$(CXX) $(CFLAGS) $(LFLAGS) -o stepper $(OBJS) $(LIBS)

clean:
	@echo "cleaning up.."
	rm -f stepper core

clobber: clean
	rm -f *.o *~ $(COMMON)/*.o $(COMMON)/*~ *.out

depend:
	@echo "Updating dependancies..."
	makedepend -m -Y. -- $(CFLAGS) -- *.C *.h $(COMMON)/*.C $(COMMON)/*.h
#	makedepend -m -Y. -f.depend -- $(CFLAGS) -- *.C	

# DO NOT DELETE
