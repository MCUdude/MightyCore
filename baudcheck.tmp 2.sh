# 1 "baudcheck.c"
# 1 "/Users/hans/Documents/Arduino/subtrees/optiboot_flash//"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "baudcheck.c"
# 24 "baudcheck.c"
bpsx=38400
bps=${bpsx/L/}
bps=${bps/U/}
fcpux=22118400L
fcpu=${fcpux/L/}
fcpu=${fcpu/U/}
# 38 "baudcheck.c"
BAUD_SETTING=$(( ( ($fcpu + $bps * 4) / (($bps * 8))) - 1 ))
# 50 "baudcheck.c"
BAUD_ACTUAL=$(( ($fcpu/(8 * (($BAUD_SETTING)+1))) ))

BAUD_ERROR=$(( (( 100*($BAUD_ACTUAL - $bps) ) / $bps) ))
ERR_TS=$(( ((( 1000*($BAUD_ACTUAL - $bps) ) / $bps) - $BAUD_ERROR * 10) ))
ERR_TENTHS=$(( ERR_TS > 0 ? ERR_TS: -ERR_TS ))




echo -e -n BAUD RATE CHECK: Desired: $bps Real: $BAUD_ACTUAL UBRRL = $BAUD_SETTING Difference: $BAUD_ERROR.$ERR_TENTHS \%
