//ANDREWJA JOB  IBM,SP,CLASS=A,MSGCLASS=X,NOTIFY=ANDREWJ
//STEP1    EXEC ASMACLG
//SYSIN    DD   *
*---------------------------------------------------------------------*
* Program Function
* This program is used to transform a sequential file with fixed length
* as LRECL into a VBM format.
*
* The input sequential file is a file to contain a file uploaded from
* a PC which is a standard AFP file like Font, Page Segment to contain
* AFP printing information and objects.
* Each line of the input file is in variable length and there must be
* a x'5A' leading byte at the very beginning of each line, followed
* by a 2-byte record length, then the data itself.
*
* A sequential file with RECFM = FB and LRECL = 80 is recommended.
*
* Author : Andrew Jan
* Created date : 5/Jul/2002
*---------------------------------------------------------------------*
*
         PRINT OFF
         LCLA  &REG
.LOOP    ANOP                              GENERATE REGS.
R&REG    EQU   &REG
&REG     SETA  &REG+1
         AIF   (&REG LE 15).LOOP
         PRINT ON
*
*------------------------------------------------*
*
         DCBD  DSORG=PS             dcb descriptor
*
*------------------------------------------------*
*
PSFILE   CSECT
PSFILE   AMODE  31
*SFILE   RMODE  ANY
         STM   R14,R12,12(R13)      use r13 as base as well as
         LR    R2,R13               reg-save area
         BALR  R12,0
         BAL   R13,76(R12)
SAVREG   DS    18F
         USING SAVREG,R13
         ST    R2,4(R13)
         ST    R13,8(R2)
*
*---MAINSTREAM------------------------------------*
*
I       USING  IHADCB,SEQIN         infile's dcb
O       USING  IHADCB,FONTM         outfile's dcb
*
        BAL    R6,OPEN_FILES        open files
*
        BAL    R6,GET_MAIN          get work for output
*
        B      GO_PROCESS
*
FINISH  EQU    *
        BAL    R6,CLOSE_FILES       close files
*
        B      RETURN               return to caller
*
*-------------------------------------------------------*
*
OPEN_FILES EQU  *
         OPEN  (FONTM,OUTPUT,SEQIN,INPUT,PRINT,OUTPUT)
         BR    R6
*
*-------------------------------------------------------*
*
GET_MAIN  EQU  *
         LH    R1,O.DCBLRECL        get input file's max lrecl.
         LA    R1,5(,R1)            add 2(len)+2(resved)+1(x'5a')
         GETMAIN RU,LV=(R1),        get the max size needed            X
               BNDRY=PAGE,          on a page boundary                 X
               LOC=(RES,ANY)        can be anywhere within 2 gb as
         ST    R1,OUTWKA            save it
         LR    R4,R1                save it
         BR    R6                   go back
*
*-------------------------------------------------------*
*
GO_PROCESS  EQU   *

         LH    R8,I.DCBLRECL        input rec length (fb)
         GET   SEQIN                read 1 rec
         LR    R2,R1                the strt addr

NEXT_OUTREC    EQU  *
         CLI   0(R2),X'5A'          flag ?
         BE    GO_ON                yes, correct

         CLI   0(R2),X'20'          space ? -- end
         B     FINISH               stop running

         PUT   PRINT,=C'Invalid control code!'
         B     FINISH               stop running

GO_ON    EQU   *
         XR    R3,R3                clear fro insert
         ICM   R3,B'0011',1(R2)     insert length (2 bytes)

         LA    R3,1(,R3)            plus the byte : x'5a'

         LR    R1,R3                copy length
         LA    R1,4(,R1)            plus extra 4 bytes
         STH   R1,0(,R4)            save the rec len to output(vbm)
         MVC   2(2,R4),=X'0000'     reserved
         LA    R4,4(,R4)            vbm format

CHECK_LEN      EQU *
         CR    R3,R8                within this rec ?
         BH    BEYOND_REC           no, branch

WITHIN_REC     EQU   *
         LR    R9,R3                temp save len (mvcl impairs r3)
         LR    R5,R3                lengths for mvcl
         MVCL  R4,R2                move to output

         L     R4,OUTWKA            str addr of output
         PUT   FONTM,0(R4)          output 1 rec
******   PUT   PRINT,0(R4)          ####################

         SR    R8,R9                bytes left  within a rec

         LTR   R8,R8                zero ?
         BZ    GO_PROCESS           yes, go process next rec

         B     NEXT_OUTREC          loop


BEYOND_REC EQU   *

         LR    R9,R3                temp save total rec len.

         LR    R3,R8                the rest within a rec
         LR    R5,R3                lengths for mvcl
         MVCL  R4,R2                move to output

         SR    R9,R8                deduct those moved

         LH    R8,I.DCBLRECL        input rec length (fb)
         GET   SEQIN                read 1 rec
         LR    R2,R1                the strt addr

         LR    R3,R9                new length

         B     CHECK_LEN            loop

*
*--------------------------------------------------------*
*
CLOSE_FILES EQU  *
         CLOSE  (SEQIN,,FONTM,,PRINT)       CLOSE FILES
         BR    R6
*
*--------------------------------------------------------*
*
RETURN   EQU   *
         L     R13,4(R13)
         RETURN (14,12),RC=0              BACK TO CALLER
*
*--------------------------------------------------------*
*
         LTORG
*
OUTWKA  DS  F
REGSAV  DS  F
WORK    DS  CL80
BLANK   DS  80C' '
*
*--------------------------------------------------------*
*
SEQIN   DCB DSORG=PS,DDNAME=SEQIN,MACRF=GL,EODAD=FINISH
FONTM   DCB DSORG=PS,DDNAME=FONTM,MACRF=PM
PRINT   DCB DSORG=PS,DDNAME=PRINT,MACRF=PM,LRECL=80
*
         END
/*
//G.SEQIN  DD  DISP=SHR,DSN=ANDREWJ.TEMP
//G.FONTM  DD  DISP=SHR,DSN=SYS1.CCPROD.AFP.PSEGLIB(TESTPSEG)
//G.PRINT  DD  SYSOUT=*
//
