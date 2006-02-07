all: stepper

include ../Makedefs

OBJS = PureState.o MixedState.o rk4.o display.o Matrices.o Bures.o gslMatrixUtils.o \
       Configuration.o Logger.o FileStreamDataLogger.o exceptions.o derivs.o main.o


# targets
stepper: $(OBJS)
	@echo "--- stepper ---"
	$(CXX) $(CFLAGS) $(LFLAGS) -o stepper $(OBJS) $(LIBS)

clean:
	@echo "cleaning up.."
	rm -f stepper core stepper.exe

clobber: clean
	rm -f *.o *~ $(COMMON)/*.o $(COMMON)/*~ *.out

depend:
	@echo "Updating dependancies..."
	makedepend -m -Y. -- $(CFLAGS) -- *.C *.h $(COMMON)/*.C $(COMMON)/*.h
#	makedepend -m -Y. -f.depend -- $(CFLAGS) -- *.C	

# DO NOT DELETE
#
