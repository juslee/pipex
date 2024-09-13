#!/bin/bash
# norminette -R CheckForbiddenSourceHeader CheckDefine

# Set PIPEX variable
PIPEX=./pipex

# Detect OS and set VALGRIND variable
UNAME_S=$(uname -s)
if [ "$UNAME_S" = "Darwin" ]; then
	# VALGRIND="leaks --atExit --list --"
	VALGRIND=""
	VAL_CHECK="leaks_check"
else
	VALGRIND="valgrind --leak-check=full --show-leak-kinds=all -s"
	VAL_CHECK="val_check"
fi

COLOR_YIB='\033[1;93m'
COLOR_YI='\033[0;93m'
COLOR_Y='\033[0;33m'
COLOR_R='\033[0;31m'
COLOR_G='\033[0;32m'
COLOR_END='\033[0m'

rm -fr results.log

deepthought () {
	{
		echo \"And you\'re ready to give it to us?\" urged Loonquawl.
		echo \"I am.\"
		echo \"Now?\"
		echo \"Now,\" said Deep Thought.
		echo They both licked their dry lips.
		echo \"Though I don\'t think,\" added Deep Thought, \"that you\'re going to like it.\"
		echo \"Doesn\'t matter\!\" said Phouchg. \"We must know it! Now\!\"
		echo \"Now?\" inquired Deep Thought.
		echo \"Yes! Now ...\"
		echo \"Alright,\" said the computer and settled into silence again. The two men fidgeted. The tension was unbearable.
		echo \"You\'re really not going to like it,\" observed Deep Thought.
		echo \"Tell us\!\"
		echo \"Alright,\" said Deep Thought. \"The Answer to the Great Question...\"
		echo \"Yes ...\!\"
		echo \"Of Life, the Universe and Everything ...\" said Deep Thought.
		echo \"Yes ...\!\"
		echo \"Is ...\" said Deep Thought, and paused.
		echo \"Yes ...\!\"
		echo \"Is ...\"
		echo \"Yes ...\!\!\!...?\"
		echo \"Forty-two,\" said Deep Thought, with infinite majesty and calm.
	} >> deepthought.txt
}

val_check () {
	if grep -q "definitely lost:" output.log; then
		cat output.log
	fi
	rm -fr output.log
}

leaks_check () {
	if grep -q "leaks for" output.log; then
		printf "${COLOR_G}[OK]\n${COLOR_END}"
	else
		cat output.log
	fi
	rm -fr output.log
}

res_check () {
	echo $1 >> results.log
	diff outfile1 outfile2
	if [ $? -ne 0 ]; then
		diff outfile1 outfile2 >> results.log
		printf "${COLOR_R}[KO]\n${COLOR_END}"
	else
		printf "${COLOR_G}[OK]\n${COLOR_END}"
	fi
}

deepthought

####################################################################################################

printf "${COLOR_YIB}\nError Tests\n${COLOR_END}"

printf "${COLOR_Y}No arguments\n${COLOR_END}"
$PIPEX
$VALGRIND $PIPEX 2> output.log; $VAL_CHECK

printf "${COLOR_Y}Too few arguments\n${COLOR_END}"
$PIPEX infile "ls -l" "wc -l"
$VALGRIND $PIPEX infile "ls -l" "wc -l" 2> output.log; $VAL_CHECK

printf "${COLOR_Y}Empty strings\n${COLOR_END}"
< ./deepthought.txt wc | > outfile1
$VALGRIND $PIPEX "/dev/urandom" "" "" outfile2 2> output.log; $VAL_CHECK
printf "${COLOR_G}[OK]\n${COLOR_END}"

printf "${COLOR_Y}Existing folder (without execution permission) entered where first command should be\n${COLOR_END}"
< infile /dev/urandom | wc -l > outfile1
$VALGRIND $PIPEX infile "/dev/urandom" "wc -l" outfile2 2> output.log; $VAL_CHECK
res_check "~~~~~~ Folder No Exec 1"

printf "${COLOR_Y}Existing folder (without execution permission) entered where second command should be\n${COLOR_END}"
< infile ls -l | /dev/urandom > outfile1
$VALGRIND $PIPEX infile "ls -l" "/dev/urandom" outfile2 2> output.log; $VAL_CHECK
res_check "~~~~~~ Folder No Exec 2"

printf "${COLOR_Y}Existing folder (with execution permission but no '/') entered where first command should be\n${COLOR_END}"
< infile libft | wc -l > outfile1
$VALGRIND $PIPEX infile "libft" "wc -l" outfile2 2> output.log; $VAL_CHECK
res_check "~~~~~~ Folder no '/' 1"

printf "${COLOR_Y}Existing folder (with execution permission but no '/') entered where second command should be\n${COLOR_END}"
< infile ls -l | libft > outfile1
$VALGRIND $PIPEX infile "wc -l" "libft" outfile2 2> output.log; $VAL_CHECK
res_check "~~~~~~ Folder no '/' 2"

