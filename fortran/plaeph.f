C Copyright (C) 2013 ESA, Flight Dynamics HSO-GF
      SUBROUTINE PLAEPH (DAY,LIST,IPV,PV,KRUT)
C
CP  GENERIC PLANETARY EPHEMERIDES ACCESS ROUTINE
C
CN  N.B. USE ORBIT LIBRARY ROUTINE PECOOT FOR CONSTANTS CONSISTENT
CN       WITH THE USED EPHEMERIDES.
C
CP  PLANETARY EPHEMERIS IS READ FROM ONE OF 9 FILES LINKED TO UNIT 12:
C
C 1: JPL EXPORT EPHEMERIDES DE118
C    FILE          : /home/oalib/orblib/data/de118
C    TIME FORMAT   : MODIFIED JULIAN DAY 1950 (MJD1950)
C    TIME SCALE    : EPHEMERIS TIME
C    START TIME    : 1959/12/10.0 = (MJD1950) 3630.0
C    END TIME      : 2022/01/21.0 = (MJD1950) 26318.0
C    ORIGIN        : SOLAR SYSTEM BARYCENTRE
C    REF.FRAME     : EARTH MEAN EQUATOR AND EQUINOX OF FK4/B1950
C
C 2: JPL EXPORT EPHEMERIDES DE200:
C    FILE          : /home/oalib/orblib/data/de200
C    TIME FORMAT   : MODIFIED JULIAN DAY 1950 (MJD1950)
C    TIME SCALE    : EPHEMERIS TIME 
C    START TIME    : 1960/01/11.0 = (MJD1950) 3662.0
C    END TIME      : 2022/02/22.0 = (MJD1950) 26350.0
C    ORIGIN        : SOLAR SYSTEM BARYCENTRE
C    REF.FRAME     : EARTH MEAN EQUATOR AND EQUINOX OF FK5/J2000
C
C 3: JPL EXPORT EPHEMERIDES DE200:
C    FILE          : /home/oalib/orblib/data/j2000
C    TIME FORMAT   : MODIFIED JULIAN DAY 2000 (MJD2000)
C    TIME SCALE    : EPHEMERIS TIME 
C    START TIME    : 1987/11/21.0 = (MJD2000) -4424.0
C    END TIME      : 2050/01/02.0 = (MJD2000) 18264.0
C    ORIGIN        : SOLAR SYSTEM BARYCENTRE
C    REF.FRAME     : EARTH MEAN EQUATOR AND EQUINOX OF FK5/J2000
C
C 4: JPL EXPORT EPHEMERIDES DE405:
C    FILE          : /home/oalib/orblib/data/de405
C    TIME FORMAT   : MODIFIED JULIAN DAY 2000 (MJD2000)
C    TIME SCALE    : BARYCENTRIC DYNAMICAL TIME (TDB)
C    START TIME    : 1899/12/04.0 = (MJD2000) -36552.0
C    END TIME      : 2050/01/02.0 = (MJD2000)  18264.0
C    ORIGIN        : SOLAR SYSTEM BARYCENTRE
C    REF.FRAME     : INTERNATIONAL CELESTIAL REFERENCE FRAME (ICRF)
C
C 5: JPL EXPORT EPHEMERIDES DE421:
C    FILE          : /home/oalib/orblib/data/de421
C    TIME FORMAT   : MODIFIED JULIAN DAY 2000 (MJD2000)
C    TIME SCALE    : BARYCENTRIC DYNAMICAL TIME (TDB)
C    START TIME    : 1899/12/04.0 = (MJD2000) -36552.0
C    END TIME      : 2050/01/02.0 = (MJD2000)  18264.0
C    ORIGIN        : SOLAR SYSTEM BARYCENTRE
C    REF.FRAME     : INTERNATIONAL CELESTIAL REFERENCE FRAME (ICRF)
C
C 6: IMCCE INPOP EPHEMERIDES 08: 
C    FILE          : /home/oalib/orblib/data/inpop08
C    TIME FORMAT   : MODIFIED JULIAN DAY 2000 (MJD2000)
C    TIME SCALE    : BARYCENTRIC DYNAMICAL TIME (TDB) ACC.TO IAU B3
C    START TIME    : 1899/12/12.5 = (MJD2000) -36543.5
C    END TIME      : 2050/01/10.5 = (MJD2000)  18272.5
C    ORIGIN        : SOLAR SYSTEM BARYCENTRE
C    REF.FRAME     : INTERNATIONAL CELESTIAL REFERENCE FRAME (ICRF)
C
C 7: IMCCE INPOP EPHEMERIDES 10A: 
C    FILE          : /home/oalib/orblib/data/inpop10a
C    TIME FORMAT   : MODIFIED JULIAN DAY 2000 (MJD2000)
C    TIME SCALE    : BARYCENTRIC DYNAMICAL TIME (TDB) ACC.TO IAU B3
C    START TIME    : 1899/12/12.5 = (MJD2000) -36543.5
C    END TIME      : 2050/01/10.5 = (MJD2000)  18272.5
C    ORIGIN        : SOLAR SYSTEM BARYCENTRE
C    REF.FRAME     : INTERNATIONAL CELESTIAL REFERENCE FRAME (ICRF)
C
C 8: IMCCE INPOP EPHEMERIDES 10E: 
C    FILE          : /home/oalib/orblib/data/inpop10e
C    TIME FORMAT   : MODIFIED JULIAN DAY 2000 (MJD2000)
C    TIME SCALE    : BARYCENTRIC DYNAMICAL TIME (TDB) ACC.TO IAU B3
C    START TIME    : 1899/12/12.5 = (MJD2000) -36543.5
C    END TIME      : 2050/01/10.5 = (MJD2000)  18272.5
C    ORIGIN        : SOLAR SYSTEM BARYCENTRE
C    REF.FRAME     : INTERNATIONAL CELESTIAL REFERENCE FRAME (ICRF)
C
C 9: JPL EXPORT EPHEMERIDES DE422:
C    FILE          : /home/oalib/orblib/data/de422
C    TIME FORMAT   : MODIFIED JULIAN DAY 2000 (MJD2000)
C    TIME SCALE    : BARYCENTRIC DYNAMICAL TIME (TDB)
C    START TIME    : 1799/12/16.0 = (MJD2000) -73064.0
C    END TIME      : 2300/01/20.0 = (MJD2000) 109592.0
C    ORIGIN        : SOLAR SYSTEM BARYCENTRE
C    REF.FRAME     : INTERNATIONAL CELESTIAL REFERENCE FRAME (ICRF)
C
CI  DAY = TIME ARGUMENT IN MJD2000
CI  LIST(I),I=1,11: PUT = 0 FOR GETTING NO DATA ON BODY NUMBER I,
CI                  PUT = 1 FOR ONLY POSITION OF BODY NUMBER I,
CI                  PUT = 2 FOR POSITION AND VELOCITY OF BODY NUMBER I.
CI  IPV = DIMENSION PV(IPV,11) PUT = 3 WHEN NO VELOCITIES ARE WANTED,
CI        PUT = 6 WHEN AT LEAST ONE VELOCITY IS WANTED.
C
C   ORDER OF DATA, FOR INDEX I = 1: MERCURY, 2: VENUS,
C  3: EARTH-MOON BARYCENTER, 4: MARS, 5: JUPITER, 6: SATURN,
C  7: URANUS, 8: NEPTUNE, 9: PLUTO, 10: MOON (GEOCENTRIC), 11: SUN.
C
CO  PV(IPV,I),I=1,11 = POSITION (KM) & VELOCITY (KM/S) OF THE BODY I
CO                     AT TIME DAY.
CO  KRUT = RETURN CODE; = 0  MEANS NO ERROR,
CO                      = 1  MEANS DAY IS TOO EARLY,
CO                      = 2  MEANS DAY IS TOO LATE,
CO                      = 3  MEANS FILE IS CORRUPTED,
CO                      = 4  EPHEMERIS FILE VERSION NOT RECOGNISED.
C
C      CHARACTER*130 SCCS_INFO(2)
C      DATA SCCS_INFO
C     &/'@(#)/home/oalib/orblib/src/SCCS/s.plaeph.f  ',
C     &' 1.4 13/02/06 ORBLIB\n'/
C
      IMPLICIT REAL*8(A-H,O-Z)
      DIMENSION LIST(11),PV(IPV,11)
      LOGICAL LOPEN
      DATA KODE/0/
      KRUT = 0
