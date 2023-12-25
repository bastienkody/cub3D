#! /bin/bash

# ------------------------------------------------------------------------------
# 					------- CUB3D PARSING TESTER -------
# ------------------------------------------------------------------------------

dir=./
exec="./cub3D"

#turn bool_ to 0 to skip specific tests
bool_makefile=0

# const
ITA="\033[3m"
BOLD="\033[1m"
UNDERL="\033[4m"
GREEN="\033[32m"
RED="\033[31m"
YEL="\033[33m"
END="\033[m"
BLU_BG="\033[44m"
YEL_BG="\033[43;1m"
RED_BG="\033[41;1m"

# print intro
echo "------------------------------------"
echo "------------------------------------"
echo -e "${BOLD}\tCub3D parsing tester${END}"
echo -e "Started at $(date +%R) - $(date +"%d %B %Y")"
echo -e "by $USER on $(uname) os"
echo -e "made by bguillau (@bastienkody)"
echo "------------------------------------"
echo "------------------------------------"

# ------------------------------------------------------------------------------
#				-----		MAKEFILE		-----
# ------------------------------------------------------------------------------
if [[ $bool_makefile == 1 ]] ; then 
echo -e "${YEL_BG}Makefile${END}"

#---------------
# makefile relink
echo -ne "${BLU_BG}Test Makefile${END}\t\t"
make re 1>/dev/null 2> stderrmake.txt
make  > stdoutmakebis.txt 2>&1
[[ -s stderrmake.txt ]] && echo -ne "${RED}make wrote on std err${END}" || echo -ne "${GREEN}no make error${END}" 
echo -n " -- "
cat stdoutmakebis.txt | egrep -viq "(nothin|already|date)" && echo -e "${RED}makefile relink?${END}" || echo -e "${GREEN}no relink${END}"
rm -rf stderrmake.txt stdoutmakebis.txt

#-------------------------
# makefile : flags and rule
echo -ne "${BLU_BG}Makefile flags${END}\t\t"
grep -sq -- "-Wall" Makefile && echo -ne "${GREEN}OK (-Wall)${END}" || echo -ne "${RED}-Wall not found${END}"
echo -n " -- "
grep -sq -- "-Wextra" Makefile && echo -ne "${GREEN}OK (-Wextra)${END}" || echo -ne "${RED}-Wextra not found${END}"
echo -n " -- "
grep -sq -- "-Werror" Makefile && echo -ne "${GREEN}OK (-Werror)${END}" || echo -ne "${RED}-Werror not found${END}"
echo -n " -- "

else make >/dev/null ; fi

# ------------------------------------------------------------------------------
#				-----		TESTS		-----
# ------------------------------------------------------------------------------


###########################################
#	arg error
	#	no arg
	#	2 args
	#	not *.cub
	#	only space as name
	#	env -i
echo -e "${YEL_BG}Textures error tests${END}"

echo -e "${BLU_BG}${exec} (no arg)${END}\t"
${exec}
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec} map/map.cub map/map.cub ${END}\t"
${exec} map/map.cub map/map.cub
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec} map/noextmap ${END}\t"
${exec} map/noextmap
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec} \"  \" ${END}\t"
${exec} " "
echo "----------------------------------------------------------------"

echo -e "${BLU_BG} env -i ${exec} map/map.cub ${END}\t"
env -i ${exec} map/map.cub 
echo "----------------------------------------------------------------"


###########################################
#	textures : [rgb + map ok]
	#	1 missing											ok
	#	all missin											ok
	#	bad ID : ie. NORTH or P								ok
	#	not a .xpm : .xpn, .mp4, .cub, no ext				ok
	#	redifinition of 1									ok
	#	redefinition of all									ok
	# 	is a directory										ok
	#	unexisting											ok
	#	no rights											ok
	#	all or some textures after the map					ok
	#	multi space separation								ok
echo -e "${YEL_BG}Textures error tests${END}"

d="map/wrongs/textures/"

echo -e "${BLU_BG}${exec} ${d}1missing.cub ${END}\t"
${exec} ${d}1missing.cub
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec} ${d}allmissing.cub ${END}\t"
${exec} ${d}allmissing.cub
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec} ${d}badid.cub ${END}\t"
${exec} ${d}badid.cub
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec} ${d}badid2.cub ${END}\t"
${exec} ${d}badid2.cub
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec} ${d}notxpm.cub ${END}\t"
${exec} ${d}notxpm.cub
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec} ${d}notxpm2.cub ${END}\t"
${exec} ${d}notxpm2.cub
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec} ${d}notxpm3.cub ${END}\t"
${exec} ${d}notxpm3.cub
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec} ${d}notxpm4.cub ${END}\t"
${exec} ${d}notxpm4.cub
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec} ${d}redef1.cub ${END}\t"
${exec} ${d}redef1.cub
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec} ${d}redefall.cub ${END}\t"
${exec} ${d}redefall.cub
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec} ${d}isadir.cub ${END}\t"
${exec} ${d}isadir.cub
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec} ${d}unexist.cub ${END}\t"
${exec} ${d}unexist.cub
echo "----------------------------------------------------------------"


## WTF NIQUE BIEN TA GM TOI FDP ARGHHHHHHHH
#echo -e "${BLU_BG}${exec} noreadingright.cub ${END}\t"
#echo truc > noreadingright.cub || pwd
#cat noreadingright.cub && chmod u-r noreadingright.cub ||{ pwd ; exit ; }
#${exec} noreadingright.cub
#rm noreadingright.cub 
#echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec} ${d}aftermap.cub ${END}\t"
${exec} ${d}aftermap.cub
echo "----------------------------------------------------------------"