printf "${COLOR_Y}Existing folder (with execution permission and with '/') entered where first command should be\n${COLOR_END}"
< infile libft/ | wc -l > outfile1
$VALGRIND $PIPEX infile "libft/" "wc -l" outfile2 2> output.log; $VAL_CHECK
res_check "~~~~~~ Folder 1"

printf "${COLOR_Y}Existing folder (with execution permission and with '/') entered where second command should be\n${COLOR_END}"
< infile ls -l | libft/ > outfile1
$VALGRIND $PIPEX infile "ls -l" "libft/" outfile2 2> output.log; $VAL_CHECK
res_check "~~~~~~ Folder 2"

printf "${COLOR_Y}False command (with flag) first\n${COLOR_END}"
< ./deepthought.txt nooo -s | wc > outfile1
$VALGRIND $PIPEX "./deepthought.txt" "nooo -s" "wc" outfile2 2> output.log; $VAL_CHECK
res_check "~~~~~~ False command 1"

printf "${COLOR_Y}False command (with flag) second\n${COLOR_END}"
< ./deepthought.txt wc | nah -s > outfile1
$VALGRIND $PIPEX "./deepthought.txt" "wc" "nah -s" outfile2 2> output.log; $VAL_CHECK
res_check "~~~~~~ False command 2"

printf "${COLOR_Y}Invalid Infile 1\n${COLOR_END}"
< nonexisting grep Now | cat > outfile1
$VALGRIND $PIPEX nonexisting "grep Now" "cat" outfile2 2> output.log; $VAL_CHECK
res_check "~~~~~~ Invalid infile 1"

printf "${COLOR_Y}Invalid Infile 2\n${COLOR_END}"
< nonexisting cat | wc > outfile1
$VALGRIND $PIPEX nonexisting "cat" "wc" outfile2 2> output.log; $VAL_CHECK
res_check "~~~~~~ Invalid infile 2"

printf "${COLOR_Y}Invalid Outfile\n${COLOR_END}"
touch notouch
chmod 000 notouch
< ./ ls -l | head -2 > notouch
$VALGRIND $PIPEX "./" "ls -l" "head -2" notouch 2> output.log; $VAL_CHECK
rm -fr notouch
printf "${COLOR_G}[OK]\n${COLOR_END}"

####################################################################################################

printf "${COLOR_YIB}\nValid Tests\n${COLOR_END}"

printf "${COLOR_Y}Test 1\n${COLOR_END}"
< ./deepthought.txt grep Deep | head -2 > outfile1
$VALGRIND $PIPEX "./deepthought.txt" "grep Deep" "head -2" outfile2 2> output.log; $VAL_CHECK
res_check "~~~~~~ 1"

printf "${COLOR_Y}Test 2\n${COLOR_END}"
< ./deepthought.txt grep the | wc -w > outfile1
$VALGRIND $PIPEX "./deepthought.txt" "grep the" "wc -w" outfile2 2> output.log; $VAL_CHECK
res_check "~~~~~~ 2"

printf "${COLOR_Y}Test 3\n${COLOR_END}"
< ./deepthought.txt grep Now | cat > outfile1
$VALGRIND $PIPEX "./deepthought.txt" "grep Now" "cat" outfile2 2> output.log; $VAL_CHECK
res_check "~~~~~~ 3"

printf "${COLOR_Y}Test 4\n${COLOR_END}"
< ./deepthought.txt wc -w | cat > outfile1
$VALGRIND $PIPEX "./deepthought.txt" "wc -w" "cat" outfile2 2> output.log; $VAL_CHECK
res_check "~~~~~~ 4"

printf "${COLOR_Y}Test 5\n${COLOR_END}"
< ./ uname -a | tail -1 > outfile1
$VALGRIND $PIPEX "./" "uname -a" "tail -1" outfile2 2> output.log; $VAL_CHECK
res_check "~~~~~~ 5"

printf "${COLOR_Y}Test 6\n${COLOR_END}"
< ./deepthought.txt tr -d e | tr [:space:] e > outfile1
$VALGRIND $PIPEX "./deepthought.txt" "tr -d e" "tr [:space:] e" outfile2 2> output.log; $VAL_CHECK
res_check "~~~~~~ 6"

printf "${COLOR_Y}Correct path (without flag) first\n${COLOR_END}"
< ./deepthought.txt /usr/bin/cat | grep Deep > outfile1
$VALGRIND $PIPEX  "./deepthought.txt" "/usr/bin/cat" "grep Deep" outfile2 2> output.log; $VAL_CHECK
res_check "~~~~~~ Correct path (without flag) 1"

printf "${COLOR_Y}Correct path (without flag) second\n${COLOR_END}"
< ./deepthought.txt grep Now | /usr/bin/cat > outfile1
$VALGRIND $PIPEX  "./deepthought.txt" "grep Now" "/usr/bin/cat" outfile2 2> output.log; $VAL_CHECK
res_check "~~~~~~ Correct path (without flag) 2"

