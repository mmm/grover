all: stepper

include ../Makedefs

OBJS = rk4.o display.o myvalarray.o\
       main.o derivs.o init.o 


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

cf.o: ../common/myvalarray.h cf.h
derivs.o: ../common/myvalarray.h derivs.h
init.o: ../common/myvalarray.h derivs.h
main.o: ../common/myvalarray.h ../common/rk4.h derivs.h init.h cf.h
cf.o: ../common/myvalarray.h
derivs.o: ../common/myvalarray.h
init.o: ../common/myvalarray.h
myvalarray.o: ../common/myvalarray.h
rk4.o: derivs.h ../common/myvalarray.h ../common/rk4.h