C
C  AT FIRST CALL CHECK FOR EPHEMERIS FILE VERSION
C
      IF (KODE .NE. 0) GOTO 10
      INQUIRE(12,OPENED=LOPEN)
      IF (.NOT. LOPEN) THEN
         OPEN (12,ACCESS='DIRECT',RECL=4)
         READ (12,REC=1,ERR=81) IEPHV
         CLOSE (12)
      ELSE
         READ (12,REC=1,ERR=81) IEPHV
      ENDIF
      IF (IEPHV .LT. 1) GOTO 82
      IF (IEPHV .GT. 9) GOTO 82
      KODE = 1
 10   CONTINUE
C
C  CALL READING ROUTINE DEPENDING ON FILE VERSION 
C
      IF (IEPHV .EQ. 9) THEN
         CALL PLA422 (DAY,LIST,IPV,PV,KRUT)
      ELSEIF (IEPHV .EQ. 8 .OR. IEPHV .EQ. 7) THEN
         CALL PLAI10 (DAY,LIST,IPV,PV,KRUT)
      ELSEIF (IEPHV .EQ. 7) THEN
         CALL PLAI10 (DAY,LIST,IPV,PV,KRUT)
      ELSEIF (IEPHV .EQ. 6) THEN
         CALL PLAI08 (DAY,LIST,IPV,PV,KRUT)
      ELSEIF (IEPHV .EQ. 5) THEN
         CALL PLA421 (DAY,LIST,IPV,PV,KRUT)
      ELSEIF (IEPHV .EQ. 4) THEN
         CALL PLA405 (DAY,LIST,IPV,PV,KRUT)
      ELSEIF (IEPHV .EQ. 3) THEN
         CALL PLANET (DAY,LIST,IPV,PV,KRUT)
      ELSEIF (IEPHV .LE. 2) THEN
         DAY50 = DAY + 18262.D0
         CALL PLANET (DAY50,LIST,IPV,PV,KRUT)
      ENDIF
      RETURN
C
C  ERROR RETURNS
C
82    KRUT = KRUT + 1
81    KRUT = KRUT + 3
      KODE = 0
      RETURN
      END
      
         
