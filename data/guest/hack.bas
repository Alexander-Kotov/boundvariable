X DIM user(VIII) AS STRING
XX user(I) = "ftd"
XXX user(II) = "knr"
XL user(III) = "gardener"
L user(IV) = "ohmega"
LX user(V) = "yang"
LXX user(VI) = "howie"
LXXX user(VII) = "hmonk"
XC user(VIII) = "bbarker"
C DIM pass(LIII) AS STRING
CX pass(I) = "airplane"
CXX pass(II) = "alphabet"
CXXX pass(III) = "aviator"
CXL pass(IV) = "bidirectional"
CL pass(V) = "changeme"
CLX pass(VI) = "creosote"
CLXX pass(VII) = "cyclone"
CLXXX pass(VIII) = "december"
CXC pass(IX) = "dolphin"
CC pass(X) = "elephant"
CCX pass(XI) = "ersatz"
CCXX pass(XII) = "falderal"
CCXXX pass(XIII) = "functional"
CCXL pass(XIV) = "future"
CCL pass(XV) = "guitar"
CCLX pass(XVI) = "gymnast"
CCLXX pass(XVII) = "hello"
CCLXXX pass(XVIII) = "imbroglio"
CCXC pass(XIX) = "january"
CCC pass(XX) = "joshua"
CCCX pass(XXI) = "kernel"
CCCXX pass(XXII) = "kingfish"
CCCXXX pass(XXIII) = "(\b.bb)(\v.vv)"
CCCXL pass(XXIV) = "millennium"
CCCL pass(XXV) = "monday"
CCCLX pass(XXVI) = "nemesis"
CCCLXX pass(XXVII) = "oatmeal"
CCCLXXX pass(XXVIII) = "october"
CCCXC pass(XXIX) = "paladin"
CD pass(XXX) = "pass"
CDX pass(XXXI) = "password"
CDXX pass(XXXII) = "penguin"
CDXXX pass(XXXIII) = "polynomial"
CDXL pass(XXXIV) = "popcorn"
CDL pass(XXXV) = "qwerty"
CDLX pass(XXXVI) = "sailor"
CDLXX pass(XXXVII) = "swordfish"
CDLXXX pass(XXXVIII) = "symmetry"
CDXC pass(XXXIX) = "system"
D pass(XL) = "tattoo"
DX pass(XLI) = "thursday"
DXX pass(XLII) = "tinman"
DXXX pass(XLIII) = "topography"
DXL pass(XLIV) = "unicorn"
DL pass(XLV) = "vader"
DLX pass(XLVI) = "vampire"
DLXX pass(XLVII) = "viper"
DLXXX pass(XLVIII) = "warez"
DXC pass(XLIX) = "xanadu"
DC pass(L) = "xyzzy"
DCX pass(LI) = "zephyr"
DCXX pass(LII) = "zeppelin"
DCXXX pass(LIII) = "zxcvbnm"
DCXL DIM i AS INTEGER
DCL DIM j AS INTEGER
DCLX DIM k AS INTEGER
DCLXX DIM m AS INTEGER
DCLXXX i = I
DCXC j = I
DCC IF CHECKPASS(user(i), pass(j)) THEN GOTO MM
DCCX k = I
DCCXX m = I
DCCXXX IF CHECKPASS(user(i), pass(j) + CHR(XLVIII + k - I) + CHR(XLVIII + m - I)) THEN GOTO MMCC
DCCXL m = m + I
DCCL IF m <= X THEN GOTO DCCXXX
DCCLX k = k + I
DCCLXX IF k <= X THEN GOTO DCCXX
DCCLXXX j = j + I
DCCXC IF j <= LIII THEN GOTO DCC
DCCC i = i + I
DCCCX IF i <= VIII THEN GOTO DCXC
DCCCXX END
MM PRINT user(i) + " " + pass(j)
MMX PRINT CHR(X)
MMXX GOTO DCCC
MMCC PRINT user(i) + " " + pass(j) + CHR(XLVIII + k - I) + CHR(XLVIII + m - I)
MMCCX PRINT CHR(X)
MMCCXX GOTO DCCC
