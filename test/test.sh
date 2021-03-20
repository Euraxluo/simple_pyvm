cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd #
echo -e "\033[35m $(ls test_*.py|xargs)\033[0m" #
total=0 #
success=0 #
error=0 #
for i in `ls test_*.py`;do  total=`echo $((total+=1))` ;t=`python -m  $i |grep SUCCESS!!! |wc -l` ;if  [[ $t == 0 ]] ;then error=`echo $((error+=1))`;echo -e "\033[41m ${i}\033[0m";else success=`echo $((success+=1))`;fi ;done #
echo -e "\033[35mtotal test case : ${total}\033[0m"
echo -e "\033[35msuccess test case : ${success}\033[0m"
echo -e "\033[35merror test case : ${error}\033[0m"