printf "${COLOR_Y}Correct path (with flag) first\n${COLOR_END}"
< ./deepthought.txt /usr/bin/grep a | wc -l > outfile1
$VALGRIND $PIPEX "./deepthought.txt" "/usr/bin/grep a" "wc -l" outfile2 2> output.log; $VAL_CHECK
res_check "~~~~~~ Correct path (with flag) 1"

printf "${COLOR_Y}Correct path (with flag) second\n${COLOR_END}"
< ./ lsblk | /usr/bin/wc -l > outfile1
$VALGRIND $PIPEX "./" "lsblk" "/usr/bin/wc -l" outfile2 2> output.log; $VAL_CHECK
res_check "~~~~~~ Correct path (with flag) 2"

printf "${COLOR_Y}Timeout?\n${COLOR_END}"
< /dev/urandom cat | head -1 > outfile1
$VALGRIND $PIPEX "/dev/urandom" "cat" "head -1" outfile2 2> output.log; $VAL_CHECK
printf "${COLOR_G}[OK]\n${COLOR_END}"

printf "${COLOR_YI}\n~~Don't forget to trace children!!~~\n${COLOR_END}"
# valgrind --leak-check=full --show-leak-kinds=all -s --trace-children=yes

####################################################################################################

printf "${COLOR_YIB}\nBonus (ignore if don't have)\n${COLOR_END}"

printf "${COLOR_Y}False command (without flag) Start\n${COLOR_END}"
< ./deepthought.txt nah | cat | tail -5 | head -2 > outfile1
$VALGRIND $PIPEX "./deepthought.txt" nah cat "tail -5" "head -2" outfile2 2> output.log; $VAL_CHECK
res_check "~~~~~~ False command B1"

printf "${COLOR_Y}False command (with flag) Mid\n${COLOR_END}"
< ./deepthought.txt cat | wc | nah -s | wc -l | cat > outfile1
$VALGRIND $PIPEX "./deepthought.txt" cat wc "nah -s" "wc -l" cat outfile2 2> output.log; $VAL_CHECK
res_check "~~~~~~ False command B2"

printf "${COLOR_Y}False command (with flags) Near End\n${COLOR_END}"
< ./deepthought.txt grep Now | tail -10 | wc -l | nah -d ect | wc > outfile1
$VALGRIND $PIPEX "./deepthought.txt" "grep Now" "tail -10" "wc -l" "nah -d ect" wc outfile2 2> output.log; $VAL_CHECK
res_check "~~~~~~ False command B3"

printf "${COLOR_Y}Test B1\n${COLOR_END}"
< ./deepthought.txt grep Now | /usr/bin/cat | wc -l > outfile1
$VALGRIND $PIPEX "./deepthought.txt" "grep Now" "/usr/bin/cat" "wc -l" outfile2 2> output.log; $VAL_CHECK
res_check "~~~~~~ B1"

printf "${COLOR_Y}Test B2\n${COLOR_END}"
< ./ du | cat | wc | cut -c 1-7 > outfile1
$VALGRIND $PIPEX "./" du cat wc "cut -c 1-7" outfile2 2> output.log; $VAL_CHECK
res_check "~~~~~~ B2"

printf "${COLOR_Y}Test B3\n${COLOR_END}"
< ./deepthought.txt cat | tr [:lower:] [:upper:] | head -5 | tail -3 | cat > outfile1
$VALGRIND $PIPEX "./deepthought.txt" cat "tr [:lower:] [:upper:]" "head -5" "tail -3" cat outfile2 2> output.log; $VAL_CHECK
res_check "~~~~~~ B3"

printf "${COLOR_Y}Test B4\n${COLOR_END}"
< ./deepthought.txt cat | grep Now | /usr/bin/ls -l | cat | tail -2 > outfile1
$VALGRIND $PIPEX "./deepthought.txt" cat "grep Now" "/usr/bin/ls -l" cat "tail -2" outfile2 2> output.log; $VAL_CHECK
res_check "~~~~~~ B4"

printf "${COLOR_Y}Test B5\n${COLOR_END}"
< ./deepthought.txt cat | cat | cat | grep Now | cat | cat | cat | tail -2 > outfile1
$VALGRIND $PIPEX "./deepthought.txt" cat cat cat "grep Now" cat cat cat "tail -2" outfile2 2> output.log; $VAL_CHECK
res_check "~~~~~~ B5"

printf "${COLOR_Y}here_doc\n${COLOR_END}"
echo "try typing: this is a sentence that is in here_doc EOF"
cat << EOF | head -4 | wc >> outfile1
test
EOF
$VALGRIND $PIPEX here_doc EOF cat "head -4" wc outfile2 2> output.log; $VAL_CHECK
res_check "~~~~~~ here_doc"
printf "${COLOR_YI}[Test it manually]\n${COLOR_END}"

rm -fr outfile1
rm -fr outfile2
rm -fr deepthought.txt
