C Copyright (C) 2013 ESA, Flight Dynamics HSO-GF
      SUBROUTINE PLAI10 (DAY,LIST,IPV,PV,KRUT)
C
CP  PLANETARY EPHEMERIDES DERIVED FROM IMCCE INPOP10A OR INPOP10E
C
CN  N.B. USE ORBIT LIBRARY ROUTINE PLCI10A FOR CONSTANTS CONSISTENT
CN       WITH INPOP10A EPHEMERIDES OR PLCI10E FOR CONSTANTS CONSISTENT
CN       WITH INPOP10E EPHEMERIDES
C
CN  N.B. THIS IS A LOW LEVEL "PRIVATE" SUBROUTINE. IT IS RECOMMENDED
CN       TO USE SUBROUTINE PLAEPH INSTEAD.
C
C IN MEAN SYSTEM OF J2000.0 WITH MODIFIED JULIAN DAY 2000, BETWEEN
C 1899/12/12.5 = (MJD2000) -36543.5 & 2050/01/10.5 = (MJD2000) 18272.5
C ON FILE: /home/oalib/orblib/data/inpop10a to unit 12 or
C          /home/oalib/orblib/data/inpop10e to unit 12
C
C THE FILE CONTAINS 1713 DATA RECORDS AND 1 HEADER RECORD, 
C EACH DATA RECORD HAS DATA FOR 32 DAYS.
C COORDINATE SYSTEM IS EQUATORIAL (ICRF); ORIGIN = SOLAR SYSTEM MASS CENTRE.
C
CI  DAY = MJD2000 IN BARYCENTRIC DYNAMICAL TIME (TDB)            
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
CO  PV(IPV,I),I=1,11 = POSITION (KM) & VELOCITY (KM/S) OF THE BODY I.
CO  KRUT = RETURN CODE; = 0  MEANS NO ERROR,
CO                      = 1  MEANS DAY IS TOO EARLY,
CO                      = 2  MEANS DAY IS TOO LATE,
CO                      = 3  MEANS FILE IS CORRUPTED.
C
C      CHARACTER*130 SCCS_INFO(2)
C      DATA SCCS_INFO
C     &/'@(#)/home/oalib/orblib/src/SCCS/s.plai10.f  ',
C     &' 1.2 13/02/06 ORBLIB\n'/
C
      IMPLICIT REAL*8(A-H,O-Z)
      DIMENSION LIST(11),PV(IPV,11)
      DIMENSION BUF(817),DINTP(11),IP(11),IC(11)
      DATA KODE/0/,EPS/1D-10/
C PARAMETERS DESCRIBING THE FILE:
C      DINT = TIME INTERVAL IN DAYS COVERED BY EACH RECORD
C      NREC = NUMBER OF RECORDS INCL. ONE HEADER RECORD
C      NPL = NUMBER OF BODIES
C      DINTP = TIME INTERVAL IN DAYS FOR THE BODIES
C      IP = POINTERS TO THE START OF COEFFICIENTS FOR THE BODIES
C      IC = NUMBER OF COEFFICIENTS FOR THE BODIES
      DATA DINT/32D0/,NREC/1714/,NPL/11/
      DATA DINTP/8D0,16D0,16D0,32D0,32D0,32D0,32D0,32D0,32D0,4D0,16D0/
      DATA IP/2,170,230,308,341,365,386,404,422,440,752/
      DATA IC/14,10,13,11,8,7,6,6,6,13,11/
C
      KRUT = 0
      IF(KODE .NE. 0) GOTO 10
C     OPEN, WITH RECORD LENGTH IN BYTES (= 8 * DIMENSION OF BUF)
      OPEN (12,ACCESS='DIRECT',RECL=6536)
C  INITIAL READ FROM FILE
      KODE = 2
      READ (12,REC=2,ERR=83) BUF
      DAYBEG = BUF(1) - DINT
   10 CONTINUE
      KEY = (DAY - DAYBEG)/DINT + 1
      IF(KEY .LT. 2) GO TO 81
      IF(KEY .GT. NREC) GOTO 82
      IF(KEY .EQ. KODE) GOTO 20
      KODE = KEY
      READ (12,REC=KEY,ERR=83) BUF
   20 CONTINUE
      DIF = DAY - BUF(1)
      IF(DIF .LT. -EPS) GOTO 83
      IF(DIF .GT. DINT + EPS) GOTO 83
C
C  START DO-LOOP TO GO THROUGH ALL BODIES
      DO 50 I = 1,NPL
      LISTI = LIST(I)
C
C  CHECK IF THIS BODY SHOULD BE CALCULATED
      IF(LISTI .LE. 0) GO TO 50
      F = DIF/DINTP(I)
      NN = F
      MAXINT = IDINT(DINT/DINTP(I) + EPS) - 1
      NN = MIN0(NN,MAXINT)
      FN = NN
      S = 4D0*(F - FN) - 2D0
      J1 = IP(I) + NN*3*IC(I)
      JS1 = IC(I)
      JS2 = 2*JS1
      J2 = J1 + JS1 - 1
      PA = .5D0*S
      PB = S*PA - 1D0
      DA = 0.5D0
      DB = S
      R1 = 0D0
      R2 = 0D0
      R3 = 0D0
      V1 = 0D0
      V2 = 0D0
      V3 = 0D0
C
C  CALCULATE POSITIONS
      DO 40 J = J1,J2
      P = PA
      PA = S*PA - PB
      PB = P
      R1 = R1 + BUF(J)*PA
      R2 = R2 + BUF(J + JS1)*PA
      R3 = R3 + BUF(J + JS2)*PA
C
C  CALCULATE DERIVATIVE IF REQUESTED
      IF(LISTI .EQ. 1) GOTO 40
      D = DA
      DA = S*DA - DB + P
      DB = D
      V1 = V1 + BUF(J)*DA
      V2 = V2 + BUF(J + JS1)*DA
      V3 = V3 + BUF(J + JS2)*DA
   40 CONTINUE
      PV(1,I) = R1
      PV(2,I) = R2
      PV(3,I) = R3
      IF(LISTI .EQ. 1) GO TO 50
C
C  SCALE FACTOR FOR DERIVATIVE
      SCALE = 216D2*DINTP(I)
      PV(4,I) = V1/SCALE
      PV(5,I) = V2/SCALE
      PV(6,I) = V3/SCALE
   50 CONTINUE
      RETURN
C
C  ERROR RETURNS
83    KRUT = 1
82    KRUT = KRUT + 1
81    KRUT = KRUT + 1
      KODE = 0
      RETURN
      END
