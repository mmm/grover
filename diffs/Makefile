all: stepper

include ../Makedefs

OBJS = State.o rk4.o display.o\
       derivs.o main.o


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

derivs.o: ../common/myvalarray.h derivs.h
main.o: ../common/State.h ../common/myvalarray.h ../common/display.h
derivs.o: ../common/myvalarray.h
State.o: ../common/rk4.h ../common/myvalarray.h ../common/State.h
display.o: ../common/myvalarray.h ../common/display.h
myvalarray.o: ../common/myvalarray.h
rk4.o: derivs.h ../common/myvalarray.h ../common/rk4.h
State.o: ../common/myvalarray.h
display.o: ../common/myvalarray.h
rk4.o: ../common/myvalarray.h
