all: stepper

include ../Makedefs

OBJS = rk4.o myvalarraydouble.o \
       main.o derivs.o init.o cf.o
#OBJS = $(COMMON)/rk4.o $(COMMON)/myvalarraydouble.o \


# targets
stepper: $(OBJS)
	@echo "--- stepper ---"
	g++ $(CFLAGS) $(LFLAGS) -o stepper $(OBJS) $(LIBS)

clean:
	@echo "cleaning up.."
	rm -f stepper

clobber: clean
	rm -f *.o *~ $(COMMON)/*.o $(COMMON)/*~

depend:
	@echo "Updating dependancies..."
	makedepend -m -Y. -- $(CFLAGS) -- *.C *.h $(COMMON)/*.C $(COMMON)/*.h
#	makedepend -m -Y. -f.depend -- $(CFLAGS) -- *.C	

# DO NOT DELETE

cf.o: ../common/myvalarraydouble.h cf.h
derivs.o: ../common/myvalarraydouble.h derivs.h
init.o: ../common/myvalarraydouble.h derivs.h
stepper.o: ../common/myvalarraydouble.h ../common/rk4.h derivs.h init.h cf.h
cf.o: ../common/myvalarraydouble.h
derivs.o: ../common/myvalarraydouble.h
init.o: ../common/myvalarraydouble.h
../common/myvalarraydouble.o: ../common/myvalarraydouble.h
../common/rk4.o: derivs.h ../common/myvalarraydouble.h ../common/rk4.h
../common/rk4.o: ../common/myvalarraydouble.h
