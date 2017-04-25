#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/camera.o \
	${OBJECTDIR}/gps.o \
	${OBJECTDIR}/hotwire.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/pressure.o \
	${OBJECTDIR}/servo.o \
	${OBJECTDIR}/temp.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-lraspicam -lraspicam_cv -lwiringPi -lwiringPiDev -lopencv_core -lopencv_imgcodecs -lopencv_highgui
CXXFLAGS=-lraspicam -lraspicam_cv -lwiringPi -lwiringPiDev -lopencv_core -lopencv_imgcodecs -lopencv_highgui

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/weather_balloon

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/weather_balloon: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/weather_balloon ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/camera.o: camera.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../raspicam -I../../wiringPi -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/camera.o camera.cpp

${OBJECTDIR}/gps.o: gps.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../wiringPi -I../../raspicam-0.0.7 -I../../opencv-master -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gps.o gps.cpp

${OBJECTDIR}/hotwire.o: hotwire.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../wiringPi -I../../raspicam-0.0.7 -I../../opencv-master -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hotwire.o hotwire.cpp

${OBJECTDIR}/hotwire.o: hotwire.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../raspicam -I../../wiringPi -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hotwire.o hotwire.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../wiringPi -I../../raspicam-0.0.7 -I../../opencv-master -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/pressure.o: pressure.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../wiringPi -I../../raspicam-0.0.7 -I../../opencv-master -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/pressure.o pressure.cpp

${OBJECTDIR}/servo.o: servo.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../wiringPi -I../../raspicam-0.0.7 -I../../opencv-master -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/servo.o servo.cpp

${OBJECTDIR}/temp.o: temp.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../wiringPi -I../../raspicam-0.0.7 -I../../opencv-master -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/temp.o temp.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
