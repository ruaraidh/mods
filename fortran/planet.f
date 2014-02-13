      SUBROUTINE PLANET(DAY,LIST,IPV,PV,KRUT)
CP  PLANETARY EPHEMERIS IS READ FROM ONE OF 3 FILES:
C
C 1: IN MEAN SYSTEM OF 1950.0 WITH MODIFIED JULIAN DAY 1950, BETWEEN
C 1959/12/10 = (MJD1950) 3630  &  2022/01/21 = (MJD1950) 26318 ON FILE:
C /home/oalib/orblib/data/de118 to unit 12.
C
C 2: IN MEAN SYSTEM OF 2000.0 WITH MODIFIED JULIAN DAY 1950, BETWEEN
C 1960/01/11 = (MJD1950) 3662  &  2022/02/22 = (MJD1950) 26350 ON FILE:
C /home/oalib/orblib/data/de200 to unit 12.
C
C 3: IN MEAN SYSTEM OF 2000.0 WITH MODIFIED JULIAN DAY 2000, BETWEEN
C 1987/11/21 = (MJD2000) -4424 &  2050/01/02 = (MJD2000) 18264 ON FILE:
C /home/oalib/orblib/data/j2000 to unit 12.
C
C EACH FILE CONTAINS 709 DATA RECORDS AND 1 HEADER RECORD, 
C EACH DATA RECORD HAS DATA FOR 32 DAYS.
C COORDINATE SYSTEM IS EQUATORIAL; ORIGIN = SOLAR SYSTEM MASS CENTRE.
C
CI  DAY = EFEMERIS TIME MJD; FROM 1950 OR 2000 DEPENDING ON FILE.
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
C      CHARACTER*160 SCCS_INFO(2)
C     &/'@(#)/home/oalib/orblib/src/SCCS/s.planet.f	',
C     &'1.4	10/09/08 	ORBLIB\n'/
C
      IMPLICIT REAL*8(A-H,O-Z)
      DIMENSION LIST(11),PV(IPV,11)
      DIMENSION BUF(745),DINTP(11),IP(11),IC(11)
      DATA KODE/0/,EPS/1D-10/
C PARAMETERS DESCRIBING THE FILE:
C      DINT = TIME INTERVAL IN DAYS COVERED BY EACH RECORD
C      NREC = NUMBER OF RECORDS
C      NPL = NUMBER OF BODIES
C      DINTP = TIME INTERVAL IN DAYS FOR THE BODIES
C      IP = POINTERS TO THE START OF COEFFICIENTS FOR THE BODIES
C      IC = NUMBER OF COEFFICIENTS FOR THE BODIES
      DATA DINT/32D0/,NREC/710/,NPL/11/
      DATA DINTP/8D0,32D0,16D0,32D0,32D0,32D0,32D0,32D0,32D0,4D0,32D0/
      DATA IP/2,146,182,272,302,329,353,377,395,413,701/
      DATA IC/12,12,15,10,9,8,8,6,6,12,15/
C
      KRUT = 0
      IF(KODE .NE. 0) GOTO 10
C     OPEN, WITH RECORD LENGTH IN BYTES (= 8 * DIMENSION OF BUF)
      OPEN (12,ACCESS='DIRECT',RECL=5960)
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