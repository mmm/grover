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

cf.o: ../common/myvalarray.h cf.h
derivs.o: ../common/myvalarray.h derivs.h
init.o: ../common/myvalarray.h derivs.h
main.o: ../common/myvalarray.h ../common/rk4.h derivs.h init.h cf.h
cf.o: ../common/myvalarray.h
derivs.o: ../common/myvalarray.h
init.o: ../common/myvalarray.h
../common/Bures.o: ../include/tnt/tnt.h ../include/tnt/version.h
../common/Bures.o: ../include/tnt/subscrpt.h ../include/tnt/tntmath.h
../common/Bures.o: ../include/tnt/cmat.h ../include/tnt/vec.h
../common/Bures.o: ../include/tnt/region2d.h ../include/tnt/index.h
../common/fwrap.o: ../include/tnt/tnt.h ../include/tnt/version.h
../common/fwrap.o: ../include/tnt/subscrpt.h ../include/tnt/tntmath.h
../common/fwrap.o: ../include/tnt/vec.h ../include/tnt/fmat.h
../common/fwrap.o: ../include/tnt/vec.h ../include/tnt/region2d.h
../common/fwrap.o: ../include/tnt/index.h
../common/Matrices.o: ../include/tnt/tnt.h ../include/tnt/version.h
../common/Matrices.o: ../include/tnt/subscrpt.h ../include/tnt/tntmath.h
../common/Matrices.o: ../include/tnt/cmat.h ../include/tnt/vec.h
../common/Matrices.o: ../include/tnt/region2d.h ../include/tnt/index.h
../common/Matrices.o: ../include/tnt/fmat.h ../include/random/uniform.h
../common/Matrices.o: ../include/random/default.h ../include/random/mt.h
../common/Matrices.o: ../include/blitz/blitz.h ../include/blitz/compiler.h
../common/Matrices.o: ../include/blitz/config.h ../include/blitz/tuning.h
../common/Matrices.o: ../include/blitz/tau.h ../include/blitz/bzdebug.h
../common/MixedState.o: ../common/PureState.h ../common/State.h
../common/MixedState.o: ../include/tnt/tnt.h ../include/tnt/version.h
../common/MixedState.o: ../include/tnt/subscrpt.h ../include/tnt/tntmath.h
../common/MixedState.o: ../include/tnt/cmat.h ../include/tnt/vec.h
../common/MixedState.o: ../include/tnt/region2d.h ../include/tnt/index.h
../common/MixedState.o: ../include/tnt/fmat.h ../include/random/uniform.h
../common/MixedState.o: ../include/random/default.h ../include/random/mt.h
../common/MixedState.o: ../include/blitz/blitz.h ../include/blitz/compiler.h
../common/MixedState.o: ../include/blitz/config.h ../include/blitz/tuning.h
../common/MixedState.o: ../include/blitz/tau.h ../include/blitz/bzdebug.h
../common/PureState.o: ../common/State.h ../include/tnt/tnt.h
../common/PureState.o: ../include/tnt/version.h ../include/tnt/subscrpt.h
../common/PureState.o: ../include/tnt/tntmath.h ../include/tnt/cmat.h
../common/PureState.o: ../include/tnt/vec.h ../include/tnt/region2d.h
../common/PureState.o: ../include/tnt/index.h ../include/tnt/fmat.h
../common/PureState.o: ../include/random/uniform.h
../common/PureState.o: ../include/random/default.h ../include/random/mt.h
../common/PureState.o: ../include/blitz/blitz.h ../include/blitz/compiler.h
../common/PureState.o: ../include/blitz/config.h ../include/blitz/tuning.h
../common/PureState.o: ../include/blitz/tau.h ../include/blitz/bzdebug.h
../common/State.o: ../include/tnt/tnt.h ../include/tnt/version.h
../common/State.o: ../include/tnt/subscrpt.h ../include/tnt/tntmath.h
../common/State.o: ../include/tnt/cmat.h ../include/tnt/vec.h
../common/State.o: ../include/tnt/region2d.h ../include/tnt/index.h
../common/State.o: ../include/tnt/fmat.h ../include/random/uniform.h
../common/State.o: ../include/random/default.h ../include/random/mt.h
../common/State.o: ../include/blitz/blitz.h ../include/blitz/compiler.h
../common/State.o: ../include/blitz/config.h ../include/blitz/tuning.h
../common/State.o: ../include/blitz/tau.h ../include/blitz/bzdebug.h
../common/Bures.o: ../common/Matrices.h ../include/tnt/tnt.h
../common/Bures.o: ../include/tnt/version.h ../include/tnt/subscrpt.h
../common/Bures.o: ../include/tnt/tntmath.h ../include/tnt/cmat.h
../common/Bures.o: ../include/tnt/vec.h ../include/tnt/region2d.h
../common/Bures.o: ../include/tnt/index.h ../include/tnt/fmat.h
../common/Bures.o: ../include/random/uniform.h ../include/random/default.h
../common/Bures.o: ../include/random/mt.h ../include/blitz/blitz.h
../common/Bures.o: ../include/blitz/compiler.h ../include/blitz/config.h
../common/Bures.o: ../include/blitz/tuning.h ../include/blitz/tau.h
../common/Bures.o: ../include/blitz/bzdebug.h ../common/exceptions.h
../common/Bures.o: ../common/Bures.h
../common/exceptions.o: ../common/exceptions.h
../common/fwrap.o: ../include/tnt/tnt.h ../include/tnt/version.h
../common/fwrap.o: ../include/tnt/subscrpt.h ../include/tnt/tntmath.h
../common/fwrap.o: ../include/tnt/vec.h ../include/tnt/fmat.h
../common/fwrap.o: ../include/tnt/vec.h ../include/tnt/region2d.h
../common/fwrap.o: ../include/tnt/index.h ../include/tnt/fortran.h
../common/Matrices.o: ../include/tnt/fmat.h ../include/tnt/subscrpt.h
../common/Matrices.o: ../include/tnt/vec.h ../include/tnt/region2d.h
../common/Matrices.o: ../include/tnt/index.h ../common/fwrap.h
../common/Matrices.o: ../include/tnt/tnt.h ../include/tnt/version.h
../common/Matrices.o: ../include/tnt/tntmath.h ../include/tnt/vec.h
../common/Matrices.o: ../common/exceptions.h ../common/Matrices.h
../common/Matrices.o: ../include/tnt/cmat.h ../include/random/uniform.h
../common/Matrices.o: ../include/random/default.h ../include/random/mt.h
../common/Matrices.o: ../include/blitz/blitz.h ../include/blitz/compiler.h
../common/Matrices.o: ../include/blitz/config.h ../include/blitz/tuning.h
../common/Matrices.o: ../include/blitz/tau.h ../include/blitz/bzdebug.h
../common/MixedState.o: ../common/rk4.h ../common/Matrices.h
../common/MixedState.o: ../include/tnt/tnt.h ../include/tnt/version.h
../common/MixedState.o: ../include/tnt/subscrpt.h ../include/tnt/tntmath.h
../common/MixedState.o: ../include/tnt/cmat.h ../include/tnt/vec.h
../common/MixedState.o: ../include/tnt/region2d.h ../include/tnt/index.h
../common/MixedState.o: ../include/tnt/fmat.h ../include/random/uniform.h
../common/MixedState.o: ../include/random/default.h ../include/random/mt.h
../common/MixedState.o: ../include/blitz/blitz.h ../include/blitz/compiler.h
../common/MixedState.o: ../include/blitz/config.h ../include/blitz/tuning.h
../common/MixedState.o: ../include/blitz/tau.h ../include/blitz/bzdebug.h
../common/MixedState.o: ../common/exceptions.h ../common/MixedState.h
../common/MixedState.o: ../common/PureState.h ../common/State.h
../common/PureState.o: ../common/rk4.h ../common/Matrices.h
../common/PureState.o: ../include/tnt/tnt.h ../include/tnt/version.h
../common/PureState.o: ../include/tnt/subscrpt.h ../include/tnt/tntmath.h
../common/PureState.o: ../include/tnt/cmat.h ../include/tnt/vec.h
../common/PureState.o: ../include/tnt/region2d.h ../include/tnt/index.h
../common/PureState.o: ../include/tnt/fmat.h ../include/random/uniform.h
../common/PureState.o: ../include/random/default.h ../include/random/mt.h
../common/PureState.o: ../include/blitz/blitz.h ../include/blitz/compiler.h
../common/PureState.o: ../include/blitz/config.h ../include/blitz/tuning.h
../common/PureState.o: ../include/blitz/tau.h ../include/blitz/bzdebug.h
../common/PureState.o: ../common/exceptions.h ../common/PureState.h
../common/PureState.o: ../common/State.h
../common/rk4.o: derivs.h ../common/myvalarray.h ../common/rk4.h
../common/State.o: ../common/rk4.h ../include/tnt/tnt.h
../common/State.o: ../include/tnt/version.h ../include/tnt/subscrpt.h
../common/State.o: ../include/tnt/tntmath.h ../include/tnt/cmat.h
../common/State.o: ../include/tnt/vec.h ../include/tnt/region2d.h
../common/State.o: ../include/tnt/index.h ../include/tnt/fmat.h
../common/State.o: ../common/State.h ../include/random/uniform.h
../common/State.o: ../include/random/default.h ../include/random/mt.h
../common/State.o: ../include/blitz/blitz.h ../include/blitz/compiler.h
../common/State.o: ../include/blitz/config.h ../include/blitz/tuning.h
../common/State.o: ../include/blitz/tau.h ../include/blitz/bzdebug.h