########################################
#	rgb : [textures + map ok]
	#	1 missing															ok
	#	all missing															ok
	#	redifinition of 1													ok
	# 	redef all															ok
	#	after map 															ok
	#	bad ID : Floor, R													ok
	#	bad format value : 4 digit, bad comma, bad sep, letter				ok
	#	bad values : -1, 2w, 256, 0x12, 0257 + some nicer overflow			ok
	#	multi space separation												ok
echo -e "${YEL_BG}Rgb error tests${END}"

d="map/wrongs/rgb/"

echo -e "${BLU_BG}${exec} ${d}1missing.cub ${END}\t"
${exec} ${d}1missing.cub
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec} ${d}allmissing.cub ${END}\t"
${exec} ${d}allmissing.cub
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec} ${d}redef1.cub ${END}\t"
${exec} ${d}redef1.cub
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec} ${d}redefall.cub ${END}\t"
${exec} ${d}redefall.cub
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec} ${d}aftermap.cub ${END}\t"
${exec} ${d}aftermap.cub
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec} ${d}badid.cub ${END}\t"
${exec} ${d}badid.cub
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec} ${d}badid2.cub ${END}\t"
${exec} ${d}badid2.cub
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec} ${d}4digit.cub ${END}\t"
${exec} ${d}4digit.cub
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec} ${d}badcomma.cub ${END}\t"
${exec} ${d}badcomma.cub
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec} ${d}badsep.cub ${END}\t"
${exec} ${d}badsep.cub
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec} ${d}letter.cub ${END}\t"
${exec} ${d}letter.cub
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec} ${d}negvalue.cub ${END}\t"
${exec} ${d}negvalue.cub
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec} ${d}ovfl256.cub ${END}\t"
${exec} ${d}ovfl256.cub
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec} ${d}ovfl525.cub ${END}\t"
${exec} ${d}ovfl525.cub
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec} ${d}ovflint32.cub ${END}\t"
${exec} ${d}ovflint32.cub
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec} ${d}ovfluint32.cub ${END}\t"
${exec} ${d}ovfluint32.cub
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec} ${d}ovflull.cub ${END}\t"
${exec} ${d}ovflull.cub
echo "----------------------------------------------------------------"


########################################
#	map : [textures + rgb ok]
	#	not perfectly walled		ok
	#	bad char					ok
	#	spaces between lines		ok
	#	no player pos				ok
	#	multi player pos			ok
	#	valid islands				
	#	empty line between			ok
	#	empty line at the end		ok
echo -e "${YEL_BG}Map error tests${END}"

d="map/wrongs/map/"

echo -e "${BLU_BG}${exec} ${d}1wallmissing.cub ${END}\t"
${exec} ${d}1wallmissing.cub
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec} ${d}wallsmissing.cub ${END}\t"
${exec} ${d}wallsmissing.cub
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec} ${d}badchar.cub ${END}\t"
${exec} ${d}badchar.cub
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec} ${d}emptymaplines.cub ${END}\t"
${exec} ${d}emptymaplines.cub
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec} ${d}endl.cub ${END}\t"
${exec} ${d}endl.cub
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec} ${d}nopp.cub ${END}\t"
${exec} ${d}nopp.cub
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec} ${d}multipp.cub ${END}\t"
${exec} ${d}multipp.cub
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec} ${d}multippsame.cub ${END}\t"
${exec} ${d}multippsame.cub
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec} ${d}spacetofloor.cub ${END}\t"
${exec} ${d}spacetofloor.cub
echo "----------------------------------------------------------------"

##################################################################
# is timeout needed? or pipes? oh, just bg jobs with & ??
##################################################################
echo -e "${YEL_BG}General tests that should launch the game (in background with '&')${END}"
echo -e "${ITA}You must close (nb tests = 8) cub3D windows${END}"
echo -e "${ITA}No error messages expected below (unless map spaces are not handled)${END}"

echo -e "${BLU_BG}Spaces in textures : ${exec} map/wrongs/textures/spaces.cub ${END}\t"
${exec} map/wrongs/textures/spaces.cub &
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}Spaces in rgb : ${exec} map/wrongs/rgb/spaces.cub ${END}\t"
${exec} map/wrongs/rgb/spaces.cub &
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}Empty lines between rgb : ${exec} map/wrongs/rgb/lineempty.cub ${END}\t"
${exec} map/wrongs/rgb/lineempty.cub &
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec}Spaces on map : map/wrongs/map/goodspaces.cub ${END}\t"
${exec} map/wrongs/map/goodspaces.cub &
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec}Lshape map : map/wrongs/map/lshape.cub ${END}\t"
${exec} map/wrongs/map/lshape.cub &
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec}Little island in map : map/wrongs/map/island.cub ${END}\t"
${exec} map/wrongs/map/island.cub &
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec}Big island in map : map/wrongs/map/sololand.cub ${END}\t"
${exec} map/wrongs/map/sololand.cub &
echo "----------------------------------------------------------------"

echo -e "${BLU_BG}${exec}Lshape map : map/wrongs/map/lshape.cub ${END}\t"
${exec} map/wrongs/map/lshape.cub &
echo "----------------------------------------------------------------"

# ------------------------------------------------------------------------------
#				-----		OUTRO		-----
# ------------------------------------------------------------------------------
make fclean &>/dev/null
